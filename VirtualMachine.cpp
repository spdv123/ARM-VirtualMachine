//
// Created by Deva on 2017/3/27.
//

#include "VirtualMachine.h"

#define MY_BUFFER_SIZE 30
// WARNING: check buffer size if signal 6 or 11

vmpf VirtualMachine::codeToFunction[MAX_FUNCTION_COUNT];

void VirtualMachine::readAnInstruction(std::string instructionLine) {
    // 这里接受一行，要做的事情是去掉label头传给Instruction类的读入处理，label头放在映射表中

    int len = instructionLine.length();
    int findFlag = 0;
    for (int i = 1; i < len; i++) {
        if (instructionLine[i] == ' ') break;
        if (instructionLine[i] == ':') {
            findFlag = i;
            break;
        }
    }
    string realInstruction;
    string labelHead;

    if (findFlag) {
        realInstruction = instructionLine.substr(findFlag + 1, len);
        labelHead = instructionLine.substr(0, findFlag);

        addLabel(labelHead);

        idToIndex[labelToID[labelHead]] = iCount;
    } else {
        realInstruction = instructionLine;
    }

    int labelFlag = 0;
    if (realInstruction[0] == 'J' || realInstruction[0] == 'B') {
        string convertedInstruction = convertLabelInstruction(realInstruction, labelFlag);
        instructions[iCount].readInstruction(convertedInstruction, labelFlag);
    } else {
        instructions[iCount].readInstruction(realInstruction);
    }

    iCount++;
}

void VirtualMachine::addLabel(string labelHead) {
    // labelToID是从string到int的map映射
    if (labelToID[labelHead] == 0) {
        labelToID[labelHead] = labelCount;
        labelCount++;
    }
}

void VirtualMachine::readAMemory(string memoryLine) {
    //cout << memoryLine << endl;

    const char *buf = memoryLine.c_str();
    unsigned int address, tmpvalue;
    sscanf(buf, "%x:%x", &address, &tmpvalue);
    memory[address] = (unsigned char) tmpvalue;
}

void VirtualMachine::initCodeToFunctionArray() {
    memset(codeToFunction, 0, sizeof(codeToFunction));
    codeToFunction[_SUB] = &VirtualMachine::doSUB;
    codeToFunction[_BNEZ] = &VirtualMachine::doBNEZ;
    codeToFunction[_JR] = &VirtualMachine::doJR;
    codeToFunction[_SLTI] = &VirtualMachine::doSLTI;
    codeToFunction[_BEQZ] = &VirtualMachine::doBEQZ;
    codeToFunction[_SLE] = &VirtualMachine::doSLE;
    codeToFunction[_ANDI] = &VirtualMachine::doANDI;
    codeToFunction[_SEQ] = &VirtualMachine::doSEQ;
    codeToFunction[_SGT] = &VirtualMachine::doSGT;
    codeToFunction[_SGEI] = &VirtualMachine::doSGEI;
    codeToFunction[_LW] = &VirtualMachine::doLW;
    codeToFunction[_SGE] = &VirtualMachine::doSGE;
    codeToFunction[_SLEI] = &VirtualMachine::doSLEI;
    codeToFunction[_XOR] = &VirtualMachine::doXOR;
    codeToFunction[_HALT] = &VirtualMachine::doHALT;
    codeToFunction[_SGTI] = &VirtualMachine::doSGTI;
    codeToFunction[_SLT] = &VirtualMachine::doSLT;
    codeToFunction[_ADD] = &VirtualMachine::doADD;
    codeToFunction[_XORI] = &VirtualMachine::doXORI;
    codeToFunction[_LB] = &VirtualMachine::doLB;
    codeToFunction[_SUBI] = &VirtualMachine::doSUBI;
    codeToFunction[_AND] = &VirtualMachine::doAND;
    codeToFunction[_SEQI] = &VirtualMachine::doSEQI;
    codeToFunction[_SNE] = &VirtualMachine::doSNE;
    codeToFunction[_SRLI] = &VirtualMachine::doSRLI;
    codeToFunction[_SW] = &VirtualMachine::doSW;
    codeToFunction[_SNEI] = &VirtualMachine::doSNEI;
    codeToFunction[_SLLI] = &VirtualMachine::doSLLI;
    codeToFunction[_ORI] = &VirtualMachine::doORI;
    codeToFunction[_SB] = &VirtualMachine::doSB;
    codeToFunction[_OR] = &VirtualMachine::doOR;
    codeToFunction[_ADDI] = &VirtualMachine::doADDI;
    codeToFunction[_OP] = &VirtualMachine::doOP;
}

