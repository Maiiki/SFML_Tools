#pragma once
#include <SFML/Graphics.hpp>
#include "shape.h"
class lineObj:public shapeObj
{
private:
	sf::Vector2f m_bgn;
	sf::Vector2f m_end;
	sf::Color m_lineColor;

public:
	sf::Vertex m_line[2];
	lineObj(sf::Vector2f begin, sf::Vector2f end) : m_bgn(begin), m_end(end) { // Se inicializan las variables
		m_lineColor = sf::Color::Black;
		m_line[0] = sf::Vertex(m_bgn, m_lineColor);											 //Inicio de la linea
		m_line[1] = sf::Vertex(m_end, m_lineColor);											// Final de la linea
	}

	void render(sf::RenderWindow* win) {
		win->draw(m_line, 2, sf::Lines);
	}

	void update() {
		m_line[0] = sf::Vertex(m_bgn, m_lineColor);
		m_line[1] = sf::Vertex(m_end, m_lineColor);
	}

	void changeFillColor(int r, int g, int b) {
		m_lineColor = sf::Color(r, g, b);
	}
};

