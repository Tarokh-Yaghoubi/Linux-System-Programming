//
// Created by ALI on 1/28/2023.
//


// #define DEBUG_VERSION

#define DEBUG_VERSION 1
#define USER_DEBUG2 1

#include "Device.h"
#include "Iso/dl_iso8583_defs_1987.h"
#include "Iso/dl_iso8583.h"
#include "Connection.h"
#include "ErrorCodes.h"
#include "Transaction.h"
#include "Service.h"
#include "Logger.h"
#include <stdio.h>
#include "Print.h"
#include "Repository.h"
#include "event_proc.h"
#include "tos_platform.h"

#include "FnpUtils.h"
#include "iso8583.h"

// #include "api_debug.h"
#include "GlbVar.h"
#include "iso8583_config.h"

#include "Util.h"

#define HEADER_LEN 5

#define fnp_str_Atoi(STR, BASE) strtol(STR, NULL, BASE)

/////////////////
// ahS16_t ahSetFields(TranData_t *tranData) {
//     int i, ret;
//     ahU8_t temp[256];
//     int f48Index = 0, tagLen = 0;
//     for (i = 0; tranData->tranConfig.fields[i] != -1; i++) {
//         log_debug("[T] - processing field index [%d] field [%d]", i, tranData->tranConfig.fields[i]);
//         memset(temp, 0, sizeof(temp));
//         switch (tranData->tranConfig.fields[i]) {
//             case 0: {
//                 int res = strcmp(tranData->tranConfig.mti, "0x82");
//                 if (res == 0) {
//                     unsigned char mtiData[] = {0x82};
//                     // ret = ISO8583_SetBit(0, &mtiData, 1, TRUE, &tranData->sendMsg);
//                     ret = ISO8583_SetBit(0, mtiData, 1);
//                     log_debug("[T] - P0 set MTI data =========== => [%s] ", mtiData);
//                 } else {
//                     log_debug("[T] P0  - else statement mti IS NOT 0X82 ===== ==> ");
//                     ret = ISO8583_SetBit(0, tranData->tranConfig.mti, 1);
//                     //log_debug("[T] - P0 does not match logon MTI ======= = [%s]", tranData->tranConfig.mti);
//                 }
//
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             }
//             case 2:
//                 // sprintf((char *) temp, "%d", tranData->log.stan);
//                 //log_debug("P2 log.stan data ===== => [%s]", temp);
//                 UInt2BinIndian(temp, tranData->log.stan, 2);
//                 ret = ISO8583_SetBit(2, temp, 2);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             case 3: {
//                 // sprintf((char *) temp, "%02d%02d", tranData->log.dateTime.month, tranData->log.dateTime.day);
//                 // log_debug("P3 dateTime data ========== => [%s]", temp);
//                 // ret = ISO8583_SetBit(3, temp, 4);
//                 // if (ret != 0) return err_tran_pack;
//                 // break;
//                 unsigned char dt[4];
//                 dt[0] = ((tranData->log.dateTime.month / 10) << 4) | (tranData->log.dateTime.month % 10);
//                 dt[1] = ((tranData->log.dateTime.day / 10) << 4) | (tranData->log.dateTime.day % 10);
//                 dt[2] = ((tranData->log.dateTime.hour / 10) << 4) | (tranData->log.dateTime.hour % 10);
//                 dt[3] = ((tranData->log.dateTime.minute / 10) << 4) | (tranData->log.dateTime.minute % 10);
//                 ret = ISO8583_SetBit(3, dt, 4);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             }
//             case 4:
//                 ret = DL_ISO8583_MSG_SetField_Str(4, tranData->log.amount, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             case 5: {
//                 log_debug("[T] - TERMINAL CODE BEFORE ASCII TO INT CONVERSION => [%s] ", g_prop.merchant.terminalId);
//                 unsigned char temp[20];
//                 unsigned int i = atoi(g_prop.merchant.terminalId);
//
//                 UInt2BinIndian(temp, i, 4);
//
//                 ret = ISO8583_SetBit(5, temp, 4);
//                 if (ret != 0) {
//                     log_debug("[T] - field05 error has occured =========== => ");
//                     return err_tran_pack;
//                 } else {
//                     log_debug("[T] - field05 has no errors =========== => ");
//                 }
//                 break;
//             }
//             case 7: {
//                 unsigned char TEMP[20];
//                 int res;
//
//                 sprintf((char *) temp, "%s", ahGetDeviceSerial());
//                 // if (IsDigitStr(temp, strlen(temp)) == 0)
//                 //     res = utilsAsc2Bcd(temp, strlen(temp), TEMP);
//                 // else {
//                 //     memset(TEMP, 0x00, sizeof(TEMP));
//                 //     TEMP[0] = 0xFF;
//                 //     strcpy(TEMP + 1, temp);
//                 //     res = strlen(TEMP) + 1;
//                 // }
//                 log_debug("[T] - device serial number is ========= => [%s]", temp);
//                 res = utilsAsc2Bcd(temp, strlen(temp), TEMP);
//                 log_debug("[T] - TEMP containing SerialNumber ============== => [%s] ", TEMP);
//                 ret = ISO8583_SetBit(7, TEMP, res);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             }
//             case 8: {
//                 // sprintf((char *) temp, "%d", tranData->log.stan);
//                 unsigned char lastStan[] = {0x00, 0x00, 0x00, 0x00};
//                 // log_debug("P8 log.stan data ===== => [%s]", temp);
//                 ret = ISO8583_SetBit(8, lastStan, 2);
//                 log_debug("[P8] log.stan data SET ============ => ");
//
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             }
//             // merchant id => 5061474
//             case 11:
//                 sprintf((char *) temp, "%d", tranData->log.stan);
//                 ret = DL_ISO8583_MSG_SetField_Str(11, temp, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             // field 10 remains
//
//             case 12:
//                 sprintf((char *) temp, "%02d%02d%02d", tranData->log.dateTime.hour, tranData->log.dateTime.minute,
//                         tranData->log.dateTime.second);
//                 ret = DL_ISO8583_MSG_SetField_Str(12, temp, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             case 13: {
//                 log_debug("[T] - P13,  adding bit 13 =============== => ");
//                 unsigned int merchantCode = atoi("5061474");
//                 UInt2BinIndian(temp, merchantCode, 4);
//                 ret = ISO8583_SetBit(13, temp, 4);
//                 log_debug("[P13] ==================== => [DONE] ");
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             }
//             case 14: {
//                 unsigned char currCode[2];
//                 UInt2BinIndian(currCode, 364, 2); // or read from config
//                 ret = ISO8583_SetBit(14, currCode, 2);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             }
//             case 15: {
//                 log_debug("[T] - entered field 15 ============== => ");
//                 unsigned char appVersionBCD[3] = {0x04, 0x00, 0x00};
//
//                 ret = ISO8583_SetBit(15, appVersionBCD, 2);
//                 if (ret != 0) return err_tran_pack;
//
//                 log_debug("[T] - exit field 15 =============== => ");
//                 break;
//             }
//             case 22:
//                 ret = DL_ISO8583_MSG_SetField_Str(22, (ahU8_t *) tranData->tranConfig.pos, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//
//             case 23:
//                 sprintf(temp, "%03d", tranData->iccData->seq);
//                 ret = DL_ISO8583_MSG_SetField_Str(23, temp, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//
//             case 24:
//                 ret = DL_ISO8583_MSG_SetField_Str(24, g_prop.connection.nii, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             case 25:
//                 ret = DL_ISO8583_MSG_SetField_Str(25, (ahU8_t *) "00", &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             case 32:
//                 ret = DL_ISO8583_MSG_SetField_Str(
//                     32, g_prop.merchant.institute[0] == 0 ? "00000000000" : g_prop.merchant.institute,
//                     &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//
//             case 33: {
//                 log_debug("[T] - P33 entered the case ============== => ");
//                 // unsigned char IP[32] = {0};
//                 char buf[32] = {0};
//
//                 // ret = TosGetLocalIP(IP);
//                 // if (ret != 0) {
//                 //     log_debug("[t] - getIpERROR ===== => ");
//                 //     return err_tran_pack;
//                 // }
//                 // log_debug("[T] - local ip address is ============ => [%s] ", IP);
//                 //
//                 // // strcpy(buf, "\x32\x3d\x31\x2e\x31\x36\x3b");
//                 // snprintf(buf,
//                 //          sizeof(buf),
//                 //          "01;SPEED=4.42;IP=%s;PHONE=0;RKIMODE=3;",
//                 //          IP);
//                 snprintf(buf,  sizeof(buf), "30C=1.45;");
//                 log_debug("[T] - app version for field 33 ======= => [%s]", buf);
//                 ret = ISO8583_SetBit(33, buf, strlen(buf));
//                 if (ret != 0) return err_tran_pack;
//
//                 log_debug("[T] - P33 exit ================= => ");
//                 break;
//             }
//             case 35:
//                 ret = DL_ISO8583_MSG_SetField_Str(35, tranData->track2, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             case 37:
//                 ret = DL_ISO8583_MSG_SetField_Str(37, tranData->log.rrn, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             case 38:
//                 ret = DL_ISO8583_MSG_SetField_Str(38, tranData->authId, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//
//             case 40: {
//                 log_debug("[T] - P40 pasargad ==================== => ");
//                 unsigned char mac[11];
//                 memset(mac, 0x00, 10);
//                 ret = ISO8583_SetBit(40, mac, 4);
//                 if (ret != 0) return err_tran_pack;
//                 log_debug("[T] - P40 exit ================== => ");
//                 break;
//             }
//             case 41:
//                 ret = DL_ISO8583_MSG_SetField_Str(41, g_prop.merchant.terminalId, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             case 42:
//                 ret = DL_ISO8583_MSG_SetField_Str(42, g_prop.merchant.merchantId, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             case 48:
//                 tagLen = strlen(ahGetDeviceSerial());
//                 temp[f48Index++] = (((tagLen + 1) / 10 & 0x0F) << 4) | ((tagLen + 1) % 10 & 0x0F);
//                 temp[f48Index++] = 1;
//                 memcpy(&temp[f48Index], ahGetDeviceSerial(), tagLen);
//                 f48Index += tagLen;
//
//                 tagLen = strlen(VERSION);
//                 temp[f48Index++] = (((tagLen + 1) / 10 & 0x0F) << 4) | ((tagLen + 1) % 10 & 0x0F);
//                 temp[f48Index++] = 2;
//                 memcpy(&temp[f48Index], VERSION, tagLen);
//                 f48Index += tagLen;
//
//
//                 temp[f48Index++] = 2 & 0x0F;
//                 temp[f48Index++] = 3;
//                 memcpy(&temp[f48Index++], "0", tagLen);
//
//                 temp[f48Index++] = 2 & 0x0F;
//                 temp[f48Index++] = 21;
//                 memcpy(&temp[f48Index++], "2", tagLen);
//
//
//                 if (tranData->chargeType[0] != 0) {
//                     tagLen = strlen(tranData->chargeType);
//                     temp[f48Index++] = (((tagLen + 1) / 10 & 0x0F) << 4) | ((tagLen + 1) % 10 & 0x0F);
//                     temp[f48Index++] = 20;
//                     memcpy(&temp[f48Index], tranData->chargeType, tagLen);
//                     f48Index += tagLen;
//                 }
//
//                 if (tranData->log.billId[0] != 0) {
//                     tagLen = strlen(tranData->log.billId);
//                     temp[f48Index++] = (((tagLen + 1) / 10 & 0x0F) << 4) | ((tagLen + 1) % 10 & 0x0F);
//                     temp[f48Index++] = 6;
//                     memcpy(&temp[f48Index], tranData->log.billId, tagLen);
//                     f48Index += tagLen;
//                 }
//
//                 if (tranData->log.payId[0] != 0) {
//                     tagLen = strlen(tranData->log.payId);
//                     temp[f48Index++] = (((tagLen + 1) / 10 & 0x0F) << 4) | ((tagLen + 1) % 10 & 0x0F);
//                     temp[f48Index++] = 7;
//                     memcpy(&temp[f48Index], tranData->log.payId, tagLen);
//                     f48Index += tagLen;
//                 }
//
//                 if (tranData->log.mobile[0] != 0) {
//                     temp[f48Index++] = 2 & 0x0F;
//                     temp[f48Index++] = 34;
//                     memcpy(&temp[f48Index++], "1", tagLen);
//
//
//                     tagLen = strlen(tranData->log.mobile);
//                     temp[f48Index++] = (((tagLen + 1) / 10 & 0x0F) << 4) | ((tagLen + 1) % 10 & 0x0F);
//                     temp[f48Index++] = 8;
//                     memcpy(&temp[f48Index], tranData->log.mobile, tagLen);
//                     f48Index += tagLen;
//                 }
//                 ret = DL_ISO8583_MSG_SetField_Bin(48, temp, f48Index, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             case 49:
//                 ret = DL_ISO8583_MSG_SetField_Str(49, "364", &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             case 52:
//                 if (tranData->iccData != NULL && !tranData->iccData->need_pin)
//                     break;
//                 ret = DL_ISO8583_MSG_SetField_Bin(52, (ahU8_t *) tranData->pin, 8, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             case 53:
//                 ret = DL_ISO8583_MSG_SetField_Bin(53, "\x08\x00\x03\x02\x02\x03\x15\x00", 8, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             case 55:
//                 ret = DL_ISO8583_MSG_SetField_Bin(55, tranData->iccData->icc, tranData->iccData->icc_len,
//                                                   &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             case 64:
//                 DL_ISO8583_MSG_SetField_Bin(64, temp, 8, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             case 90:
//                 ret = DL_ISO8583_MSG_SetField_Str(90, tranData->additional, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             case 116:
//                 ret = DL_ISO8583_MSG_SetField_Str(116, "73000d02116", &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             case 128:
//                 ret = DL_ISO8583_MSG_SetField_Bin(128, temp, 8, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//         }
//     }
//     return AH_SUCCESSFUL;
// }

