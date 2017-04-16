//
// Created by Deva on 2017/3/27.
//

#ifndef VIRTUALARM_VIRTUALMACHINE_H
#define VIRTUALARM_VIRTUALMACHINE_H

#include <cstring>
#include <string>
#include <iostream>
#include <map>
#include "Instruction.h"
#include "Loop.h"

using namespace std;

#define MAX_INSTRUCTION_COUNT 110010
#ifndef MAX_REGISTER_COUNT
#define MAX_REGISTER_COUNT 32
#endif
#define MAX_FUNCTION_COUNT 36

#define MAX_MEMORY_LEN 0xFFFF

#define MAX_JUMP_COUNT 1000000

#define MAX_BLOCK_COUNT 10010

#define MAX_LOOP_COUNT 30

class VirtualMachine;

enum {
    _NUM = 0x00,
    _REG = 0x01,
    _LABEL = 0x02
};

typedef void (VirtualMachine::*vmpf)(int *ops); // 指向操作函数
// http://stackoverflow.com/a/1485990/5493775

class VirtualMachine {
public:
    VirtualMachine();

    void readAnInstruction(string instructionLine);

    void readAMemory(string memoryLine);

    void setOutputFile(int argc, char **argv);

    void run();

    static void initCodeToFunctionArray();

    unsigned int usedReg; // 32位，标记用过的寄存器 if( usedReg & (1 << regID) ) ...

    int getICount() const;

    Instruction instructions[MAX_INSTRUCTION_COUNT]; // 存储所有指令

    int getJumpTarget(Instruction& ins, int curAddr); // 获取一个跳转指令的跳转目标下标

    Loop loops[MAX_LOOP_COUNT];

    int loopCount;

    int currentLoop[MAX_INSTRUCTION_COUNT]; // 标记当前指令对应的循环入口，为0说明当前指令不是循环入口
    int outLoop[MAX_INSTRUCTION_COUNT]; // 标记当前指令对应的循环出口，为0说明当前指令不是循环出口
private:
    // 指令计数器
    int EIP; // 指令寄存器
    int R[MAX_REGISTER_COUNT]; // 存储寄存器

    int iCount;

    map<string, int> labelToID; // 把label转成ID
    int labelCount;
    int idToIndex[MAX_INSTRUCTION_COUNT]; // 把ID转成下标

    map<unsigned int, unsigned char> memory2;
    unsigned char memory[MAX_MEMORY_LEN + 10];

    char outputFilename[256];

    static vmpf codeToFunction[MAX_FUNCTION_COUNT];

    void doSUB(int *ops);

    void doBNEZ(int *ops);

    void doJR(int *ops);

    void doSLTI(int *ops);

    void doBEQZ(int *ops);

    void doSLE(int *ops);

    void doANDI(int *ops);

    void doSEQ(int *ops);

    void doSGT(int *ops);

    void doSGEI(int *ops);

    void doLW(int *ops);

    void doSGE(int *ops);

    void doSLEI(int *ops);

    void doXOR(int *ops);

    void doHALT(int *ops);

    void doSGTI(int *ops);

    void doSLT(int *ops);

    void doADD(int *ops);

    void doXORI(int *ops);

    void doLB(int *ops);

    void doSUBI(int *ops);

    void doAND(int *ops);

    void doSEQI(int *ops);

    void doSNE(int *ops);

    void doSRLI(int *ops);

    void doSW(int *ops);

    void doSNEI(int *ops);

    void doSLLI(int *ops);

    void doORI(int *ops);

    void doSB(int *ops);

    void doOR(int *ops);

    void doADDI(int *ops);

    void doOP(int *ops);

    void addLabel(string labelHead);

    int loadMemory(unsigned int address);

    void storeMemory(unsigned int address, int value);

    string convertLabelInstruction(const string &realInstruction, int &labelFlag);
    // 将带有label的指令转换为带有数字的指令，labelPos对于JR是1， 对于BNEZ是2

    bool checkReg(const string &s);

    bool checkNum(const string &s);

    int regToRegID(const string &reg);

    int labelToSaveID(const string &label);

};


#endif //VIRTUALARM_VIRTUALMACHINE_H
