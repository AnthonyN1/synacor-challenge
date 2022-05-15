/*
	Synacor Challenge
	Author: Anthony Nool (AnthonyN1)
	Virtual Machine Operations Implementation
*/

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "virtual_machine.h"


/**
 * Starts the program within the virtual machine, executing its instructions.
 *
 * @throws  std::exception if an invalid instruction is executed. See "arch-spec" for details.
 *
 */
void VirtualMachine::start(){
	while(programCounter_ < MEMORY_SIZE){
		switch(memory_[programCounter_]){
			case 0: stopExecution(); break;
			case 1: setReg(memory_[programCounter_ + 1] - START_REG, getValue(memory_[programCounter_ + 2])); programCounter_ += 3; break;
			case 2: push(getValue(memory_[programCounter_ + 1])); programCounter_ += 2; break;
			case 3: setReg(memory_[programCounter_ + 1] - START_REG, getValue(pop())); programCounter_ += 2; break;
			case 4: setReg(memory_[programCounter_ + 1] - START_REG, (getValue(memory_[programCounter_ + 2]) == getValue(memory_[programCounter_ + 3])) ? 1 : 0); programCounter_ += 4; break;
			case 5: setReg(memory_[programCounter_ + 1] - START_REG, (getValue(memory_[programCounter_ + 2]) > getValue(memory_[programCounter_ + 3])) ? 1 : 0); programCounter_ += 4; break;
			case 6: programCounter_ = getValue(memory_[programCounter_ + 1]); break;
			case 7: if(getValue(memory_[programCounter_ + 1]) != 0){ programCounter_ = getValue(memory_[programCounter_ + 2]); } else{ programCounter_ += 3; } break;
			case 8: if(getValue(memory_[programCounter_ + 1]) == 0){ programCounter_ = getValue(memory_[programCounter_ + 2]); } else{ programCounter_ += 3; } break;
			case 9: setReg(memory_[programCounter_ + 1] - START_REG, (getValue(memory_[programCounter_ + 2]) + getValue(memory_[programCounter_ + 3])) % START_REG); programCounter_ += 4; break;
			case 10: setReg(memory_[programCounter_ + 1] - START_REG, (getValue(memory_[programCounter_ + 2]) * getValue(memory_[programCounter_ + 3])) % START_REG); programCounter_ += 4; break;
			case 11: setReg(memory_[programCounter_ + 1] - START_REG, (getValue(memory_[programCounter_ + 2]) % getValue(memory_[programCounter_ + 3])) % START_REG); programCounter_ += 4; break;
			case 12: setReg(memory_[programCounter_ + 1] - START_REG, (getValue(memory_[programCounter_ + 2]) & getValue(memory_[programCounter_ + 3])) % START_REG); programCounter_ += 4; break;
			case 13: setReg(memory_[programCounter_ + 1] - START_REG, (getValue(memory_[programCounter_ + 2]) | getValue(memory_[programCounter_ + 3])) % START_REG); programCounter_ += 4; break;
			case 14: setReg(memory_[programCounter_ + 1] - START_REG, (~getValue(memory_[programCounter_ + 2])) % START_REG); programCounter_ += 3; break;
			case 15: setReg(memory_[programCounter_ + 1] - START_REG, (memory_[getValue(memory_[programCounter_ + 2])]) % START_REG); programCounter_ += 3; break;
			case 16: writeMem(getValue(memory_[programCounter_ + 1]), getValue(memory_[programCounter_ + 2])); programCounter_ += 3; break;
			case 17: push(programCounter_ + 2); programCounter_ = getValue(memory_[programCounter_ + 1]); break;
			case 18: programCounter_ = getValue(pop()); break;
			case 19: outputASCII(getValue(memory_[programCounter_ + 1])); programCounter_ += 2; break;
			case 20:
				break;
			case 21: programCounter_ += 1; break;
			default: throw std::runtime_error("VM: unable to parse instruction.");
		}
	}
}


/**
 *
 * @param val  The literal or register.
 * @return     Either the literal value of val, or the value stored in the register val.
 * 
 */
uint16_t VirtualMachine::getValue(uint16_t val) const noexcept {
	return (val < START_REG) ? val : registers_[val - START_REG];
}


/**
 * Stops execution, and terminates the program.
 *
 */
void VirtualMachine::stopExecution() const noexcept {
	std::cout << "Program terminating..." << std::endl;
	exit(0);
}

/**
 * Sets the value of the register at regIdx to val.
 *
 * @param regIdx  The index of the register.
 * @param val     The value to write.
 *
 */
void VirtualMachine::setReg(unsigned int regIdx, uint16_t val) noexcept {
	registers_[regIdx] = val;
}

/**
 * Pushes val onto the stack.
 *
 * @param val  The value to push.
 *
 */
void VirtualMachine::push(uint16_t val) noexcept {
	stack_.push_back(val);
}

/**
 * Pops the top value off of the stack.
 *
 * @throws        std::out_of_range if the stack is empty.
 *
 */
uint16_t VirtualMachine::pop(){
	if(stack_.empty()){
		throw std::out_of_range("VM: attempted to pop an empty stack.");
	}

	uint16_t val = stack_.back();
	stack_.pop_back();
	return val;
}

/**
 * Sets the value of the memory address memIdx to val.
 * 
 * @param memIdx  The index of the memory space.
 * @param val     The value to write.
 * 
 */
void VirtualMachine::writeMem(unsigned int memIdx, uint16_t val) noexcept {
	memory_[memIdx] = val;
}





/**
 * Outputs the character represented by ASCII code val.
 *
 * @param val  The ASCII code of the character to output.
 *
 */
void VirtualMachine::outputASCII(uint16_t val) const noexcept {
	std::cout << char(val);
}
