#pragma once
#include <SFML/Graphics.hpp>
#include "shape.h"
class lineObj:public shapeObj
{
private:
	sf::Vector2f m_bgn;
	sf::Vector2f m_end;
	sf::Color m_lineColor_b;
	sf::Color m_lineColor_e;

public:
	sf::Vertex m_line[2];
	lineObj(sf::Vector2f begin, sf::Vector2f end, sf::Color ColorBgn, sf::Color ColorEnd ) 
		: m_bgn(begin), m_end(end), m_lineColor_b(ColorBgn), m_lineColor_e(ColorEnd) // Se inicializan las variables
	{ 
		
		m_line[0] = sf::Vertex(m_bgn, m_lineColor_b);											 //Inicio de la linea
		m_line[1] = sf::Vertex(m_end, m_lineColor_e);											// Final de la linea
	}

	void render(sf::RenderWindow* win) 
	{
		win->draw(m_line, 2, sf::Lines);
	}

	void update() 
	{
		m_line[0] = sf::Vertex(m_bgn, m_lineColor_b);
		m_line[1] = sf::Vertex(m_end, m_lineColor_e);
	}

	void changeFillColor(sf::Color color)
	{
		m_lineColor_b = color;
	}
};

