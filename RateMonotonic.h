#include <iostream>
#include <math.h>
//#include<Windows.h>
#include <numeric>
#include <algorithm>
#include<fstream>
#include <vector>
#include<SFML/Window.hpp>
using namespace sf;
static int HyperPeriod = 1;
using namespace std;

struct Process
{
	int id;
	int execution_time;
	int period;
	int arrival;
	int deadline;
	int remaining_time;
	int priority;

};

static int LCM(int, int);
bool Compare_Period(Process&, Process&);
bool Compare_Deadline(Process&, Process&);
static void Rate_Monotonic(vector<Process>);
static int Calculate_HyperPeriod(vector<Process>&);
static bool Is_Scheduleable(vector<Process>);
void ChangeInterface(int);
int HCF(int, int);
void Print_Gantt_Chart(vector<int>);
void drawBoxes(int , vector<int> );