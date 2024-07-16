#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace sf;
using namespace std;

vector<RectangleShape> generateWall(int wallSize,int wigth,int length,int id){
	vector<RectangleShape> wall;

	for(int x = 0;x<wigth;x+=wallSize){
		RectangleShape temp;
		temp.setSize(Vector2f(wallSize,wallSize));
		temp.setPosition(x,wigth-wallSize);
		temp.setFillColor(Color::Cyan);
		wall.push_back(temp);

	}
	if(id == 1){
		for(int x=0;x<wigth;x+=wallSize){
			for(int y=0;y<length - wallSize;y+=wallSize){
				if(x == 0 || x == wigth-wallSize || y == 0 || y == length-wallSize){
					RectangleShape temp;
					temp.setSize(Vector2f(wallSize,wallSize));
					temp.setPosition(x,y);
					temp.setFillColor(Color::Cyan);

					wall.push_back(temp);
				}
			}
		}
	}else if(id == 2){
		for(int x = 0;x < wigth;x += wallSize){
			for(int y = 0;y<wigth;y+=wallSize){
				if((x == 100 && y > 100) || (y == 600 && x > 300) || (y == 100 && (x >=100 && x < 500))){
					RectangleShape temp;
					temp.setSize(Vector2f(wallSize,wallSize));
					temp.setPosition(x,y);
					temp.setFillColor(Color::Cyan);

					wall.push_back(temp);

				}
			}
		}	
	}
	return wall;
}
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
	vector<RectangleShape> wall = generateWall(snakeSize,wigth,wigth,2);
	//Game Interface
	
	sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSerif-Bold.ttf")) {
        return -1; // Handle error
    }

	Text scoreText;
    scoreText.setFont(font); // Set the font
	scoreText.setPosition(20,810);
    scoreText.setCharacterSize(24); // Set the character size (in pixels)
    scoreText.setFillColor(Color::White); // Set the text color
	
	//main window loop
    while (window.isOpen())
    {
        Event event;
		bool gameOver = false;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
			
			//snake head move
			int lastMove = -1;
            int x = snake[1].getPosition().x;
            int y = snake[1].getPosition().y;
		
            if (Keyboard::isKeyPressed(Keyboard::Up) && y - snakeSize >= 0){
                snake[1].setPosition(x, y - snakeSize);
				lastMove = 1;
			}else if (Keyboard::isKeyPressed(Keyboard::Down) && y + snakeSize <= wigth-snakeSize){
                snake[1].setPosition(x, y + snakeSize);
				lastMove = 2;
			}else if (Keyboard::isKeyPressed(Keyboard::Right) && x + snakeSize <= wigth-snakeSize){
                snake[1].setPosition(x + snakeSize, y);
				lastMove = 3;
			}else if (Keyboard::isKeyPressed(Keyboard::Left) && x - snakeSize >= 0){
                snake[1].setPosition(x - snakeSize, y);
				lastMove = 4;
			}

			snake[1].setFillColor(Color::Red);
			snake[1].setSize(Vector2f(snakeSize,snakeSize));
			
			//when snake meet food
            if (snake[1].getPosition() == snake[0].getPosition()) {
                snake[0].setPosition(rand() % (wigth/snakeSize) * snakeSize, rand() % (wigth/snakeSize) * snakeSize);

                RectangleShape tail;
                tail.setSize(Vector2f(snakeSize, snakeSize));
                tail.setFillColor(Color::White);
                tail.setPosition(snake[snake.size() - 1].getPosition());
                snake.push_back(tail);
            }

			//snake move
			if(snake[1].getPosition().x != x || snake[1].getPosition().y != y){	
            	for (int i = snake.size() - 1; i > 2; i--) {
                	snake[i].setPosition(snake[i-1].getPosition());
            	}
            	snake[2].setPosition(x, y);
			}

			for(int i=2;i<snake.size();i++){
				if(snake[i].getPosition() == snake[1].getPosition()){
					window.close();	
				}
			}

			//print result
			scoreText.setString("Score: " + to_string(snake.size()-2) + "	" + "Level: " + to_string((snake.size()-2) / 5));
        }

        window.clear();
        for (int i = 0; i < snake.size(); i++)
            window.draw(snake[i]);
		for(int i=0;i<wall.size();i++)
			window.draw(wall[i]);
		window.draw(scoreText);
        window.display();
    }

    return 0;
}