void VirtualMachine::doSUB(int *ops) {
    R[ops[0]] = R[ops[1]] - R[ops[2]];
}

void VirtualMachine::doBNEZ(int *ops) {
    //if((usedReg & (1 << ops[0])) == 0) return;

    int newEIP = 0;
    if (R[ops[0]]) {
        if (ops[4] == _LABEL) {
            newEIP = idToIndex[ops[1]] - 1;
        } else {
            newEIP = EIP + ops[1];
        }

        /*
        if((usedReg & (1 << ops[0])) == 0) {
            if(newEIP < EIP) return; // 只允许向后跳转
        }
         */
        EIP = newEIP;
    }

}

void VirtualMachine::doBEQZ(int *ops) {
    //if((usedReg & (1 << ops[0])) == 0) return;

    int newEIP = 0;
    if (!R[ops[0]]) {
        if (ops[4] == _LABEL) {
            newEIP = idToIndex[ops[1]] - 1;
        } else {
            newEIP = EIP + ops[1];
        }

        /*
        if((usedReg & (1 << ops[0])) == 0) {
            if(newEIP < EIP) return;
        }*/
        EIP = newEIP;
    }
}

void VirtualMachine::doJR(int *ops) {

    if (ops[4] == _LABEL) {
        EIP = idToIndex[ops[0]] - 1;
    } else if (ops[4] == _REG) {
        EIP += R[ops[0]] - 1;
    } else {
        EIP += ops[0] - 1;
    }
}


void VirtualMachine::doSLTI(int *ops) {
    R[ops[0]] = R[ops[1]] < ops[2] ? 1 : 0;
}

void VirtualMachine::doSLE(int *ops) {
    R[ops[0]] = R[ops[1]] <= R[ops[2]] ? 1 : 0;
}

void VirtualMachine::doANDI(int *ops) {
    R[ops[0]] = R[ops[1]] & ops[2];
}

void VirtualMachine::doSEQ(int *ops) {
    R[ops[0]] = R[ops[1]] == R[ops[2]] ? 1 : 0;
}

void VirtualMachine::doSGT(int *ops) {
    R[ops[0]] = R[ops[1]] > R[ops[2]] ? 1 : 0;
}

void VirtualMachine::doSGEI(int *ops) {
    R[ops[0]] = R[ops[1]] >= ops[2] ? 1 : 0;
}

void VirtualMachine::doLW(int *ops) {
    unsigned int address = R[ops[1]] + ops[2];
    R[ops[0]] = loadMemory(address);
}

void VirtualMachine::doSGE(int *ops) {
    R[ops[0]] = R[ops[1]] >= R[ops[2]] ? 1 : 0;
}

void VirtualMachine::doSLEI(int *ops) {
    R[ops[0]] = R[ops[1]] <= ops[2] ? 1 : 0;
}

void VirtualMachine::doXOR(int *ops) {
    R[ops[0]] = R[ops[1]] ^ R[ops[2]];
}

void VirtualMachine::doHALT(int *ops) {}

void VirtualMachine::doSGTI(int *ops) {
    R[ops[0]] = R[ops[1]] > ops[2] ? 1 : 0;
}

void VirtualMachine::doSLT(int *ops) {
    R[ops[0]] = R[ops[1]] < R[ops[2]] ? 1 : 0;
}

void VirtualMachine::doADD(int *ops) {
    R[ops[0]] = R[ops[1]] + R[ops[2]];
}

