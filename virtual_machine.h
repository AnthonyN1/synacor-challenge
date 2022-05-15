/*
	Synacor Challenge
	Author: Anthony Nool (AnthonyN1)
	Virtual Machine Header
*/

#ifndef __virtual_machine_h_
#define __virtual_machine_h_

#include <cstdint>
#include <vector>

const unsigned int MEMORY_SIZE = (1 << 15);
const unsigned int NUM_REGISTERS = 8;
const unsigned int START_REG = 32768;


/**
 * This class represents a virtual machine that can run a binary file with a strict instruction set.
 * See "arch-spec" for more information.
 *
 */
class VirtualMachine{
	public:
		VirtualMachine(const char* filename);
		VirtualMachine(const VirtualMachine &vm) noexcept;
		VirtualMachine & operator=(const VirtualMachine &vm) noexcept;

		void start();
	private:
		void copy(const VirtualMachine &vm) noexcept;

		uint16_t getValue(uint16_t val) const noexcept;

		void stopExecution() const noexcept;
		void setReg(unsigned int regIdx, uint16_t val) noexcept;
		void push(uint16_t val) noexcept;
		uint16_t pop();
		void writeMem(unsigned int memIdx, uint16_t val) noexcept;
		void outputASCII(uint16_t val) const noexcept;


		unsigned int programCounter_ = 0;          /** The memory index of the current instruction. */

		uint16_t memory_[MEMORY_SIZE] = {0};       /** The program's instructions stored as 16-bit values. */
		uint16_t registers_[NUM_REGISTERS] = {0};  /** The registers allocated for the program. */

		std::vector<uint16_t> stack_;              /** The unbound stack allocated for the program. */
};


#endif
