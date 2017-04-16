//
// Created by Deva on 2017/3/30.
//

#include "Scanner.h"

scpf Scanner::codeToFunction[MAX_FUNCTION_COUNT];

void Scanner::setVm(VirtualMachine *vm) {
    Scanner::vm = vm;
}

void Scanner::initCodeToFunctionArray() {
    memset(codeToFunction, 0, sizeof(codeToFunction));
    codeToFunction[_SUB] = &Scanner::doSUB;
    codeToFunction[_BNEZ] = &Scanner::doBNEZ;
    codeToFunction[_JR] = &Scanner::doJR;
    codeToFunction[_SLTI] = &Scanner::doSLTI;
    codeToFunction[_BEQZ] = &Scanner::doBEQZ;
    codeToFunction[_SLE] = &Scanner::doSLE;
    codeToFunction[_ANDI] = &Scanner::doANDI;
    codeToFunction[_SEQ] = &Scanner::doSEQ;
    codeToFunction[_SGT] = &Scanner::doSGT;
    codeToFunction[_SGEI] = &Scanner::doSGEI;
    codeToFunction[_LW] = &Scanner::doLW;
    codeToFunction[_SGE] = &Scanner::doSGE;
    codeToFunction[_SLEI] = &Scanner::doSLEI;
    codeToFunction[_XOR] = &Scanner::doXOR;
    codeToFunction[_HALT] = &Scanner::doHALT;
    codeToFunction[_SGTI] = &Scanner::doSGTI;
    codeToFunction[_SLT] = &Scanner::doSLT;
    codeToFunction[_ADD] = &Scanner::doADD;
    codeToFunction[_XORI] = &Scanner::doXORI;
    codeToFunction[_LB] = &Scanner::doLB;
    codeToFunction[_SUBI] = &Scanner::doSUBI;
    codeToFunction[_AND] = &Scanner::doAND;
    codeToFunction[_SEQI] = &Scanner::doSEQI;
    codeToFunction[_SNE] = &Scanner::doSNE;
    codeToFunction[_SRLI] = &Scanner::doSRLI;
    codeToFunction[_SW] = &Scanner::doSW;
    codeToFunction[_SNEI] = &Scanner::doSNEI;
    codeToFunction[_SLLI] = &Scanner::doSLLI;
    codeToFunction[_ORI] = &Scanner::doORI;
    codeToFunction[_SB] = &Scanner::doSB;
    codeToFunction[_OR] = &Scanner::doOR;
    codeToFunction[_ADDI] = &Scanner::doADDI;
    codeToFunction[_OP] = &Scanner::doOP;
}

void Scanner::doSUB(Instruction &ins) {
    doADD(ins);
}

void Scanner::doSLTI(Instruction &ins) {
    doADDI(ins);
}

void Scanner::doSLE(Instruction &ins) {
    doADD(ins);
}

void Scanner::doANDI(Instruction &ins) {
    doADDI(ins);
}

void Scanner::doSEQ(Instruction &ins) {
    doADD(ins);
}

void Scanner::doSGT(Instruction &ins) {
    doADD(ins);
}

void Scanner::doSGEI(Instruction &ins) {
    doADDI(ins);
}

void Scanner::doLW(Instruction &ins) {
    // well, memory operation is hard to determine
    doADDI(ins);
}

void Scanner::doSGE(Instruction &ins) {
    doADD(ins);
}

void Scanner::doSLEI(Instruction &ins) {
    doADDI(ins);
}

void Scanner::doXOR(Instruction &ins) {
    doADD(ins);
}

void Scanner::doHALT(Instruction &ins) {

}

void Scanner::doSGTI(Instruction &ins) {
    doADDI(ins);
}

void Scanner::doSLT(Instruction &ins) {
    doADD(ins);
}

void Scanner::doXORI(Instruction &ins) {
    doADDI(ins);
}

void Scanner::doLB(Instruction &ins) {
    doADDI(ins);
}

void Scanner::doSUBI(Instruction &ins) {
    doADDI(ins);
}

void Scanner::doAND(Instruction &ins) {
    doADD(ins);
}

void Scanner::doSEQI(Instruction &ins) {
    doADDI(ins);
}

void Scanner::doSNE(Instruction &ins) {
    doADD(ins);
}

void Scanner::doSRLI(Instruction &ins) {
    doADDI(ins);
}

void Scanner::doSW(Instruction &ins) {
    doADDI(ins);
}

void Scanner::doSNEI(Instruction &ins) {
    doADDI(ins);
}

void Scanner::doSLLI(Instruction &ins) {
    doADDI(ins);
}

void Scanner::doORI(Instruction &ins) {
    doADDI(ins);
}

void Scanner::doSB(Instruction &ins) {
    doADDI(ins);
}

void Scanner::doOR(Instruction &ins) {
    doADD(ins);
}

void Scanner::doADD(Instruction &ins) {
    if ((usedReg & (1 << ins.ops[0])) != 0) {
        ins.isNeedExec = true;
        usedReg |= (1 << ins.ops[1]);
        usedReg |= (1 << ins.ops[2]);
    }
}

void Scanner::doADDI(Instruction &ins) {
    if ((usedReg & (1 << ins.ops[0])) != 0) {
        ins.isNeedExec = true;
        usedReg |= (1 << ins.ops[1]);
    }
}

void Scanner::doBNEZ(Instruction &ins) {
    if (ins.isNeedExec) {
        usedReg |= (1 << ins.ops[0]);
    }
}

void Scanner::doBEQZ(Instruction &ins) {
    doBNEZ(ins);
}

