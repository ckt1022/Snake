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
#include <ctime>

using namespace sf;
using namespace std;
RectangleShape generateRectangle(int size,int x,int y,Color a){
	RectangleShape temp;
	temp.setSize(Vector2f(size,size));
	temp.setPosition(x,y);
	temp.setFillColor(a);
	return temp;
}
vector<RectangleShape> generateWall(int wallSize,int wigth,int length,int id){
	vector<RectangleShape> wall;

	for(int x = 0;x<wigth;x+=wallSize)
		wall.push_back(generateRectangle(wallSize,x,wigth-wallSize,Color::Cyan));

	if(id == 1){
		for(int x=0;x<wigth;x+=wallSize){
			for(int y=0;y<length - wallSize;y+=wallSize){
				if(x == 0 || x == wigth-wallSize || y == 0 || y == length-wallSize)
					wall.push_back(generateRectangle(wallSize,x,y,Color::Cyan));
			}
		}
	}else if(id == 2){
		for(int x = 0;x < wigth;x += wallSize){
			for(int y = 0;y<wigth;y+=wallSize){
				if((x == 100 && y > 100) || (y == 600 && x > 300) || (y == 100 && (x >=100 && x < 500)))
					wall.push_back(generateRectangle(wallSize,x,y,Color::Cyan));
			}
		}	
	}else if(id == 3){
		for(int x = 0;x < wigth;x += wallSize){
			for(int y = 0;y < wigth;y += wallSize){
				if(((x >= 0 && x<280) || (x>=500 && x<=wigth)) && y == 380 || ((y >= 0 && y<280) || (y>=500 && y<=wigth)) && x == 380)
					wall.push_back(generateRectangle(wallSize,x,y,Color::Cyan));
			}
		}	
	}
	return wall;
}

