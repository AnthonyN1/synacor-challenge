/*
	Synacor Challenge
	Author: Anthony Nool (AnthonyN1)
	Main
*/

#include <cstdint>
#include <iostream>
#include <stdexcept>

#include "virtual_machine.h"



int main(int argc, char** argv){
	// Checks the command-line arguments.
	if(argc != 2){
		std::cerr << "Error: incorrect command-line arguments.\n"
		          << "Usage: ./challenge.exe <binary file name>\n"
				  << "Exiting..." << std::endl;
		return 1;
	}

	// Creates a new VirtualMachine.
	try{
		VirtualMachine vm(argv[1]);
	} catch(const std::invalid_argument &e){
		std::cerr << e.what() << std::endl;
		return 1;
	}

	
	return 0;
}
