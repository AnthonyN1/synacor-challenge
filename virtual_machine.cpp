/*
	Synacor Challenge
	Author: Anthony Nool (AnthonyN1)
	Virtual Machine Implementation
*/

#include <cstdint>
#include <stdexcept>

#include "parser.h"
#include "virtual_machine.h"


/**
 * Constructs a new VirtualMachine object from the name of the input binary file.
 *
 * @param filename  The name of the binary file.
 * @return          None.
 * @throws          std::invalid_argument if the parser fails to read the file.
 *
 */
VirtualMachine::VirtualMachine(const char* filename){
	try{
		Parser::readBinaryFile(filename, memory_);
	} catch(const std::invalid_argument &e){
		throw;
	}

	programCounter_ = 0;
	stackSize_ = MIN_STACK_SIZE;
	stack_ = new uint16_t[stackSize_];
}

/**
 * Copies the fields of a VirtualMachine object to a new object.
 * 
 * @param vm  The VirtualMachine object to copy from.
 * @return    None.
 * @throws    None.
 *
 */
VirtualMachine::VirtualMachine(const VirtualMachine &vm) noexcept {
	copy(vm);
}

/**
 * Sets the current object equal to the VirtualMachine vm.
 *
 * @param vm  The VirtualMachine object to copy from.
 * @return    The current object.
 * @throws    None.
 *
 */
VirtualMachine & VirtualMachine::operator=(const VirtualMachine &vm) noexcept {
	if(this != &vm){
		delete [] stack_;
		copy(vm);
	}

	return *this;
}

/**
 * Deletes and dynamically-allocated memory stored in this object.
 *
 * @return  None.
 * @throws  None.
 *
 */
VirtualMachine::~VirtualMachine() noexcept {
	delete [] stack_;
}


/**
 * Copies the fields of a VirtualMachine object to the current object.
 *
 * @param vm  The VirtualMachine object to copy from.
 * @return    None.
 * @throws    None.
 *
 */
void VirtualMachine::copy(const VirtualMachine &vm) noexcept {
	programCounter_ = vm.programCounter_;
	for(unsigned int i = 0; i < MEMORY_SIZE; ++i) memory_[i] = vm.memory_[i];
	for(unsigned int i = 0; i < NUM_REGISTERS; ++i) registers_[i] = vm.registers_[i];
	stackSize_ = vm.stackSize_;
	stack_ = new uint16_t[stackSize_];
	for(unsigned int i = 0; i < stackSize_; ++i) stack_[i] = vm.stack_[i];
}