// ahSetFields changed to work with DL_ISO8583_XXX lib functions'
//
// ahS16_t ahSetFields(TranData_t *tranData) {
//     unsigned long ret;
//     int i;
//     ahU8_t temp[256];
//     int f48Index = 0, tagLen = 0;
//     for (i = 0; tranData->tranConfig.fields[i] != -1; i++) {
//         log_debug("[T] - processing field index [%d] field [%d]", i, tranData->tranConfig.fields[i]);
//         memset(temp, 0, sizeof(temp));
//         switch (tranData->tranConfig.fields[i]) {
//             case 0: {
//                 int res = strcmp(tranData->tranConfig.mti, "0x82");
//                 if (res == 0) {
//                     unsigned char mtiData[] = {0x82};
//                     ret = ISO8583_SetBit(0, (const DL_UINT8 *)mtiData, 1, 0, &tranData->sendMsg);
//                     log_debug("[T] - P0 set MTI data =========== => [%s] ", mtiData);
//                 } else {
//                     log_debug("[T] P0  - else statement mti IS NOT 0X82 ===== ==> ");
//                     ret = ISO8583_SetBit(0, (const DL_UINT8 *)tranData->tranConfig.mti, 1, 0, &tranData->sendMsg);
//                 }
//
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             }
//             case 2:
//                 // tranData->log.stan = 31;
//                 UInt2BinIndian(temp, tranData->log.stan, 2);
//                 ret = ISO8583_SetBit(2, (const DL_UINT8 *)temp, 2, 0, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             case 3: {
//
//                 unsigned char dt[4];
//                 unsigned int fanapTime = LocalDate_to_FanapDate();
//
//                 log_debug("FanapTime = %u (0x%08X)", fanapTime, fanapTime);
//
//                 dt[0] = (fanapTime >> 24) & 0xFF;
//                 dt[1] = (fanapTime >> 16) & 0xFF;
//                 dt[2] = (fanapTime >>  8) & 0xFF;
//                 dt[3] =  fanapTime        & 0xFF;
//
//                 log_debug("dt[] = %02X %02X %02X %02X", dt[0], dt[1], dt[2], dt[3]);
//
//                 ret = ISO8583_SetBit(3, dt, 4, 0, &tranData->sendMsg);
//
//                 if (ret != 0) {
//                     log_debug("[T] - field05 error has occured =========== => ");
//                     return err_tran_pack;
//                 }
//                 break;
//             }
//
//             case 4:
//                 ret = DL_ISO8583_MSG_SetField_Str(4, tranData->log.amount, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             case 5: {
//                 log_debug("[T] - TERMINAL CODE BEFORE ASCII TO INT CONVERSION => [%s] ", g_prop.merchant.terminalId);
//                 unsigned char temp[20];
//                 unsigned int i = atoi(g_prop.merchant.terminalId);
//
//                 UInt2BinIndian(temp, i, 4);
//
//                 ret = ISO8583_SetBit(5, (const DL_UINT8 *)temp, 4, 0, &tranData->sendMsg);
//                 if (ret != 0) {
//                     log_debug("[T] - field05 error has occured =========== => ");
//                     return err_tran_pack;
//                 } else {
//                     log_debug("[T] - field05 has no errors =========== => ");
//                 }
//                 break;
//             }
//             case 7: {
//                 unsigned char TEMP[20];
//                 int res;
//
//                 // sprintf((char *) temp, "%s", ahGetDeviceSerial());
//
//                 const char *serial = ahGetDeviceSerial();
//                 while (*serial && (*serial < '0' || *serial > '9')) serial++;
//                 sprintf((char *) temp, "%s", serial);
//
//                 log_debug("[T] - device serial number is ========= => [%s]", temp);
//                 res = utilsAsc2Bcd(temp, strlen(temp), TEMP, sizeof(temp)); // TEMP to temp: last param
//                 log_debug("[T] - TEMP containing SerialNumber ============== => [%s] ", TEMP);
//                 ret = ISO8583_SetBit(7, (const DL_UINT8 *)TEMP, res, 0, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             }
//             case 8: {
//                 unsigned char lastStan[] = {0x00, 0x00};
//                 // unsigned char lastStan[2];
//                 // unsigned int prev = (tranData->log.stan > 0) ? tranData->log.stan - 1 : 0;
//                 // UInt2BinIndian(lastStan, prev, 2);
//
//                 ret = ISO8583_SetBit(8, (const DL_UINT8 *)lastStan, 2, 0, &tranData->sendMsg);
//                 log_debug("[P8] log.stan data SET ============ => ");
//
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             }
//             case 11:
//                 sprintf((char *) temp, "%d", tranData->log.stan);
//                 ret = DL_ISO8583_MSG_SetField_Str(11, temp, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//
//             case 12:
//                 sprintf((char *) temp, "%02d%02d%02d", tranData->log.dateTime.hour, tranData->log.dateTime.minute,
//                         tranData->log.dateTime.second);
//                 ret = DL_ISO8583_MSG_SetField_Str(12, temp, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             case 13: {
//                 log_debug("[T] - P13,  adding bit 13 =============== => ");
//                 unsigned int merchantCode = atoi("71237582");
//                 UInt2BinIndian(temp, merchantCode, 4);
//                 ret = ISO8583_SetBit(13, (const DL_UINT8 *)temp, 4, 0, &tranData->sendMsg);
//                 log_debug("[P13] ==================== => [DONE] ");
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             }
//             case 14: {
//                 unsigned char currCode[2];
//                 UInt2BinIndian(currCode, 364, 2);
//                 ret = ISO8583_SetBit(14, currCode, 2); // Unchanged as per instructions
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             }
//             case 15: {
//                 log_debug("[T] -  entered field 15 ============== => ");
//                 unsigned char appVersionBCD[2] = {0x9C, 0x78};
//
//                 ret = ISO8583_SetBit(15, (const DL_UINT8 *)appVersionBCD, 2, 0, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//
//                 log_debug("[T] - exit field 15 =============== => ");
//                 break;
//             }
//             case 22:
//                 ret = DL_ISO8583_MSG_SetField_Str(22, (ahU8_t *) tranData->tranConfig.pos, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//
//             case 23:
//                 sprintf(temp, "%03d", tranData->iccData->seq);
//                 ret = DL_ISO8583_MSG_SetField_Str(23, temp, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//
//             case 24:
//                 ret = DL_ISO8583_MSG_SetField_Str(24, g_prop.connection.nii, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             case 25:
//                 ret = DL_ISO8583_MSG_SetField_Str(25, (ahU8_t *) "00", &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             case 26: {
//                 unsigned char dial[] = {0x01};
//                 ret = ISO8583_SetBit(26, dial, 1, 0, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             }
//             case 32:
//                 ret = DL_ISO8583_MSG_SetField_Str(
//                     32, g_prop.merchant.institute[0] == 0 ? "00000000000" : g_prop.merchant.institute,
//                     &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//
//             case 33: {
//                 log_debug("[T] - P33 entered the case ============== => ");
//                 char buf[32] = {0};
//
//                 snprintf(buf,  sizeof(buf), "30C=1.45;");
//                 log_debug("[T] - app version for field 33 ======= => [%s]", buf);
//                 ret = ISO8583_SetBit(33, (const DL_UINT8 *)buf, strlen(buf), FALSE, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//
//                 log_debug("[T] - P33 exit ================= => ");
//                 break;
//             }
//             case 35:
//                 ret = DL_ISO8583_MSG_SetField_Str(35, tranData->track2, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             case 37:
//                 ret = DL_ISO8583_MSG_SetField_Str(37, tranData->log.rrn, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//             case 38:
//                 ret = DL_ISO8583_MSG_SetField_Str(38, tranData->authId, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 break;
//
//             case 40: {
//                 log_debug("[T] - P40 pasargad ==================== => ");
//                 unsigned char mac[4] = {0xFF, 0xFF, 0xFF, 0xFF};
//                 // memset(mac, 0x00, 10);
//                 ret = ISO8583_SetBit(40, (const DL_UINT8 *)mac, 4, 0, &tranData->sendMsg);
//                 if (ret != 0) return err_tran_pack;
//                 log_debug("[T] - P40 exit ================== => ");
//                 break;
//             }
//             default: {
//                 log_debug("[T] - no such a field!");
//                 return err_tran_pack;
//                 break;
//             }
//         }
//     }
//     return AH_SUCCESSFUL;
// }


