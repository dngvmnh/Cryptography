/*
 * prince.h
 *
 *  Created on: 18 Oct 2023
 *      Author: khaim
 */
#include <io.h>
#include <system.h>

#ifndef PRINCE_H_
#define PRINCE_H_

//  PRINCE Macro
#define PRINCE_ADDR_KEY0        0x10
#define PRINCE_ADDR_BLOCK0      0x20
#define PRINCE_ADDR_RESULT0     0x30
#define PRINCE_ADDR_CTRL        0x08
#define PRINCE_ADDR_STATUS      0x09
#define PRINCE_ADDR_CONFIG      0x0a
#define PRINCE_CONFIG_EN        0x01
#define PRINCE_CONFIG_DE        0x00


static void prince_cipher(
		unsigned int *key,
		unsigned int *data_in,
		unsigned int config,
		unsigned int *data_out)
{

	for(int i = 0; i < 4; i++)
		IOWR(PRINCE_0_BASE, PRINCE_ADDR_KEY0 + i, key[i]);

	for(int i = 0; i < 2; i++)
		IOWR(PRINCE_0_BASE, PRINCE_ADDR_BLOCK0  + i, data_in[i]);

	IOWR(PRINCE_0_BASE, PRINCE_ADDR_CONFIG, config);
	IOWR(PRINCE_0_BASE, PRINCE_ADDR_CTRL, 0x1);

	while (IORD(PRINCE_0_BASE, PRINCE_ADDR_STATUS) == 0);

	data_out[0] = IORD(PRINCE_0_BASE, PRINCE_ADDR_RESULT0);
	data_out[1] = IORD(PRINCE_0_BASE, PRINCE_ADDR_RESULT0 + 1);
}




#endif /* PRINCE_H_ */
