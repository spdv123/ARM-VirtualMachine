//
// Created by Deva on 2017/3/20.
//

#include <iostream>
#include "Instruction.h"

map<string, char> Instruction::instructionCode;
// http://stackoverflow.com/questions/9282354/static-variable-link-error

void Instruction::readInstruction(string &buffer, int labelFlag) {
    //cout << "[" << buffer << "]" << endl;
    // 此处实现根据buffer读入指令
    vector<string> tokens = splitWithSpace(buffer);

    command = instructionCode[tokens[0]];
    int opNum = tokens.size();
    for(int i=1; i<opNum; i++){
        const char * buf = tokens[i].c_str();
        if(buf[0] == 'R'){
            sscanf(buf, "R%d", &ops[i-1]);
        }else{
            sscanf(buf, "%d", &ops[i-1]);
        }
    }
    ops[3] = opNum - 1;
    ops[4] = labelFlag;
}

void Instruction::initCode() {
    instructionCode["SUB"] = _SUB;
    instructionCode["BNEZ"] = _BNEZ;
    instructionCode["JR"] = _JR;
    instructionCode["SLTI"] = _SLTI;
    instructionCode["BEQZ"] = _BEQZ;
    instructionCode["SLE"] = _SLE;
    instructionCode["ANDI"] = _ANDI;
    instructionCode["SEQ"] = _SEQ;
    instructionCode["SGT"] = _SGT;
    instructionCode["SGEI"] = _SGEI;
    instructionCode["LW"] = _LW;
    instructionCode["SGE"] = _SGE;
    instructionCode["SLEI"] = _SLEI;
    instructionCode["XOR"] = _XOR;
    instructionCode["HALT"] = _HALT;
    instructionCode["SGTI"] = _SGTI;
    instructionCode["SLT"] = _SLT;
    instructionCode["ADD"] = _ADD;
    instructionCode["XORI"] = _XORI;
    instructionCode["LB"] = _LB;
    instructionCode["SUBI"] = _SUBI;
    instructionCode["AND"] = _AND;
    instructionCode["SEQI"] = _SEQI;
    instructionCode["SNE"] = _SNE;
    instructionCode["SRLI"] = _SRLI;
    instructionCode["SW"] = _SW;
    instructionCode["SNEI"] = _SNEI;
    instructionCode["SLLI"] = _SLLI;
    instructionCode["ORI"] = _ORI;
    instructionCode["SB"] = _SB;
    instructionCode["OR"] = _OR;
    instructionCode["ADDI"] = _ADDI;
    instructionCode["OP"] = _OP;
}

Instruction::Instruction() {
    isNeedExec = false;
}

vector<string> Instruction::splitWithSpace(const string &sentence) {
    istringstream iss(sentence);

    vector<string> tokens;
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(tokens));

    return tokens;
}

void Instruction::testOutput() {
    printf("%d: ", command);
    for(int i=0;i<3;i++) cout << ops[i] << " ";
    cout << endl;
}