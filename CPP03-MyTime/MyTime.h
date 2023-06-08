#pragma once
#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;
class MyTime
{
public:
	//MyTime()
	//{
	//	h = m = s = 0;
	//}
	MyTime(int h = 0, int m = 0, int s = 0)
	{
		set_hour(h).set_minute(m).set_second(s);
	}

	void print();
	void print_standard();

	MyTime& set_hour(int hour)
	{
		if (hour >= 0 && hour < 24)
			h = hour;
		else
			throw invalid_argument("hour must be between 0 & 23");

		return *this;
	}

	MyTime& set_minute(int minute)
	{
		if (minute >= 0 && minute < 60)
			m = minute;
		else
			throw invalid_argument("minute must be between 0 & 59");

		return *this;
	}

	MyTime& set_second(int second)
	{
		if (second >= 0 && second < 60)
			s = second;
		else
			throw invalid_argument("second must be between 0 & 59");

		return *this;
	}

	int get_hour() const
	{
		return h;
	}

	int get_minute() const
	{
		return m;
	}

	int get_second() const
	{
		return s;
	}

private:
	int h, m, s;
};

