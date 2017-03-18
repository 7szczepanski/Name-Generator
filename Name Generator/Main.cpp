/*
Nick/Name Generator
Created by Mateusz Szczepanski 18.03.2017
I will propably take word from dictionary (file), and then manipulate it or add it to other word to create nickname.
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <time.h>
#include <fstream>
#include <Windows.h>
#define _WIN32_WINNT 0x0500 

using namespace sf;
using namespace std;

int width = 600;
int height = 200;

int generateLenght();

string random_string(size_t length);
void pushwords(vector<string> &dict);
string random_string_dict(vector<string> &dict);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
	vector<string> dictionary;
	pushwords(dictionary);
	srand(time(NULL));
	sf::Font font;
	string name;
	name = "Generate random nickname";
	Vector2f mousePositionFloat;

	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}

	sf::RenderWindow window(sf::VideoMode(width, height), "Nickname Generator");
	sf::RectangleShape background(Vector2f(width, height));
	background.setFillColor(Color(51, 51, 51));

	sf::Text text;
	text.setCharacterSize(20);
	text.setPosition(Vector2f(50, height / 2 - 10));
	text.setFont(font);

	

	sf::RectangleShape button(Vector2f(100, 50));
	button.setOrigin(50, 25);
	button.setFillColor(Color(80, 185, 240));
	button.setPosition(Vector2f(width - width / 5, height / 2));

	sf::RectangleShape checkRandom(Vector2f(100, 50));
	checkRandom.setFillColor(Color(80, 185, 240));
	checkRandom.setPosition(button.getPosition().x-button.getSize().x/2, button.getPosition().y+30);

	sf::FloatRect buttonBox(button.getPosition().x-button.getSize().x/2, button.getPosition().y-button.getSize().y/2, button.getSize().x, button.getSize().y);

	sf::Text buttonName;
	buttonName.setCharacterSize(18);
	buttonName.setString("Generate!");
	buttonName.setPosition(Vector2f(button.getPosition().x - button.getSize().x / 2 + 10, button.getPosition().y-9));
	buttonName.setFont(font);

	sf::Text checkRandomName;
	checkRandomName.setCharacterSize(18);
	checkRandomName.setString("Randomize!");
	checkRandomName.setPosition(Vector2f(checkRandom.getPosition().x + 2, checkRandom.getPosition().y + 10 ));
	checkRandomName.setFont(font);
	
	sf::FloatRect checkRandomBox(button.getPosition().x - button.getSize().x / 2, button.getPosition().y + 30, button.getSize().x, button.getSize().y);

	sf::Text explain1;
	sf::Text explain2;
	sf::Text signature;

	explain1.setPosition(width - 280, 10);
	explain2.setPosition(width - 280, 36);
	explain1.setCharacterSize(12);
	explain2.setCharacterSize(12);
	explain1.setString("Generate uses dictionary to create nickanme");
	explain2.setString("Randomize uses random length and characters");
	explain1.setFont(font);
	explain2.setFont(font);
	signature.setPosition(5, height - 20);
	signature.setCharacterSize(10);
	signature.setString("Created by Mateusz Szczepanski 2017");
	signature.setColor(Color(32, 133, 191));
	signature.setFont(font);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		mousePositionFloat = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

		window.clear();
		window.draw(background);
		button.setFillColor(Color(80, 185, 240));
		checkRandom.setFillColor(Color(80, 185, 240));
		if (checkRandomBox.contains(mousePositionFloat)) {
			if (Mouse::isButtonPressed(Mouse::Button::Left)) {
				name = random_string(generateLenght());
			}
			checkRandom.setFillColor(Color(11, 81, 122));
		}
		if (buttonBox.contains(mousePositionFloat)) {
			if (Mouse::isButtonPressed(Mouse::Button::Left)) {
				name = random_string_dict(dictionary);
			}
			button.setFillColor(Color(11, 81, 122));
		}
		
		text.setString(name);

		window.draw(text);
		window.draw(button);
		window.draw(buttonName);
		window.draw(checkRandom);
		window.draw(checkRandomName);
		window.draw(explain1);
		window.draw(explain2);
		window.draw(signature);
		window.display();
	}

	return 0;
}

int generateLenght() {
	int length;
	length = rand() % 20 + 1;
	return length;
}



string random_string(size_t length)
{
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	string str(length, 0);
	generate_n(str.begin(), length, randchar);
	return str;
}

void pushwords(vector<string> &dict) {
	string str;
	fstream file("dictionary.txt");
	while (file >> str) {
		dict.push_back(str);
	}
}

string random_string_dict(vector<string> &dict) {
	string str;
	string left, right;
	int l;
	int r;
	r = rand() % dict.size() + 0;
	l = rand() % dict.size() + 0;
	if (r == l) {
		r = rand() % dict.size() + 0;
	}
	left = dict[l];
	right = dict[r];
	str = left+right;
	return str;
}