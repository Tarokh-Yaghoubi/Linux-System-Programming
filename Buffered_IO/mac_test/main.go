package main

import (
	"crypto/des"
	"crypto/sha1"
	"encoding/hex"
	"fmt"
	"math"

	"github.com/pkg/errors"
)

func GeneratePepIsoDefaultKeyWithSerial(serial string) []byte {
	data := []byte{1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8}
	temp := make([]byte, 16)
	
	if len(serial) >= 15 {
		copy(temp, serial[len(serial)-15:])
	} else {
		copy(temp[15-len(serial):], serial)
	}
	
	// Removed the "utils." prefix since Xor is in the same file
	data = Xor(data, temp)

	// Replaced custom "cipher.SHA1" with standard Go library implementation
	hash := sha1.Sum(data)
	key := hash[:]

	result := make([]byte, 8)
	for i := 0; i < 8; i++ {
		result[i] = key[i*2]
	}
	return result
}

func desMac(data, key []byte) ([]byte, error) {
	block, err := des.NewCipher(key)
	if err != nil {
		return nil, errors.Wrap(err, "mac new cipher")
	}
	result := make([]byte, 8)
	for i := 0; i < len(data); i += 8 {
		temp := make([]byte, 8)
		copy(temp, data[i:])
		// Removed the "utils." prefix
		temp = Xor(temp, result)
		block.Encrypt(result, temp)
	}
	return result[:4], nil
}

func Xor(dest, src []byte) []byte {
	result := make([]byte, int(math.Max(float64(len(src)), float64(len(dest)))))
	for i := 0; i < len(dest) && i < len(src); i++ {
		result[i] = src[i] ^ dest[i]
	}
	return result
}

func main() {
	// Your serial number
	serial := "S2810102600129135"
	// serial := "201657357804"
	// Your raw ISO data represented as a hexadecimal string
	isoHex := "826B0A0000810001177C4BD3043F409B0828101026001291350000043EFFCE000C4353504545443D302E31313B49503D3139322E3136382E312E3130313B50484F4E453D30323135353731323637343B494D45493D3132333435363738393031323334353B"
	// isoHex := "826B0A000081000617661157003EA451062016573578040005008A290D000C4353504545443D302E31303B49503D3139322E3136382E312E3130313B50484F4E453D30323135353731323637343B494D45493D3132333435363738393031323334353B"
	// Convert the hex string into raw bytes
	isoData, err := hex.DecodeString(isoHex)
	if err != nil {
		fmt.Println("Failed to decode hex string:", err)
		return
	}

	// 1. Generate the Master Key
	key := GeneratePepIsoDefaultKeyWithSerial(serial)
	fmt.Printf("Derived Key: %X\n", key)

	// 2. Generate the MAC
	mac, err := desMac(isoData, key)
	if err != nil {
		fmt.Println("Error calculating MAC:", err)
		return
	}

	fmt.Printf("Calculated MAC: %X\n", mac)
}
