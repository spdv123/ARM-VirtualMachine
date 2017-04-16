//
// Created by Deva on 2017/4/4.
//

#include "Loop.h"

Loop::Loop() {
    executed = false;
    //ignore = false;
}

void Loop::setInR(const int *R) {
    for(int i=0;i<MAX_REGISTER_COUNT;i++) inR[i] = R[i];
}

void Loop::setOutR(const int *R) {
    for(int i=0;i<MAX_REGISTER_COUNT;i++) outR[i] = R[i];
}

bool Loop::checkInR(const int *R) {
    for(int i=0;i<MAX_REGISTER_COUNT;i++) {
        if(readRegs & (1 << i)) {
            if(R[i] != inR[i]) return false;
        }
    }
    return true;
}

void Loop::fakeOutR(int *R){
    for(int i=0;i<MAX_REGISTER_COUNT;i++) {
        if(writeRegs & (1 << i)) {
            R[i] = outR[i];
        }
    }
}


