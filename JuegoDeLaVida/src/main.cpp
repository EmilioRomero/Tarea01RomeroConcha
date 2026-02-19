#include <SFML/Graphics.hpp>
#include "Celula.h"
#include <vector>
#include <typeinfo>
#include <iostream>
#include <chrono>
#include <thread>

void calculaEstadosFuturos(const std::vector<Celula*>& celulas);

int vecinosVivos(int i, const std::vector<Celula*>& celulas);

int main()
{
	// Se crea la ventana de la aplicación
	sf::RenderWindow window( sf::VideoMode( { 504, 504 } ), "Juego de la vida" );

	// Ciclo en el que se crean los objetos
	float pos_x = 0.f;
	float pos_y = 0.f;

	// Lista que almacena las celulas
	std::vector<Celula*> celulas;

	// Se crean las celulas y se guardan apuntadores de las mismas
	for (int i = 0; i<5; i++){
		for (int j = 0; j<5;j++)
		{
			Celula* celula = new Celula(pos_x,pos_y);
			pos_x += 101.f;
			celulas.push_back(celula);
		}
		pos_x = 0.f;
		pos_y += 101.f;
	}

	// El color de fondo a usar
	sf::Color color(203,224,233);

	// GAME LOOP
	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
			//Se revisa cuando se da un click
			else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
			{
				// Se obtiene la coordenada del click
				int mouse_x = mouseButtonPressed->position.x;
        		int mouse_y = mouseButtonPressed->position.y;

				//Se obtienen los indices correspondientes del arreglo de cuadrados
				int coord_x = mouse_x/101;
				int coord_y = mouse_y/101;

				// Se convierte el indice a una dimension
				int index = (coord_y*5+coord_x);

				celulas.at(index)->cambiaEstado();
				// Se redibujan las Celulas
				window.clear(color);
				for (Celula* celula : celulas)
				{
					window.draw(celula->getCuadrado());
				}
				window.display();
			}
			//Se revisa cuando se presiona la tecla ENter para comenzar la simulación
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scan::Enter)
				{
					// número de iteraciones a realizar 
					int iteraciones = 24;
					int contador = 0;

					while(contador++ <iteraciones)
					{
						// Se verifica si todas las celulas estan muertas para temrinar la simulación.
						bool muertos = false;
						for (Celula* celula: celulas)
						{
							if (celula->isViva())
								muertos = true;
						}
						if (!muertos)
							break;
			
						// Comienza la simulación
						std::cout<<"Iteración : "<<contador<<std::endl;
						calculaEstadosFuturos(celulas); // Se calculan los nuevos estados
						// Se actualizan los estados de la celula
						for (Celula* celula: celulas)
						{
							if (celula->isViva() != celula->getEstadoFuturo())
							{
								celula->cambiaEstado();
								celula->setEstadoFuturo(false);
							}
						}
						// Se redibujan las celulas
						window.clear(color);
						for (Celula* celula : celulas)
						{
							window.draw(celula->getCuadrado());
						}
						window.display();
						// Se duerme el hilo medio segundo
						std::this_thread::sleep_for(std::chrono::milliseconds(500));
					}
				}
			}
		}

		window.clear(color);
		for (Celula* celula : celulas)
		{
			window.draw(celula->getCuadrado());
		}
		window.display();
	}
}

/**
 * @brief función que asigna los estados futuros a las células. 
 * Esta función debe verificar el número de vecinos vivos por cada celula y actaulizar su estado futuro
 * de acuerdo a las reglas del juego de la vida
 */
void calculaEstadosFuturos(const std::vector<Celula*>& celulas)
{
	//TODO
	for(int i = 0; i < 25; i++){
		Celula* cel = celulas.at(i);
		int vecinos = vecinosVivos(i, celulas);
		if(cel->isViva()){
			if(vecinos < 2){
				cel->setEstadoFuturo(false);
			}else if (vecinos < 4){
				cel->setEstadoFuturo(true);
			}else{
				cel->setEstadoFuturo(false);
			}
			
		}else{
			if((vecinos == 3)){
				cel->setEstadoFuturo(true);
			}else{
				cel->setEstadoFuturo(false);
			}
		}
	}
}

