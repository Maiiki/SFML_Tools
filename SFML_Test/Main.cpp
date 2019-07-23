#pragma once
#include "GameManager.h"

int main() 
{
	static size_t quadSide = 50; //20
	static size_t nHorGrid = 10; //50
	static size_t nVerGrid = 10; //50
	static size_t nMines = 20;
	gameManager game(nHorGrid * quadSide, nVerGrid * quadSide, quadSide, nHorGrid, nVerGrid, nMines);
	return 0;
}