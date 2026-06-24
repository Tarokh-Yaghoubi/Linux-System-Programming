//
// Created by ALI on 1/27/2023.
//


#include <stdlib.h>
#include "Connection.h"
#include "Logger.h"
#include "string.h"
#include "tos_platform.h"
#include "ErrorCodes.h"
#include "gui_guider.h"
#include "Device.h"
#include "Repository.h"

int socketHandle = -1;



static ahFRes_t ahSockConnect(ConnectionProperties_t * con);
static int socketWrite(const char *data, int len);
static int socketRead(char *data, ahU32_t *len, int timeoutMs);


ahS32_t ahWifiInit(){
    WIFI_CTRL_INFO wifi_info;
    memset(&wifi_info, 0, sizeof(WIFI_CTRL_INFO));
    int ret = wifi_open_implement(NULL);
    if (ret != 0)
        return -1;
    wifi_info.wifi_list_num = TosWifiScan(wifi_info.setting_wifi_info, 20);
    if (wifi_info.wifi_list_num <= 0) {
        return -1;
    }
    if (g_prop.connection.wifiInfoSt.ssid[0]){
        strcpy(wifi_info.target_ap.wifi_target_pwd, g_prop.connection.wifiInfoSt.wifi_target_pwd);
        strcpy(wifi_info.target_ap.ap_info.ssid, g_prop.connection.wifiInfoSt.ssid);
        wifi_info.target_ap.ap_info.sec_mode = g_prop.connection.wifiInfoSt.sec_mode;
    }
    else {
        return -1;
    }

    if (!check_target_ap_in_list(&wifi_info))
        return -1;

    return wifi_connect(&wifi_info.target_ap);
}

ahFRes_t ahCommInit() {
    ahU16_t ret = AH_FAIL;
    ahU32_t startTime = TosGetTickCount();

    if (g_prop.connection.connectionType == kCONNECTION_TYPE_WIFI){
        ret = ahWifiInit();
        if (ret == 0){
            TosSetDefaultNetworkInteface(INTERFACE_WIFI);
        }
    }

    if (g_prop.connection.connectionType == kCONNECTION_TYPE_GPRS) {
        ret = TosModemOpen();
        ret += TosModemSetApn("irancell", "", "", PDP_AUTH_ANY, PDP_PROTOCOL_IP);
        ret += TosModemDataOn();
        TosSetDefaultNetworkInteface(INTERFACE_GPRS);

    }

    if (ret != 0)
        log_error("Ethernet Open ret = %d", ret);

    savePreference();

    return ret;
}
ahFRes_t ahCheckConnection(){
    if (g_prop.connection.connectionType == kCONNECTION_TYPE_GPRS){
        return TosMobileDataAvailable();
    }
    else if (g_prop.connection.connectionType == kCONNECTION_TYPE_WIFI){
        return TosWifiCheck(NULL);
    }
    else{
        return AH_FAIL;
    }
}
void ahCommSetConnectionType(){
    (g_prop.connection.connectionType == kCONNECTION_TYPE_WIFI) ? TosSocSetProperty(CONNECTION_TYPE, 1) :
    (g_prop.connection.connectionType == kCONNECTION_TYPE_GPRS) ? TosSocSetProperty(CONNECTION_TYPE, 0) : 0;
}
void sendMsg(int id){
    message_t msg = {0};
    msg.id = id;
    conn_send_msg(&msg);
}
ahFRes_t ahConnect(ConnectionProperties_t * con) {
    ahU32_t end = TosGetTickCount() + 30000;
    int st;
    while(TosGetTickCount() < end){
        st = ahCheckConnection();
        if (st>0)
            break;
        TosDelayMS(100);
    }
    if(st > 0){
        log_debug("network available");
        return ahSockConnect(con);
    }
    log_error("network status is not ok");
    sendMsg(MSG_CONN_FAILED);
    return AH_FAIL;
}

