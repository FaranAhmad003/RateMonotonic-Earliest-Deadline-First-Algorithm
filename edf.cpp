#include <SFML/Graphics.hpp>
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace sf;
using namespace std;

#define arrival			0
#define execution 		1
#define deadline		2
#define period			3
#define abs_arrival		4
#define execution_copy  5
#define abs_deadline	6
#define IDLE_TASK_ID	1023   // Just a number I assigned
#define ALL 			1
#define CURRENT 		0

struct task
{
	int T[7];
	int instance;
	int alive;
	int Arrival;
	int time;

};

int gcd(int a, int b)
{
    // while (b != 0) {
    //     int t = b;
    //     b = a % b;
    //     a = t;
    // }
    // return a;
    // error here
    if(b==0)
    {
        return a;
    }
    else
    return gcd(b,a%b);
}

int lcm(int *a, int n)
{
	int res = 1, i;
	for (i = 0; i < n; i++)
	{
		res = res * a[i] / gcd(res, a[i]);
	}
	return res;
}
int hyperperiod_calc(task *t1, int n)
{
	int i = 0, ht, a[10];
	while (i < n)

	{
		a[i] = t1->T[period];
		t1++;
		i++;
	}
	ht = lcm(a, n);

	return ht;
}
void get_tasks(task *t1, int n)
{
	int i = 0;
	while (i < n)
	{
		//printf("Enter Task %d parameters\n", i + 1);
        cout<< "Enter Task " << i + 1 << " parameters\n";
		// printf("Arrival time: ");
		// scanf("%d", &t1->T[arrival]);
        cout<<"Arrival Time: ";
        cin>>t1->T[arrival];

		// printf("Execution time: ");
		// scanf("%d", &t1->T[execution]);
		// printf("Deadline time: ");
		// scanf("%d", &t1->T[deadline]);
		// printf("Period: ");
		// scanf("%d", &t1->T[period]);
             cout<<"Execution Time: ";
            cin>>t1->T[execution];

            cout<<"Deadline Time: ";
            cin>>t1->T[deadline];

            cout<<"Period Time: ";
            cin>>t1->T[period];

		t1->T[abs_arrival] = 0;
		t1->T[execution_copy] = 0;
		t1->T[abs_deadline] = 0;
		t1->instance = 0;
		t1->alive = 0;
		t1++;
		i++;
	}
}



int sp_interrupt(task *t1, int tmr, int n)
{
	int i = 0, n1 = 0, a = 0;
	task *t1_copy;
	t1_copy = t1;
	while (i < n)
	{
		if (tmr == t1->T[abs_arrival])
		{
			t1->alive = 1;
			a++;
		}
		t1++;
		i++;
	}

	t1 = t1_copy;
	i = 0;

	while (i < n)
	{
		if (t1->alive == 0)
			n1++;
		t1++;
		i++;
	}

	if (n1 == n || a != 0)
	{
		return 1;
	}

	return 0;
}

void update_abs_deadline(task *t1, int n, int all)
{
	int i = 0;
	if (all)
	{
		while (i < n)
		{
			t1->T[abs_deadline] = t1->T[deadline] + t1->T[abs_arrival];
			t1++;
			i++;
		}
	}
	else
	{
		t1 += n;
		t1->T[abs_deadline] = t1->T[deadline] + t1->T[abs_arrival];
	}
}

void update_abs_arrival(task *t1, int n, int k, int all)
{
	int i = 0;
	if (all)
	{
		while (i < n)
		{
			t1->T[abs_arrival] = t1->T[arrival] + k * (t1->T[period]);
			t1++;
			i++;
		}
	}
	else
	{
		t1 += n;
		t1->T[abs_arrival] = t1->T[arrival] + k * (t1->T[period]);
	}
}

