//
// Created by Deva on 2017/3/20.
//

#ifndef VIRTUALARM_INSTRUCTION_H
#define VIRTUALARM_INSTRUCTION_H

#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;

enum {
    _SUB = 0x01,
    _BNEZ,
    _JR,
    _SLTI,
    _BEQZ,
    _SLE,
    _ANDI,
    _SEQ,
    _SGT,
    _SGEI,
    _LW,
    _SGE,
    _SLEI,
    _XOR,
    _HALT,
    _SGTI,
    _SLT,
    _ADD,
    _XORI,
    _LB,
    _SUBI,
    _AND,
    _SEQI,
    _SNE,
    _SRLI,
    _SW,
    _SNEI,
    _SLLI,
    _ORI,
    _SB,
    _OR,
    _ADDI,
    _OP
};

class Instruction {
public:
    Instruction();

    void readInstruction(string &buffer, int labelFlag=0);

    static void initCode(); // 初始化指令转换表

    void testOutput();

    char command; // 尽可能压缩空间，因为只有33种指令要处理
    int ops[5]; // ops[3] 是opNum ops[4] 是标志位

    bool isNeedExec;

private:

    static map<string, char> instructionCode; // 将指令转换表定义为静态成员变量

    vector<string> splitWithSpace(const string &sentence);
};


#endif //VIRTUALARM_INSTRUCTION_H
