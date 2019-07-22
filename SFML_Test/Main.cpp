#pragma once
#include "GameManager.h"

int main() 
{
	static size_t quadSide = 20; //50
	static size_t nHorGrid = 50; //11
	static size_t nVerGrid = 50; //18
	gameManager game(nHorGrid * quadSide, nVerGrid * quadSide, quadSide, nHorGrid, nVerGrid);
	return 0;
}