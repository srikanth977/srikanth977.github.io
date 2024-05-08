/*
 * ModbusRS232Slave.h
 *
 *  Created on: May 8, 2024
 *      Author: Chili
 */

#ifndef MODBUSRTU_SLAVE_INC_MODBUSRS232SLAVE_H_
#define MODBUSRTU_SLAVE_INC_MODBUSRS232SLAVE_H_

#define MaxFrameIndex 255u
#define fc3_HoldingRegMax 125u
#define fc3_HoldingRegOffset 40001u
extern unsigned char MY_SLAVE_ID;
extern volatile unsigned char ResponseFrameSize;
extern volatile unsigned char data_in[MaxFrameIndex+1];
extern volatile unsigned int DataPos;

//Holding Register Array
static unsigned int HoldingRegisters[] = {
24288,	30717,	52317,	58320,	53844,	7596,	50869,	64892,	58209,	15124,	//0-9
38131,	16852,	62343,	25973,	11963,	49434,	31745,	48278,	50955,	50027,	//10-19
62940,	38520,	51144,	54693,	60394,	14244,	62402,	62647,	65457,	56695,	//20-29
40971,	29608,	37659,	60486,	3321,	769,	52458,	61584,	55023,	61523,	//30-39
50744,	51336,	3649,	48678,	29801,	43147,	1325,	32661,	49277,	32353,	//40-49
48858,	41522,	32167,	13748,	24501,	2375,	6957,	45371,	53417,	34799,	//50-59
51057,	3290,	13510,	48962,	65080,	22597,	38672,	14315,	48621,	49290,	//60-69
30178,	1793,	13119,	54566,	1570,	31355,	1754,	21305,	5750,	25520,	//70-79
23688,	54689,	64511,	17349,	33911,	31220,	64245,	17176,	43586,	30999,	//80-89
12761,	42338,	62682,	7424,	6981,	36057,	63189,	4897,	52723,	61279,	//90-99
};

//Input Register Array
static unsigned int InputRegisters[] = {
24288,	30717,	52317,	58320,	53844,	7596,	50869,	64892,	58209,	15124,	//0-9
38131,	16852,	62343,	25973,	11963,	49434,	31745,	48278,	50955,	50027,	//10-19
62940,	38520,	51144,	54693,	60394,	14244,	62402,	62647,	65457,	56695,	//20-29
40971,	29608,	37659,	60486,	3321,	769,	52458,	61584,	55023,	61523,	//30-39
50744,	51336,	3649,	48678,	29801,	43147,	1325,	32661,	49277,	32353,	//40-49
48858,	41522,	32167,	13748,	24501,	2375,	6957,	45371,	53417,	34799,	//50-59
51057,	3290,	13510,	48962,	65080,	22597,	38672,	14315,	48621,	49290,	//60-69
30178,	1793,	13119,	54566,	1570,	31355,	1754,	21305,	5750,	25520,	//70-79
23688,	54689,	64511,	17349,	33911,	31220,	64245,	17176,	43586,	30999,	//80-89
12761,	42338,	62682,	7424,	6981,	36057,	63189,	4897,	52723,	61279,	//90-99
};

static unsigned char Coils[] = {
		0b110011,	0b101111,	0b10001100,	0b10001010,	0b100011,	0b10110,	0b1011011,	0b10001110,	0b11101011,	0b1001111,		//0-9
		0b0,		0b11101001,	0b10011011,	0b11001111,	0b1001101,	0b100110,	0b10001101,	0b11010111,	0b10011010,	0b11001101,		//10-19
		0b11011011,	0b100010,	0b1111001,	0b1111100,	0b1001101,	0b10000011,	0b1010110,	0b10000001,	0b11011110,	0b11110110,		//20-29
		0b1110111,	0b111010,	0b1111111,	0b100101,	0b11111110,	0b1,		0b101,		0b1100100,	0b10110011,	0b10010000,		//30-39
		0b11010110,	0b10110,	0b1110101,	0b1011101,	0b1011010,	0b11100,	0b11010110,	0b1111011,	0b10011110,0b11111010		//40-49
};

static unsigned char DiscreteInputs[] = {
		0b00110011,	0b00101111,	0b10001100,	0b10001010,	0b00100011,	0b00010110,	0b01011011,	0b10001110,	0b11101011,	0b01001111,		//0-9
		0b00000000,	0b11101001,	0b10011011,	0b11001111,	0b01001101,	0b00100110,	0b10001101,	0b11010111,	0b10011010,	0b11001101,		//10-19
		0b11011011,	0b0100010,	0b01111001,	0b01111100,	0b01001101,	0b10000011,	0b01010110,	0b10000001,	0b11011110,	0b11110110,		//20-29
		0b01110111,	0b0111010,	0b01111111,	0b00100101,	0b11111110,	0b00000001,	0b00000101,	0b01100100,	0b10110011,	0b10010000,		//30-39
		0b11010110,	0b0010110,	0b01110101,	0b01011101,	0b01011010,	0b00011100,	0b11010110,	0b01111011,	0b10011110, 0b11111010		//40-49
};

unsigned short CRC16 (volatile unsigned char *puchMsg, unsigned short usDataLen );
unsigned int MBRegisterCount(void);
void AppendDatatoMBRegister(unsigned int StAddr,unsigned int count, unsigned int *inreg, volatile unsigned char *outreg);
unsigned int MBStartAddress(void);
void MBSendData(unsigned char count);
void AppendCRCtoMBRegister(unsigned char packtop);
void MBException(unsigned char exceptionCode);
void MBProcessRegisters(unsigned int *InArr, unsigned int InArrSize);
void MBProcessBits(unsigned char *InArr, unsigned int InArrSize);
void AppendBitsToRegisters(unsigned int StAddr, unsigned int count, unsigned char *inreg, volatile unsigned char *outreg);

#endif /* MODBUSRTU_SLAVE_INC_MODBUSRS232SLAVE_H_ */