// edited and modified by Claude AI:

ahS16_t ahSetFields(TranData_t *tranData) {
    unsigned long ret;
    int i;
    ahU8_t temp[256];
    char buf[256];

    for (i = 0; tranData->tranConfig.fields[i] != -1; i++) {
        log_debug("[T] - processing field [%d]", tranData->tranConfig.fields[i]);
        memset(temp, 0, sizeof(temp));

        switch (tranData->tranConfig.fields[i]) {
            case 0: {
                // int res = strcmp(tranData->tranConfig.mti, "0x82");
                // if (res == 0) {
                //
                //
                // }
                unsigned char mtiData[] = {0x82};
                ret = ISO8583_SetBit(0, mtiData, 1);
                if (ret != 0) return err_tran_pack;
                break;
            }

            case 2:
                UInt2BinIndian(temp, tranData->log.stan, 2);
                ret = ISO8583_SetBit(2, temp, 2);
                if (ret != 0) return err_tran_pack;
                break;

            case 3: {
                unsigned int fanapTime = LocalDate_to_FanapDate();
                UInt2BinIndian(temp, fanapTime, 4);
                log_debug("[T] - F3 FanapTime = %u (0x%08X)", fanapTime, fanapTime);
                ret = ISO8583_SetBit(F03h04_LocalDateTime, temp, sIsoDef[F03h04_LocalDateTime].len);
                if (ret != 0) return err_tran_pack;
                break;
            }

            case 5: {
                unsigned int termId = atoi(g_prop.merchant.terminalId);
                // unsigned int termId = atoi("4105297");

                UInt2BinIndian(temp, termId, 4);
                log_debug("[T] - F5 TerminalId = %u", termId);
                ret = ISO8583_SetBit(5, temp, 4);
                if (ret != 0) return err_tran_pack;
                break;
            }

            case 7: {
                unsigned char TEMP[20];
                int res;
                const char *serial = ahGetDeviceSerial();

                /* skip leading non-numeric chars (e.g. 'S' in "S2810102600020526") */
                while (*serial && (*serial < '0' || *serial > '9')) serial++;

                sprintf((char *) temp, "%s", serial);

                log_debug("[T] - F7 serial (numeric) = [%s]", temp);

                res = utilsAsc2Bcd(temp, strlen(temp), TEMP, sizeof(TEMP));


                // unsigned char TEMP[20] = {0};
                // int res;
                // const char *serial = ahGetDeviceSerial();
                //
                // // skip leading non-numeric chars
                // while (*serial && (*serial < '0' || *serial > '9')) serial++;
                //
                // log_debug("[T] - F7 serial (numeric) = [%s]", serial);
                //
                // TEMP[0] = 0xFF;
                // res = utilsAsc2Bcd(serial, strlen(serial), TEMP + 1, sizeof(TEMP) - 1);
                // res += 1; // account for the 0xFF byte

                ret = ISO8583_SetBit(7, TEMP, res);
                if (ret != 0) return err_tran_pack;
                break;
            }

            case 8: {
                // unsigned short lastStan = 0; /* use your M3P equivalent */
                unsigned short lastStan = (tranData->log.stan < 0) ? 0 : tranData->log.stan - 1;
                UInt2BinIndian(temp, lastStan, 2);
                log_debug("[T] - F8 LastSuccessSTAN = %u", lastStan);
                ret = ISO8583_SetBit(8, temp, 2);
                if (ret != 0) return err_tran_pack;
                break;
            }

            case 13: {
                unsigned int merchantId = atoi(g_prop.merchant.merchantId);
                // unsigned int merchantId = atoi("9054477");
                UInt2BinIndian(temp, merchantId, 4);
                log_debug("[T] - F13 MerchantId = %u", merchantId);
                ret = ISO8583_SetBit(13, temp, 4);
                if (ret != 0) return err_tran_pack;
                break;
            }

            case 15: {
                log_debug("[T] -  entered field 15 ============== => ");
                unsigned char appVersionBCD[2] = {0x00, 0x0C};

                ret = ISO8583_SetBit(15, appVersionBCD, 2);
                if (ret != 0) return err_tran_pack;

                log_debug("[T] - exit field 15 =============== => ");
                break;
            }

            case 33: {
                /* "2=1.16;" in hex: 32 3d 31 2e 31 36 3b */
                // const char *f33_prefix = "\x32\x3d\x31\x2e\x31\x36\x3b";
                // int f33_len = 7;

                char ip[32] = {0};
                char imei[16] = {0};
                char *phone = "02181075000";

                TosGetLocalIP(ip);
                settings_get_imei(imei, sizeof(imei));

                char f33_content[128] = {0};
                // sprintf(f33_content, "SPEED=0.11;IP=%s;PHONE=%s;IMEI=%s;", ip, phone, imei);
                strcpy(f33_content, "SPEED=0.11;IP=192.168.1.101;PHONE=02155712674;IMEI=123456789012345;");
                int f33_len = strlen(f33_content);

                log_debug("[T] - F33 len=%d data=[%s]", f33_len, f33_content);
                log_debug("[T] - ip len=%d", strlen(ip));
                log_debug("[T] - phone len=%d", strlen(phone));
                log_debug("[T] - imei len=%d", strlen(imei));

                ret = ISO8583_SetBit(33, (unsigned char *) f33_content, f33_len);
                if (ret != 0) return err_tran_pack;
                break;
            }

            case 40: {
                memset(temp, 0x00, 4);
                ret = ISO8583_SetBit(40, temp, 4);
                if (ret != 0) return err_tran_pack;
                break;
            }

            default:
                log_debug("[T] - unknown field [%d]", tranData->tranConfig.fields[i]);
                return err_tran_pack;
        }
    }

    return AH_SUCCESSFUL;
}

