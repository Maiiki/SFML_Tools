#include <SFML/Graphics.hpp>
#include "line.h"
#include "circle.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace sf;

int main()
{
	/* initialize random seed: */
	srand(time(NULL));

	// create the window
	int winW = 800, winH = 800;
	float shapeW = 100;

	RenderWindow window(VideoMode(winW, winH), "My window", Style::None); // Creación de la ventana
	RenderWindow* p_win = &window; //Puntero a la dirección de la ventana

	CircleShape circle(shapeW); //Crear circulo
	circle.setFillColor(Color(150, 50, 250)); //Colorear circulo
	circle.setOutlineThickness(10.f); //Darle grosor a la linea
	circle.setOutlineColor(Color(250, 150, 100));
	circle.setPosition(((winW / 2)-shapeW/2), ((winH / 2)-shapeW/2));

	lineObj cLine(Vector2f(50, 50), Vector2f(200, 50));
	circleObj cCircle(50.f, winW / 2, winH / 2);
	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == Event::Closed)
				window.close();
		}
		// clear the window with black color
		window.clear(Color::White);
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