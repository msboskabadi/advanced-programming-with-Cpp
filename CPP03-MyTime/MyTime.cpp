#include "MyTime.h"

void MyTime::print()
{
	cout << setw(2) << setfill('0') << h << ":" << setw(2) << setfill('0') 
		<< m << ":" << setw(2) << setfill('0') << s << "\n";
}

void MyTime::print_standard()
{
	int h2 = (h > 12) ? h % 12 : h;
	cout << setw(2) << setfill('0') << h2 << ":" << setw(2) << setfill('0') << m << ":"
		<< setw(2) << setfill('0') << s;

	(h >= 12) ? cout << " PM\n" : cout << " AM\n";
}
