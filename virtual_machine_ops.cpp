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
			// Opcode 0: stops execution and terminates the program.
			case 0: std::cout << "Program terminating..." << std::endl; exit(0);
			// Opcode 1: sets register <a> to the value of <b>.
			case 1: setReg(1, getValueAt(2)); programCounter_ += 3; break;
			// Opcode 2: pushes <a> onto the stack.
			case 2: push(getValueAt(1)); programCounter_ += 2; break;
			// Opcode 3: removes the top element from the stack and writes it into <a>.
			case 3: setReg(1, pop()); programCounter_ += 2; break;
			// Opcode 4: sets <a> to 1 if <b> is equal to <c>, 0 otherwise.
			case 4: setReg(1, (getValueAt(2) == getValueAt(3)) ? 1 : 0); programCounter_ += 4; break;
			// Opcode 5: sets <a> to 1 if <b> is greater than <c>, 0 otherwise.
			case 5: setReg(1, (getValueAt(2) > getValueAt(3)) ? 1 : 0); programCounter_ += 4; break;
			// Opcode 6: jumps to <a>.
			case 6: programCounter_ = getValueAt(1); break;
			// Opcode 7: if <a> is nonzero, jumps to <b>.
			case 7: if(getValueAt(1) != 0){ programCounter_ = getValueAt(2); } else{ programCounter_ += 3; } break;
			// Opcode 8: if <a> is zero, jumps to <b>.
			case 8: if(getValueAt(1) == 0){ programCounter_ = getValueAt(2); } else{ programCounter_ += 3; } break;
			// Opcode 9: stores into <a> the sum of <b> and <c>.
			case 9: setReg(1, (getValueAt(2) + getValueAt(3)) % START_REG); programCounter_ += 4; break;
			// Opcode 10: stores into <a> the product of <b> and <c>.
			case 10: setReg(1, (getValueAt(2) * getValueAt(3)) % START_REG); programCounter_ += 4; break;
			// Opcode 11: stores into <a> the remainder of <b> divided by <c>.
			case 11: setReg(1, getValueAt(2) % getValueAt(3)); programCounter_ += 4; break;
			// Opcode 12: stores into <a> the bitwise AND of <b> and <c>.
			case 12: setReg(1, getValueAt(2) & getValueAt(3)); programCounter_ += 4; break;
			// Opcode 13: stores into <a> the bitwise OR of <b> and <c>.
			case 13: setReg(1, getValueAt(2) | getValueAt(3)); programCounter_ += 4; break;
			// Opcode 14: stores into <a> the bitwise NOT of <b>.
			case 14: setReg(1, (~getValueAt(2)) % START_REG); programCounter_ += 3; break;
			// Opcode 15: stores into <a> the value at memory address <b>.
			case 15: setReg(1, (memory_[getValueAt(2)]) % START_REG); programCounter_ += 3; break;
			// Opcode 16: writes the value from <b> to memory address <a>.
			case 16: memory_[getValueAt(1)] = getValueAt(2); programCounter_ += 3; break;
			// Opcode 17: writes the address of the next instruction to the stack, and jumps to <a>.
			case 17: push(programCounter_ + 2); programCounter_ = getValueAt(1); break;
			// Opcode 18: removes the top element from the stack and jumps to it.
			case 18: programCounter_ = pop(); break;
			// Opcode 19: outputs the character represented by ASCII code <a>.
			case 19: std::cout << char(getValueAt(1)); programCounter_ += 2; break;
			case 20:
				break;
			// Opcode 21: no operation.
			case 21: programCounter_ += 1; break;
			default: throw std::runtime_error("VM: unable to parse instruction.");
		}
	}
}


/**
 * Gets the value stored at the memory address using the program counter offset.
 * Returns either the literal value, or the value in the register.
 *
 * @param pcOffset  The program counter positive offset.
 * @return          Either the literal value of the value at the memory address, or the value stored in the register.
 *
 */
uint16_t VirtualMachine::getValueAt(unsigned pcOffset) const noexcept {
	uint16_t val = memory_[programCounter_ + pcOffset];
	return (val < START_REG) ? val : registers_[val - START_REG];
}


/**
 * Sets the value of the register stored at the memory address using the program counter offset to val.
 *
 * @param pcOffset  The program counter positive offset.
 * @param val       The value to write.
 *
 */
void VirtualMachine::setReg(unsigned int pcOffset, uint16_t val) noexcept {
	unsigned int regIdx = memory_[programCounter_ + pcOffset] - START_REG;
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
 * @throws  std::out_of_range if the stack is empty.
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
