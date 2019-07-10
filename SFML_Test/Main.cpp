#pragma once
#include <SFML/Graphics.hpp>
#include "iostream"
#include "shape.h"
#include "line.h"
#include "circle.h"
#include "rectangle.h"
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

	// run the program as long as the window is open
	std::vector<shapeObj> objects;
	objects.push_back(lineObj(sf::Vector2f(50, 50), sf::Vector2f(200, 50)));
	objects.push_back(circleObj(50.f, 150.f, 150.f));
	objects.push_back(rectObj(50.f, 50.f, 200.f, 200.f));
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
		for (size_t i = 0; i < objects.size(); ++i)
		{
			objects[i].changeFillColor(rand() % 150, rand() % 150, rand() % 150);
		}
		for (size_t i = 0; i < objects.size(); ++i)
		{
			objects[i].update();
		}
		for (size_t i = 0; i < objects.size(); ++i)
		{
			objects[i].render(p_win);
		}

		// end the current frame
		window.display();
	}
	return 0;
}