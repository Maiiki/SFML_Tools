#include <SFML/Graphics.hpp>
using namespace sf;
#pragma once
class circleObj
{
private:
	float m_r;
	Color m_fillColor;
	Color m_lineThick;
	Color m_lineColor;
	float m_posX;
	float m_posY;
	CircleShape circle;

public:
	circleObj(float radius, float posX, float posY) : m_r(radius), m_posX(posX), m_posY(posY) {
		m_fillColor = Color::Black;
		circle.setRadius(m_r);
		circle.setFillColor(m_fillColor);
		circle.setPosition(Vector2f(m_posX, m_posY));
	}

	void render(RenderWindow* win) {
		win->draw(circle);
	}

	void update() {
		circle.setRadius(m_r);
		circle.setFillColor(m_fillColor);
		circle.setPosition(Vector2f(m_posX, m_posY));
	}

	void changeColor(int r, int g, int b) {
		m_fillColor = Color(r, g, b);
		update();
	}
};

