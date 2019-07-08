#pragma once
#include <SFML/Graphics.hpp>
class circleObj
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
	circleObj(float radius, float posX, float posY) : m_r(radius), m_posX(posX), m_posY(posY) {
		m_fillColor = sf::Color::Black;
		circle.setRadius(m_r);
		circle.setFillColor(m_fillColor);
		circle.setPosition(sf::Vector2f(m_posX, m_posY));
	}

	void render(sf::RenderWindow* win) {
		win->draw(circle);
	}

	void update() {
		circle.setRadius(m_r);
		circle.setFillColor(m_fillColor);
		circle.setPosition(sf::Vector2f(m_posX, m_posY));
	}

	void changeColor(int r, int g, int b) {
		m_fillColor = sf::Color(r, g, b);
		update();
	}
};

