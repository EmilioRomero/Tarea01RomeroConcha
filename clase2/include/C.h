#ifndef C_H
#define C_H

#include <iostream>

class C
{
    private:
        int m_atributo;
    
    public:

        C():m_atributo{5}
        {
            std::cout<<"Constructor vacío de C"<<std::endl;
        };

        C(int num):m_atributo{num}
        {
            std::cout<<"Constructor NO vacío de C"<<std::endl;
        };

        //void info();
        virtual void info();
        //virtual int suma(int x) = 0;

};

#endif