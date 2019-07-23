#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "iostream"
#include "shape.h"
#include "line.h"
#include "circle.h"
#include "rectangle.h"
#include "sorters.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "quadObj.h"

class gameManager {
public:
	gameManager(std::size_t windowWidth, std::size_t windowHeight, std::size_t quadSize, std::size_t nHorGrid, std::size_t nVerGrid, std::size_t nMines)
		: m_winW(windowWidth), m_winH(windowHeight), m_nHorGrid(nHorGrid), m_nVerGrid(nVerGrid), m_quadSize(quadSize), m_nMines(nMines)
	{
		p_win = new sf::RenderWindow(sf::VideoMode(m_winW, m_winH), "SFML Tools", sf::Style::None);
		gameLoop();
	}

private:
	std::size_t m_winW, m_winH, m_nHorGrid, m_nVerGrid, m_quadSize, m_nMines;
	std::vector<lineObj*> m_grid;
	std::vector<shapeObj*> m_gameObjects;
	sf::RenderWindow* p_win;
	sf::Window* p_refWin;
	std::vector<std::vector<quadObj*>>matrix;
	bool b_Alive;

	void gameLoop() 
	{
		createMatrix();
		//createGrid();
		b_Alive = true;
		while (p_win->isOpen() && b_Alive)
		{
			sf::Event event;
			while (p_win->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					p_win->close();
				}
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						showQuad(event.mouseButton.x/m_quadSize, event.mouseButton.y/m_quadSize);
					}
					if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
					{
						setWarning(event.mouseButton.x/m_quadSize, event.mouseButton.y/m_quadSize);
					}
				}
			}

			p_win->clear(sf::Color(253, 43, 134));
			updateGame();
			renderGame(p_win);
			p_win->display();
		}
		deleteAll();
	}

	void updateGame() 
	{
		/*for (std::size_t i = 0; i < m_gameObjects.size(); ++i) 
		{
			m_gameObjects[i]->update();
		}*/
		
		/*---------Update Matrix---------*/
		for (size_t i = 0; i < matrix.size(); ++i) {
			for (size_t j = 0; j < matrix[i].size(); j++)
			{
				matrix[i][j]->update();
			}
		}
	};
	void renderGame(sf::RenderWindow* win) 
	{
		///*----------Draw grid----------*/
		//for (std::size_t i = 0; i < m_grid.size(); ++i) 
		//{
		//	m_grid[i]->render(win);
		//}
		///*--------Draw objects--------*/
		//for (std::size_t i = 0; i < m_gameObjects.size(); ++i) 
		//{
		//	m_gameObjects[i]->render(win);
		//}
		/*--------Draw Matrix--------*/
		for (size_t i = 0; i < matrix.size(); ++i) {
			for (size_t j = 0; j < matrix[i].size(); j++)
			{
				matrix[i][j]->render(win);
			}
		}
	};

	void deleteAll()
	{
		/*----------Delete grid----------*/
		for (std::size_t i = 0; i < m_grid.size(); ++i)
		{
			delete m_grid[i];
		}
		/*--------Delete objects--------*/
		for (std::size_t i = 0; i < m_gameObjects.size(); ++i)
		{
			delete m_gameObjects[i];
		}
	}

	void createMatrix()
	{
		//Add the columns to the matrix for p1
		for (size_t i = 0; i < m_nHorGrid; ++i) {
			//Add the rows to the matrix for p1
			matrix.push_back(std::vector<quadObj*>(m_nVerGrid, 0));
			for (size_t j = 0; j < m_nVerGrid; j++)
			{
				matrix[i][j] = new quadObj(m_quadSize, m_quadSize, m_quadSize * i, m_quadSize * j);
			}
		}
		addMines();
	}

	void createGrid() 
	{
		/*----------Create Vertical lines--------*/
		for (size_t i = 1; i < m_nHorGrid; ++i) 
		{
			sf::Vector2f begin(m_quadSize * i, 0);
			sf::Vector2f end(m_quadSize * i, m_winH);
			m_grid.push_back(createLine(begin, end, sf::Color(185, 103, 255), sf::Color(1, 205, 254))); 
		}

		/*----------Create horizontal lines--------*/
		for (size_t i = 1; i < m_nVerGrid; ++i) 
		{
			sf::Vector2f begin(0, m_quadSize * i);
			sf::Vector2f end(m_winW, m_quadSize * i);
			if (i <= m_nVerGrid / 2) 
			{
				m_grid.push_back(createLine(begin, end, sf::Color(185, 103, 255), sf::Color(185, 103, 255)));
			}
			else 
			{
				m_grid.push_back(createLine(begin, end, sf::Color(1, 205, 254), sf::Color(1, 205, 254)));
			}
		}
	}

	void addMines()
	{
		int nMinesPlaced = 0;
		srand(time(NULL));
		while (nMinesPlaced < m_nMines)
		{
			if (matrix[rand() % m_nHorGrid][rand() % m_nVerGrid]->setMine()) { nMinesPlaced++; }
		}
	}

	/*------------------------Input Related------------------------*/
	void highlightQuad(float width, float height, float posX, float posY)
	{

	}
	
	void showQuad(int x, int y)
	{
		if (x >= 0 && x <= m_nHorGrid && y >= 0 && y <= m_nVerGrid)
		{
			for (size_t i = 0; i <= 2; i++)
			{
				for (size_t j = 0; j <= 2; j++)
				{
					matrix[x][y]->showQuad();
					showQuad(x - 1 + i, y - 1 + j);
				}
			}
		}
	}
	
	void setWarning(int x, int y)
	{
		matrix[x][y]->setWarning();
	}

	/*------------------------Simple shapes addition------------------------*/
	lineObj* createLine(sf::Vector2f begin, sf::Vector2f end, sf::Color colorBgn, sf::Color colorEnd) 
	{
		lineObj* line = new lineObj(begin, end, colorBgn, colorEnd);
		return line;
	}

	circleObj* createCircle(float radius, float posX, float posY, sf::Color color) 
	{
		circleObj* circle = new circleObj(radius, posX, posY, color);
		return circle;
	}

	rectObj* createRect(float width, float height, float posX, float posY, sf::Color color)
	{
		rectObj* rect = new rectObj(width, height, posX, posY, color);
		return rect;
	}

};