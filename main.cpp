#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <random>

using namespace sf;
using namespace std;

int main()
{
	int wigth = 650;
	int length = 650;
    RenderWindow window(VideoMode(wigth,length), "Snake");

    vector<RectangleShape> snake;
	
    RectangleShape food;
	int snakeSize = 10;
    food.setSize(Vector2f(snakeSize, snakeSize));
    food.setPosition(rand() % (wigth/10) * snakeSize, rand() % (wigth/10) * snakeSize);
    food.setFillColor(Color::Green);

    RectangleShape ori;
    ori.setSize(Vector2f(snakeSize, snakeSize));
    ori.setPosition(wigth/2-snakeSize/2,wigth/2-snakeSize/2);
    ori.setFillColor(Color::Red);

    snake.push_back(food);
    snake.push_back(ori);

	//Game Interface


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
			bool move = false;

			if(snake[1].getPosition().x != x || snake[1].getPosition().y != y)
				move = true;

            if (snake[1].getPosition() == snake[0].getPosition()) {
                snake[0].setPosition(rand() % (wigth/10) * snakeSize, rand() % (wigth/10) * snakeSize);

                RectangleShape tail;
                tail.setSize(Vector2f(snakeSize, snakeSize));
                tail.setFillColor(Color::White);
                tail.setPosition(snake[snake.size() - 1].getPosition());
                snake.push_back(tail);
            }
			if(move){	
            	for (int i = snake.size() - 1; i > 2; i--) {
                	snake[i].setPosition(snake[i-1].getPosition());
            	}
            	snake[2].setPosition(x, y);
			}

		//	scoreText.setString("Score: " + to_string(snake.size()-2));
        }

        window.clear();
        for (int i = 0; i < snake.size(); i++)
            window.draw(snake[i]);
		//window.draw(scoreText);
        window.display();
    }

    return 0;
}

