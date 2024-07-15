#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace sf;
using namespace std;

int main()
{
	int wigth = 800 , length = 850;
	//創建視窗
    RenderWindow window(VideoMode(wigth,length), "Snake");
	
	//貪食蛇設定
    vector<RectangleShape> snake;
	
    RectangleShape food;
	int snakeSize = 20;
    food.setSize(Vector2f(snakeSize,snakeSize));
    food.setPosition(rand() % (wigth/snakeSize) * snakeSize, rand() % (wigth/snakeSize) * snakeSize);
    food.setFillColor(Color::Green);

    RectangleShape ori;
    ori.setSize(Vector2f(snakeSize, snakeSize));
    ori.setPosition(wigth/2-snakeSize/2-10,wigth/2-snakeSize/2-10);
    ori.setFillColor(Color::Red);

    snake.push_back(food);
    snake.push_back(ori);

	//背景障礙物
	vector<RectangleShape> wall;

	int wallSize = snakeSize;

	for(int x=0;x<wigth;x+=20){
		for(int y=0;y<wigth;y+=20){
			if(x == 0 || x == wigth-wallSize || y == 0 || y == wigth-wallSize){
				RectangleShape temp;
				temp.setSize(Vector2f(wallSize,wallSize));
				temp.setPosition(x,y);
				temp.setFillColor(Color::Cyan);

				wall.push_back(temp);
			}
		}
	}

	//Game Interface
	
	sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        return -1; // Handle error
    }

	Text scoreText;
    scoreText.setFont(font); // Set the font
	scoreText.setPosition(20,810);
    scoreText.setCharacterSize(24); // Set the character size (in pixels)
    scoreText.setFillColor(sf::Color::White); // Set the text color
	
	//main window loop
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            int x = snake[1].getPosition().x;
            int y = snake[1].getPosition().y;
		
            if (Keyboard::isKeyPressed(Keyboard::Up) && y - snakeSize >= 0)
                snake[1].setPosition(x, y - snakeSize);
			if (Keyboard::isKeyPressed(Keyboard::Down) && y + snakeSize <= wigth-snakeSize)
                snake[1].setPosition(x, y + snakeSize);
			if (Keyboard::isKeyPressed(Keyboard::Right) && x + snakeSize <= wigth-snakeSize)
                snake[1].setPosition(x + snakeSize, y);
			if (Keyboard::isKeyPressed(Keyboard::Left) && x - snakeSize >= 0)
                snake[1].setPosition(x - snakeSize, y);

			snake[1].setFillColor(Color::Red);
			snake[1].setSize(Vector2f(snakeSize,snakeSize));

            if (snake[1].getPosition() == snake[0].getPosition()) {
                snake[0].setPosition(rand() % (wigth/snakeSize) * snakeSize, rand() % (wigth/snakeSize) * snakeSize);

                RectangleShape tail;
                tail.setSize(Vector2f(snakeSize, snakeSize));
                tail.setFillColor(Color::White);
                tail.setPosition(snake[snake.size() - 1].getPosition());
                snake.push_back(tail);
            }
			if(snake[1].getPosition().x != x || snake[1].getPosition().y != y){	
            	for (int i = snake.size() - 1; i > 2; i--) {
                	snake[i].setPosition(snake[i-1].getPosition());
            	}
            	snake[2].setPosition(x, y);
			}
			scoreText.setString("Score: " + to_string(snake.size()-2) + "	" + "Level: " + to_string((snake.size()-2) / 5));
        }

        window.clear();
        for (int i = 0; i < snake.size(); i++)
            window.draw(snake[i]);
		for(int i=0;i<wall.size();i++){
			window.draw(wall[i]);
		}
		window.draw(scoreText);
        window.display();
    }

    return 0;
}

