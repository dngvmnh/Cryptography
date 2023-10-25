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
#include <aes_wrapper.h>
#include <chacha_wrapper.h>
#include <prince_wrapper.h>


int main()
{
	printf("Hello from Nios II!\n");


	//   ___ _          ___ _
	//  / __| |_  __ _ / __| |_  __ _
	// | (__| ' \/ _` | (__| ' \/ _` |
	//  \___|_||_\__,_|\___|_||_\__,_|
	printf("\n\nChaCha cipher -------------------------------------\n");

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





	//    _   ___ ___
	//   /_\ | __/ __|
	//  / _ \| _|\__ \
	// /_/ \_\___|___/
  	printf("\n\nAES cipher ----------------------------------------\n");

  	unsigned int aes_key_128[4] = {0x0, 0x0, 0x0, 0x0};
  	unsigned int aes_block[4] 	= {0x0, 0x0, 0x0, 0x0};
  	unsigned int aes_exp_res[4] = {0x0, 0x0, 0x0, 0x0};

  	unsigned int aes_res[4] 	= {0x0, 0x0, 0x0, 0x0};

  	// ========================================
  	printf("\nTEST 1 - Encryption\n");
	aes_key_128[0] = 0x39383736;
	aes_key_128[1] = 0x35343332;
	aes_key_128[2] = 0x31303938;
	aes_key_128[3] = 0x37363534;

	aes_block[0] = 0x31323334;
	aes_block[1] = 0x35363738;
	aes_block[2] = 0x39303132;
	aes_block[3] = 0x33343536;

	aes_exp_res[0] = 0x6f2f5312;
	aes_exp_res[1] = 0x53e5f4da;
	aes_exp_res[2] = 0xd07781b2;
	aes_exp_res[3] = 0xa1e33d0b;


	aes_128_cipher(AES_EN, aes_key_128, aes_block, aes_res);
	printf("EXPECTED: %08x_%08x_%08x_%08x\n", aes_exp_res[0], aes_exp_res[1], aes_exp_res[2], aes_exp_res[3]);
	printf("RESULT:   %08x_%08x_%08x_%08x\n", aes_res[0], aes_res[1], aes_res[2], aes_res[3]);


	// ========================================
	printf("\nTEST 2 - Encryption ---------------------------------\n");
	aes_block[0] = 0x6d616b68;
	aes_block[1] = 0x61696d69;
	aes_block[2] = 0x6e687669;
	aes_block[3] = 0x7070726f;

	aes_key_128[0] = 0x73616d73;
	aes_key_128[1] = 0x756e6767;
	aes_key_128[2] = 0x616c6178;
	aes_key_128[3] = 0x79733231;

	aes_exp_res[0] = 0x48aabecf;
	aes_exp_res[1] = 0xeb074f5a;
	aes_exp_res[2] = 0xf8f85a2c;
	aes_exp_res[3] = 0x096918ed;

	aes_128_cipher(AES_EN, aes_key_128, aes_block, aes_res);
	printf("EXPECTED: %08x_%08x_%08x_%08x\n", aes_exp_res[0], aes_exp_res[1], aes_exp_res[2], aes_exp_res[3]);
	printf("RESULT:   %08x_%08x_%08x_%08x\n", aes_res[0], aes_res[1], aes_res[2], aes_res[3]);

	// ===========================================================================================
	printf("\nTEST 3 - Encryption again\n");

	aes_block[0] = 0x6465736c;
	aes_block[1] = 0x61627665;
	aes_block[2] = 0x78726973;
	aes_block[3] = 0x6376213f;

	aes_key_128[0] = 0x31323334;
	aes_key_128[1] = 0x35363738;
	aes_key_128[2] = 0x39303132;
	aes_key_128[3] = 0x33343536;

	aes_exp_res[0] = 0x6e6f9733;
	aes_exp_res[1] = 0x6428318a;
	aes_exp_res[2] = 0xbd2fb855;
	aes_exp_res[3] = 0xfd1ee6b4;

	aes_128_cipher(AES_EN, aes_key_128, aes_block, aes_res);
	printf("EXPECTED: %08x_%08x_%08x_%08x\n", aes_exp_res[0], aes_exp_res[1], aes_exp_res[2], aes_exp_res[3]);
	printf("RESULT:   %08x_%08x_%08x_%08x\n", aes_res[0], aes_res[1], aes_res[2], aes_res[3]);


	// ===========================================================================================
	printf("\nTEST 4 - Encryption\n");

	aes_block[0] = 0x6bc1bee2;
	aes_block[1] = 0x2e409f96;
	aes_block[2] = 0xe93d7e11;
	aes_block[3] = 0x7393172a;

	aes_key_128[0] = 0x2b7e1516;
	aes_key_128[1] = 0x28aed2a6;
	aes_key_128[2] = 0xabf71588;
	aes_key_128[3] = 0x09cf4f3c;

	aes_exp_res[0] = 0x3ad77bb4;
	aes_exp_res[1] = 0x0d7a3660;
	aes_exp_res[2] = 0xa89ecaf3;
	aes_exp_res[3] = 0x2466ef97;

	aes_128_cipher(AES_EN, aes_key_128, aes_block, aes_res);
	printf("EXPECTED: %08x_%08x_%08x_%08x\n", aes_exp_res[0], aes_exp_res[1], aes_exp_res[2], aes_exp_res[3]);
	printf("RESULT:   %08x_%08x_%08x_%08x\n", aes_res[0], aes_res[1], aes_res[2], aes_res[3]);


	//   ___ ___ ___ _  _  ___ ___
	//  | _ \ _ \_ _| \| |/ __| __|
	//  |  _/   /| || .` | (__| _|
	//  |_| |_|_\___|_|\_|\___|___|
	printf("\n\nPRINCE cipher\n");

	// ======================== ENCRYPT TEST ===============================
	unsigned int prince_key[4] 	= {0x00000000, 0x00000000, 0x00000000, 0x00000000};
	unsigned int prince_block[2] 	= {0x00000000, 0x00000000};
	unsigned int prince_exp_res[2]	= {0x0d02dfda, 0x818665aa}; // Expected data out
	unsigned int prince_result[2];

	prince_cipher(prince_key, prince_block, PRINCE_CONFIG_EN, prince_result);

	printf("\nEncryption test setup (display in hexadecimal):\n");
	printf("Key:\t %08x_%08x_%08x_%08x\n", prince_key[3], prince_key[2], prince_key[1], prince_key[0]);
	printf("Block:\t %08x_%08x\n", prince_block[1], prince_block[0]);
	printf("Expect:\t %08x_%08x\n", prince_exp_res[1], prince_exp_res[0]);

	printf("Result:\t ");
	printf("%08x_%08x\n", prince_result[1], prince_result[0]);
	printf("\n");



	// ======================== DECRYPT TEST ===============================
	prince_key[3]	= 0x00112233;
	prince_key[2]	= 0x44556677;
	prince_key[1]	= 0x8899aabb;
	prince_key[0]	= 0xccddeeff;

	// Cipher out to be decrypt
	prince_block[1] = 0xd6dcb597;
	prince_block[0] = 0x8de756ee;

	// Expected data out
	prince_exp_res[1] = 0x01234567;
	prince_exp_res[0] = 0x89abcdef;

	prince_cipher(prince_key, prince_block, PRINCE_CONFIG_DE, prince_result);

	printf("\nDecryption test setup (display in hexadecimal):\n");
	printf("Key:\t %08x_%08x_%08x_%08x\n", prince_key[3], prince_key[2], prince_key[1], prince_key[0]);
	printf("Block:\t %08x_%08x\n", prince_block[1], prince_block[0]);
	printf("Expect:\t %08x_%08x\n", prince_exp_res[1], prince_exp_res[0]);

	printf("Result:\t ");
	printf("%08x_%08x\n", prince_result[1], prince_result[0]);



  	// Blinking LED Test ...
  	while(1) {
		IOWR(LED_BASE, 0, 0x155);
		usleep(100000);
		IOWR(LED_BASE, 0, 0x2aa);
		usleep(100000);
	}

  return 0;
}
