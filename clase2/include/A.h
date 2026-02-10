#ifndef A_H
#define A_H

#include <iostream>

class A
{
    //Bloque privado
    private:

        //miembro(atributos en java) se acostumbra agregar m_
        int m_numero;
   
    public:
        
        // Constructor vacío
        A()
        {
            std::cout<<"Soy el constructor vacío \n"<<std::endl;
        }

        // Constructor con parámetro
        A(int num): m_numero{num}
        {
            std::cout<<"Constructor von valor: " << m_numero<< "\n"<<std::endl;
        }

        //DEstructor
        ~A()
        {
            std::cout<<"Me destruyo: "<<m_numero<<"\n"<<std::endl;
        }

        //Funciones
        void printInfo();

        int accion(int numero);

};

#endif