void VirtualMachine::doXORI(int *ops) {
    R[ops[0]] = R[ops[1]] ^ ops[2];
}

void VirtualMachine::doLB(int *ops) {
    unsigned int address = R[ops[1]] + ops[2];
    if (address > MAX_MEMORY_LEN)
        R[ops[0]] = memory2[address];
    else
        R[ops[0]] = memory[address];
}

void VirtualMachine::doSUBI(int *ops) {
    R[ops[0]] = R[ops[1]] - ops[2];
}

void VirtualMachine::doAND(int *ops) {
    R[ops[0]] = R[ops[1]] & R[ops[2]];
}

void VirtualMachine::doSEQI(int *ops) {
    R[ops[0]] = R[ops[1]] == ops[2] ? 1 : 0;
}

void VirtualMachine::doSNE(int *ops) {
    R[ops[0]] = R[ops[1]] != R[ops[2]] ? 1 : 0;
}

void VirtualMachine::doSRLI(int *ops) {
    if (ops[2]) {
        int inf = 0x7fffffff;
        int tmp = R[ops[1]] >> 1;
        tmp &= inf;
        tmp >>= (ops[2] - 1);
        R[ops[0]] = tmp;
    } else {
        R[ops[0]] = R[ops[1]];
    }
}

void VirtualMachine::doSW(int *ops) {
    unsigned int address = R[ops[1]] + ops[2];
    storeMemory(address, R[ops[0]]);
}

void VirtualMachine::doSNEI(int *ops) {
    R[ops[0]] = R[ops[1]] != ops[2] ? 1 : 0;
}

void VirtualMachine::doSLLI(int *ops) {
    R[ops[0]] = R[ops[1]] << ops[2];
}

void VirtualMachine::doORI(int *ops) {
    R[ops[0]] = R[ops[1]] | ops[2];
}

void VirtualMachine::doSB(int *ops) {
    unsigned int address = R[ops[1]] + ops[2];
    if (address > MAX_MEMORY_LEN)
        memory2[address] = R[ops[0]] & 0xff;
    else
        memory[address] = R[ops[0]] & 0xff;
}

void VirtualMachine::doOR(int *ops) {
    R[ops[0]] = R[ops[1]] | R[ops[2]];
}

void VirtualMachine::doADDI(int *ops) {
    R[ops[0]] = R[ops[1]] + ops[2];
}

void VirtualMachine::doOP(int *ops) {
    int numToOutput;
    if (ops[3] == 1) {
        numToOutput = R[ops[0]];
    } else if (ops[0]) {
        unsigned int address = R[ops[0]] + ops[1];
        numToOutput = loadMemory(address);
    } else {
        unsigned int address = ops[1];
        numToOutput = loadMemory(address);
    }
    //cout << numToOutput << endl;
    printf("%d\r\n", numToOutput);
}

void VirtualMachine::run() {
    int lastEIP = -1;
    EIP = 0;
    while (EIP < iCount) {
        if(currentLoop[EIP] && lastEIP == EIP - 1) {
            int loopID = currentLoop[EIP];
            if(loops[loopID].executed) {
                if(loops[loopID].checkInR(R)) {
                    loops[loopID].fakeOutR(R);
                    EIP = loops[loopID].outAddress;
                    continue; // ignore EIP ++;
                } else {
                    // loops[loopID].ignore = true;
                    // 不匹配。。。
                }
            } else {
                // 初始化Loop的入口列表
                loops[loopID].setInR(R);
            }
        }

        if(outLoop[EIP]) {
            int loopID = outLoop[EIP];
            if(! loops[loopID].executed) {
                loops[loopID].setOutR(R);
                loops[loopID].executed = true;
            }
        }

        lastEIP = EIP;
        if (instructions[EIP].isNeedExec)
            (this->*codeToFunction[instructions[EIP].command])(instructions[EIP].ops);

        //cout << "EIP:" << EIP << endl;
        //instructions[EIP].testOutput();
        EIP++;
    }
}

