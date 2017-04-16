//
// Created by Deva on 2017/4/4.
//

#ifndef VIRTUALARM_LOOP_H
#define VIRTUALARM_LOOP_H

#define MAX_REGISTER_COUNT 32

class Loop {
public:
    Loop();

    void setInR(const int * R);
    void setOutR(const int * R);

    bool checkInR(const int * R);
    void fakeOutR(int * R); // 假装执行了这一块，直接跳过并输出到R

    int readRegs;
    int writeRegs;
    int inR[MAX_REGISTER_COUNT];
    int outR[MAX_REGISTER_COUNT];

    int outAddress;

    bool executed;
    //bool ignore;
};


#endif //VIRTUALARM_LOOP_H
