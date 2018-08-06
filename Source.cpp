#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
RenderWindow window(VideoMode(600, 600), "Snake");

class Snake
{
	public:
	short x;
	short y;
	bool dead;
	
	int collision(short opX, short opY)
	{
		if (opX == x && opY == y)
		{
			dead = true;
		}
	}
};
int frame;
int gridSize;
char loopAround;
char leader;
bool enteredFramerate = false;
int main()
{
	bool startup = true;
	Event event0;
	int s = 600;
	if (enteredFramerate == false)
	{
		std::cout << "Enter Grid Size: ";
		std::cin >> gridSize;
		std::cout << "Enter Desired Framerate: ";
		std::cin >> frame;
		std::cout << "1 for true, 0 for false\n" << "Loop Around: ";
		std::cin >> loopAround;
		loopAround = loopAround % 2;
		std::cout << "1 for true, 0 for false" << std::endl;
		std::cout << "Leader a different color: ";
		std::cin >> leader;
		leader = leader % 2;
		enteredFramerate = true;
	}
	std::cout << "Press Enter to Continue" << std::endl;
	while (startup == true)
	{
		while (window.pollEvent(event0)) {
			if (event0.type == Event::Closed)
			{
				window.close();
				return 0;
			}
			if (event0.type == Event::KeyPressed && event0.key.code == Keyboard::Return)
			{
				startup = false;
			}
		}
	}
	int r = s / gridSize;
	int r2 = s / 2;
	int r3;
	if (gridSize <= 15)
	{
		r3 = 4;
	}
	else if (gridSize <= 20)
	{
		r3 = 3;
	}
	else if (gridSize < 30)
	{
		r3 = 2;
	}
	else
	{
		r3 = 1;
	}
	short x = gridSize / 2;
	short y = gridSize / 2;
	short lastx;
	short lasty;
	short last2x;
	short last2y;
	Snake parts[gridSize * gridSize];
	bool doneOnce = false;
	RectangleShape partRend[gridSize * gridSize];
	bool hasEaten = false;
	RectangleShape Character;
	Character.setSize(Vector2f(r - 2, r - 2));
	if (leader == 1)
	{
		Character.setFillColor(Color(0, 255, 128, 255));
	}
	else {
		Character.setFillColor(Color::Green);
	}
	
	Character.setPosition(r2, r2);
	window.setFramerateLimit(frame);
	char facing = 1;
	unsigned short foodx;
	unsigned short foody;
	short length = -1;
	foodx = rand() % gridSize;
	foody = rand() % gridSize;
	RectangleShape Food;
	Food.setSize(Vector2f(r - r3, r - r3));
	Food.setFillColor(Color::Red);
	Food.setPosition((foodx * r) + 1, (foody * r) + 1);

	while (window.isOpen())
	{
		Event event;
		window.clear();
		if (length == (gridSize * gridSize) - 1)
		{
			std::cout << "You Won!" << std::endl;
			main();
		}
		for (int l = 0; l <= gridSize; l++)
		{
			int l2 = l * r;
			RectangleShape lineh;
			RectangleShape linev;
			lineh.setSize(Vector2f(s, 1));
			linev.setSize(Vector2f(1, s));
			lineh.setFillColor(Color(128, 128, 128, 255));
			linev.setFillColor(Color(128, 128, 128, 255));
			lineh.setPosition(0, l2);
			linev.setPosition(l2, 0);
			window.draw(lineh);
			window.draw(linev);
		}
		if (doneOnce == true)
		{
			last2x = lastx;
			last2y = lasty;
		}
		lastx = x;
		lasty = y;
		if (hasEaten == true)
		{
			for (int i = length; i >= 0; i--)
			{
				if (i != 0 && i != 1)
				{
					parts[i].x = parts[i - 1].x;
					parts[i].y = parts[i - 1].y;
					parts[i].collision(x, y);
				}
				else if (i == 1) {
					parts[i].x = last2x;
					parts[i].y = last2y;
				}
				else
				{
					parts[i].x = lastx;
					parts[i].y = lasty;
				}
				partRend[i].setPosition((parts[i].x * r) + 1, (parts[i].y * r) + 1);
				window.draw(partRend[i]);
				if (parts[i].dead == true)
				{
					main();
				}
			}
		}
		if (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::W && facing != 2 && facing != 0)
			{
				facing = 0;
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up && facing != 2 && facing != 0)
			{
				facing = 0;
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::S && facing != 0 && facing != 2)
			{
				facing = 2;
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down && facing != 0 && facing != 2)
			{
				facing = 2;
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::A && facing != 1 && facing != 3)
			{
				facing = 3;
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Left && facing != 1 && facing != 3)
			{
				facing = 3;
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::D && facing != 3 && facing != 1)
			{
				facing = 1;
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Right && facing != 3 && facing != 1)
			{
				facing = 1;
			}
			
		}
		if (facing == 0)
		{
			y--;
		}
		else if (facing == 1)
		{
			x++;
		}
		else if (facing == 2)
		{
			y++;
		}
		else if (facing == 3) {
			x--;
		}
		if (x < 0)
		{
			if (loopAround == 1)
			{
				x = gridSize - 1;
			}
			else
			{
				main();
			}
		}
		else if (x > gridSize - 1)
		{
			if (loopAround == 1)
			{
				x = 0;
			}
			else
			{
				main();
			}
		}
		if (y < 0)
		{
			if (loopAround == 1)
			{
				y = gridSize - 1;
			}
			else
			{
				main();
			}
		}
		else if (y > gridSize - 1)
		{
			if (loopAround == 1)
			{
				y = 0;
			}
			else
			{
				main();
			}
		}
		if (x == foodx && y == foody)
		{
			++length;
			std::cout << "Length: " << length + 1 << std::endl;
			if (hasEaten == true)
			{
				foodx = rand() % gridSize;
				foody = rand() % gridSize;
				for (int o = length; o >= 0; o--)
				{
					if (parts[o].x == foodx && parts[o].y == foody)
					{
						foodx = rand() % gridSize;
						foody = rand() % gridSize;
					}
				}
			}
			else
			{
				foodx = rand() % gridSize;
				foody = rand() % gridSize;
			}
			parts[length].x = last2x;
			parts[length].y = last2y;
			parts[length].dead = false;
			partRend[length].setSize(Vector2f(r - 2, r - 2));
			partRend[length].setFillColor(Color::Green);
			partRend[length].setPosition((parts[length].x * r) + 1, (parts[length].y * r) + 1);
			hasEaten = true;
		}
		if (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::W && facing != 2 && facing != 0)
			{
				facing = 0;
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up && facing != 2 && facing != 0)
			{
				facing = 0;
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::S && facing != 0 && facing != 2)
			{
				facing = 2;
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down && facing != 0 && facing != 2)
			{
				facing = 2;
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::A && facing != 1 && facing != 3)
			{
				facing = 3;
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Left && facing != 1 && facing != 3)
			{
				facing = 3;
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::D && facing != 3 && facing != 1)
			{
				facing = 1;
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Right && facing != 3 && facing != 1)
			{
				facing = 1;
			}
			
		}
		Character.setPosition((x * r) + 1, (y * r) + 1);
		Food.setPosition((foodx * r) + 1, (foody * r) + 1);
		window.draw(Food);
		window.draw(Character);
		window.display();
		doneOnce = true;
	}

	return 0;
}