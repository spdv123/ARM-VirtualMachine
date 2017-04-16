//
// Created by Deva on 2017/3/30.
//

#ifndef VIRTUALARM_SCANNER_H
#define VIRTUALARM_SCANNER_H


#include "VirtualMachine.h"

class Scanner;
typedef void (Scanner::*scpf)(Instruction& ins); // 指向操作函数

class Scanner {
public:
    void setVm(VirtualMachine *vm);

    static void initCodeToFunctionArray();

    void optimize();
private:
    VirtualMachine * vm;

    unsigned int usedReg;

    int EIP;

    bool firstScan;

    static scpf codeToFunction[MAX_FUNCTION_COUNT];

    void doSUB(Instruction& ins);

    void doBNEZ(Instruction& ins);

    void doJR(Instruction& ins);

    void doSLTI(Instruction& ins);

    void doBEQZ(Instruction& ins);

    void doSLE(Instruction& ins);

    void doANDI(Instruction& ins);

    void doSEQ(Instruction& ins);

    void doSGT(Instruction& ins);

    void doSGEI(Instruction& ins);

    void doLW(Instruction& ins);

    void doSGE(Instruction& ins);

    void doSLEI(Instruction& ins);

    void doXOR(Instruction& ins);

    void doHALT(Instruction& ins);

    void doSGTI(Instruction& ins);

    void doSLT(Instruction& ins);

    void doADD(Instruction& ins);

    void doXORI(Instruction& ins);

    void doLB(Instruction& ins);

    void doSUBI(Instruction& ins);

    void doAND(Instruction& ins);

    void doSEQI(Instruction& ins);

    void doSNE(Instruction& ins);

    void doSRLI(Instruction& ins);

    void doSW(Instruction& ins);

    void doSNEI(Instruction& ins);

    void doSLLI(Instruction& ins);

    void doORI(Instruction& ins);

    void doSB(Instruction& ins);

    void doOR(Instruction& ins);

    void doADDI(Instruction& ins);

    void doOP(Instruction& ins);

    void addALoop(int start, int destination);
};


#endif //VIRTUALARM_SCANNER_H
