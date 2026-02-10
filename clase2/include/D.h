#ifndef D_H
#define D_H

#include <iostream>

#include "C.h"

class D: public C

{
    public:

    D(): C{7}
    {
        std::cout<< "Constructor de D"<<std::endl;
    }

    void info();// override;
};

#endif