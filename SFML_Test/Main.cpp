#pragma once
#include "GameManager.h"

int main() {
	gameManager game(800, 800);
	return 0;
}



//int main()
//{
//	/* initialize random seed: */
//	srand((unsigned int)time(NULL));
//
//	// create the window
//	int winW = 800, winH = 800;
//	float shapeW = 100;
//
//	sf::RenderWindow window(sf::VideoMode(winW, winH), "My window", sf::Style::None); // Creación de la ventana
//	sf::RenderWindow* p_win = &window; //Puntero a la dirección de la ventana
//
//	// run the program as long as the window is open
//	std::vector<shapeObj*> objects;
//
//	//------------------------------Forma cochina y fea ----------------------------------//
//	lineObj line(sf::Vector2f(50, 50), sf::Vector2f(200, 50));
//	circleObj circle(50.f, 150.f, 150.f);
//	rectObj rect(50.f, 50.f, 400.f, 400.f);
//
//	objects.push_back(&line);
//	objects.push_back(&circle);
//	objects.push_back(&rect);
//
//	//---------------------------Memoria dinamica nivel Dios (failed xO)------------------------------//
//	/*objects.push_back(&lineObj(sf::Vector2f(50, 50), sf::Vector2f(200, 50)));
//	objects.push_back(&circleObj(50.f, 150.f, 150.f));
//	objects.push_back(&rectObj(50.f, 50.f, 200.f, 200.f));*/
//
//	while (window.isOpen())
//	{
//		// check all the window's events that were triggered since the last iteration of the loop
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			// "close requested" event: we close the window
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//		// clear the window with black color
//		window.clear(sf::Color::White);
//		// draw everything here...
//		// window.draw(...);
//		for (size_t i = 0; i < objects.size(); ++i)
//		{
//			objects[i]->changeFillColor(rand() % 150, rand() % 150, rand() % 150);
//			objects[i]->update();
//			objects[i]->render(p_win);
//		}
//
//		// end the current frame
//		window.display();
//	}
//	return 0;
//}