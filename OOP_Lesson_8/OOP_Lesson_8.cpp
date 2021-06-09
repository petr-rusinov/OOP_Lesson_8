#include <iostream>
using namespace std;

// 1. 
// Написать шаблонную функцию div, которая должна вычислять результат деления двух параметров 
// и запускать исключение DivisionByZero, если второй параметр равен 0. 
// В функции main выводить результат вызова функции div в консоль, а также ловить исключения.

#define DivisionByZero 1

template <class T>
T _div(T first, T second)
{
	if (second == 0)
		throw (DivisionByZero);
	return first / second;
}

void task_1()
{
	try
	{
		double result = _div<double>(2.2, 0);
	}
	catch (int a)
	{
		cerr << "Error: " << a << endl;
	}
}

// 2. 
// Написать класс Ex, хранящий вещественное число x и имеющий конструктор по вещественному числу, 
// инициализирующий x значением параметра. Написать класс Bar, хранящий вещественное число y 
// (конструктор по умолчанию инициализирует его нулем) и имеющий метод set с единственным вещественным параметром a. 
// Если y + a > 100, возбуждается исключение типа Ex с данными a*y, иначе в y заносится значение a. 
// В функции main завести переменную класса Bar и в цикле в блоке try вводить с клавиатуры целое n. 
// Использовать его в качестве параметра метода set до тех пор, пока не будет введено 0. 
// В обработчике исключения выводить сообщение об ошибке, содержащее данные объекта исключения.

class Ex
{
private:
	double m_x;
public:
	Ex(double x) : m_x(x) { }
	const double getError() const { return m_x; }
};

class Bar
{
private:
	double m_y;
public:
	Bar() { m_y = 0; }
	void set(double a)
	{
		if (m_y + a > 100)
			throw Ex(m_y * a);
		else
			m_y = a;
	}
};

void task_2()
{
	Bar b;
	try
	{
		b.set(10);
		b.set(100);
	}
	catch (Ex& ex)
	{
		cerr << ex.getError() << endl;
	}
}

// 3.
// Написать класс «робот», моделирующий перемещения робота по сетке 10x10, у которого есть метод, 
// означающий задание переместиться на соседнюю позицию. Эти методы должны запускать классы-исключения 
// OffTheField, если робот должен уйти с сетки, и IllegalCommand, если подана неверная команда 
// (направление не находится в нужном диапазоне). Объект исключения должен содержать всю необходимую 
// информацию — текущую позицию и направление движения. Написать функцию main, пользующуюся этим классом 
// и перехватывающую все исключения от его методов, а также выводящую подробную информацию о всех возникающих ошибках.
//

class OffTheField
{

};

class IllegalCommand
{

};

template <class T>
class Coords
{
	T m_x, m_y;
public:
	Coords() : Coords(0, 0) { }
	Coords(T x, T y) : m_x(x), m_y(y) { }
	T getX() const { return m_x; }
	T getY() const { return m_y; }
	void setX(T x) { m_x = x; }
	void setY(T y) { m_y = y; }
	void setCoords(T x, T y) { m_x = x; m_y = y; }
	void incX(T dx) { m_x += dx; }
	void incY(T dy) { m_y += dy; }
};


enum class eDirection { UP, DOWN, LEFT, RIGHT };
class Robot
{
private:
	const int m_maxX = 10;
	const int m_maxY = 10;
	const int m_minX = 0;
	const int m_minY = 0;
	Coords<int> m_coords;
public:
	Robot() : m_coords(0, 0) { }
	void move(eDirection direction)
	{
		switch (direction)
		{
		case eDirection::UP:
			m_coords.incY(1);
			break;
		case eDirection::DOWN:
			m_coords.incY(-1);
			break;
		case eDirection::LEFT:
			m_coords.incX(-1);
			break;
		case eDirection::RIGHT:
			m_coords.incX(1);
			break;
		default:
			throw IllegalCommand();
			break;
		}
		if (m_coords.getX() > m_maxX-1 || m_coords.getX() < m_minX ||  m_coords.getY() > m_maxY-1 || m_coords.getY() < m_minY)
			throw OffTheField();
			
	}
	const Coords<int>& getCoords() const
	{
		return m_coords;
	}
	void setCoords(const Coords<int>& coords)
	{
		m_coords = coords;
	}
	void printCoords() const
	{
		cout << "Coords: " << m_coords.getX() << ", " << m_coords.getY() << endl;
	}
};


void task_3()
{
	Robot robot;
	Coords<int> c(0, 0);
	robot.setCoords(c);
	Coords<int> cc = robot.getCoords();

	try
	{
		cout << "Moving up..." << endl;
		int i = 10;
		while (--i)
		{
			robot.move(eDirection::UP); robot.printCoords();
		}
	}
	catch (OffTheField& otf)
	{
		cerr << "Error!" << endl;
	}

	try
	{
		cout << endl << "Moving down..." << endl;
		int i = 10;

		while (--i)
		{
			robot.move(eDirection::DOWN); robot.printCoords();
		}
	}
	catch (OffTheField& otf)
	{
		cerr << "Error!" << endl;
	}
	try
	{
		cout << endl << "Moving right..." << endl;
		int i = 10;

		while (--i)
		{
			robot.move(eDirection::RIGHT); robot.printCoords();
		}
	}
	catch (OffTheField& otf)
	{
		cerr << "Error!" << endl;
	}

	try
	{
		cout << endl << "Moving left..." << endl;
		int i = 10;

		while (--i)
		{
			robot.move(eDirection::LEFT); robot.printCoords();
		}
	}
	catch (OffTheField& otf)
	{
		cerr << "Error!" << endl;
	}
}

int main()
{
	//task_1();
	//task_2();
	task_3();

}
