## ARM Virtual Machine

Execute ARM assemble instructions such as

```s
addi r1 r0 30000;
addi r2 r0 0;
addi r3 r0 0;
addi r8 r0 0;
addi r9 r0 0;
addi r16 r0 0;
addi r14 r0 0;
loop:addi r5 r0 0;
	loop1: add r3 r1 r1;
		addi r5 r5 1;
		sle r6 r5 r1;
		bnez r6 loop1;
	addi r2 r2 1;
	sle r4 r2 r1;
	bnez r4 loop;
loop2:addi r10 r0 0;
	loop3: add r9 r1 r1;
		addi r10 r10 1;
		sle r11 r10 r1;
		bnez r11 loop3;
	addi r8 r8 1;
	sle r12 r8 r1;
	bnez r12 loop2;
addi r5 r5 0;
add r2 r2 r5;
add r10 r10 r2;
add r8 r8 r10;
op r8;
halt
```

### Compile

```sh
cmake
```

or

```sh
g++ main.cpp Instruction.cpp Instruction.h MyInput.cpp MyInput.h VirtualMachine.cpp VirtualMachine.h Scanner.cpp Scanner.h Loop.cpp Loop.h -o VirtualMachine -O3
```

### Execute

```sh
./VirtualMachine [-i InstructionsFile] [-m MemoryFile] [-o OutputFile]
```

### Examples

See testcases folder for more info.