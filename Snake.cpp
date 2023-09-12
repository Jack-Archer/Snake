#include <iostream>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <stdio.h>


using namespace std;

class window {
public:
	char buf[1200];
	window() {
		cls();
	}
	void cls()
	{
		for (int i = 0; i < 1200; ++i)
		{
			buf[i] = ' ';
		}
	}
	void show()
	{
		HANDLE hStdout;
		COORD destCoords;
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		destCoords.X = 0;
		destCoords.Y = 0;
		SetConsoleCursorPosition(hStdout, destCoords);


		int count = 0;
		for (int i = 0; i < 62; ++i)
		{
			cout << "#";
	    }
		cout << "\n";
		for (int i = 0; i < 1200; ++i)
		{
			if (count == 0) cout << "#";
			cout << buf[i];
			++count;
			if (count >= 60)
			{
				cout << "#\n";
				count = 0;
			}
		}
		for (int i = 0; i < 62; ++i)
		{
			cout << "#";
		}
	}
	void putchar(int x, int y, char c)
	{
		if (x < 60 && y < 20 && x >= 0 && y >= 0)
		{
			buf[(60 * y) + x] = c;
		}
	}
	char getchar(int x, int y)
	{
		if (x < 60 && y < 20 && x >= 0 && y >= 0)
			return buf[(60 * y) + x];
		else return 0;
	}
};

window field;

class figure {
public:
	char sym;
	int x;
	int y;

	void display()
	{
		field.putchar(x, y, sym);
	}
};

class snake {
public:
	vector<figure>body;
	figure food;
	int dx;
	int dy;

	snake()
	{
		food.sym = '*';
		randfood();

		figure temp;
		temp.x = 30;
		temp.y = 9;
		temp.sym = 'O';
		body.push_back(temp);
		
		for (int i = 0; i < 4; ++i)
		{
			temp.x = 30+i;
			temp.y = 10;
			temp.sym = 'o';
			body.push_back(temp);

		}
		dx = 1;
		dy = 0;
	}
	void draw()
	{
		for (int i = 0; i < body.size(); ++i)
		{
			body[i].display();
		}
	}
	void drawfood()
	{
		food.display();
	}
	void move()
	{
		for (int i = body.size() - 1; i > 0; --i)
		{
			body[i].x = body[i - 1].x;
			body[i].y = body[i - 1].y;
		}
		body[0].x = body[0].x + dx;
		body[0].y = body[0].y + dy;

	}
	void randfood()
	{
		food.x = rand() % 60;
		food.y = rand() % 20;

	}

	bool chek()
	{
		if (body[0].x == food.x && body[0].y == food.y)
		{
			body.push_back(body[1]);
			randfood();
		}
		for (int i = 1; i < body.size(); ++i)
		{
			if (body[0].x == body[i].x && body[0].y == body[i].y)
				return 0;
		}
		if (body[0].x >= 60 || body[0].y >= 20 || body[0].x < 0 || body[0].y < 0)
		{
			return 0;
		}

		return 1;
	}
};


int main() {
	srand(time(0));
	snake s;


	int key = 0;
	bool ex = 0;
	while (ex == 0)
	{
		if (_kbhit())
		{
			key = _getch();
		}
		if (key == 27){ex = 1;}

		if (key == 'a') { s.dx = -1; s.dy = 0; }
		if (key == 'd') { s.dx = 1; s.dy = 0; }
		if (key == 'w') { s.dy = -1; s.dx = 0; }
		if (key == 's') { s.dy = 1; s.dx = 0; }


		field.cls();
		s.move();
		s.draw();
		s.drawfood();
		field.show();
		if (s.chek() == 0) ex = 1;

		Sleep(200);

	}



	return 0;
}