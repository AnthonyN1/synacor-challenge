/*
	Synacor Challenge
	Author: Anthony Nool (AnthonyN1)
	Parser Header
*/

#ifndef __parser_h_
#define __parser_h_

#include <cstdint>


class Parser{
	public:
		static void readBinaryFile(const char* filename, uint16_t* memory);
	private:
		static uint16_t getValue(uint8_t* bytes) noexcept;
};


#endif
