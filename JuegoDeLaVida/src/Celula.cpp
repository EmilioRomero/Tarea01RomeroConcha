#include "Celula.h"

sf::RectangleShape& Celula::getCuadrado()
{
    return m_cuadrado;
}

void Celula::cambiaEstado()
{
    if(m_estado == true){
        m_estado = false;
        m_cuadrado.setFillColor(sf::Color::Black);
    }
    else{
        m_estado = true;
        m_cuadrado.setFillColor(sf::Color::White);
    }
}

bool Celula::isViva()
{
    return m_estado;
}

void Celula::setEstadoFuturo(bool estado)
{
    m_estadoFuturo = estado;
}

bool Celula::getEstadoFuturo()
{
    return m_estadoFuturo;
}

int Celula::unVecino(){
    if(m_estado){
        return 1;
    } return 0;
}