ahS16_t ahConnectServer(TranData_t *data) {
    ahFRes_t ret;
    if (ahGetConnectionStatus() == 0)
        ret = ahConnect(&g_prop.connection);
    else {
        while (ahGetConnectionStatus() == kCONNECTION_IN_PROGRESS) {
            TosDelayMS(10);
        }
        if (ahGetConnectionStatus() == kCONNECTION_ESTABLISHED)
            ret = AH_SUCCESSFUL;
        else
            ret = err_comm_connect;
    }
    if (ret != AH_SUCCESSFUL) {
        data->reasonCode = ret;
        return err_comm_connect;
    }
    return ret;
}

ahS16_t tranProc(TranData_t *data) {
    ahU8_t msgBuf[1024] = {0};
    // ahU8_t *msgBuf = TosMalloc(1024);
    // if (!msgBuf) {
    //     log_debug("[T] - could not allocate memory using malloc() ----- ");
    //     return err_comm_init;
    // }
    // memset(msgBuf, 0, 1024);

    fnp_Keys fnpKeys;
    ahU32_t msgLen = 0;
    // do {
    //     if (data->log.tranType == kTRAN_SETTLEMENT || data->log.tranType == kTRAN_REVERSAL ||
    //         data->log.tranType == kTRAN_LOGON)
    //         break;
    //     SafInfo_t saf;
    //     if (tblSafRead(&saf) != AH_SUCCESSFUL)
    //         break;
    //     int decideResult = ahDecide();
    //     if (decideResult != AH_SUCCESSFUL)
    //         return decideResult;
    // } while (0);
    //
    //
    // do {
    //     if (data->log.tranType != kTRAN_BALANCE && data->log.tranType != kTRAN_PURCHASE &&
    //         data->log.tranType != kTRAN_TOPUP && data->log.tranType != kTRAN_BILL_PAYMENT &&
    //         data->log.tranType != kTRAN_VOUCHER)
    //         break;
    //
    //     S32 ret = TosPrnStatus();
    //     if (ret == AH_SUCCESSFUL)
    //         break;
    //
    //     else if (ret == ERR_PRN_PAPER_LACK) {
    //         app_failure_tip_msgbox("کاغذ در پرينتر موجود نيست", 3000);
    //     } else
    //         app_failure_tip_msgbox("خطا در پرينتر", 3000);
    //     return AH_FAIL;
    // } while (0);


    app_loading_msgbox("برقراری ارتباط ...");


    do {
        // DL_ISO8583_HANDLER isoHandler;
        // DL_ISO8583_DEFS_pepiso_GetHandler(&isoHandler);
        // DL_ISO8583_MSG_Init(NULL, 0, &data->sendMsg);


        // uint8_t   macHex[8 + 1]	= {0};
        // uint8_t   macBin[4 + 1]	= {0};

        // ISO8583_ClearBackup();
        ISO8583_Clear();
        iso8583_SetISODef(sIsoDef);

        if (ahSetFields(data) != AH_SUCCESSFUL) {
            log_debug("[T] - PROBLEM HAS OCCURED WHILE AH SET FIELD RETURNS ============ => ");
            return err_tran_pack;
        }

        //  DL_ISO8583_MSG_Dump(&isoHandler, &data->sendMsg);

        log_debug("[T] - calling ISO8583_MSG_Dump() ========== => ");


        ISO8583_MSG_Dump(0);
        //DL_ISO8583_MSG_Dump(&isoHandler, &data->sendMsg);
        // ahU8_t packRet = DL_ISO8583_MSG_Pack(&isoHandler, &data->sendMsg, msgBuf + 2, &msgLen);
        //log_debug("msgBuf after PACK FUNC =========== => [%s]", msgBuf + 2);
        //log_hex("msgBUF after MAC ======== => ", msgBuf + 2, msgLen);
        ahU8_t packRet = ISO8583_Pack(msgBuf + 2, &msgLen);
        log_debug("[T] - ############################################# - ");
        log_hex("[T] - sendBuffer before header changes => ", msgBuf, msgLen);

        if (packRet != 0) {
            log_error("Msg Pack failed =%d", packRet);
            return err_tran_pack;
        }
        // log_debug("[T] - tranConfig.macIndex value ============== => [%d] ", data->tranConfig.macIndex);
        unsigned char * serial = (unsigned char *)ahGetDeviceSerial();
        log_debug("[T] - unsigned char value of serial number is =========== => [%s]", serial);

        unsigned char macData[4];
        unsigned char * master = GeneratePepIsoDefaultKeyWithSerial((char *)serial);

        log_hex("[T] - calculated masterKey using GeneratePepIsoDefaultKeyWithSerial =>  ", master, 8);
        // log_hex("[T] - msgBuf value before passing to des_mac function ======= => ", msgBuf + 2, msgLen - 4);

        des_mac(msgBuf + 2, msgLen - 4, master, macData);
        log_hex("[T] - macData after calculation ================ =>  ", macData, 4);

        // fnp_enc_GenDefaultKeysEx(&fnpKeys, serial, 0);
        // log_debug("[T] - fnpKeys dataLEN after passing to fnp_enc_GenDefaultKeysEx => [%d]", fnpKeys.MACKeyLen);
        // comportHexShow(fnpKeys.MACKey, 8);
        //
        // createMac(fnpKeys.MACKey,  msgBuf + 2, msgLen - 4, macHex, macBin);
        //
        // // comportHexShow(msgBuf, msgLen);
        //
        memcpy(msgBuf + 2 + (msgLen - 4), macData, 4);
        // log_hex("msgBUF after MAC ======== => ", msgBuf + 2, msgLen);

        // if (data->tranConfig.macIndex > 0) {
        //     ahS16_t ret;
        //     ahU8_t macBuf[20] = {0};
        //     ahU8_t temp[16] = {0};
        //
        //     if ((ret = ahPedGetMac(data->tranConfig.macIndex, msgBuf + 2 + HEADER_LEN, msgLen - 8, macBuf)) !=
        //         AH_SUCCESSFUL) {
        //         return err_ped_mac_generate;
        //     }
        //
        //     memset(temp, 0, sizeof(temp));
        //     ahBcd2Asc(macBuf, 4, temp);
        //     switch (ret) {
        //         case 0:
        //             memcpy(msgBuf + 2 + HEADER_LEN + msgLen - 8, temp, 8);
        //             break;
        //         default:
        //             return err_tran_pack;
        //     }
        // }


        // ahU8_t hdr[HEADER_LEN] = {0};
        // hdr[0] = 0x60;
        // ahU16_t nii = strtol(g_prop.connection.nii, NULL, 10);
        // hdr[1] = (nii >> 8) & 0xff;
        // hdr[2] = nii & 0xff;
        // memcpy(msgBuf + 2, hdr, HEADER_LEN);
        // msgLen += HEADER_LEN;
        ahU8_t lenHex[2];
        lenHex[0] = (msgLen >> 8) & 0xFF;
        lenHex[1] = msgLen & 0xFF;
        memcpy(msgBuf, lenHex, 2);
        msgLen = msgLen + 2;
    } while (0);

    int connectionRet = ahConnectServer(data);
    if (connectionRet != AH_SUCCESSFUL)
        return connectionRet;


    /// TODO :
    // if (data->log.tranType == kTRAN_PURCHASE || data->log.tranType == kTRAN_TOPUP ||
    //     data->log.tranType == kTRAN_VOUCHER || data->log.tranType == kTRAN_BILL_PAYMENT) {
    //     SafInfo_t saf = {0};
    //     saf.type = kTRAN_REVERSAL;
    //     saf.amount = strtol(data->log.amount, NULL, 10);
    //     saf.stan = data->log.stan;
    //     strcpy(saf.processCode, data->tranConfig.processCode);
    //     strcpy(saf.currency, "364");
    //     strcpy(saf.termId, g_prop.merchant.terminalId);
    //     sprintf(saf.maskedPan, "%.6s%.4s", data->log.hashPan, data->log.hashPan + strlen(data->log.hashPan) - 4);
    //     sprintf(saf.dateTime, "%04d%02d%02d%02d%02d%02d", data->log.dateTime.year, data->log.dateTime.month,
    //             data->log.dateTime.day, data->log.dateTime.hour, data->log.dateTime.minute, data->log.dateTime.second);
    //     saf.nextOccurrence = ahGetNowLong() + SCHEDULE_PERIOD;
    //     saf.retryCount = 0;
    //     tblSafUpdate(&saf, AH_FALSE);
    //     g_prop.terminal.printStatus = 1;
    // }

    g_prop.terminal.stan += 1;
    if (g_prop.terminal.stan > 999999)
        g_prop.terminal.stan = 1;
    savePreference();

    log_hex("[T] - before sending the data and calling ahSend() ===== => ", msgBuf, msgLen);
    app_loading_msgbox("ارسال اطلاعات ...");
    if (ahSend(msgBuf, msgLen, g_prop.connection.recvTimeout_ms) != AH_SUCCESSFUL)
        return err_comm_send;
    memset(msgBuf, 0, 1024);
    ahU32_t len = 1024;
    app_loading_msgbox("دریافت اطلاعات ...");
    if (ahReceive(msgBuf, &len, g_prop.connection.recvTimeout_ms) != 0)
        return err_comm_receive;
    log_hex("recv Message", msgBuf, len);
    msgLen = len;
    if (msgLen < HEADER_LEN + 2)
        return err_comm_receive;
    if (len != msgBuf[0] * 256 + msgBuf[1] + 2) {
        log_trace;
        return err_comm_receive;
    }
    // ISO8583_Free();

    // DL_ISO8583_MSG_Init(NULL, 0, &data->recvMsg);
    // DL_ISO8583_HANDLER isoHandler;
    // DL_ISO8583_DEFS_pepiso_GetHandler(&isoHandler);
    ISO8583_ClearBackup();
    // ISO8583_Clear();
    iso8583_SetISODef(sIsoDef);

    // ahU16_t buffLen = msgLen;
    //const DL_ERR procResult = DL_ISO8583_MSG_Unpack(&isoHandler, msgBuf + 2, buffLen - 2, &data->recvMsg);
    log_debug("[T] - calling ISO8583 UNPACK function ======== => ");

    //DL_ISO8583_MSG_Dump(&isoHandler, &data->recvMsg);

    const int procResult = ISO8583_Unpack(msgBuf);
    if (procResult != kDL_ERR_NONE) {
        log_error("unpack failed");
        // return err_tran_msg_unpack;
    }
    log_debug("[T] - calling ISO8583_MSG_Dump() ============== => ");
    ISO8583_MSG_Dump(1);

    // ahU8_t *str;
    // if (DL_ISO8583_MSG_HaveField(17, &data->recvMsg)) {
    //     DL_ISO8583_MSG_GetField_Str(17, &data->recvMsg, &str);
    //     // strcpy(data->log.rrn, str);
    //     log_debug("[T] - get field 17 str is ========= => [%s]", (char *) str);
    // }
    // if (DL_ISO8583_MSG_HaveField(20, &data->recvMsg)) {
    //     DL_ISO8583_MSG_GetField_Str(20, &data->recvMsg, &str);
    //     // strcpy(data->authId, str);
    //     log_debug("[T] - get field 20 str is ========== => [%s]", (char *) str);
    // }
    // if (DL_ISO8583_MSG_HaveField(42, &data->recvMsg)) {
    //     log_debug("[T] - field 42 lives ! =============== => ");
    // } else {
    //     log_debug("[T] - field 42 detection failed ! =========== => ");
    // }


    // ahS16_t resp;
    // resp = ahGetRespCode(data);
    // if (resp < 0) {
    //     log_error("get respcode failed");
    //     // return resp;
    // }
    // for (int i = 0; i < sizeof(data->ltv) / sizeof(Ltv_t); i++) {
    //     if (data->ltv[i].key == 50) {
    //         TosSetTime(data->ltv[i].value);
    //     }
    //     if (data->ltv[i].key == 38) {
    //         ahCp1256toUtf8(data->ltv[i].value, data->ltv[i].len, data->log.bankName);
    //     }
    //     if (data->ltv[i].key == 98) {
    //         memset(g_prop.terminal.posCode, 0, sizeof(g_prop.terminal.posCode));
    //         strncpy(g_prop.terminal.posCode, data->ltv[i].value, data->ltv[i].len);
    //     }
    // }
    // data->respCode = resp;
    // if (resp > 0) {
    //     ahBeepFail();
    //     return err_tran_not_successful;
    // }

    ISO8583_Free();
    // TosFree(msgBuf);
    return AH_SUCCESSFUL;
}