VirtualMachine::VirtualMachine() {
    memset(R, 0, sizeof(R));
    //memset(labelJumpCount, 0, sizeof(labelJumpCount));
    memset(currentLoop, 0, sizeof(currentLoop));
    memset(outLoop, 0, sizeof(outLoop));

    iCount = 0;
    labelCount = 1;
    loopCount = 1;
}

int VirtualMachine::loadMemory(unsigned int address) {
    if (address > MAX_MEMORY_LEN)
        return (memory2[address] << 24) + (memory2[address + 1] << 16) + (memory2[address + 2] << 8) +
               memory2[address + 3];
    return (memory[address] << 24) + (memory[address + 1] << 16) + (memory[address + 2] << 8) + memory[address + 3];
}

void VirtualMachine::storeMemory(unsigned int address, int value) {
    if (address > MAX_MEMORY_LEN) {
        memory2[address + 3] = (unsigned char) (value & 0xff);
        memory2[address + 2] = (unsigned char) ((value >> 8) & 0xff);
        memory2[address + 1] = (unsigned char) ((value >> 16) & 0xff);
        memory2[address] = (unsigned char) ((value >> 24) & 0xff);
        return;
    }
    memory[address + 3] = (unsigned char) (value & 0xff);
    memory[address + 2] = (unsigned char) ((value >> 8) & 0xff);
    memory[address + 1] = (unsigned char) ((value >> 16) & 0xff);
    memory[address] = (unsigned char) ((value >> 24) & 0xff);
}

int VirtualMachine::labelToSaveID(const string &label) {
    int id = labelToID[label];
    return id;
}


string VirtualMachine::convertLabelInstruction(const string &realInstruction, int &labelFlag) {
    int labelPos = realInstruction[0] == 'J' ? 1 : 2;
    istringstream iss(realInstruction);

    vector<string> splitInstructions;
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(splitInstructions));

    string convertedInstruction = "";
    for (int i = 0; i < labelPos; i++) {
        convertedInstruction += splitInstructions[i];
        convertedInstruction += ' ';
    }

    string &label = splitInstructions[labelPos];

    if (checkReg(label)) {
        labelFlag = _REG;
        int convertedID = regToRegID(label);
        convertedInstruction += to_string(convertedID);
    } else if (checkNum(label)) {
        labelFlag = _NUM;
        convertedInstruction += label;
    } else {
        labelFlag = _LABEL;
        addLabel(label);
        convertedInstruction += to_string(labelToSaveID(label));
    }

    return convertedInstruction;
}

inline bool VirtualMachine::checkReg(const string &s) {
    if (s[0] != 'R') return false;
    if (s.length() > 3) return false;
    for (int i = 1; i < s.length(); i++)
        if (s[i] < '0' || s[i] > '9') return false;
    return true;
}

inline bool VirtualMachine::checkNum(const string &s) {
    if (s[0] >= '0' && s[0] <= '9') return true;
    if (s[0] == '-') return true;
    return false;
}

int VirtualMachine::regToRegID(const string &reg) {
    int Rid = 0;
    const char *cstr = reg.c_str();
    sscanf(cstr, "R%d", &Rid);
    return Rid;
}

void VirtualMachine::setOutputFile(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-o")) {
            strcpy(outputFilename, argv[i + 1]);
            freopen(outputFilename, "w", stdout);
            break;
        }
    }
}

int VirtualMachine::getICount() const {
    return iCount;
}

int VirtualMachine::getJumpTarget(Instruction &ins, int curAddr) {
    // 这个函数不去判断条件跳转是否真正满足，仅仅返回跳转目标地址
    switch (ins.command) {
        case _BNEZ:
        case _BEQZ:
            if (ins.ops[4] == _LABEL) {
                return idToIndex[ins.ops[1]];
            } else {
                return curAddr + ins.ops[1] + 1;
            }
        case _JR:
            if (ins.ops[4] == _LABEL) {
                return idToIndex[ins.ops[0]];
            } else if (ins.ops[4] == _REG) {
                return curAddr + R[ins.ops[0]];
            } else {
                return curAddr + ins.ops[0];
            }
        default:
            return -1;
    }
}