void copy_execution_time(task *t1, int n, int all)
{
// 	int i = 0;
// 	if (all)
// 	{
// 		while (i < n)
// 		{
// 			t1->T[execution_copy] = t1->T[execution];
// 			t1++;
// 			i++;
// 		}
// 	}
// 	else
// 	{
// 		t1 += n;
// 		t1->T[execution_copy] = t1->T[execution];

// 	}
 int i=0;
    if(all)
    {
        while(i<n)
        {
            t1->T[execution_copy]=t1->T[execution];
            t1++;
            i++;
        }
    }
    else
    {
        t1=t1+n;
        t1->T[execution_copy]=t1->T[execution];
    }
}

int min(task *t1, int n, int p)
{
        // int i,min=0x7FFF;// initializing min to maximum value of 16 bit it can be done with 0 as well but for better code using operating system logics from lab 8 
    // int task_id=IDLE_TASK_ID;
    // while(i<n)
    // {
    //     if(min>t1->T[p]&&t1->alive==1)
    //     t1++;
    //     i++;
    // }
    // return task_id;
	int i = 0, min = 0x7FFF, task_id = IDLE_TASK_ID;
	while (i < n)
	{
		if (min > t1->T[p] && t1->alive == 1)
		{
			min = t1->T[p];
			task_id = i;
		}
		t1++;
		i++;
	}
	return task_id;
}
// void update_abs_updated(task* t1,int n,int k,int all)
// {
//     int i=0;
//     if(all)
//     {
//         while (i<n)
//         {
//             t1->T[abs_arrival]=t1->T[arrival]+k*(t1->T[period]);
//             t1++;
//             i++;
//             /* code */
//         }
        
