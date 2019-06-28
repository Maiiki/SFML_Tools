#include <SFML/Graphics.hpp>
using namespace sf;
#pragma once
class lineObj
{
private:
	Vector2f m_bgn;
	Vector2f m_end;
	Color m_lineColor;

public:
	Vertex m_line[2];
	lineObj(Vector2f begin, Vector2f end) : m_bgn(begin), m_end(end) { // Se inicializan las variables
		m_lineColor = Color::Black;
		m_line[0] = Vertex(m_bgn, m_lineColor);											 //Inicio de la linea
		m_line[1] = Vertex(m_end, m_lineColor);											// Final de la linea
	}

	void render(RenderWindow* win) {
		win->draw(m_line, 2, Lines);
	}

	void update() {
		m_line[0] = Vertex(m_bgn, m_lineColor);
		m_line[1] = Vertex(m_end, m_lineColor);
	}

	void changeColor(int r, int g, int b) {
		m_lineColor = Color(r, g, b);
		update();
	}
};

