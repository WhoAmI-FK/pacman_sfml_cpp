#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Collision.hpp"
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Ghost.h"
#include "blueprint.h"
#include <sstream>
#include <ctime>
#include <fstream>
#include <string>
#include <map>
#include <Windows.h>
using std::string;
using namespace sf;
class level {
private:
	RenderWindow window;
	Player p;
	Image map, map_coin;
	Texture map_t, map_t_c;
	Sprite map_s, map_s_c;
	std::map<string, int> players;
	void updateMap()
	{
		for(int i = 0;i<h;i++)
			for (int j = 0; j < w; j++)
			{
				Map[i][j] = SaveMap[i][j];
			}
	}
	/*void ChooseYourCharacter()
	{
		sf::Font font;
		font.loadFromFile("Pacifico.ttf");
		Text text("Select your character:\n",font,60);
		text.setFillColor(Color::White);
		text.setStyle(Text::Bold);
		window.close();
		win.create(sf::VideoMode(1200, 800), "PICK", Style::Fullscreen);
		playerText.setPosition(Vector2f(200, 200));


	}*/

	void lose_screen(Player& p, sf::RenderWindow& win, std::map<string, int>& m)
	{
		sf::Font font;
		font.loadFromFile("Pacifico.ttf");
		Text text("YOU LOSE!\nTRY AGAIN!\n", font, 120);
		text.setFillColor(Color::Red);
		text.setStyle(Text::Bold);
		Text playerText;
		win.close();

		win.create(sf::VideoMode(1200, 800), "LOSE", Style::Fullscreen);
		playerText.setPosition(Vector2f(200, 200));
		playerText.setFont(font);
		sf::String playerInput;
		Event locev;
		while (win.isOpen()) {
			while (win.pollEvent(locev))
			{
				if (locev.type == Event::TextEntered)
				{
					if (locev.text.unicode < 128)
					{
						playerInput += locev.text.unicode;
						playerText.setString("Enter your name:" + playerInput);
					}
				}
			}
			win.clear(Color::Black);
			if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Escape)) win.close();
			text.setPosition(sf::Vector2f(400 / 2.0f, 600 / 2.0f));
			win.draw(text);
			win.draw(playerText);
			win.display();
		}
		if (!playerInput.isEmpty())
			m[playerInput] = p.getScore();

	}

	void Player_collide(Player& p,Ghost& g)
	{
		if (Collision::PixelPerfectTest(g.getSprite(), p.getSprite())) {
			{
				p.death.play();
				lose_screen(p, window, players);
			}
		}
	}
	void input(Player& p) {
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			p.moveLeft();
			p.dir = 1;
		}
		else p.stopLeft();
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			p.dir = 0;
			p.moveRight();
		}
		else p.stopRight();
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			p.dir = 2;
			p.moveDown();
		}
		else p.stopDown();
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			p.dir = 3;
			p.moveUp();
		}
		else p.stopUp();
	}

	void load_from_file()
	{
		std::ifstream f("players.txt");
		string str;
		int score;
		while (!f.eof())
		{
			f >> str >> score;
			players[str] = score;
		}
		f.close();
	}
	void save_to_file()
	{
		std::ofstream f("players.txt");
		for (auto it : players)
		{
			f << it.first << "\n" << it.second << "\n";
		}
		f.close();
	}
	void checkWin(Player& p)
	{//686
		if (p.getScore() == 686) {
			sf::Font font;
			font.loadFromFile("Pacifico.ttf");
			Text text("YOU WIN!\nCONGRATULATIONS!", font, 60);
			text.setFillColor(Color::Yellow);
			text.setStyle(Text::Bold);
			Text playerText;
			window.close();
			window.create(sf::VideoMode(1200, 800), "WIN", Style::Fullscreen);
			playerText.setPosition(sf::Vector2f(700, 600 / 2.0f));
			playerText.setFont(font);
			sf::String playerInput;
			Event localevent;
			while (window.isOpen())
			{
				while (window.pollEvent(localevent))
				{
					if (localevent.type == Event::TextEntered)
					{
						if (localevent.text.unicode < 128)
						{
							playerInput += localevent.text.unicode;
							playerText.setString("Enter your name:"+playerInput);
						}
					}
				}
				window.clear(Color::Black);
				if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
				text.setPosition(sf::Vector2f(400 / 2.0f, 600 / 2.0f));
				window.draw(text);
				window.draw(playerText);
				window.display();
			}
		//	if (!playerInput.isEmpty() && players.size() < 5) {
				players[playerInput] = p.getScore();
		//	}
		}
	}
	void demo()
	{
	//	load_from_file();
		updateMap();
		window.close();
		Player p;
		Ghost g1(18,12,165,0,47,47,&p);
		Ghost g2(20, 11, 138, 53,47,47,&p);
		Ghost g3(20, 11, 138, 107,47,47,&p);
		window.create(sf::VideoMode(1300, 800), "PACMAN");
		float CurrentFrame = 0;
		sf::Clock clock;
		// BG MUSIC
		Music BG;
		BG.openFromFile("bg.ogg");
		BG.setVolume(20.f);
		BG.play();
		BG.setLoop(true);



		while (window.isOpen())
		{
			srand(time(0));
			Time dt = clock.restart();
			float time = dt.asSeconds();
			window.clear(Color::Black);
			sf::Event event;
			map.loadFromFile("mapelement.png");
			map_t.loadFromImage(map);
			map_s.setTexture(map_t);
			map_coin.loadFromFile("coin.png");
			map_t_c.loadFromImage(map_coin);
			map_s_c.setTexture(map_t_c);
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			
				for (int i = 0; i < h; i++)
					for (int j = 0; j < w; j++)
					{
						if (Map[i][j] == 'b') {
							map_s.setTextureRect(IntRect(0, 0, 32, 32));
							map_s.setPosition(j * 32, i * 32);
							window.draw(map_s);
						}
						if (Map[i][j] == 'a')
						{
							map_s_c.setTextureRect(IntRect(0, 0, 32, 32));
							map_s_c.setPosition(j * 32, i * 32);
							window.draw(map_s_c);
						}

					} // count 684


				input(p);
				window.draw(g1.getSprite());
				window.draw(p.getSprite());
				window.draw(g2.getSprite());
				window.draw(g3.getSprite());
				g1.update(time);
				g2.update(time);
				g3.update(time);
				p.update(time);
				checkWin(p);
				Player_collide(p, g1);
				Player_collide(p, g2);
				Player_collide(p, g3);
				window.display();
		}
		save_to_file();
		BG.stop();
		menu();
	}
	void view()
	{
		load_from_file();
		window.create(sf::VideoMode(1200, 800), "PACMAN", Style::Fullscreen);
		sf::Font font;
		font.loadFromFile("Pacifico.ttf");
		Text text;
		string str;
		char buff[255];
		for (auto t : players)
		{
			int a = t.second;
			_itoa_s(a, buff, 10);
			str += (t.first + ": " + buff + "\n");
		}
		text.setString(str);
		text.setFillColor(Color::White);
		text.setFont(font);
		text.setStyle(Text::Bold);
		while (window.isOpen())
		{
			window.clear(Color::Black);
			text.setPosition(100, 100);
			window.draw(text);
			window.display();
			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				window.close();
				menu();
			}
		}
	}
	Sprite& getMapSprite() { return map_s; }

public:
	level() {};
	
	void menu() {
		
		window.create(sf::VideoMode(1200, 800), "PACMAN", Style::Fullscreen);
		while (window.isOpen())
		{
			Image img;
			img.loadFromFile("logo.png");
			img.createMaskFromColor(Color::White);
			Texture img_t;
			img_t.loadFromImage(img);
			Sprite img_s;
			img_s.setTexture(img_t);
			window.clear(Color::Black);
			img_s.setPosition(sf::Vector2f(300, 200));
			sf::Font font;
			font.loadFromFile("Pacifico.ttf");
			Text text("\t*PRESS ENTER TO PLAY\n\t*PRESS V TO WATCH THE LEADERBOARD\n\t*PRESS ESC TO EXIT\n",font,28);
			text.setFillColor(Color::White);
			text.setStyle(Text::Bold);
			text.setPosition(sf::Vector2f(300, 400));
			window.draw(text);
			window.draw(img_s);
			window.display();
			if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				window.close();
				demo();
			}
			if (Keyboard::isKeyPressed(Keyboard::V)) {
				view();
			}

		}
	}

};