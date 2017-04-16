build:
	g++ main.cpp Instruction.h MyInput.h VirtualMachine.h Scanner.h Instruction.cpp MyInput.cpp VirtualMachine.cpp Scanner.cpp -o VirtualMachine -std=c++11 -O3

clean:
	rm -f VirtualMachine
