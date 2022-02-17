#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;

class Cell
{
private:
	Texture texture;
	Image img;
	Sprite sprite;
public:
	float m_Speed;
	Vector2f pos;
	Cell(String, float,float, float,int, int,int, int);
	Sprite& getSprite() { return sprite; }
	virtual void collide() = 0;
};
Cell::Cell(String str = "Pacman.png",
	float s = 200, float l_x = 90, float l_y = 90, int x = 16,int y = 3,int h = 44 , int w = 44)
{
	m_Speed = s;
	img.loadFromFile(str);
	img.createMaskFromColor(Color(0, 0, 0));
	texture.loadFromImage(img);
	sprite.setTexture(texture);
	pos.x = l_x; pos.y = l_y;
	sprite.setTextureRect(IntRect(x,y,h,w));
	sprite.setPosition(pos);
	
}





/*bool m_LeftPressed;
bool m_RightPressed;
bool m_UpPressed;
bool m_DownPressed;
void moveLeft();
void moveRight();
void moveUp();
void moveDown();
void stopLeft();
void stopRight();
void stopUp();
void stopDown(); */