
#include "RateMonotonic.h"
#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int LCM(int n1, int n2) 
{

  int Value, check = 1;
  Value = (n1 > n2) ? n1 : n2;

  while (check)
  {
      if (Value % n1 == 0 && Value % n2 == 0)
      {
          return Value;
      }
      Value++;
  }
  return 0;
}

 bool Compare_Period(Process &p1, Process &p2) 
 {
   return (p1.period < p2.period);
 }

void Sort(vector<Process>& tasks) 
{
    /*
  for (int i = 0; i < tasks.size(); ++i) 
  {
    for (int j = 0; j < tasks.size() - i; ++j)
     {
      if (tasks[j].period > tasks[j + 1].period) 
      {
        int temp = tasks[j].period;
        tasks[j].period = tasks[j + 1].period;
        tasks[j + 1].period = temp;
      }
    }
  }*/

  sort(tasks.begin(), tasks.end(),Compare_Period);
}

int Get_Next_Arrival_Time(const vector<Process>& tasks)
{
    int next_value = tasks[0].arrival;

    for (int i = 0; i < tasks.size(); i++)
    {
        if (next_value > tasks[i].arrival)
        {
            next_value = tasks[i].arrival;
        }   
    }
    return next_value;
}

 void Rate_Monotonic(vector<Process> tasks)
  {
      {
      //    Sort(tasks);
      //    int Size = tasks.size();

      //    vector<int> Chart(HyperPeriod);

      //    for (int j = 0; j < Size; j++)
      //    {
      //        tasks[j].priority = Size - j;                                       //?  Sets priority according to increasing period
      //        tasks[j].remaining_time = tasks[j].execution_time;                  //   At Start, the remaining time willl be equal to total execution time

      //    }

      //    for (int j = 0; j < HyperPeriod; j++)
      //    {
      //        int Highest_Priority = 0;

      //        for (int j = 0; j < Size; j++)
      //        {
      //            if (tasks[j].period <= j && tasks[j].remaining_time > 0 && tasks[j].priority > Highest_Priority)
      //            {
      //                Highest_Priority = tasks[j].priority;
      //            }

      //            if (Highest_Priority > 0)
      //            {
      //                for (int k = 0; k < Size; k++)
      //                {
      //                    if (tasks[k].priority == Highest_Priority)
      //                    {
      //                        tasks[k].remaining_time--;
      //                        Chart[j] = tasks[k].id;

      //                        tasks[k].deadline = tasks[k].period;

      //                        if (tasks[k].remaining_time == 0)
      //                        {
      //                            tasks[k].remaining_time = tasks[k].execution_time;
      //                            tasks[k].period += tasks[k].period;
      //                            tasks[k].priority = Size - j;
      //                        }
      //                        break;
      //                    }
      //                }
      //            }
      //        }
      //    }
      //    for (int j = 0; j < Size; j++)
      //    {
      //        cout << Chart[j] << "  ";
      //    }


      //    Print_Gantt_Chart(Chart);

      }

        vector<int> pro(HyperPeriod);
        vector<int> wait_time(HyperPeriod);
        
      int index =0;

     ofstream File;
     File.open("RM_Schedular.txt");
     //File << tasks.size() << endl;

     Sort(tasks);

     int Current_Time = 0;
     int Size = tasks.size();

     for (int i = 0; i < Size; i++) 
     {
         tasks[i].remaining_time = tasks[i].execution_time;
         tasks[i].deadline = tasks[i].period;
     }

     cout << "\n\nGANTT CHART:  " << endl;
     cout << "PID    Tasks Processed     Time\n";
     int End_Time = tasks[0].period;                        // final time 
     
     for (Process& p : tasks)
     {
         End_Time = LCM(End_Time, p.period);
     }

     while (Current_Time <= End_Time)
     {
         int Next_Process = -1;
         int Minimum_Deadline = 99999999;
         int Tasks_Processed = 1;
         int Waiting_Time = 0;

         for (int i = 0; i < Size; i++)
         {
             if (tasks[i].remaining_time > 0)
             {
                 if ((tasks[i].deadline < Minimum_Deadline) && (Current_Time >= tasks[i].arrival))
                 {
                     Next_Process = i;
                     Minimum_Deadline = tasks[i].deadline;
                     break;
                 }
             }
         }

         if (Next_Process == -1) 
         {
             Waiting_Time = Get_Next_Arrival_Time(tasks) - Current_Time;
             Current_Time = Current_Time + Waiting_Time;

             cout << "wait" << "      -> " << Waiting_Time << "             Time = " << Current_Time << '\n';
             pro[index] = Current_Time;
             wait_time[index] = Waiting_Time; 
             index++;

             File << 0 << " " << Waiting_Time << endl;
             continue;
         }

         tasks[Next_Process].remaining_time = tasks[Next_Process].remaining_time - Tasks_Processed;

         Current_Time = Current_Time + Tasks_Processed;


         cout << "P" << tasks[Next_Process].id << "        -> " << Tasks_Processed << "             Time = " << Current_Time << endl;
         File << tasks[Next_Process].id << " " << Tasks_Processed << endl;
         pro[index] = tasks[Next_Process].id;
             wait_time[index] = Current_Time; 
             index++;

         if (tasks[Next_Process].remaining_time == 0) 
         {
             tasks[Next_Process].deadline =  tasks[Next_Process].period;
             tasks[Next_Process].remaining_time = tasks[Next_Process].execution_time;
             tasks[Next_Process].arrival += tasks[Next_Process].period;
         }
     }
   // drawBoxes(pro.size(),pro);
     cout << endl;  File.close();
}