ahFRes_t ahSend(ahU8_t *data, ahU32_t dataLen, ahU16_t timeout){
    return socketWrite(data, dataLen);
}
ahFRes_t ahReceive(ahU8_t *data, ahU32_t *dataLen, ahU16_t timeout){
    ahFRes_t ret;
    return socketRead(data, dataLen,  timeout);
}

ahFRes_t ahDisconnect(){
    sendMsg(MSG_CONN_IDLE);
    return socketClose();
}


//<editor-fold desc="Modem Functions">



ahFRes_t ahPreDial(){
    sendMsg(MSG_CONN_PRE_DIAL);
    return AH_SUCCESSFUL;
}
//</editor-fold>


//<editor-fold desc="ssl Functions">

int socketIpCheck(char *asci_addr, uint8_t *ip, unsigned char *ip_validity)
{
    int retval;
    unsigned int intValue;
    char *p,i=0;
    char addr_tmp[128]={0};
    api_enter("(%s) enter", asci_addr);


    snprintf(addr_tmp, sizeof(addr_tmp),"%s", asci_addr);
    p=strtok(addr_tmp, ".");
    if(p==NULL){
        return -1;
    }
    ip[i]=atoi(p);
    api_printf("ip[%d]=%d",i, ip[i]);
    i++;

    while( (p=strtok(NULL, ".")) != NULL){
        intValue=atoi(p);
        api_printf("ip[%d]=%d",i, intValue);
        if(intValue > 255 || intValue < 0 ){
            break;
        }
        ip[i] = intValue;
        i++;
        if(i>4){
            break;
        }
    }
    if(i!=4){
        *ip_validity=0;
        retval = -1;
    }else{
        *ip_validity=1;
        retval = 0;
    }

    api_exit("()=%d exit", retval);
    return retval;
}
static int tcpConnect(const char *ip, short port) {
    log_trace;
    ahCommSetConnectionType();

    int data;

    data = ahCheckConnection();
    log_debug("data = %d", data);
    if (data <= 0)
        return err_comm_connect;

    int handle = TosSocCreate();
    if (handle < 0){
        log_error("Tcp init connection Failed %d", handle);
        return err_comm_connect;
    }
    SOC_ADDR_INFO addr = {0};

    ahU8_t valid = 0;
    socketIpCheck(ip, addr.addr, &valid);
    if (valid != 1)
        return err_comm_connect;
    addr.addr_len = 4;
    addr.port = port;
    addr.soc_type = SOC_SOCK_STREAM;
    int r = TosSocConnectTimeout(handle, &addr, 20000);
    if (r < 0){
        log_error("connection failed %d" , r);
        return err_comm_connect;
    }
    return handle;
}

//</editor-fold>

//<editor-fold desc="Socket Functions">
ahFRes_t ahSockConnect(ConnectionProperties_t * con){
    char ip[16] = {0};
    log_debug("connection = %s:%d", con->serverIp, con->port);
    if (socketHandle < 0) {
        strcpy(ip, con->serverIp);
        socketHandle = tcpConnect(ip, con->port);
    }
    if (socketHandle < 0)
        return err_comm_connect;
    sendMsg(MSG_CONN_ESTABLISHED);
    return AH_SUCCESSFUL;
}
int socketWrite(const char *data, int len) {
    if (socketHandle < 0) {
        return err_comm_send;
    }
    int ret = TosSocSend(socketHandle, data, len);
    log_hex("sent Message", data, len);
    if (ret == len) {
        log_debug("RET equals LEN ========== => [%d][%d]", ret, len);
        return AH_SUCCESSFUL;
    }
    return err_comm_send;
}

