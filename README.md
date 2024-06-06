## DEMO

**1. Simulating Signals**

![Simulating Signals](https://github.com/dngvmnh/Cryptography/assets/133772077/ccd5a6dd-5d2f-461e-9dd9-1c73a7da137c)

**2. Interacting With FPGA**

https://github.com/dngvmnh/Cryptography/assets/133772077/45402efd-6607-45cd-9e34-0804a4decd89

**3. Welding PCB**

![Welding PCB](https://github.com/dngvmnh/Cryptography/assets/133772077/ffad9eff-71eb-40b7-bec5-a0e4417b54cb)

## Project Description

**1. Overview**

This is a Digital Security System Design involving some cryptographic algorithms such as Caesar, ChaCha, AES, Prince. Cryptography has been driven by escalating security challenges, especially lightweight encryption. The primary objective of this research is the design and implementation of electronic circuits, specializing in encryption algorithms and lightweight encryption, targeting preconfigured microcontrollers. This study aims to develop and implement data encryption within limited hardware such as microcontroller environments. Its results can be applied to subsequent research in the same field.

**2. The PIISE Program**

This research project is carried out within the PTNK Initiative in Interdisciplinary Science and Engineering (PIISE) Summer Research Internship Program under the topic Information Technology at DESLAB - University of Science from July 27, 2023 to October 29, 2023. The program is established and ran by PTNK (VNU-HCM High School for The Gifted) PIISE organization.

## Implementation

The implementation of this project includes three main stages: designing Printed Circuit Board, Assembling FPGA, System on Chip and simulating cryptographic algorithms.

-	The schematic and layout of the PCB can be found here: [Design folder]( https://github.com/dngvmnh/Cryptography/tree/main/Solar_Charger)
  
-	Intel DE10 Standard FPGA Board is used in order to assemble a preconfigured microcontroller. The SoC System use the Nios 2 CPU as the processor.
  
-	This project delved into to the application of Bolean Algebra: Full and Half Adder 1 Bit. In many computers and other kinds of processors, adders are used in the arithmetic logic units (ALUs) used to calculate addresses, table indices, increment and decrement operators and similar operations.
  
For more details, refer to this repository: [System on Chip Design]( https://github.com/dngvmnh/Cryptography/tree/main/FPGA_SOC%20files), [AES Algorithm]( https://github.com/dngvmnh/Cryptography/tree/main/aes), [ChaCha20 Algorithm]( https://github.com/dngvmnh/Cryptography/tree/main/chacha), [PRINCE Algorithm]( https://github.com/dngvmnh/Cryptography/tree/main/prince).

## Results and discussion

In terms of the Printed Circuit Board design, the 18650 rechargeable batteries can be charged and protected from overheating or overloading by the voltage-reducing and load-cutting charging circuit. The circuit design uses the 1N5819 diode and LM317 voltage regulator, which control the current direction and adjust the output voltage according to a custom signal. This way, the 18650 rechargeable batteries can handle different input voltage levels.

Regarding simulating section, despite the improvements in speed, performance, and security of the PRINCE encryption algorithm, some potential difficulties and dangers are still spotted. PRINCE encryption has advanced in terms of asymmetry, but the algorithm can still be compromised by brute-force techniques. The sizes of bits and bytes in PRINCE encryption are relatively small, so applications that require more bits or bytes for encryption may not be compatible with it.

Images and videos of this project can be found here: [Media](https://github.com/dngvmnh/Cryptography/tree/main/Result/Media)

## Report

For further information, refer to this report: [View on GitHub](https://github.com/dngvmnh/Cryptography/blob/main/Result/Report/PIISE%20-%20Report%20-%20KHTN.pdf) or [Download PDF](https://github.com/dngvmnh/Cryptography/raw/main/Result/Report/PIISE%20-%20Report%20-%20KHTN.pdf)