/**
 * @brief Función auxiliar que se usa para calcular el número de vecinos vivos de una célula
 * dado un índice del vector celulas. Devuelve un entero que indica cuántos de los 8 o menos
 * vecinos que tiene la célula están vivos
 */
int vecinosVivos(int i, const std::vector<Celula*>& celulas){
	int vecinos = 0;
	switch (i){
		case 0:{
			Celula* c1 = celulas.at(1);
			Celula* c5 = celulas.at(5);
			Celula* c6 = celulas.at(6);
			vecinos += c1->unVecino();
			vecinos += c5->unVecino();
			vecinos += c6->unVecino();
			return vecinos;
		}
		case 4:{
			Celula* c3 = celulas.at(3);
			Celula* c8 = celulas.at(8);
			Celula* c9 = celulas.at(9);
			vecinos += c3->unVecino();
			vecinos += c8->unVecino();
			vecinos += c9->unVecino();
			return vecinos;
		}
		case 20:{
			Celula* c15 = celulas.at(15);
			Celula* c16 = celulas.at(16);
			Celula* c21 = celulas.at(21);
			vecinos += c15->unVecino();
			vecinos += c16->unVecino();
			vecinos += c21->unVecino();
			return vecinos;
		}
		case 24:{
			Celula* c18 = celulas.at(18);
			Celula* c19 = celulas.at(19);
			Celula* c23 = celulas.at(23);
			vecinos += c18->unVecino();
			vecinos += c19->unVecino();
			vecinos += c23->unVecino();
			return vecinos;
		}
		default:{
			if (i < 4){
				Celula* v1 = celulas.at(i-1);
				Celula* v2 = celulas.at(i+1);
				Celula* v3 = celulas.at(i+4);
				Celula* v4 = celulas.at(i+5);
				Celula* v5 = celulas.at(i+6);
				vecinos += v1->unVecino();
				vecinos += v2->unVecino();
				vecinos += v3->unVecino();
				vecinos += v4->unVecino();
				vecinos += v5->unVecino();
				return vecinos;
			}
			else if (i > 20){
				Celula* v1 = celulas.at(i-6);
				Celula* v2 = celulas.at(i-5);
				Celula* v3 = celulas.at(i-4);
				Celula* v4 = celulas.at(i-1);
				Celula* v5 = celulas.at(i+1);
				vecinos += v1->unVecino();
				vecinos += v2->unVecino();
				vecinos += v3->unVecino();
				vecinos += v4->unVecino();
				vecinos += v5->unVecino();
				return vecinos;
			}
			else if ((i % 5) == 0){
				Celula* v1 = celulas.at(i-5);
				Celula* v2 = celulas.at(i-4);
				Celula* v3 = celulas.at(i+1);
				Celula* v4 = celulas.at(i+5);
				Celula* v5 = celulas.at(i+6);
				vecinos += v1->unVecino();
				vecinos += v2->unVecino();
				vecinos += v3->unVecino();
				vecinos += v4->unVecino();
				vecinos += v5->unVecino();
				return vecinos;
			}
			else if (((i + 1) % 5) == 0){
				Celula* v1 = celulas.at(i-6);
				Celula* v2 = celulas.at(i-5);
				Celula* v3 = celulas.at(i-1);
				Celula* v4 = celulas.at(i+4);
				Celula* v5 = celulas.at(i+5);
				vecinos += v1->unVecino();
				vecinos += v2->unVecino();
				vecinos += v3->unVecino();
				vecinos += v4->unVecino();
				vecinos += v5->unVecino();
				return vecinos;
			}
			else{
				Celula* v1 = celulas.at(i-6);
				Celula* v2 = celulas.at(i-5);
				Celula* v3 = celulas.at(i-4);
				Celula* v4 = celulas.at(i-1);
				Celula* v5 = celulas.at(i+1);
				Celula* v6 = celulas.at(i+4);
				Celula* v7 = celulas.at(i+5);
				Celula* v8 = celulas.at(i+6);
				vecinos += v1->unVecino();
				vecinos += v2->unVecino();
				vecinos += v3->unVecino();
				vecinos += v4->unVecino();
				vecinos += v5->unVecino();
				vecinos += v6->unVecino();
				vecinos += v7->unVecino();
				vecinos += v8->unVecino();
				return vecinos;
			}
		}
	}
}