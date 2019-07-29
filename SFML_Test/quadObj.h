#pragma once
#include "shape.h"
#include "line.h"
#include <iostream>
class quadObj :	public shapeObj
{
private:
	float m_w, m_h, m_posX, m_posY, m_lineThick, m_posAdjust;
	bool b_isMine;
	bool b_isShown;
	bool b_isWarning;
	bool b_mouseOnMe;
	sf::Color m_fillColor;
	sf::Color m_lineColor;
	sf::Color m_mineLineColor;
	sf::RectangleShape m_rect;
	sf::CircleShape m_circle;
	size_t m_closeMines;
	/*sf::Font m_font;
	sf::Text m_num;*/
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	std::vector<lineObj*> m_nMines;
	
public:
	quadObj(float width, float height, float posX, float posY)
		:m_w(width), m_h(height), m_posX(posX), m_posY(posY)
	{
		m_fillColor = sf::Color(99, 126, 168);
		m_lineColor = sf::Color(253, 43, 134); //(52, 68, 102)
		m_mineLineColor = sf::Color::White; //(1, 205, 254)
		m_lineThick = m_w/50;
		b_isMine = false;
		b_isShown = false;
		b_isWarning = false;
		b_mouseOnMe = false;
		m_closeMines = 0;

		m_rect.setSize(sf::Vector2f(m_w, m_h));
		m_rect.setPosition(sf::Vector2f(m_posX, m_posY));
		m_rect.setFillColor(m_fillColor);
		m_rect.setOutlineColor(m_lineColor);
		m_rect.setOutlineThickness(m_lineThick);

		m_posAdjust = m_w/4;
		m_circle.setRadius((m_w/2)- m_posAdjust);
		m_circle.setPosition(sf::Vector2f(m_posX+ m_posAdjust, m_posY+ m_posAdjust));
		m_circle.setFillColor(sf::Color(255, 251, 150));

		/*m_font = font;
		m_num.setFont(m_font);*/
	}

	virtual void render(sf::RenderWindow* win)
	{
		if (b_isShown)
		{
			if (b_isMine)
			{
				win->draw(m_circle);
			}
			else
			{
				if (m_closeMines > 0)
				{
					drawNum(win);
				}
			}
		}
		else
		{
			win->draw(m_rect);
			b_mouseOnMe = false;
		}
		
	}

	virtual void update()
	{
		if (b_isWarning) { changeFillColor(sf::Color(52, 68, 102)); }
		else if (b_mouseOnMe) 
		{ 
			changeFillColor(sf::Color(60, 165, 207));
			
		}
		else{ changeFillColor(sf::Color(99, 126, 168)); }
		updateNum();
		m_rect.setSize(sf::Vector2f(m_w, m_h));
		m_rect.setPosition(sf::Vector2f(m_posX, m_posY));
		m_rect.setFillColor(m_fillColor);
		m_rect.setOutlineColor(m_lineColor);
		m_rect.setOutlineThickness(m_lineThick);
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
	
	void addMineCounter()
	{
		if (b_isMine) {

		}
		m_closeMines++;
		//num.setString(m_closeMines);
	}

	int giveState()
	{
		if (b_isShown) { return 1; }
		else if (b_isMine) { return 2; }
		else { return 0; }
	}

	void updateNum()
	{
		/*----------Show number of mines as lines--------*/
		if (m_closeMines > 0)
		{
			//Posición y dimensiones de un rectangulo inscrito que es 20% más pequeño
			float ins_x = m_posX + (m_w / 10.f);
			float ins_y = m_posY + (m_h / 10.f);
			float ins_w = (m_w * 0.8f);
			float ins_h = (m_h * 0.8f);

			switch (m_closeMines)
			{
				/*----------Del case 1 al 4 todas las lineas son horizontales---------*/
			case 1:
				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + (ins_w / 2), ins_y),
					sf::Vector2f(ins_x + (ins_w / 2), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));
				
				/*---------deprecated--------*/
				

				break;

			case 2:
				/*----------Lineas verticales---------*/
				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + (ins_w / 3), ins_y),
					sf::Vector2f(ins_x + (ins_w / 3), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + ((ins_w / 3) * 2), ins_y),
					sf::Vector2f(ins_x + ((ins_w / 3) * 2), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));

