//
// Created by wufuheng on 11/17/2018.
//

#ifndef PNSEI_MYTIME_H

#include "pnsei.h"

namespace _mytime{
    void system_info(){
        cout << chrono::system_clock::period::num << "/" << chrono::system_clock::period::den << endl;
    }
};

#define PNSEI_MYTIME_H

#endif //PNSEI_MYTIME_H
