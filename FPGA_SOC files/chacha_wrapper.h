/*
 * chacha.h
 *
 *  Created on: 18 Oct 2023
 *      Author: khaim
 */
#include <io.h>
#include <system.h>

#ifndef CHACHA_H_
#define CHACHA_H_

//  ChaCha Macro
#define CHACHA_ADDR_CTRL           0x08
#define CHACHA_ADDR_STATUS         0x09
#define CHACHA_ADDR_KEYLEN         0x0a
#define CHACHA_ADDR_ROUNDS         0x0b
#define CHACHA_KEYLEN_128 		   0x00
#define CHACHA_KEYLEN_256 		   0x01
#define CHACHA_ADDR_KEY0           0x10
#define CHACHA_ADDR_IV0            0x20
#define CHACHA_ADDR_IV1            0x21
#define CHACHA_ADDR_DATA_IN0       0x40
#define CHACHA_ADDR_DATA_OUT0      0x80

static void chacha_cipher(
		unsigned int key_len,
		unsigned int *key,
		unsigned int *iv,
		unsigned int num_round,
		unsigned int *data_in,
		unsigned int *data_out)
{

	for(int i = 0; i < 8; i++)
		IOWR(CHACHA_0_BASE, CHACHA_ADDR_KEY0 + i, key[i]);

	for(int i = 0; i < 16; i++)
		IOWR(CHACHA_0_BASE, CHACHA_ADDR_DATA_IN0 + i, data_in[i]);

	IOWR(CHACHA_0_BASE, CHACHA_ADDR_IV0, iv[0]);
	IOWR(CHACHA_0_BASE, CHACHA_ADDR_IV1, iv[1]);
	IOWR(CHACHA_0_BASE, CHACHA_ADDR_KEYLEN, key_len);
	IOWR(CHACHA_0_BASE, CHACHA_ADDR_ROUNDS, num_round);
	IOWR(CHACHA_0_BASE, CHACHA_ADDR_CTRL, 0x01);

	while(IORD(CHACHA_0_BASE, CHACHA_ADDR_STATUS) == 0);
	for(int i = 0; i < 16; i++)
		data_out[i] = IORD(CHACHA_0_BASE, CHACHA_ADDR_DATA_OUT0 + i);
}





static void chacha_cipher_next_block(unsigned int *data_out) {
	IOWR(CHACHA_0_BASE, CHACHA_ADDR_CTRL, 0x02);

	while(IORD(CHACHA_0_BASE, CHACHA_ADDR_STATUS) == 0);
	for(int i = 0; i < 16; i++)
		data_out[i] = IORD(CHACHA_0_BASE, CHACHA_ADDR_DATA_OUT0 + i);
}



#endif /* CHACHA_H_ */
