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

class gameManager {
public:
	gameManager(std::size_t windowWidth, std::size_t windowHeight): m_winW(windowWidth), m_winH(windowHeight) {
		sf::RenderWindow window(sf::VideoMode(m_winW, m_winH), "SFML Tools", sf::Style::None);
		p_win = &window;
		gameLoop();
	}

private:
	std::size_t m_winW, m_winH;
	std::vector<shapeObj*> gameObjects;
	sf::RenderWindow* p_win;

	void gameLoop() {
		while (p_win->isOpen())
		{
			sf::Event event;
			while (p_win->pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					p_win->close();
				}
			}
			p_win->clear(sf::Color::White);
			updateGame();
			renderGame(p_win);
			p_win->display();
		}
		
	}

	void updateGame() {};
	void renderGame(sf::RenderWindow* win) {};


};