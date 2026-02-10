#ifndef B_H
#define B_H

#include <iostream>
#include "A.h"

class B
{
    private:
        int m_valor;

        //Constante
        //const int m_const;

        //Comentar cosntructor de A para ver que ocurre
        //A a;
    public:

        B()//B(int numer): m_const{numer},a{90}
        {
            m_valor = 5;
            //m_const = 7;
            std::cout << "Constructor B sin params, valor: "<<m_valor<< std::endl;//", const: "<<m_const<<std::endl;
        }
};

#endif