#include<iostream>
#include<stdlib.h>		// for _kbhit()
#include<conio.h>		// for system(), getch()
#include<windows.h> 		//for slow moment of the snake it means for "sleep(10)" function
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
/*x,y is for snake head coordinate and fruitX, fruitY is for fruit co-ordinate*/
enum eDir
{
	STOP = 0, LEFT =1, RIGHT = 2, UP = 3, DOWN = 4
};
eDir dir;
/* Snake look like this after making n playing the game
	and Snake's body should follow it's mouth coordinate
	so game will be prepare so lets go
 	o	 Ooooooo---, 	O
	o					o
	o					o
	O,	----ooooooO,	o
*/
int tailX[100], tailY[100];
int nTail;

void  setUp()
{
	gameOver = false;
	dir = STOP;
	x = width/2;
	y = height/2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score= 0;

}
void draw()
{
	system("cls");
	for (int i=0; i<width+1; i++)		//Upper  wall
		cout<<"#";
	cout<<endl;

	for(int i =0; i<height; i++)	//Side wall
	{
		for(int j=0; j<width; j++)
		{
			if(j == 0)
				cout<<"\xDB";		// leFt side wall
			if(i == y && j == x)
				cout<<"O";
			else if(i == fruitY && j == fruitX)
				cout<<"F";          // Fruit of Snake
			else
			{
				bool print = false;
				for( int k=0; k<nTail; k++)		// to add body of snake
				{
					if(tailX[k] == j && tailY[k] == i)
					{
						cout<< "O";             // Mouth of Snake
						print = true;
					}

				}

				if(!print)
					cout<<" ";
			}

			if(j == width-1)
				cout<<"\xBA";		// Right side wall

		}
		cout<<endl;
	}
	for (int i=0; i<width+1; i++)		//Lower wall
		cout<<"\xC4";

	cout<<endl<<endl;
	cout<<"Score : "<<score;

}
void input()
{
	/* "_kbhit()" is a function to get input from console window
	if keyBoard key is press or Hit it will return positive number
	else return NULL(0) */
	if(_kbhit())
	{
		switch(_getch())
		{
			case 'a':
				dir = LEFT;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'w':
				dir = UP;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'x':
				gameOver = true;
				break;

		}
	}
}
void logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2x, prev2y;
	tailX[0] = x;
	tailY[0] = y;
	for( int i=1; i<nTail; i++)
	{
		prev2x = tailX[i];
		prev2y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2x;
		prevY = prev2y;

	}
	switch(dir)
	{
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		default:
			break;

	}
	//If Snake go out of the house then game over
/*	if ( x<0 || x>width || y>height || y<0)
		gameOver == true;
*/
	// I want snake go in one wall and come opposit wall
	if( x >= width) x= 0; else if (x < 0) x = width - 1;
	if( y >= height) y = 0; else if (y < 0) y = height - 1;

	for(int i=0; i<nTail; i++)
	{
		if(tailX[i] == x && tailY[i] == y)		// if snake head touch it's own body
			gameOver = true;
	}
	/*If snake find the fruit then increase score
	and change the fruite position */
	if(x==fruitX && y==fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}

int main()
{
	system("color 4e");
	setUp();
	while(!gameOver)
	{
		draw();
		input();
		logic();
		Sleep(10);
	}

	return 0;
}
