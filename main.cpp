/*
	Synacor Challenge
	Author: Anthony Nool (AnthonyN1)
	Main
*/

#include <cstdint>
#include <iostream>
#include <stdexcept>

#include "parser.h"

const unsigned int MEMORY_SIZE = (1 << 15);


int main(int argc, char** argv){
	// Checks the command-line arguments.
	if(argc != 2){
		std::cerr << "Error: incorrect command-line arguments.\n"
		          << "Usage: ./challenge.exe <binary file name>\n"
				  << "Exiting..." << std::endl;
		return 1;
	}

	// Reads the program into memory.
	uint16_t memory[MEMORY_SIZE];
	try{
		Parser::readBinaryFile(argv[1], memory);
	} catch(const std::invalid_argument &e){
		std::cerr << e.what() << std::endl;
		return 1;
	}

	for(unsigned int i = 0; i < MEMORY_SIZE; ++i){
		std::cout << memory[i] << "\n";
	}
	std::cout << std::endl;
	
	return 0;
}
