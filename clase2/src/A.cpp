#include "A.h"

void A::printInfo(){
    std::cout << "Informacion\n"<<std::endl;
}

int A::accion(int numero){
    return numero + m_numero;
}