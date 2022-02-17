#pragma once
#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "Player.h"
#include "blueprint.h"
#include "level.h"
#include <ctime>
#include <map>
#include <string>
using namespace sf;
using std::string;
class Ghost : public Cell {
	int x = 165, y = 0, h=47, w=47;
	float CurrentFrame = 0;
public:
	Player* p;
	float dx, dy;
	int dir = 0;
	int getH() const { return h; }
	int getW() const { return w; }
	bool LP;
	bool RP;
	bool UP;
	bool DP;
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown(); 
	
	virtual void collide() {
		for(int i = pos.y/32;i<(pos.y+Ghost::h)/32;i++)
			for (int j = pos.x / 32; j < (pos.x + Ghost::w) / 32; j++)
			{
				if (Map[i][j] == 'b')
				{
					if (dy > 0)
					{
						int r = rand() % 3 + 1;
						pos.y = i * 32 - Ghost::h - 5;

						if (pos.y == p->pos.y)
						{
							if (pos.x > p->pos.x)
							{
								moveLeft();
							}
							if (pos.x < p->pos.x)
							{
								moveRight();
							}
						}
						else if (pos.x == p->pos.x)
						{
							if (pos.y > p->pos.y)
							{
								moveUp();
							}
							if (pos.y < p->pos.y)
							{
								moveDown();
							}
						}
						else {
							switch (r) {
							case 1: moveUp();  break;
							case 2: moveLeft(); break;
							case 3: moveRight(); break;
							}
							stopDown();
						}
					}
					if (dy < 0)
					{

						int r = rand() % 3 + 1;

						pos.y = i * 32 + 32;
						if (pos.y == p->pos.y)
						{
							if (pos.x > p->pos.x)
							{
								moveLeft();
							}
							if (pos.x < p->pos.x)
							{
								moveRight();
							}
						}
						else if (pos.x == p->pos.x)
						{
							if (pos.y > p->pos.y)
							{
								moveUp();
							}
							if (pos.y < p->pos.y)
							{
								moveDown();
							}
						}
						else {
							switch (r)
							{
							case 1: moveDown();  break;
							case 2: moveRight();  break;
							case 3: moveLeft(); break;
							}
							stopUp();
						}
					}
					if (dx > 0)
					{

						int r = rand() % 3 + 1;

						pos.x = j * 32 - Ghost::w;
						
							switch (r)
							{
							case 1: moveLeft();  break;
							case 2: moveUp();   break;
							case 3: moveDown();  break;
							}
							stopRight();
					}
					if (dx < 0)
					{

						int r = rand() % 3 + 1;

						pos.x = j * 32 + 32;
						
						if (pos.y == p->pos.y)
						{
							if (pos.x > p->pos.x)
							{
								moveLeft();
							}
							if (pos.x < p->pos.x)
							{
								moveRight();
							}
						}
						else if (pos.x == p->pos.x)
						{
							if (pos.y > p->pos.y)
							{
								moveUp();
							}
							if (pos.y < p->pos.y)
							{
								moveDown();
							}
						}
						else {
							switch (r)
							{
							case 1: moveRight(); break;
							case 2: moveUp();  break;
							case 3: moveDown();  break;
							}
							stopLeft();
						}
					}
			}
			}
	}
	Ghost(int pos_x = 18,int pos_y = 12,int x_x = 165,int y_y = 0, int h_h = 47,int w_w = 47,Player* ptr = nullptr) : Cell("Pacman.png", 90, pos_x*32, pos_y*32, x_x, y_y,h_h, w_w),dir(3),x(x_x),
		y(y_y),h(h_h),w(w_w),LP(false), RP(false), UP(true), DP(false),p(ptr){}
	void update(float ElapsedTime);
};

void Ghost::update(float ElapsedTime)
{
	switch (dir)
	{
	case 0: dx = m_Speed; dy = 0; break;
	case 1: dx = -m_Speed; dy = 0; break;
	case 2: dx = 0; dy = m_Speed; break;
	case 3: dx = 0; dy = -m_Speed; break;
	}
	if (LP)
	{
		pos.x += dx * ElapsedTime;
	}
	if (RP)
	{
		pos.x += dx * ElapsedTime;
	}
	if (DP)
	{
		pos.y += dy * ElapsedTime;
	}
	if (UP)
	{
		pos.y += dy * ElapsedTime;
	}
	collide();
	getSprite().setPosition(pos);
}

void Ghost::moveLeft()
{
	dir = 1;
	LP = true;
}

void Ghost::stopLeft()
{
	LP = false;
}

void Ghost::stopRight()
{
	RP = false;
}
void Ghost::stopDown()
{
	DP = false;
}
void Ghost::stopUp()
{
	UP = false;
}
void Ghost::moveUp()
{
	dir = 3;
	UP = true;
}

void Ghost::moveDown()
{
	dir = 2;
	DP = true;
}

void Ghost::moveRight()
{
	dir = 0;
	RP = true;
}

