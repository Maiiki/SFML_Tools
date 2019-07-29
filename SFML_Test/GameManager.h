#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
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
		m_empties = (m_nHorGrid * m_nVerGrid) - m_nMines;
		gameLoop();
	}

private:
	std::size_t m_winW, m_winH, m_nHorGrid, m_nVerGrid, m_quadSize, m_nMines, m_revealed, m_empties;
	std::vector<lineObj*> m_grid;
	std::vector<shapeObj*> m_gameObjects;
	sf::RenderWindow* p_win;
	sf::Window* p_refWin;
	std::vector<std::vector<quadObj*>>matrix;
	bool b_Alive, b_firstClick, b_Won;
	int mouse_x, mouse_y;
	/*sf::Font m_font;
	sf::FileInputStream m_stream;*/

	void gameLoop() 
	{
		//loadFont();
		createMatrix();
		//createGrid();
		b_Alive = true;
		b_Won = false;
		b_firstClick = true;
		m_revealed = 0;
		while (p_win->isOpen())
		{
			sf::Event event;
			while (p_win->pollEvent(event))
			{
				if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					p_win->close();
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {resetGame();}

				if (event.type == sf::Event::MouseMoved)
				{
					mouse_x = event.mouseMove.x / m_quadSize;
					mouse_y = event.mouseMove.y / m_quadSize;
				}

				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (b_Alive && !b_Won)
					{
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							if (b_firstClick)
							{
								addMines(event.mouseButton.x / m_quadSize, event.mouseButton.y / m_quadSize);
								countMines();
								b_firstClick = false;
							}
							if (checkMine(event.mouseButton.x / m_quadSize, event.mouseButton.y / m_quadSize)) {
								showQuad(event.mouseButton.x / m_quadSize, event.mouseButton.y / m_quadSize);
							}
						}

						if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
						{
							setWarning((event.mouseButton.x / m_quadSize), (event.mouseButton.y / m_quadSize));
						}
					}
						
				}
			}

			if (b_Alive && !b_Won) { p_win->clear(sf::Color(253, 43, 134)); }
			else if (b_Won) { p_win->clear(sf::Color(52, 68, 102)); }
			else { p_win->clear(sf::Color(138, 7, 7)); }
			
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

		/*---------Highlight quad---------*/
		matrix[mouse_x][mouse_y]->mouseOn();
		/*---------Update Matrix---------*/
		for (size_t i = 0; i < matrix.size(); ++i) {
			for (size_t j = 0; j < matrix[i].size(); j++)
			{
				matrix[i][j]->update();
			}
		}
	}

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
	}

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

	void resetGame()
	{
		matrix.clear();
		createMatrix();
		b_Alive = true;
		b_Won = false;
		b_firstClick = true;
		m_revealed = 0;
	}

	/*void loadFont()
	{
		try
		{
			m_stream.open("Resources/Dry Brush.ttf");
			m_font.loadFromStream(m_stream);
		}
		catch (const std::exception&)
		{
			std::cout << "Cant do" << std::endl;
		}
	}*/

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

	void addMines(int x, int y)
	{
		int nMinesPlaced = 0;
		srand(time(NULL));
		int mine_x;
		int mine_y;
		while (nMinesPlaced < m_nMines)
		{
			mine_x = rand() % m_nHorGrid;
			mine_y = rand() % m_nVerGrid;

			if (mine_x != x || mine_y != y)
			{
				if (matrix[mine_x][mine_y]->setMine()) { nMinesPlaced++; }
			}
		}
	}

	void countMines() {
		for (size_t x = 0; x < m_nHorGrid; x++)
		{
			for (size_t y = 0; y < m_nVerGrid; y++)
			{
				if (matrix[x][y]->giveState() != 2)
				{
					if (y > 0) { if (matrix[x][y - 1]->giveState() == 2) { matrix[x][y]->addMineCounter(); } }
					if (y < m_nVerGrid - 1) { if (matrix[x][y + 1]->giveState() == 2) { matrix[x][y]->addMineCounter(); } }
					if (x > 0)
					{
						if (matrix[x - 1][y]->giveState() == 2) { matrix[x][y]->addMineCounter(); }
						if (y > 0) { if (matrix[x - 1][y - 1]->giveState() == 2) { matrix[x][y]->addMineCounter(); } }
						if (y < m_nVerGrid - 1) { if (matrix[x - 1][y + 1]->giveState() == 2) { matrix[x][y]->addMineCounter(); } }
					}
					if (x < m_nHorGrid - 1)
					{
						if (matrix[x + 1][y]->giveState() == 2) { matrix[x][y]->addMineCounter(); }
						if (y > 0) { if (matrix[x + 1][y - 1]->giveState() == 2) { matrix[x][y]->addMineCounter(); } }
						if (y < m_nVerGrid - 1) { if (matrix[x + 1][y + 1]->giveState() == 2) { matrix[x][y]->addMineCounter(); } }
					}
				}
				////Deprecated
				//for (size_t k = 0; k < 3; k++)
				//{
				//	for (size_t l = 0; l < 3; l++)
				//	{
				//		if (!((x < 1) || (x > m_nHorGrid - 2) || (y < 1) || (y > m_nVerGrid - 2)))
				//		{
				//			if (matrix[x - 1 + k][y - 1 + l]->giveState() == 2)
				//			{
				//				matrix[x][y]->addMineCounter();
				//			}
				//		}
				//	}
				//}
			}
		}
	}

	void showMines()
	{
		for (size_t x = 0; x < matrix.size(); x++)
		{
			for (size_t y = 0; y < matrix[x].size(); y++)
			{
				if (matrix[x][y]->giveState() == 2) { matrix[x][y]->showQuad(); }
			}
		}
	}

	/*------------------------Input Related------------------------*/
	
	bool checkMine(int x, int y)
	{
		int quadState = matrix[x][y]->giveState();
		if (quadState == 2)
		{
			showMines();
			b_Alive = false;
			std::cout << "Player lost..." << std::endl;
		}
		return b_Alive;
	}

	void showQuad(int x, int y)
	{
		int quadState = matrix[x][y]->giveState();
		
		if (quadState != 2 && quadState != 1)
		{
			matrix[x][y]->showQuad();
			m_revealed++;
			if (m_revealed == m_empties)
			{
				b_Won = true;
				std::cout << "Player won!!" << std::endl;
			}
			if (x > 0)
			{
				showQuad(x - 1, y);
			}
			if (y > 0)
			{
				showQuad(x, y - 1);
			}
			if (x < m_nHorGrid-1)
			{
				showQuad(x + 1, y);
			}
			if (y < m_nVerGrid-1)
			{
				showQuad(x, y + 1);
			}
			//if (!((x < 1) || (x > m_nHorGrid - 2) || (y < 1) || (y > m_nVerGrid - 2)))
			//{
			//	//for (size_t i = 0; i <= 2; ++i)
			//	//{
			//	//	for (size_t j = 0; j <= 2; ++j)
			//	//	{
			//	//		showQuad(x - 1 + i, y - 1 + j);
			//	//		//matrix[x - 1 + i][y - 1 + j]->showQuad();	
			//	//	}
			//	//}
			//}
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