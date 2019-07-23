#pragma once
#include "shape.h"
class quadObj :	public shapeObj
{
private:
	float m_w, m_h, m_posX, m_posY, m_lineThick, m_bombAdjust;
	bool b_isMine;
	bool b_isShown;
	bool b_isWarning;
	sf::Color m_fillColor;
	sf::Color m_lineColor;
	sf::RectangleShape rect;
	sf::CircleShape circle;

public:
	quadObj(float width, float height, float posX, float posY)
		:m_w(width), m_h(height), m_posX(posX), m_posY(posY)
	{
		m_fillColor = sf::Color(99, 126, 168);
		m_lineColor = sf::Color(52, 68, 102);
		m_lineThick = m_w/20;
		b_isMine = false;
		b_isShown = false;
		b_isWarning = false;
		rect.setSize(sf::Vector2f(m_w, m_h));
		rect.setPosition(sf::Vector2f(m_posX, m_posY));
		rect.setFillColor(m_fillColor);
		rect.setOutlineColor(m_lineColor);
		rect.setOutlineThickness(m_lineThick);

		m_bombAdjust = m_w/4;
		circle.setRadius((m_w/2)- m_bombAdjust);
		circle.setPosition(sf::Vector2f(m_posX+ m_bombAdjust, m_posY+ m_bombAdjust));
		circle.setFillColor(sf::Color(255, 251, 150));
	}

	virtual void render(sf::RenderWindow* win)
	{
		if (b_isShown)
		{
			if (b_isMine)
			{
				win->draw(circle);
			}
		}
		else
		{
			win->draw(rect);
		}
		
	}

	virtual void update()
	{
		if (b_isWarning) { changeFillColor(sf::Color(52, 68, 102)); }
		else{ changeFillColor(sf::Color(99, 126, 168)); }
		rect.setSize(sf::Vector2f(m_w, m_h));
		rect.setPosition(sf::Vector2f(m_posX, m_posY));
		rect.setFillColor(m_fillColor);
		rect.setOutlineColor(m_lineColor);
		rect.setOutlineThickness(m_lineThick);
	}

	virtual void changeFillColor(sf::Color color)
	{
		m_fillColor = color;
	}

	virtual void changeLineColor(sf::Color color)
	{
		m_lineColor = color;
	}

	virtual void changeLineThickness(float thickness)
	{
		m_lineThick = thickness;
	}
	
	int giveState()
	{
		if (b_isShown) { return 1; }
		else if (b_isMine) { return 2; }
		else { return 0; }
	}
	void setWarning() { b_isWarning = !b_isWarning; }
	void showQuad() { if (!b_isWarning) { b_isShown = true; } }
	bool setMine() 
	{	
		if (b_isMine == false)
		{
			b_isMine = true;
			return b_isMine;
		}
		else
		{
			return false;
		}
		
	}
};

