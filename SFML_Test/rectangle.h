#pragma once
#include <SFML/Graphics.hpp>
#include "shape.h"
class rectObj:public shapeObj
{
private:
	float m_w, m_h, m_posX, m_posY;
	sf::Color m_fillColor;
	sf::Color m_lineThick;
	sf::Color m_lineColor;
	sf::RectangleShape rect;

public:
	rectObj(float width, float height, float posX, float posY, sf::Color color)
		:m_w(width), m_h(height), m_posX(posX),m_posY(posY),m_fillColor(color)
	{
		rect.setSize(sf::Vector2f(m_w, m_h));
		rect.setPosition(sf::Vector2f(m_posX, m_posY));
		rect.setFillColor(m_fillColor);
	}

	~rectObj()
	{
	}

	virtual void render(sf::RenderWindow* win) 
	{
		win->draw(rect);
	}

	virtual void update() 
	{
		rect.setSize(sf::Vector2f(m_w, m_h));
		rect.setPosition(sf::Vector2f(m_posX, m_posY));
		rect.setFillColor(m_fillColor);
	}

	virtual void changeFillColor(sf::Color color) 
	{
		m_fillColor = color;
	}
};