//     }
//     else
//     {
//         t1=t1+n;
//         t1->T[abs_arrival]=t1->T[arrival]+k*(k*t1->T[period]);
//     }
// }
float cpu_util(task *t1, int n)
{
	int i = 0;
	float cu = 0;
	while (i < n)
	{
		cu = cu + (float)t1->T[execution] / (float)t1->T[deadline];
		t1++;
		i++;
	}
	return cu * 100;
}
int timer = 0;
//graphics library here
void drawBoxes(int numBoxes, vector<int> ids)
{
    // Create a window
    RenderWindow window(VideoMode(600, 400), "Earliest Deadline First");
    Font font;
        if (!font.loadFromFile("arial.ttf"))
    {
        // Error handling: The font file could not be loaded
        cout<<"Font cannot be loaded"<<endl;
    }
    Text text("Earliest Deadline First",font,20);
    text.setFillColor(Color::Red);
    text.setPosition(135,0);
    text.setStyle(Text::Underlined);

    
    Text IDs[ids.size()];

   // cout << "init id\n";
if(numBoxes<6){
    for (int i = 0; i < ids.size(); i++) {
        IDs[i] = Text(to_string(ids[i]), font, 12);
        IDs[i].setPosition(10 + i * 60,175);
        IDs[i].setFillColor(Color::Red);
    }}
    if(numBoxes>6){
    for (int i = 0; i < ids.size(); i++) {
        IDs[i] = Text(to_string(ids[i]), font, 12);
        IDs[i].setPosition(20 + i * 20,17);
        IDs[i].setFillColor(Color::Red);
    }}

    Text timechart;
    // Text ID(to_string(task_id),font,12);
    // ID.setPosition(10,10);
    // ID.setFillColor(Color::Red);
 vector<RectangleShape> boxes(numBoxes);
    // Create the boxes
    if(numBoxes>6)
    {
    for (int i = 0; i < numBoxes; i++)
    {
        boxes[i].setSize(Vector2f(15,15));
        boxes[i].setFillColor(Color::Transparent);
        boxes[i].setOutlineColor(Color::Red);
        boxes[i].setOutlineThickness(2);
        boxes[i].setPosition(10+(i * 20 + 10), 170);
       // Text timechart(to_string(i),font,12);

        timechart.setFillColor(Color::Red);
        timechart.setPosition(i*10+10,160);
       
    }
    }
    if(numBoxes<6)
    {
    for (int i = 0; i < numBoxes; i++)
    {
        boxes[i].setSize(Vector2f(50,50));
        boxes[i].setFillColor(Color::Transparent);
        boxes[i].setOutlineColor(Color::Red);
        boxes[i].setOutlineThickness(2);
        boxes[i].setPosition(i * 60 + 10, 150);
        Text timechart(to_string(i),font,12);;
        timechart.setFillColor(Color::Red);
        timechart.setPosition(i * 60 + 10,170);
    }
    }


    // Main loop
    while (window.isOpen())
    {
        // Process events
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        // Clear the window
        window.clear(Color::Black);

        // Draw the boxes
        for (int i = 0; i < numBoxes; i++)
        {
            window.draw(boxes[i]);
        }
        for (int i = 0; i < ids.size(); i++){
            window.draw(IDs[i]);
        }
        window.draw(text);
        // Display the window
        window.display();
    }
}
int main()
{
    task *t;
    int n,hyper_period,active_task_id;
    float cpu_utilization;
    cout<<"Enter Number of Task\n";
    cin>>n;
    if(n==0)
    {
        cout<<"no task are schedulable";
        return 0;
    }
    t=(task *) malloc(n*sizeof(task));
    get_tasks(t,n);
    cpu_utilization=cpu_util(t,n);
    cout<<"Cpu Utilization: "<<cpu_utilization;

    if(cpu_utilization>1)
    cout<<"\nTask can be scheduled\n";
    else
    cout<<"\nTask are not schedulabe/not feasible\n";

    hyper_period=hyperperiod_calc(t,n);
    copy_execution_time(t,n,ALL);
    update_abs_arrival(t,n,0,ALL);
    update_abs_deadline(t,n,ALL);

    vector<int> ids;

    while(timer<=hyper_period)
    {
        if (sp_interrupt(t, timer, n))
		{
			active_task_id = min(t, n, abs_deadline);
		}
        	if (active_task_id == IDLE_TASK_ID)
		{
			cout << timer << " Idle\n";
            ids.push_back(0);
		}
        		if (active_task_id != IDLE_TASK_ID)
		{

			if (t[active_task_id].T[execution_copy] != 0)
			{
				t[active_task_id].T[execution_copy]--;
				cout << timer << "  Task " << active_task_id + 1 << endl;
                ids.push_back(active_task_id+1);
			}

			if (t[active_task_id].T[execution_copy] == 0)
			{
				t[active_task_id].instance++;
				t[active_task_id].alive = 0;
				copy_execution_time(t, active_task_id, CURRENT);
				update_abs_arrival(t, active_task_id, t[active_task_id].instance, CURRENT);
				update_abs_deadline(t, active_task_id, CURRENT);
				active_task_id = min(t, n, abs_deadline);
			}
		}
		++timer;
    }
    free(t);
    drawBoxes(hyper_period+1,ids);
	return 0;
    
}


// int main()
// {
//     // Create a window
//     RenderWindow window(VideoMode(600, 400), "Dynamic Boxes");

//     // Ask the user for the number of boxes to create
//     int numBoxes;
//     cout << "Enter the number of boxes to create: ";
//     cin >> numBoxes;

//     // Create the boxes
//     vector<RectangleShape> boxes(numBoxes);
//     for (int i = 0; i < numBoxes; i++)
//     {
//         boxes[i].setSize(Vector2f(50, 50));
//         boxes[i].setFillColor(Color::Red);
//         boxes[i].setOutlineColor(Color::Red);
//         boxes[i].setOutlineThickness(2);
//         boxes[i].setPosition(i * 60 + 50, 150);
//     }

//     // Main loop
//     while (window.isOpen())
//     {
//         // Process events
//         Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == Event::Closed)
//             {
//                 window.close();
//             }
//         }

//         // Clear the window
//         window.clear(Color::White);

//         // Draw the boxes
//         for (int i = 0; i < numBoxes; i++)
//         {
//             window.draw(boxes[i]);
//         }

//         // Display the window
//         window.display();
//     }

//     return 0;
// }
