/*
	Synacor Challenge
	Author: Anthony Nool (AnthonyN1)
	Parser Implementation
*/

#include <cstdint>
#include <cstdio>
#include <iostream>
#include <stdexcept>

#include "parser.h"


/**
 * Reads a binary file, and stores 16-bit values into an array.
 * Binary file requirements:
 * - Contains 16-bit little-endian values.
 * - Has at most 2^15 (32,768) values. 
 *
 * @param filename  The name of the binary file.
 * @param memory    A pointer to a memory space for 16-bit values. Requires the array to be a 15-bit address space.
 * @return          None.
 * @throws          std::invalid_argument if filename is not the name of a file matching the above requirements.
 *
 */
void Parser::readBinaryFile(const char* filename, uint16_t* memory){
	// Opens the binary file.
	FILE* file = fopen(filename, "rb");
	if(file == nullptr) throw std::invalid_argument("Parser: file unable to be opened.");

	// Gets the size of the file (in bytes).
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	rewind(file);

	if(size % 2 != 0) throw std::invalid_argument("Parser: file does not contain 16-bit values.");
	if(size > (1 << 15) * 2) throw std::invalid_argument("Parser: file exceeds the maximum number of values.");

	// Reads in the values from the file into memory.
	unsigned int offset = 0;
	uint8_t bytes[2];

	while(fread(bytes, 2, 1, file) == 1){
		memory[offset] = getValue(bytes);
		++offset;
	}

	// Closes the file.
	fclose(file);
}


/**
 * Converts a little-endian 16-bit value to big-endian.
 *
 * If the big-endian value is invalid (32776..65535), returns 0.
 *
 * @param bytes  A pointer to a byte array of size 2.
 * @return       A big-endian 2-byte value.
 * @throws       None.
 *
 */
uint16_t Parser::getValue(uint8_t* bytes) noexcept {
	uint16_t val = bytes[0] | (bytes[1] << 8);

	if(val > 32775){
		std::cerr << "Warning: encountered invalid value while reading file. Defaulting to 0." << std::endl;
		val = 0;
	}

	return val;
}