ahFRes_t ahGetRespCode(TranData_t *data) {
    ahU8_t *resp;
    ahS8_t *endptr;
    ahU8_t ret = DL_ISO8583_MSG_GetField_Str(39, &data->recvMsg, &resp);
    if (ret != 0)
        return err_tran_msg_unpack;
    ahS32_t result = strtol(resp, &endptr, 10);
    if (endptr == resp)
        return err_tran_msg_unpack;
    return result;
}


ahS16_t ahUpdateSafToSettle(TranData_t *data) {
    if (data->log.tranType == kTRAN_PURCHASE || data->log.tranType == kTRAN_TOPUP ||
        data->log.tranType == kTRAN_BILL_PAYMENT || data->log.tranType == kTRAN_VOUCHER) {
        SafInfo_t saf = {0};
        saf.type = kTRAN_SETTLEMENT;
        saf.amount = strtol(data->log.amount, NULL, 10);
        saf.stan = data->log.stan;
        strcpy(saf.processCode, data->tranConfig.processCode);
        strcpy(saf.currency, "364");
        strcpy(saf.termId, g_prop.merchant.terminalId);
        sprintf(saf.dateTime, "%04d%02d%02d%02d%02d%02d", data->log.dateTime.year, data->log.dateTime.month,
                data->log.dateTime.day, data->log.dateTime.hour, data->log.dateTime.minute, data->log.dateTime.second);
        strncpy(saf.rrn, data->log.rrn, 12);
        strncpy(saf.authId, data->authId, 6);
        saf.nextOccurrence = ahGetNowLong() + SCHEDULE_PERIOD;
        saf.retryCount = 0;
        return tblSafUpdate(&saf, AH_FALSE);
    }
    return AH_SUCCESSFUL;
}