void Scanner::doJR(Instruction &ins) {
    ins.isNeedExec = true;
    if (ins.ops[4] == _REG) {
        usedReg |= (1 << ins.ops[0]);
    }
}

void Scanner::doOP(Instruction &ins) {
    ins.isNeedExec = true;
    if (ins.ops[0]) {
        usedReg |= (1 << ins.ops[0]);
    }
}

void printBits(size_t const size, void const *const ptr) {
    unsigned char *b = (unsigned char *) ptr;
    unsigned char byte;
    int i, j;

    for (i = size - 1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

void Scanner::addALoop(int start, int destination) {
    int readRegs=0, writeRegs=0;
    for(int i=destination;i<=start;i++) {
        switch (vm->instructions[i].command) {
            case _SLE:
            case _SEQ:
            case _SGE:
            case _SLT:
            case _SGT:
            case _SNE:
            case _SUB:
            case _AND:
            case _OR:
            case _XOR:
            case _ADD:
                readRegs |= (1 << vm->instructions[i].ops[1]);
                readRegs |= (1 << vm->instructions[i].ops[2]);
                writeRegs |= (1 << vm->instructions[i].ops[0]);
                break;
            case _SLTI:
            case _SGEI:
            case _SGTI:
            case _SLEI:
            case _SEQI:
            case _SNEI:
            case _ANDI:
            case _ADDI:
            case _XORI:
            case _SUBI:
            case _SLLI:
            case _SRLI:
            case _ORI:
            case _LW:
            case _LB:
                readRegs |= (1 << vm->instructions[i].ops[1]);
                writeRegs |= (1 << vm->instructions[i].ops[0]);
                break;
            case _SW:
            case _SB:
                readRegs |= (1 << vm->instructions[i].ops[1]);
                readRegs |= (1 << vm->instructions[i].ops[0]);
                break;
            case _BNEZ:
            case _BEQZ:
                readRegs |= (1 << vm->instructions[i].ops[0]);
                break;
            case _JR:
                if (vm->instructions[i].ops[4] == _REG) {
                    readRegs |= (1 << vm->instructions[i].ops[0]);
                }
                break;
            case _OP:
                readRegs |= (1 << vm->instructions[i].ops[0]);
                break;
            default:
                break;
        }
    }

    vm->loops[vm->loopCount].readRegs = readRegs;
    vm->loops[vm->loopCount].writeRegs = writeRegs;

    vm->currentLoop[destination] = vm->loopCount;
    vm->outLoop[start + 1] = vm->loopCount;

    vm->loops[vm->loopCount].outAddress = start + 1;

    vm->loopCount ++;
}

void Scanner::optimize() {
    usedReg = 0;
    int saveUsedReg = -1;
    int iCount = vm->getICount();

    // 第一遍扫描，检测寄存器的使用状况
    firstScan = true;
    /*
    while (saveUsedReg != usedReg) {
        for (EIP = iCount - 1; EIP >= 0; EIP--) {
            (this->*codeToFunction[vm->instructions[EIP].command])(vm->instructions[EIP]);
        }
        saveUsedReg = usedReg;
    }
    */
    // TODO : 是否需要多次扫描
    for (EIP = iCount - 1; EIP >= 0; EIP--) {
        (this->*codeToFunction[vm->instructions[EIP].command])(vm->instructions[EIP]);
    }

    // 第二遍扫描，检测循环中是否出现需要执行的指令，如果出现则循环的跳转是需要执行的
    for (EIP = 0; EIP < iCount; EIP++) {
        char &command = (vm->instructions[EIP]).command;
        if (command == _BNEZ || command == _BEQZ) {
            int start = EIP;
            int destination = vm->getJumpTarget(vm->instructions[EIP], EIP);
            if (start > destination) {
                // Add a loop
                // 循环是从后跳到前边的
                addALoop(start, destination);

                swap(start, destination);
            }

            for (int i = start; i <= destination; i++) {
                if (vm->instructions[i].isNeedExec) {
                    vm->instructions[EIP].isNeedExec = true;
                    usedReg |= (1 << (vm->instructions[EIP]).ops[0]);
                    break;
                }
            }
        }
    }

    // 第三遍扫描，由于刚才的跳转指令使用的寄存器被加入usedReg，重新扫描一遍使用情况
    firstScan = false;
    for (EIP = iCount - 1; EIP >= 0; EIP--) {
        (this->*codeToFunction[vm->instructions[EIP].command])(vm->instructions[EIP]);
    }

    //printBits(sizeof(unsigned int), &usedReg);

    // 第四遍扫描，如果一个循环只有头和尾两条指令需要执行且尾部是BNEZ，那么跳出语句一定是判断了赋值语句中的寄存器是否为0
    // 因此直接把该寄存器赋值为0
    for (EIP = 0; EIP < iCount; EIP++) {
        char &command = (vm->instructions[EIP]).command;
        if (command == _BNEZ) {
            int start = EIP;
            int destination = vm->getJumpTarget(vm->instructions[EIP], EIP);
            if (start < destination) continue; // 如果往后跳，不是循环，不用考虑
            swap(start, destination);

            bool doNotPass = false;
            for (int i = start + 1; i <= destination - 1; i++) {
                if (vm->instructions[i].isNeedExec) {
                    doNotPass = true;
                    break;
                }
            }
            if (!doNotPass) {
                vm->instructions[EIP].isNeedExec = false;
                vm->instructions[start].command = _XOR;
                vm->instructions[start].ops[1] = 0;
                vm->instructions[start].ops[2] = 0;
            }
        }
    }
}