void ChangeInterface(int x)
{

    if (x == 1)
    {
        system("color F0");		//white
    }
    else if (x == 2)
    {
        system("color 1F");		//blue
    }
    else if (x == 3)
    {
        system("color 2F");		//green
    }
    else if (x == 4)
    {
        system("color 5F");		//purple
    }
    else if (x == 6)
    {
        system("color 8E");	    //gray
    }
    else
    {
        system("color 31");
    }
}

void Print_Gantt_Chart(vector<int> Chart)
{

  cout << "RM Scheduling Gantt Chart:  " << endl;

  for (int j = 0; j < HyperPeriod; j++) 
  {
    if (j % 10 == 0)
    {
      cout << "|";
    }

    if (Chart[j] != -1)
    {
      cout << "P" << Chart[j];
    } 
    else
    {
      cout << ".";
    }
  }
  cout << "|\n";

}

 int HCF(int a, int b) 
 {
   if (b == 0) 
   {
     return a;
   }
   return HCF(b, a % b);
 }

int Calculate_HyperPeriod(vector<Process> &tasks) 
{
  for(int i=0 ;i< tasks.size(); i++)
  {
    HyperPeriod = LCM(HyperPeriod,tasks[i].period);
  }
  return HyperPeriod;
}

bool Is_Scheduleable(vector<Process> tasks)
{
      int Size = tasks.size();
      double Utilization_Value = 0;
      for (int j = 0; j < Size; j++)
      {
          Utilization_Value += (double)tasks[j].execution_time / (double)tasks[j].period;
      }
    
       
      if (Utilization_Value <= 1.00)
      {
          // double Check_value = Size * (pow(2.0, 1.0 / Size) - 1.0);

          //if (Utilization_Value <= Check_value)
          //{
            //  return true;
          //}

          return true;
      }
      else
      {
          return false;
      }

}


// // //graphics
// void drawBoxes(int numBoxes, vector<int> ids)
// {
//     // Create a window
//     RenderWindow window(VideoMode(600, 400), "Rate Monotonic Schedule");
//     Font font;
//         if (!font.loadFromFile("arial.ttf"))
//     {
//         // Error handling: The font file could not be loaded
//         cout<<"Font cannot be loaded"<<endl;
//     }
//     Text text("Rate Monotonic Schedule",font,20);
//     text.setFillColor(Color::Black);
//     text.setPosition(135,0);
//     text.setStyle(Text::Underlined);
    
    
//     Text IDs[ids.size()];

//    // cout << "init id\n";
// if(numBoxes<6){
//     for (int i = 0; i < ids.size(); i++) {
//         IDs[i] = Text(to_string(ids[i]), font, 12);
//         IDs[i].setPosition(10 + i * 60,175);
//         IDs[i].setFillColor(Color::Black);
//     }}
//     if(numBoxes>6){
//     for (int i = 0; i < ids.size(); i++) {
//         IDs[i] = Text(to_string(ids[i]), font, 12);
//         IDs[i].setPosition(20 + i * 20,170);
//         IDs[i].setFillColor(Color::Black);
//     }}

//     Text timechart;
//     // Text ID(to_string(task_id),font,12);
//     // ID.setPosition(10,10);
//     // ID.setFillColor(Color::Black);
//  vector<RectangleShape> boxes(numBoxes);
//     // Create the boxes
//     if(numBoxes>6)
//     {
//     for (int i = 0; i < numBoxes; i++)
//     {
//         boxes[i].setSize(Vector2f(15,15));
//         boxes[i].setFillColor(Color::Transparent);
//         boxes[i].setOutlineColor(Color::Black);
//         boxes[i].setOutlineThickness(2);
//         boxes[i].setPosition(10+(i * 20 + 10), 170);
//        // Text timechart(to_string(i),font,12);

//         timechart.setFillColor(Color::Black);
//         timechart.setPosition(i*10+10,160);
       
//     }
//     }
//     if(numBoxes<6)
//     {
//     for (int i = 0; i < numBoxes; i++)
//     {
//         boxes[i].setSize(Vector2f(50,50));
//         boxes[i].setFillColor(Color::Transparent);
//         boxes[i].setOutlineColor(Color::Black);
//         boxes[i].setOutlineThickness(2);
//         boxes[i].setPosition(i * 60 + 10, 150);
//         Text timechart(to_string(i),font,12);;
//         timechart.setFillColor(Color::Black);
//         timechart.setPosition(i * 60 + 10,170);
//     }
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
//         for (int i = 0; i < ids.size(); i++){
//             window.draw(IDs[i]);
//         }
//         window.draw(text);
//         // Display the window
//         window.display();
//     }
// }


int main()
{

    ChangeInterface(4);

    int Total_Processes = 0;
    cout << "Enter Number of Process  =  ";
    cin >> Total_Processes;


    vector<Process> Tasks(Total_Processes);
    for (int i = 0; i < Total_Processes; i++)
    {
        cout << "Enter Execution time of P" << i + 1 << ":     ";
        cin >> Tasks[i].execution_time;

        cout << "Enter Period of P" << i + 1 << ":     ";
        cin >> Tasks[i].period;

        Tasks[i].id = i + 1;
        Tasks[i].deadline = Tasks[i].period;
    }

    Calculate_HyperPeriod(Tasks);
   
    
    if (Is_Scheduleable(Tasks))
    {

        Rate_Monotonic(Tasks);
    }
    else
    {
        cout << "Cannot Be Scheduled with Rate Monotonic Algorithm " << endl;
    }
    

    return 0;
}