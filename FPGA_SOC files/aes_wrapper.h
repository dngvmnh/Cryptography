/*
 * aes.h
 *
 *  Created on: 18 Oct 2023
 *      Author: khaim
 */
#include <io.h>
#include <system.h>

#ifndef AES_H_
#define AES_H_

#define AES_ADDR_CTRL     	0x08
#define AES_ADDR_STATUS   	0x09
#define AES_ADDR_CONFIG   	0x0A

#define AES_ADDR_KEY0     	0x10
#define AES_ADDR_BLOCK0   	0x20
#define AES_ADDR_RESULT0  	0x30

#define AES_CONFIG_128_KEY  0x00
#define AES_CONFIG_256_KEY  0x02

#define AES_CONFIG_128_EN  	0x01
#define AES_CONFIG_128_DE  	0x00
#define AES_CONFIG_256_EN  	0x03
#define AES_CONFIG_256_DE  	0x02

#define AES_CTRL_INIT_KEY 	0x01
#define AES_CTRL_START 		0x02


// General "bit" rule for encryption and decryption
#define AES_EN 	0x01
#define AES_DE  0x00


static void aes_128_cipher(
		unsigned char operation,
		unsigned int *key,
		unsigned int *block,
		unsigned int *res)
{

	for(int i = 0; i < 4; i++)
		IOWR(AES_0_BASE, AES_ADDR_KEY0 + i, key[i]);

	for(int i = 4; i < 8; i++)
		IOWR(AES_0_BASE, AES_ADDR_KEY0 + i, 0x0);

	IOWR(AES_0_BASE, AES_ADDR_CONFIG, AES_CONFIG_128_KEY);
	IOWR(AES_0_BASE, AES_ADDR_CTRL,   AES_CTRL_INIT_KEY);
	while(IORD(AES_0_BASE, AES_ADDR_STATUS) == 0);



	for(int i = 0; i < 4; i++)
		IOWR(AES_0_BASE, AES_ADDR_BLOCK0 + i, block[i]);


	unsigned char AES_CONFIG = 0x00;
	if (operation == 0x01)
		AES_CONFIG = AES_CONFIG_128_EN;
	else
		AES_CONFIG = AES_CONFIG_128_DE;

	IOWR(AES_0_BASE, AES_ADDR_CONFIG, AES_CONFIG);
	IOWR(AES_0_BASE, AES_ADDR_CTRL, AES_CTRL_START);
	while(IORD(AES_0_BASE, AES_ADDR_STATUS) == 0);


	for(int i = 0; i < 4; i++)
		res[i] = IORD(AES_0_BASE, AES_ADDR_RESULT0 + i);
}


#endif /* AES_H_ */
