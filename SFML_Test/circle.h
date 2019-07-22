#pragma once
#include <SFML/Graphics.hpp>
#include "shape.h"
class circleObj:public shapeObj
{
private:
	float m_r;
	sf::Color m_fillColor;
	sf::Color m_lineThick;
	sf::Color m_lineColor;
	float m_posX;
	float m_posY;
	sf::CircleShape circle;

public:
	circleObj(float radius, float posX, float posY, sf::Color color) 
		: m_r(radius), m_posX(posX), m_posY(posY), m_fillColor(color) 
	{
		circle.setRadius(m_r);
		circle.setPosition(sf::Vector2f(m_posX, m_posY));
		circle.setFillColor(m_fillColor);
	}

	virtual void render(sf::RenderWindow* win) 
	{
		win->draw(circle);
	}

	virtual void update() 
	{
		circle.setRadius(m_r);
		circle.setFillColor(m_fillColor);
		circle.setPosition(sf::Vector2f(m_posX, m_posY));
	}

	void changeFillColor(sf::Color color)
	{
		m_fillColor = color;
	}
};

