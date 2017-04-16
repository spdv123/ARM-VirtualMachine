#ifndef VIRTUALARM_MYINPUT_H
#define VIRTUALARM_MYINPUT_H

#include <string>
#include "VirtualMachine.h"

using namespace std;

const int MAX_FILE_LEN = 128;

inline int isUpperOrNumOrMinus(char c) {
    if(c >= 'A' && c <= 'Z') return 1;
    if(c >= '0' && c <= '9') return 1;
    if(c == '-' || c == '_') return 1;
    return 0;
}

inline int isLower(char c) {
    if(c >= 'a' && c <= 'z') return 1;
    return 0;
}

inline int isSpace(char c) {
    if(c == ' ' || c == '\t' || c == '\n') return 1;
    return 0;
}

inline char toUpper(char c) {
    return c - 32;
}

class MyInput {
public:
    void setFileNames(int argc, char ** argv);
    void dealInputFile();
    void dealMemoryFile();
    void setVM(VirtualMachine * _vm);
    ~MyInput();

private:
    void openFiles();
    void closeFiles();

    char inputFileName[MAX_FILE_LEN] = {0};
    char memoryFileName[MAX_FILE_LEN] = {0};
    FILE *inputFile = 0, *memoryFile = 0;
    string myBuf;
    VirtualMachine * vm;
};


#endif //VIRTUALARM_MYINPUT_H
