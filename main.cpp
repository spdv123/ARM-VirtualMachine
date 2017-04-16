#include <iostream>
#include "Instruction.h"
#include "MyInput.h"
#include "VirtualMachine.h"
#include "Scanner.h"

int main(int argc, char ** argv) {

    // 初始化操作
    Instruction::initCode();
    VirtualMachine::initCodeToFunctionArray();
    Scanner::initCodeToFunctionArray();

    // 处理输入
    VirtualMachine vm;
    vm.setOutputFile(argc, argv);

    MyInput myInput;
    myInput.setFileNames(argc, argv);
    myInput.setVM(&vm);

    myInput.dealInputFile();
    myInput.dealMemoryFile();

    // 尝试优化
    Scanner scanner;
    scanner.setVm(&vm);
    scanner.optimize();

    // 开始执行
    vm.run();

    //cout << sizeof(vm.instructions) << endl;
    return 0;
}