ahFRes_t ahProcessUnsuccessTran(TranData_t *data, ahS16_t ret) {
    const ahU8_t retCodesNeedReverse[] = {80};
    if (ret == err_tran_not_successful) {
        log_trace;
        ahPrnReceiptUnsuccess(data, kPRINT_CUSTOMER);
        if (!ahIsInU8Array(retCodesNeedReverse, sizeof(retCodesNeedReverse), data->respCode))
            tblSafRemoveLast();
    }
    return AH_SUCCESSFUL;
}

ahS16_t showUnsuccessResult(ahFRes_t ret, TranData_t *data) {
    if (ret == err_comm_connect || ret == err_comm_send) {
        char errCode[20] = {0};
        if (data->reasonCode != 0) {
            sprintf(errCode, "(%d)", data->reasonCode);
        }
        app_failure_tip_msgbox("خطا در برقراري ارتباط", 3000);
    } else if (ret == err_comm_receive) {
        app_failure_tip_msgbox("خطا در دريافت پيام", 3000);
    } else if (ret == err_tran_not_successful) {
        char errCode[20] = {0};
        if (data->respMsg[0] > 0) {
            app_failure_tip_msgbox(data->respMsg, 3000);
        } else {
            char msg[100] = {0};
            sprintf(errCode, "%d", data->respCode);
            sprintf(msg, "تراکنش ناموفق - %s", errCode);
            app_failure_tip_msgbox(msg, 3000);
        }
    } else {
        char errMsg[30] = {0};
        sprintf(errMsg, "تراکنش ناموفق - (%d)", ret);
        app_failure_tip_msgbox(errMsg, 3000);
    }
    return AH_SUCCESSFUL;
}

ahS16_t ahParseLtv(ahU8_t *field48, ahU16_t len, Ltv_t *ltv, ahU8_t expLen) {
    ahU16_t index = 0, i = 0;
    while (index < len) {
        ahU8_t len = (field48[index] >> 4) * 10 + (field48[index] & 0x0F);
        ltv[i].key = (field48[index + 1] >> 4) * 10 + (field48[index + 1] & 0x0F);
        ltv[i].len = len - 1;
        memcpy(ltv[i++].value, &field48[index + 2], len - 1);
        index += (len + 1);
        if (i >= expLen)
            return -1;
    }
    return i;
}
