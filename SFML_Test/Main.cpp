#pragma once
#include "GameManager.h"

int main() 
{
	static size_t quadSide = 20; //20
	static size_t nHorGrid = 50; //50
	static size_t nVerGrid = 50; //50
	static size_t nMines = 50;
	gameManager game(nHorGrid * quadSide, nVerGrid * quadSide, quadSide, nHorGrid, nVerGrid, nMines);
	return 0;
}