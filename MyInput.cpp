#include <iostream>
#include <cstdio>
#include <cstring>
#include "MyInput.h"
using namespace std;

void MyInput::setFileNames(int argc, char ** argv) {
    for(int i=1;i<argc;i++) {
        if(!strcmp(argv[i], "-i")) strcpy(inputFileName, argv[i+1]);
        if(!strcmp(argv[i], "-m")) strcpy(memoryFileName, argv[i+1]);
    }
    openFiles();
}

void MyInput::openFiles() {
    inputFile = fopen(inputFileName, "r");
    if(memoryFileName[0]) memoryFile = fopen(memoryFileName, "r");
}

void MyInput::closeFiles() {
    if(inputFile) {
        fclose(inputFile);
        inputFile = 0;
    }
    if(memoryFile) {
        fclose(memoryFile);
        memoryFile = 0;
    }
}

void MyInput::dealInputFile() {
    int outedSpace = 0;
    int noNeedSpace = 0;
    char c = fgetc(inputFile);
    while(isSpace(c)) c = fgetc(inputFile);
    while(c != EOF) {
        if(isSpace(c)) {
            outedSpace = 1;
        } else if(isUpperOrNumOrMinus(c)) {
            if((!noNeedSpace) && outedSpace) {
                //fputc(' ', outputFile);
                myBuf += ' ';
            }
            noNeedSpace = 0;
            outedSpace = 0;
            //fputc(c, outputFile);
            myBuf += c;
        } else if(isLower(c)) {
            if((!noNeedSpace) && outedSpace) {
                //fputc(' ', outputFile);
                myBuf += ' ';
            }
            noNeedSpace = 0;
            outedSpace = 0;
            //fputc(toUpper(c), outputFile);
            myBuf += toUpper(c);
        } else if(c == ':') {
            noNeedSpace = 1;
            //fputc(':', outputFile);
            myBuf += ':';
        } else if(c == ';') {
            noNeedSpace = 1;
            //fputc(';', outputFile);
            //fputc('\n', outputFile);
            vm->readAnInstruction(myBuf);
            myBuf = "";
        }
        c = fgetc(inputFile);
    }
    //fputc('\n', outputFile);
    vm->readAnInstruction(myBuf);
    myBuf = "";
}

void MyInput::dealMemoryFile() {
    if(!memoryFile)
        return;
    char c = fgetc(memoryFile);
    while(c != EOF) {
        if(isUpperOrNumOrMinus(c)) {
            //fputc(c, outputFile);
            myBuf += c;
        } else if(isLower(c)) {
            //fputc(toUpper(c), outputFile);
            myBuf += toUpper(c);
        } else if(c == ':') {
            //fputc(c, outputFile);
            myBuf += c;
        } else if(c == '\n') {
            vm->readAMemory(myBuf);
            myBuf = "";
        }
        c = fgetc(memoryFile);
    }
    if(myBuf != "") vm->readAMemory(myBuf);
}

void MyInput::setVM(VirtualMachine * _vm) {
    vm = _vm;
}

MyInput::~MyInput() {
    closeFiles();
}