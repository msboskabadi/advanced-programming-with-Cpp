#include <iostream>
#include <thread>
#include <mutex>
#include <random>

//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

using namespace std::chrono_literals; //for 10s to work as std::chrono::seconds(10)

const int LINE_LEN = 80;
int global_var = 0;
// Evil globals
bool running = false;
std::mutex ConsoleLock;

// This is untested on Linux but should work
#ifdef __linux__ 
void gotoxy(int x, int y)
{
	printf("%c[%d;%df", 0x1B, y, x);
}
#define clear() printf("\033[H\033[J")

#elif _WIN32
#include <Windows.h>
void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}
#define clear() system("cls");
#else
// Put your own console gotoxy() and clear() definitions here
#endif

std::string MakeBar(int value)
{
	std::string bar(value, 219); //219 is the code for █ char (used to to produce a solid line ==> ████████ )
	return bar;
}

std::string MakeBlankLine()
{
	std::string bar(LINE_LEN, ' ');
	return bar;
}

void DrawGraph(int line, int line_length, bool down)
{
	ConsoleLock.lock();
	global_var++;
	// Only need to erase a line if we're making it shorter
	if (down)
	{
		gotoxy(1, line);
		std::cout << GREEN << MakeBlankLine();
	}
	gotoxy(1, line);
	std::cout << MakeBar(line_length);
	ConsoleLock.unlock();
}

void DrawBar(int line, int speed)
{
	// Wait for the green flag so we all start at the same time
	while (!running)
		;
	while (running)
	{
		for (int i = 1; i < LINE_LEN; i++)
		{
			DrawGraph(line, i, false);			
			std::this_thread::sleep_for(std::chrono::milliseconds(speed));
		}
		for (int i = LINE_LEN - 1; i > 0; i--)
		{
			DrawGraph(line, i, true);
			std::this_thread::sleep_for(std::chrono::milliseconds(speed));
		}
	}
}

int main()
{
	//random_device is a uniformly-distributed integer random number generator that produces non-deterministic random numbers.
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(10, 100);

	// Spawn the threads
	static const int num_threads = 20;

	std::thread threads[num_threads];

	for (int i = 0; i < num_threads; ++i)
	{
		//DrawBar(i + 1, distr(eng));
		threads[i] = std::thread(DrawBar, i + 1, distr(eng));// rand()
	}

	// Go!
	running = true;

	// Let them run for a while
	std::this_thread::sleep_for(5s); //std::chrono::seconds(10)

	// Tell them to stop
	running = false;

	// Wait for them all to finish
	for (auto& thread : threads) {
		thread.join();
	}
	
	clear();

	std::cout << "\nglobal var = " << global_var << std::endl;
	return 0;
}