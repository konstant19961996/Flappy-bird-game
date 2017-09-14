#include <SFML/Graphics.hpp>
class Paddle
{
	sf::RenderWindow* window;
	sf::RectangleShape rectangle;
	int y;
	int player;
	int score;
public:
	Paddle (sf::RenderWindow* window, int player)
	{
		this->score=0;
		this->y=300;
		this->player=player;
		this->window = window;
		// ������������� ������ ��� ������� � ������� Vector2f
		this->rectangle.setSize(sf::Vector2f(10,100));
		// ��� �������� ��������� �������� ����� �� ������ �������� ���� � �����
		this->rectangle.setOrigin(5,50);
		// � ������������� ������� � ��������� �������
		if (this->player == 1)
		{
			this->rectangle.setPosition(25, this->y);
		}
		else
		{
			this->rectangle.setPosition(775, this->y);
		}
	}
	void setY(int y)
	{
		if ((y>=0) && (y<=600))
			this->y=y;
	}
	 // ����� ��� ��������� �������
	void draw()
	{
		this->window->draw(this->rectangle);
	}
	/* ��������� ������� ������ � ����������� �������
        ������ ����� ��������� ���������, ������ -- ��������� W � S */
	void update (float time)
	{
		if (this->player == 1)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				// �������� ��������� ������� � ����������� �� ������� �������
				this->y -= time * 0.3;
				this->setY(this->y);  // setY - ������ ��� ���������� Y
			}
			else  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				this->y += time * 0.3;
				this->setY(this->y);
			}
		}
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				this->setY(this->y - time * 0.3);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				this->setY(this->y + time * 0.3);
			}
		}
	}
};
