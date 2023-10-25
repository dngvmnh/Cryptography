/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include <io.h>
#include <system.h>


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
		IOWR(CHACHA_WRAPPER_0_BASE, CHACHA_ADDR_KEY0 + i, key[i]);

	for(int i = 0; i < 16; i++)
		IOWR(CHACHA_WRAPPER_0_BASE, CHACHA_ADDR_DATA_IN0 + i, data_in[i]);

	IOWR(CHACHA_WRAPPER_0_BASE, CHACHA_ADDR_IV0, iv[0]);
	IOWR(CHACHA_WRAPPER_0_BASE, CHACHA_ADDR_IV1, iv[1]);
	IOWR(CHACHA_WRAPPER_0_BASE, CHACHA_ADDR_KEYLEN, key_len);
	IOWR(CHACHA_WRAPPER_0_BASE, CHACHA_ADDR_ROUNDS, num_round);
	IOWR(CHACHA_WRAPPER_0_BASE, CHACHA_ADDR_CTRL, 0x01);

	while(IORD(CHACHA_WRAPPER_0_BASE, CHACHA_ADDR_STATUS) == 0);
	for(int i = 0; i < 16; i++)
		data_out[i] = IORD(CHACHA_WRAPPER_0_BASE, CHACHA_ADDR_DATA_OUT0 + i);
}

static void chacha_cipher_next_block(unsigned int *data_out) {
	IOWR(CHACHA_WRAPPER_0_BASE, CHACHA_ADDR_CTRL, 0x02);

	while(IORD(CHACHA_WRAPPER_0_BASE, CHACHA_ADDR_STATUS) == 0);
	for(int i = 0; i < 16; i++)
		data_out[i] = IORD(CHACHA_WRAPPER_0_BASE, CHACHA_ADDR_DATA_OUT0 + i);
}



int main()
{
	printf("Hello from Nios II!\n");

  	// ====================== TEST ONE (all zeros) ================================================
  	unsigned int chacha_key[8] 		= { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
  	unsigned int chacha_iv[2] 		= { 0x0, 0x0 };
  	unsigned int chacha_data_in[16] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
  	unsigned int chacha_dump[16] 	= { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };

  	unsigned int chacha_expected_8_128[16] = { 0xe28a5fa4, 0xa67f8c5d,
  			0xefed3e6f, 0xb7303486, 0xaa8427d3, 0x1419a729, 0x572d7779,
  			0x53491120, 0xb64ab8e7, 0x2b8deb85, 0xcd6aea7c, 0xb6089a10,
  			0x1824beeb, 0x08814a42, 0x8aab1fa2, 0xc816081b };

  	chacha_cipher(CHACHA_KEYLEN_128, chacha_key, chacha_iv, 0x08, chacha_data_in, chacha_dump);

  	printf("\nChaCha - 8 round - 128-bit key\n");
  	printf("EXPECTED: ");
  	for (int i = 0; i < 16; i++) {
  		printf("%08x_", chacha_expected_8_128[i]);
  	}
  	printf("\nRESULT:   ");
  	for (int i = 0; i < 16; i++) {
  		printf("%08x_", chacha_dump[i]);
  	}
  	printf("\n");

  	// ================================== TEST TWO ================================================
  	chacha_key[0] = 0x00112233;
  	chacha_key[1] = 0x44556677;
  	chacha_key[2] = 0x8899aabb;
  	chacha_key[3] = 0xccddeeff;
  	chacha_key[4] = 0xffeeddcc;
  	chacha_key[5] = 0xbbaa9988;
  	chacha_key[6] = 0x77665544;
  	chacha_key[7] = 0x33221100;

  	chacha_iv[0] = 0x0f1e2d3c;
  	chacha_iv[1] = 0x4b596877;

  	unsigned int chacha_expected_8_256[16] = { 0x60fdedbd, 0x1a280cb7,
  			0x41d0593b, 0x6ea03090, 0x10acf18e, 0x1471f689, 0x68f4c9e3,
  			0x11dca149, 0xb8e027b4, 0x7c81e035, 0x3db01389, 0x1aa5f68e,
  			0xa3b13dd2, 0xf3b8dd08, 0x73bf3746, 0xe7d6c567 };

  	chacha_cipher(CHACHA_KEYLEN_256, chacha_key, chacha_iv, 0x08, chacha_data_in, chacha_dump);

  	printf("\nChaCha - 8 round - 256-bit key\n");
  	printf("EXPECTED: ");
  	for (int i = 0; i < 16; i++) {
  		printf("%08x_", chacha_expected_8_256[i]);
  	}
  	printf("\nRESULT:   ");
  	for (int i = 0; i < 16; i++) {
  		printf("%08x_", chacha_dump[i]);
  	}
  	printf("\n");

  	// ================================== TEST THREE ==============================================
  	chacha_cipher_next_block(chacha_dump);
  	printf("\nChaCha - 8 round - 256-bit key (continue/next 512-bit STATE block)\n");
  	printf("EXPECTED: fe882395_601ce8ad_ed444867_fe62ed87_41420002_e5d28bb5_73113a41_8c1f4008_e954c188_f38ec4f2_6bb8555e_2b7c92bf_4380e2ea_9e553187_fdd42821_794416de");
  	printf("\nRESULT:   ");
  	for (int i = 0; i < 16; i++) {
  		printf("%08x_", chacha_dump[i]);
  	}
  	printf("\n");

  	while(1) {
		IOWR(LED_BASE, 0, 0x155);
		usleep(100000);
		IOWR(LED_BASE, 0, 0x2aa);
		usleep(100000);
	}

  return 0;
}