int socketRead(char *data, ahU32_t *len, int timeoutMs) {
    ahU8_t buf[1024];
    int rd = 0;
    int r = 1;
    if (!data || !len || socketHandle < 0) {
        log_error("%s %d", __FILE__, __LINE__);
        return err_comm_receive;
    }
    int ret = 0;
    while (rd < (int) sizeof(buf)) {

        ret = TosSocSelect(socketHandle, timeoutMs);
        log_debug("socket reading %d ", ret);

        if (ret == 0) {
            r = TosSocRecv(socketHandle, buf + rd, sizeof(buf) - rd);
            if (r < 0) {
                log_error("Socket_read error return %d", r);
                return err_comm_receive;
            }
            rd += r;
            log_debug("r = %d, rd = %d, %d, %d", r, rd, buf[0], buf[1]);
            if (rd > 1 && rd == buf[0] * 256 + buf[1] + 2)
                break;
        }
        else if (ret < 0){
            log_error("receive error err= %d", ret);
            return err_comm_receive;
        }
    }
    log_debug("read %d bytes contents:\n%.*s\n", rd, rd, buf);
    if (rd != buf[0] * 256 + buf[1] +  2){
        log_error("receive error len mismatch %d != %d", rd, buf[0] * 256 + buf[1] + 2);
        return err_comm_receive;
    }
    *len = rd;
    memcpy(data, buf, rd);
    return AH_SUCCESSFUL;
}
ahFRes_t socketClose(){
    if (socketHandle >= 0)
        TosSocClose(socketHandle);
    socketHandle = -1;
    return AH_SUCCESSFUL;
}

//</editor-fold>

//<editor-fold desc="Wifi">
void wifi_close_implement(WIFI_CTRL_INFO * wifi_info)
{
    TosWifiClose();
    if (wifi_info != NULL) {
        memset(wifi_info, 0, sizeof(WIFI_CTRL_INFO));
        wifi_info->wifi_auto_connect_flag = 0;
        wifi_info->wifi_list_num = 0;
    }
    g_prop.connection.connectionType = kCONNECTION_TYPE_GPRS;
    savePreference();
}
int wifi_open_implement(WIFI_CTRL_INFO * wifi_info){
    STATUSBAR_INFO sys_statusbar_info;
    if (wifi_info != NULL)
        memset(wifi_info, 0, sizeof(WIFI_CTRL_INFO));
    get_statusbar_info(&sys_statusbar_info);
    if (sys_statusbar_info.wifi_status == 0) {
        int retval = TosWifiOpen();
        if (retval < 0) {
            wifi_close_implement(wifi_info);
            return -1;
        }
    }
    return 0;
}
int32_t wifi_check_state(WIFI_AP_INFO *wifi_ap_info)
{
    int32_t wifi_status;
    while (1) {
        wifi_status = TosWifiCheck(wifi_ap_info);
        if (wifi_status != 0)
            break;
        TosDelayMS(100);
    }
    return wifi_status;
}
int check_target_ap_in_list(WIFI_CTRL_INFO *wifi_info)
{
    int i;
    int result = false;
    for (i = 0; i < wifi_info->wifi_list_num; i++) {
        if (strcmp((char *) wifi_info->setting_wifi_info[i].ssid, (char *) wifi_info->target_ap.ap_info.ssid) == 0) {
            result = true;
            break;
        }
    }
    return result;
}
int32_t wifi_connect(WIFI_TARGET_INFO *wifi_connect_target)
{
    int32_t connect_flag, wifi_pwd_len;
    WIFI_PARAM setting_wifi_param;
    memset(&setting_wifi_param, 0, sizeof(WIFI_PARAM));
    setting_wifi_param.dhcp_enable = 1;

    wifi_pwd_len = strlen(wifi_connect_target->wifi_target_pwd);

    if (wifi_connect_target->ap_info.sec_mode == WLAN_SEC_WEP) {
        WEP_KEY wep_key;
        strcpy((char *) wep_key.Key[0], wifi_connect_target->wifi_target_pwd);
        wep_key.Idx = 0;
        wep_key.KeyLen = wifi_pwd_len;
        memcpy(&setting_wifi_param.wep, &wep_key, sizeof(WEP_KEY));
    } else {
        strcpy((char *) setting_wifi_param.wpa, wifi_connect_target->wifi_target_pwd);
    }
    connect_flag = TosWifiConnect(&wifi_connect_target->ap_info, &setting_wifi_param);
    return connect_flag;
}
//</editor-fold>

