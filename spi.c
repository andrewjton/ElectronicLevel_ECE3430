#include "spi.h"

void InitializeSPI()
{	
	SET_USCIA0_MISO_AS_AN_INPUT;
	SET_USCIA0_MOSI_AS_AN_OUTPUT;
	SET_SPI_SCK_AS_AN_OUTPUT;
}

void SPISendByte(unsigned char SendValue)
{
	USCIA0_MOSI_PORT &= ~(USCIA0_MOSI_BIT); // initialize pin to low?

	int i;
	for(i = 0; i < 8; i++)
	{
		if((SendValue & 0b10000000) > 0) // Get the MSB, if 1, set pin high
		{
			USCIA0_MOSI_PORT |= USCIA0_MOSI_BIT;
		}
		else
		{
			USCIA0_MOSI_PORT &= ~(USCIA0_MOSI_BIT); //set pin to low
		}
		SendValue = SendValue << 1;

		RISE_SCK;
		FALL_SCK;

	}

	USCIA0_MOSI_PORT &= ~(USCIA0_MOSI_BIT); // leave pin low?
}

unsigned char SPIReceiveByte() //SO is driven after falling edge of clock
{
	unsigned char receivedValue = 0;
	unsigned char SPI_bit = 0;
	int i = 0;
	for (i = 0; i < 8; i++)
	{
		receivedValue = receivedValue << 1; // ready to add on the next bit

		SPI_bit = ((USCIA0_MISO_PORT >> 1) & 0x01); // Bit value is stored in Bit 1
		receivedValue |= SPI_bit;

		RISE_SCK;
		FALL_SCK;
	}
	return receivedValue;
}
