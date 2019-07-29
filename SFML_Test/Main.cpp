#pragma once
#include "GameManager.h"

int main() 
{
	/*---------Controles---------*/
	/*Mouse
	Click derecho : Revelar cuadro.
	Click izquierdo : Poner bandera (advertencia).
	Teclado
	ESC : Salir del juego.
	R : Reiniciar juego.*/ 

	//Cambiar el tamaño de cada cuadro:
	static size_t quadSide = 50; //50 (recomendado).
	
	//Cambiar el número de cuadros horizontales:
	static size_t nHorGrid = 20; //20 (recomendado).

	//Cambiar el número de cuadros verticales:
	static size_t nVerGrid = 20; //20 (recomendado).

	//Cambiar el número de minas:
	static size_t nMines = 100; // WARNING!!! No mayor a nHorGrid por nVerGrid. 100 (recomendado) 

	gameManager game(nHorGrid * quadSide, nVerGrid * quadSide, quadSide, nHorGrid, nVerGrid, nMines);
	return 0;
}