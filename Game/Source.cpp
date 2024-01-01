#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Physics2D.h>

using namespace sf;
using namespace std;
using namespace Physics2D;

//Function definitions
Texture loadTexture(string);
Font loadFont(string);
Vector2f vRound(Vector2f);

int main() {
	//Initialize Game:
	Vector2f windowSize = Vector2f(1920, 1080);
	RenderWindow window(VideoMode(windowSize.x, windowSize.y), "MyGame");
	Event event;

	/*  Game stage:
	*		1: Title Screen
	*		2: Playing Game
	*		3: End Game
	*/
	int gameStage = 1;
	//Load Images for Game:
	//TODO: Remove Watermarks from Sky Image
	Texture backgroundTex = loadTexture("Art/Sky.jpg");
	Font gameFont = loadFont("Fonts/ARCADECLASSIC.TTF");
	Sprite background(backgroundTex);

	//Create starting screen text:
	Text startText;
	startText.setFont(gameFont);
	startText.setString("Click Anywhere to Play!\n");
	startText.setCharacterSize(32);
	Vector2f center = startText.getGlobalBounds().getSize() / 2.f;
	Vector2f localBounds = vRound(center + startText.getLocalBounds().getPosition());
	startText.setOrigin(localBounds);
	startText.setPosition(Vector2f(window.getSize() / 2u));

	AABB temp = AABB(Vector2f(1,1), Vector2f(3,3));
	cout << temp.getCenter().x << "," << temp.getCenter().y << " " << temp.getSize().x << "," << temp.getSize().y << endl;

	//Main Game Loop:
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (gameStage == 1 && event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					gameStage = 2;
				}
			}
		}

		window.draw(background);
		if (gameStage == 1) window.draw(startText);
		window.display();

	}
	return 0;
}

Vector2f vRound(Vector2f v) {
	return Vector2f(round(v.x), round(v.y));
}

Font loadFont(string filename) {
	Font ft;
	if (!ft.loadFromFile(filename)) {
		cout << "Error loading Font" << endl << "Path: " << filename << endl;
	}
	return ft;
}

Texture loadTexture(string filename) {
	Texture tex;
	if (!tex.loadFromFile(filename)) {
		cout << "Error loading texture" << endl << "Path: " << filename << endl;
	}
	return tex;
}