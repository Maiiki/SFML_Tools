#pragma once
#include <SFML/Graphics.hpp>
class shapeObj
{
public:
	shapeObj() {};
	~shapeObj() {};
	virtual void update() {};
	virtual void render(sf::RenderWindow* win) {};
	virtual void changeFillColor(int r, int g, int b) {};
private:

};