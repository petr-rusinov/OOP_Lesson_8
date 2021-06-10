﻿#include <iostream>
using namespace std;

// 1. 
// Написать шаблонную функцию div, которая должна вычислять результат деления двух параметров 
// и запускать исключение DivisionByZero, если второй параметр равен 0. 
// В функции main выводить результат вызова функции div в консоль, а также ловить исключения.


class DivisionByZero
{
private:
	string m_errString;
public:
	DivisionByZero() : m_errString("Division by Zero") { }
	const string& getError() const { return m_errString; }
};

template <class T>
T _div(T first, T second)
{
	if (second == 0)
		throw DivisionByZero();
	return first / second;
}

void task_1()
{
	cout << "------- TASK 1 -------" << endl;
	try
	{
		double result = _div<double>(2.2, 1);
		cout << "Result: " << result << endl;
		result = _div<double>(2.2, 0);
		cout << "Result: " << result << endl;
	}
	catch (DivisionByZero& a)
	{
		cerr << "Error: " << a.getError() << endl;
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
	cout << "------- TASK 2 -------" << endl;
	Bar b;
	int n = 0;
	do
	{
		cout << "Enter the number, 0 to exit: ";
		cin >> n;
		try
		{
			b.set(n);
		}
		catch (Ex& ex)
		{
			cerr << "Error: " << ex.getError() << endl;
		}

	} while (n);


}

// 3.
// Написать класс «робот», моделирующий перемещения робота по сетке 10x10, у которого есть метод, 
// означающий задание переместиться на соседнюю позицию. Эти методы должны запускать классы-исключения 
// OffTheField, если робот должен уйти с сетки, и IllegalCommand, если подана неверная команда 
// (направление не находится в нужном диапазоне). Объект исключения должен содержать всю необходимую 
// информацию — текущую позицию и направление движения. Написать функцию main, пользующуюся этим классом 
// и перехватывающую все исключения от его методов, а также выводящую подробную информацию о всех возникающих ошибках.
//




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
ostream& operator << (ostream& out, eDirection d)
{
	switch (d)
	{
	case eDirection::UP:
		out << "UP";
		break;
	case eDirection::DOWN:
		out << "DOWN";
		break;
	case eDirection::LEFT:
		out << "LEFT";
		break;
	case eDirection::RIGHT:
		out << "RIGHT";
		break;
	default:
		break;
	}
	return out;
}

class OffTheField
{
private:
	Coords<int> m_coords;
	eDirection m_dir;
public:
	OffTheField(Coords<int>& coords, eDirection dir) : m_coords(coords), m_dir(dir) { }
	const Coords<int>& getCoords() const
	{
		return m_coords;
	}
	const eDirection getDir() const { return m_dir; }
};

class IllegalCommand
{
private:
	int m_cmd;
public:
	IllegalCommand(int cmd) : m_cmd(cmd) { }
	int getError() { return m_cmd; }
};



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
			throw IllegalCommand(static_cast<int>(direction));
			break;
		}
		if (m_coords.getX() > m_maxX-1 || m_coords.getX() < m_minX ||  m_coords.getY() > m_maxY-1 || m_coords.getY() < m_minY)
			throw OffTheField(m_coords, direction);
			
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
	cout << "------- TASK 3 -------" << endl;
	try
	{
		cout << "Robot moving..." << endl;
		int i = 10; // >10 для исключения
		while (--i)
		{
			robot.move(eDirection::UP); robot.printCoords();
			//robot.move(eDirection::DOWN); robot.printCoords();
			//robot.move(eDirection::LEFT); robot.printCoords();
			//robot.move(eDirection::RIGHT); robot.printCoords();
		}
		robot.move(static_cast<eDirection>(100));  //тест неправильной команды
	}
	catch (OffTheField& otf)
	{
		cerr << "Error! Coords " << "X: " << otf.getCoords().getX() << ", Y: " << otf.getCoords().getY() << ", Direction: " << otf.getDir() << endl;
	}
	catch (IllegalCommand& ic)
	{
		cerr << "Error! Illegal comand: " << ic.getError() << endl;
	}

}

int main()
{
	task_1();
	task_2();
	task_3();

}
