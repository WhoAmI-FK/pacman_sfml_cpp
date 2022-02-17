#pragma once
#include <SFML/Audio.hpp>
#include "Cell.h"
#include "blueprint.h"
class Player : public Cell {
private:
	SoundBuffer stepBuf;
	Sound step;
	int x = 16;
	int y = 3;
	int h = 44;
	int w = 44;
	int score = 0;
	bool LP;
	bool RP;
	float ForStep = 0;
	bool UP;
	bool DP;
	float CurrentFrame = 0;
public:
	float dx, dy;
	int dir = 0;
	int getScore() const { return score; }
	int getH() const { return h; }
	int getW() const { return w; }
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();
	virtual void collide() {
		for (int i = pos.y / 32; i < (pos.y + Player::h) / 32; i++)
			for (int j = pos.x / 32; j < (pos.x + Player::w) / 32; j++) {
				if (Map[i][j] == 'b')
				{
					if (dy > 0)
					{
						pos.y = i * 32 - Player::h;// - 5;
					}
					if (dy < 0)
					{
						pos.y = i * 32 + 32;
					}
					if (dx > 0)
					{
						pos.x = j * 32 - Player::w;
					}
					if (dx < 0)
					{
						pos.x = j * 32 + 32+Player::w;
					}
				}
				if (Map[i][j] == 'a') {
					Map[i][j] = ' ';
					score++;
				}
			}
	}
	Sound death;
	SoundBuffer soundDeath;

	Player(): Cell(),LP(false),RP(false),UP(false),DP(false){
		stepBuf.loadFromFile("step.ogg");
		step.setBuffer(stepBuf);
		soundDeath.loadFromFile("death.ogg");
		death.setBuffer(soundDeath);
	}
	void update(float ElapsedTime);
};

void Player::moveLeft()
{
	LP = true;
}

void Player::stopLeft()
{
	LP = false;
}

void Player::stopRight()
{
	RP = false;
}
void Player::stopDown()
{
	DP = false;
}
void Player::stopUp()
{
	UP = false;
}
void Player::moveUp()
{
	UP = true;
}

void Player::moveDown()
{
	DP = true;
}

void Player::moveRight()
{
	RP = true;
}



void Player::update(float ElapsedTime)
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
		 ForStep += 0.035;
			pos.x += dx * ElapsedTime;
			if (CurrentFrame > 117) {
				CurrentFrame = 0;
			}
			if (ForStep >4)
			{
				step.play();
				ForStep -= 4;
			}
			getSprite().setTextureRect(IntRect(x + CurrentFrame+w, y, -w, h));
			CurrentFrame += 50;
	}
	if (RP)
	{
		
		 ForStep += 0.035;
		pos.x += dx * ElapsedTime;
		if (CurrentFrame > 117) {
			CurrentFrame = 0;
		}
		if (ForStep > 4)
		{
			step.play();
			ForStep -= 4;
		}
		getSprite().setTextureRect(IntRect(x+CurrentFrame, y, w, h));
		CurrentFrame += 50;
	}
	if (DP)
	{	
		ForStep += 0.035;
		if (CurrentFrame > 117) {
			CurrentFrame = 0;
		}
		if (ForStep > 4)
		{
			step.play();
			ForStep -= 4;
		}
		pos.y += dy * ElapsedTime;
			getSprite().setTextureRect(IntRect(x, y, w, h));		
			CurrentFrame += 50;
	}
	if (UP)
	{
		ForStep += 0.035;
		if (CurrentFrame > 117)
		{
			CurrentFrame = 0;
		}
		if (ForStep > 4)
		{
			step.play();
			ForStep -= 4;
		}
		pos.y += dy * ElapsedTime;
			getSprite().setTextureRect(IntRect(x, y, w, h));
			CurrentFrame += 50;
	}
	collide();
	getSprite().setPosition(pos);
}