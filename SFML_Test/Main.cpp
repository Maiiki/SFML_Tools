#pragma once
#include <SFML/Graphics.hpp>
#include "iostream"
#include "line.h"
#include "circle.h"
#include "sorters.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int main()
{
	/* initialize random seed: */
	srand((unsigned int)time(NULL));

	// create the window
	int winW = 800, winH = 800;
	float shapeW = 100;

	sf::RenderWindow window(sf::VideoMode(winW, winH), "My window", sf::Style::None); // Creación de la ventana
	sf::RenderWindow* p_win = &window; //Puntero a la dirección de la ventana

	sf::CircleShape circle(shapeW); //Crear circulo
	circle.setFillColor(sf::Color(150, 50, 250)); //Colorear circulo
	circle.setOutlineThickness(10.f); //Darle grosor a la linea
	circle.setOutlineColor(sf::Color(250, 150, 100));
	circle.setPosition(((winW / 2)-shapeW/2), ((winH / 2)-shapeW/2));

	lineObj cLine(sf::Vector2f(50, 50), sf::Vector2f(200, 50));
	circleObj cCircle(50.f, winW / 2.f, winH / 2.f);
	// run the program as long as the window is open

	std::vector<int> vB;
	std::vector<int> vI;
	std::vector<int> vQ;

	for (int i = 0; i < 20; ++i) {
		vB.push_back(rand() % 100);
		vI.push_back(rand() % 100);
		vQ.push_back(rand() % 100);
	}
	
	BubbleSort bSort;
	InsertSort iSort;
	QuickSort qSort;

	for (int i = 0; i < 20; ++i) {
		std::cout << vB[i] << " ";
	}
	std::cout << "\n";
	for (int i = 0; i < 20; ++i) {
		std::cout << vI[i] << " ";
	}
	std::cout << "\n";
	for (int i = 0; i < 20; ++i) {
		std::cout << vQ[i] << " ";
	}
	std::cout << "\n";

	bSort.Sort(vB);
	iSort.Sort(vI);
	qSort.Sort(vQ);

	for (int i = 0; i < 20; ++i) {
		std::cout << vB[i] << " ";
	}
	std::cout << "\n";
	for (int i = 0; i < 20; ++i) {
		std::cout << vI[i] << " ";
	}
	std::cout << "\n";
	for (int i = 0; i < 20; ++i) {
		std::cout << vQ[i] << " ";
	}
	std::cout << "\n";
	
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// clear the window with black color
		window.clear(sf::Color::White);
		// draw everything here...
		// window.draw(...);
		//Dibujar circulo
		cCircle.changeColor(rand() % 150, rand() % 150, rand() % 150);
		cCircle.render(p_win);
		cLine.changeColor(rand()%150, rand()%150, rand()%150);
		cLine.render(p_win);



		
		// end the current frame
		window.display();
	}
	return 0;
}