bool checkValidStep(vector<RectangleShape> wall,int x,int y){
	for(int i=0;i<wall.size();i++){
		if(wall[i].getPosition().x == x && wall[i].getPosition().y == y)
			return false;
	}
	return true;
}
int main()
{
	srand(time(NULL));
	int wigth = 800 , length = 850;
	//創建視窗
    RenderWindow window(VideoMode(wigth,length), "Snake");
	
	//貪食蛇設定
	bool gameOver = false;
    vector<RectangleShape> snake;
	
    RectangleShape food;
	int  snakeSize = 20;
    food.setSize(Vector2f(snakeSize,snakeSize));
    food.setPosition(rand() % (wigth/snakeSize) * snakeSize, rand() % (wigth/snakeSize) * snakeSize);
    food.setFillColor(Color::Green);

    RectangleShape ori;
    ori.setSize(Vector2f(snakeSize, snakeSize));
    ori.setPosition(wigth/2-snakeSize/2-10.0,wigth/2-snakeSize/2-10.0);
    ori.setFillColor(Color::Red);

    snake.push_back(food);
    snake.push_back(ori);

	
	//字體
	Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSerif-Bold.ttf")) {
        return -1; // Handle error
    }

	//顯示訊息設定
	//起始畫面
	bool start = true;
	Text startText("Snake Game",font,60);
	startText.setPosition(175,350);
	Text option1("	Press 'Enter' to start",font,25);
	option1.setPosition(200,425);
	option1.setFillColor(Color::Blue);

	//得分訊息
	Text scoreText;
    scoreText.setFont(font);
	scoreText.setPosition(20,810);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(Color::White);
	
	//結束訊息
	Text gameText("Game Over !!",font,60);
	gameText.setPosition(175,350);
	gameText.setFillColor(Color::Red);

	Text endText("Press 'Space' to start a new game\n	Press 'LShift' to home page",font,25);
	endText.setPosition(150,425);
	endText.setFillColor(Color::White);

	Text endScore;
	endScore.setFont(font);
	endScore.setCharacterSize(20);
	endScore.setPosition(10,10);
	endScore.setFillColor(Color::White);

	//main window loop
    while (window.isOpen())
    {
		vector<RectangleShape> wall = generateWall(snakeSize,wigth,wigth,(snake.size()-2)/5);
        Event event;
	    while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
			//起始與結束介面邏輯判斷
			if(gameOver && Keyboard::isKeyPressed(Keyboard::Space) || (start && Keyboard::isKeyPressed(Keyboard::Enter))){
				snake.erase(snake.begin()+2,snake.end());
				snake[1].setSize(Vector2f(snakeSize, snakeSize));
    			snake[1].setPosition(wigth/2-snakeSize/2-10,wigth/2-snakeSize/2-10);
    			snake[1].setFillColor(Color::Red);
				
				int tempX,tempY;
				do{
					tempX = rand() % (wigth/snakeSize) * snakeSize;
					tempY = rand() % (wigth/snakeSize) * snakeSize;
				}while(!checkValidStep(wall,tempX,tempY));
					
				snake[0].setPosition(tempX,tempY);

				gameOver = false;
				if(start)
					start = false;
			}
			if(gameOver && Keyboard::isKeyPressed(Keyboard::RShift))
				start = true;

			//snake head move
            int x = snake[1].getPosition().x;
            int y = snake[1].getPosition().y;
		
            if (Keyboard::isKeyPressed(Keyboard::Up) && y - snakeSize >= 0){
                snake[1].setPosition(x, y - snakeSize);
			}else if (Keyboard::isKeyPressed(Keyboard::Down) && y + snakeSize <= wigth-snakeSize){
                snake[1].setPosition(x, y + snakeSize);
			}else if (Keyboard::isKeyPressed(Keyboard::Right) && x + snakeSize <= wigth-snakeSize){
                snake[1].setPosition(x + snakeSize, y);
			}else if (Keyboard::isKeyPressed(Keyboard::Left) && x - snakeSize >= 0){
                snake[1].setPosition(x - snakeSize, y);
			}

			snake[1].setFillColor(Color::Red);
			snake[1].setSize(Vector2f(snakeSize,snakeSize));
			
			//when snake meet food
            if (snake[1].getPosition() == snake[0].getPosition()) {
				int tempX,tempY;
				do{
					tempX = rand() % (wigth/snakeSize) * snakeSize;
					tempY = rand() % (wigth/snakeSize) * snakeSize;
				}while(!checkValidStep(wall,tempX,tempY));
					
				snake[0].setPosition(tempX,tempY);

				//生成尾巴
                snake.push_back(generateRectangle(snakeSize,snake[snake.size() - 1].getPosition().x,snake[snake.size() - 1].getPosition().y,Color::White));
            }

			//snake move
			if(snake[1].getPosition().x != x || snake[1].getPosition().y != y){	
            	for (int i = snake.size() - 1; i > 2; i--) {
                	snake[i].setPosition(snake[i-1].getPosition());
            	}
            	snake[2].setPosition(x, y);
			}

			//print result
			scoreText.setString("Score: " + to_string(snake.size()-2) + "	" + "Level: " + to_string((snake.size()-2) / 5));
        }

		for(int i=2;i<snake.size();i++){
			if(snake[i].getPosition() == snake[1].getPosition()){
				gameOver = true;	
			}
		}

		for(int i=0;i<wall.size();i++){
			if(wall[i].getPosition() == snake[1].getPosition())
				gameOver = true;
		}
		
		//清除畫面
        window.clear();
		
		//顯示畫面
		if(start){
			window.draw(startText);
			window.draw(option1);
		}else if(gameOver){
			endScore.setString("Final Score: "+ to_string(snake.size()-2) + "	 Level: " + to_string((snake.size())/5));
			window.draw(endScore);
			window.draw(gameText);
			window.draw(endText);
		}else{
        	for (int i = 0; i < snake.size(); i++)
            	window.draw(snake[i]);
			for(int i=0;i<wall.size();i++)
				window.draw(wall[i]);
			window.draw(scoreText);
		}
        window.display();
    }

    return 0;
}