				/*---------deprecated--------*/
				
				break;

			case 3:
				/*----------Lineas verticales---------*/
				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + (ins_w / 4), ins_y),
					sf::Vector2f(ins_x + (ins_w / 4), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + ((ins_w / 4) * 2), ins_y),
					sf::Vector2f(ins_x + ((ins_w / 4) * 2), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + ((ins_w / 4) * 3), ins_y),
					sf::Vector2f(ins_x + ((ins_w / 4) * 3), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));

				/*---------deprecated--------*/
				
				break;

			case 4:
				/*----------Lineas verticales---------*/
				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + (ins_w / 5), ins_y),
					sf::Vector2f(ins_x + (ins_w / 5), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + ((ins_w / 5) * 2), ins_y),
					sf::Vector2f(ins_x + ((ins_w / 5) * 2), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + ((ins_w / 5) * 3), ins_y),
					sf::Vector2f(ins_x + ((ins_w / 5) * 3), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + ((ins_w / 5) * 4), ins_y),
					sf::Vector2f(ins_x + ((ins_w / 5) * 4), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));

				/*---------deprecated--------*/
				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + (ins_w / 5), ins_y),
					sf::Vector2f(ins_x + (ins_w / 5), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + ((ins_w / 5) * 2), ins_y),
					sf::Vector2f(ins_x + ((ins_w / 5) * 2), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + ((ins_w / 5) * 3), ins_y),
					sf::Vector2f(ins_x + ((ins_w / 5) * 3), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + ((ins_w / 5) * 4), ins_y),
					sf::Vector2f(ins_x + ((ins_w / 5) * 4), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));
				break;

				/*-----Del case 5 al 6 se dibujan todas las lineas horizontales y se agrega una vertical por cada número que aumenta----*/
			case 5:
				/*---------Lineas horizontales--------*/
				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x, ins_y + (ins_h / 2)),
					sf::Vector2f(ins_x + ins_w, ins_y + (ins_h / 2)),
					m_mineLineColor, m_mineLineColor));

				/*----------Lineas verticales---------*/
				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + (ins_w / 5), ins_y),
					sf::Vector2f(ins_x + (ins_w / 5), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + ((ins_w / 5) * 2), ins_y),
					sf::Vector2f(ins_x + ((ins_w / 5) * 2), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + ((ins_w / 5) * 3), ins_y),
					sf::Vector2f(ins_x + ((ins_w / 5) * 3), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + ((ins_w / 5) * 4), ins_y),
					sf::Vector2f(ins_x + ((ins_w / 5) * 4), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));
				break;

			case 6:
				/*---------Lineas horizontales--------*/
				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x, ins_y + (ins_h / 3)),
					sf::Vector2f(ins_x + ins_w, ins_y + (ins_h / 3)),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x, ins_y + (ins_h / 3) * 2),
					sf::Vector2f(ins_x + ins_w, ins_y + (ins_h / 3) * 2),
					m_mineLineColor, m_mineLineColor));

				/*----------Lineas verticales---------*/
				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + (ins_w / 5), ins_y),
					sf::Vector2f(ins_x + (ins_w / 5), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + ((ins_w / 5) * 2), ins_y),
					sf::Vector2f(ins_x + ((ins_w / 5) * 2), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + ((ins_w / 5) * 3), ins_y),
					sf::Vector2f(ins_x + ((ins_w / 5) * 3), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + ((ins_w / 5) * 4), ins_y),
					sf::Vector2f(ins_x + ((ins_w / 5) * 4), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));
				break;

			case 7:
				/*---------Lineas horizontales--------*/
				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x, ins_y + (ins_h / 4)),
					sf::Vector2f(ins_x + ins_w, ins_y + (ins_h / 4)),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x, ins_y + (ins_h / 4) * 2),
					sf::Vector2f(ins_x + ins_w, ins_y + (ins_h / 4) * 2),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x, ins_y + (ins_h / 4) * 3),
					sf::Vector2f(ins_x + ins_w, ins_y + (ins_h / 4) * 3),
					m_mineLineColor, m_mineLineColor));
				/*----------Lineas verticales---------*/
				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + (ins_w / 5), ins_y),
					sf::Vector2f(ins_x + (ins_w / 5), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + ((ins_w / 5) * 2), ins_y),
					sf::Vector2f(ins_x + ((ins_w / 5) * 2), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + ((ins_w / 5) * 3), ins_y),
					sf::Vector2f(ins_x + ((ins_w / 5) * 3), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + ((ins_w / 5) * 4), ins_y),
					sf::Vector2f(ins_x + ((ins_w / 5) * 4), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));
				break;

			case 8:
				/*---------Lineas horizontales--------*/
				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x, ins_y + (ins_h / 5)),
					sf::Vector2f(ins_x + ins_w, ins_y + (ins_h / 5)),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x, ins_y + (ins_h / 5) * 2),
					sf::Vector2f(ins_x + ins_w, ins_y + (ins_h / 5) * 2),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x, ins_y + (ins_h / 5) * 3),
					sf::Vector2f(ins_x + ins_w, ins_y + (ins_h / 5) * 3),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x, ins_y + (ins_h / 5) * 4),
					sf::Vector2f(ins_x + ins_w, ins_y + (ins_h / 5) * 4),
					m_mineLineColor, m_mineLineColor));
				/*----------Lineas verticales---------*/
				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + (ins_w / 5), ins_y),
					sf::Vector2f(ins_x + (ins_w / 5), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + ((ins_w / 5) * 2), ins_y),
					sf::Vector2f(ins_x + ((ins_w / 5) * 2), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + ((ins_w / 5) * 3), ins_y),
					sf::Vector2f(ins_x + ((ins_w / 5) * 3), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));

				m_nMines.push_back(createLine(
					sf::Vector2f(ins_x + ((ins_w / 5) * 4), ins_y),
					sf::Vector2f(ins_x + ((ins_w / 5) * 4), ins_y + ins_h),
					m_mineLineColor, m_mineLineColor));
			default:
				break;
			}
		}
		
		/*----------Load Image---------*/
		/*std::string dir = "Resources/";
		std::string fileName = dir + std::to_string(m_closeMines)+".png";
		if (!m_texture.loadFromFile(fileName, sf::IntRect(static_cast<int>(m_posX+m_posAdjust), static_cast<int>(m_posY+m_posAdjust), static_cast<int>(m_w/2), static_cast<int>(m_h / 2))))
		{
			std::cout << "Could not load image" << std::endl;
		}
		m_sprite.setTexture(m_texture);*/

		/*----------Load Font---------*/
		/*m_num.setString('5');
		m_num.setPosition(sf::Vector2f(m_posX + m_posAdjust, m_posY + m_posAdjust));
		m_num.setCharacterSize(m_w/2);
		m_num.setFillColor(sf::Color(1, 205, 254));*/
	}


	lineObj* createLine(sf::Vector2f begin, sf::Vector2f end, sf::Color colorBgn, sf::Color colorEnd)
	{
		lineObj* line = new lineObj(begin, end, colorBgn, colorEnd);
		return line;
	}

	void drawNum(sf::RenderWindow* win)
	{
		for (size_t i = 0; i < m_nMines.size(); i++)
		{
			m_nMines[i]->render(win);
		}
	}

	void mouseOn() { b_mouseOnMe = true; }
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

