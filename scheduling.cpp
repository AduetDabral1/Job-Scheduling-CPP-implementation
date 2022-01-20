#include <iostream>
#include <stdio.h>
#include <cstring>
#include <climits>
#include <string.h>
#define SIZE 200
using namespace std;

struct Process
{
    int P_ID; //Process ID
    int bt;   //Burst Time
    int wt;   //Waiting Time
    int tat;  //Turn Around Time
    int at;   //Arrival Time
    int ao;   //Arrival Order
    int ct;   //Completion Time
    int st;
};

class Queue
{
private:
    int items[SIZE], front, rear;

public:
    Queue()
    {
        front = -1;
        rear = -1;
    }
    // Check if the queue is full
    bool isFull()
    {
        if (front == 0 && rear == SIZE - 1)
        {
            return true;
        }
        if (front == rear + 1)
        {
            return true;
        }
        return false;
    }
    // Check if the queue is empty
    bool isEmpty()
    {
        if (front == -1)
            return true;
        else
            return false;
    }
    // Adding an element
    void enQueue(int element)
    {
        if (isFull())
        {
            cout << "Queue is full";
        }
        else
        {
            if (front == -1)
                front = 0;
            rear = (rear + 1) % SIZE;
            items[rear] = element;
        }
    }
    // Removing an element
    int deQueue()
    {
        int element;
        if (isEmpty())
        {
            return (-1);
        }
        else
        {
            element = items[front];
            if (front == rear)
            {
                front = -1;
                rear = -1;
            }
            // Q has only one element,
            // so we reset the queue after deleting it.
            else
            {
                front = (front + 1) % SIZE;
            }
            return (element);
        }
    }

    
    // Function to display status of Circular Queue
    void display()
    {
        int i;
        if (isEmpty())
        {
            cout << endl
                 << "Empty Queue" << endl;
        }
        else
        {
            cout << "Front -> " << front;
            cout << endl
                 << "Items -> ";
            for (i = front; i != rear; i = (i + 1) % SIZE)
                cout << items[i];
            cout << items[i];
            cout << endl
                 << "Rear -> " << rear;
        }
    }
    int peek()                          //Display Front Element
    {
        if (isEmpty())
        {
            return 0;
        }
        return items[front];
    }
};

void FCFS();                            //First Come First Serve Scheduling
void SJF();                             //Shortest Job First Scheduling
void Priority();                        //Priority Scheduling
void RoundRobin();                      //Round Robin Scheduling
void Gantt(Process p[], int);           //Gantt Chart for scheduling algorithms

//MAIN METHOD
int main()
{
    int choice;
    system("cls");
    cout << "Specify the scheduling algorithm to allocate processes:\n1. First Come First Serve\n2. Shortest Job First\n3. Priority Scheduling\n4. Round Robin Scheduling\n Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        FCFS();
        break;
    case 2:
        SJF();
        break;
    case 3:
        Priority();
        break;
    case 4:
        RoundRobin();
        break;
    default:
        cout << "Incorrect Input!!";
        break;
    }
    return 0;
}

//FIRST COME FIRST SERVE SCHEDULING ALGORITHM
void FCFS()
{
    int n, i, j;
    double avwt = 0, avtat = 0;
    cout << "\nEnter total number of processes: ";
    cin >> n;

    Process P[100];

    for (i = 0; i < n; i++)
        P[i].P_ID = i + 1;

    cout << "\nEnter Process Burst Time:\n";
    for (i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "]:";
        cin >> P[i].bt;
    }

    cout << "\nEnter Process Arrival Time:\n";
    for (i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "] :";
        cin >> P[i].at;
    }

    P[0].wt = 0; //waiting time for first process is 0

    //Calculating waiting time
    for (i = 1; i < n; i++)
    {
        P[i].wt = 0;
        for (j = 0; j < i; j++)
        {
            P[i].wt += P[j].bt;
        }

        if (P[i].wt < 0)
            P[i].wt = 0;
    }

    cout << "\nProcess \tArrivalTime \tBurstTime \tWaitingTime \tTurnAroundTime \tCompletionTime";
    //Calculating turnaround time and Completion Time
    for (i = 0; i < n; i++)
    {
        P[i].tat = P[i].bt + P[i].wt;
        avwt += P[i].wt;
        avtat += P[i].tat;
        P[i].ct = P[i].tat + P[i].at;
        cout << "\nP[" << P[i].P_ID << "]"
             << "\t\t" << P[i].at << "\t\t" << P[i].bt << "\t\t" << P[i].wt << " \t\t" << P[i].tat << "\t\t" << P[i].ct;
    }
    avwt /= i;
    avtat /= i;
    cout << "\n\nAverage Waiting Time:  " << avwt;
    cout << "\nAverage Turnaround Time:  " << avtat;
    cout << "\n\n";
    Gantt(P, n);
}

//SHORTEST JOB FIRST SCHEDULING ALGORITHM
void SJF()
{

    int n, i, j, c, t, count = 0, complete = 0, temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0, temp5 = 0, temp6 = 0, temp7 = 0;
    double avwt = 0, avtat = 0;

    cout << "\nEnter total number of processes: ";
    cin >> n;

    Process P[100];

    for (i = 0; i < n; i++)
        P[i].P_ID = i + 1;

    cout << "\nEnter Process Burst Time:\n";
    for (i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "]:";
        cin >> P[i].bt;
    }

    cout << "\nEnter Process Arrival Time:\n";
    for (i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "]:";
        cin >> P[i].at;
    }

    for (i = 0; i < n; i++)
    {
        if (P[i].at == 0)
        {
            count++;
        }
    }

    if (count == n)
    {
        cout << "All Processes has arrived at the same time.\nEnter Arrival Order:\n";
        for (i = 0; i < n; i++)
        {
            cout << "P[" << i + 1 << "]:";
            cin >> P[i].ao;
        }
    }

    cout << "Specify whether the Scheduling is \n1.Preemptive \n2.Non-Preemptive \n Enter your choice:";
    cin >> c;

    if (c == 2)
    {
        if (count == n)
        {
            for (i = 0; i < n - 1; i++)
            {
                for (j = 0; j < n - 1 - i; j++)
                {
                    if (P[j].bt > P[j + 1].bt || (P[j].bt == P[j + 1].bt && P[j].ao > P[j + 1].ao))
                    {
                        temp1 = P[j].bt;
                        P[j].bt = P[j + 1].bt; //Arranging Based on Shortest Burst Time
                        P[j + 1].bt = temp1;

                        temp2 = P[j].P_ID;
                        P[j].P_ID = P[j + 1].P_ID;
                        P[j + 1].P_ID = temp2;

                        if (count == n)
                        {
                            temp3 = P[j].ao;
                            P[j].ao = P[j + 1].ao;
                            P[j + 1].ao = temp3;
                        }
                        temp4 = P[j].at;
                        P[j].at = P[j + 1].at;
                        P[j + 1].at = temp4;
                    }
                }
            }
            P[0].wt = 0; //waiting time for first process is 0

            //Calculating waiting time

            for (i = 1; i < n; i++)
            {
                P[i].wt = 0;
                for (j = 0; j < i; j++)
                    P[i].wt += P[j].bt;
            }

            //Calculating Turnaround time

            for (i = 0; i < n; i++)
            {
                P[i].tat = P[i].bt + P[i].wt;
                avwt += P[i].wt;
                avtat += P[i].tat;
            }

            //Calculating Completion time

            for (i = 0; i < n; i++)
            {
                P[i].ct = P[i].tat + P[i].at;
            }

            Gantt(P, n);

            for (i = 0; i < n - 1; i++)
            {
                for (j = 0; j < n - 1 - i; j++)
                {
                    if (P[j].P_ID > P[j + 1].P_ID)
                    {
                        temp1 = P[j].bt;
                        P[j].bt = P[j + 1].bt; //Disarranging
                        P[j + 1].bt = temp1;

                        temp2 = P[j].P_ID;
                        P[j].P_ID = P[j + 1].P_ID;
                        P[j + 1].P_ID = temp2;

                        if (count == n)
                        {
                            temp3 = P[j].ao;
                            P[j].ao = P[j + 1].ao;
                            P[j + 1].ao = temp3;
                        }
                        temp4 = P[j].at;
                        P[j].at = P[j + 1].at;
                        P[j + 1].at = temp4;

                        temp5 = P[j].wt;
                        P[j].wt = P[j + 1].wt;
                        P[j + 1].wt = temp5;

                        temp6 = P[j].tat;
                        P[j].tat = P[j + 1].tat;
                        P[j + 1].tat = temp6;

                        temp7 = P[j].ct;
                        P[j].ct = P[j + 1].ct;
                        P[j + 1].ct = temp7;
                    }
                }
            }
        }
        else
        {
            int rt[n], min, shortest = 0;

            for (i = 0; i < n; i++)
            {
                rt[i] = P[i].bt;
            }

            min = INT_MAX;
            t = 0;
            while (complete != n)
            {
                for (i = 0; i < n; i++)
                {
                    if (P[i].at <= t && rt[i] > 0 && rt[i] < min)
                    {
                        if (rt[i] == min && P[i].at > P[shortest].at)
                        //Sorting if Burst Time is same on the basis of Arrival Time
                        {
                            continue;
                        }
                        min = rt[i];
                        shortest = i;
                    }
                }
                t = t + rt[shortest];
                rt[shortest] = 0;
                P[shortest].ct = t;
                complete++;
                min = INT_MAX;
            }

            for (i = 0; i < n; i++)
            {
                P[i].wt = P[i].ct - P[i].bt - P[i].at;
                if (P[i].wt < 0)
                {
                    P[i].wt = 0;
                }
                P[i].tat = P[i].bt + P[i].wt;
                avwt += P[i].wt;
                avtat += P[i].tat;
            }
        }
    }

    if (c == 1)
    {
        int rt[n], min, shortest = 0;

        for (i = 0; i < n; i++)
        {
            rt[i] = P[i].bt;
        }

        min = INT_MAX;

        for (t = 0; complete != n; t++)
        {
            for (i = 0; i < n; i++)
            {
                if (P[i].at <= t && rt[i] > 0 && rt[i] < min)
                {
                    if (rt[i] == min && (P[i].ao > P[shortest].ao || P[i].at > P[shortest].at))
                    //Sorting if Burst Time is same on the basis of Arrival Time Or Arrival Order
                    {
                        continue;
                    }
                    min = rt[i];
                    shortest = i;
                }
            }
            rt[shortest]--;
            min = rt[shortest];

            if (min == 0)
                min = INT_MAX;

            if (rt[shortest] == 0)
            {
                P[shortest].ct = t + 1;
                complete++;
            }
        }

        for (i = 0; i < n; i++)
        {
            P[i].wt = P[i].ct - P[i].bt - P[i].at;
            if (P[i].wt < 0)
            {
                P[i].wt = 0;
            }
            P[i].tat = P[i].bt + P[i].wt;
            avwt += P[i].wt;
            avtat += P[i].tat;
        }
    }
    if (count == n)
    {
        cout << "\nProcess \tBurstTime \tArrivalTime \tArrival Order   \tWaitingTime   \tTurnAroundTime  \tCompletionTime";
    }
    else
    {
        cout << "\nProcess \tBurstTime \tArrivalTime  \tWaitingTime   \tTurnAroundTime  \tCompletionTime";
    }

    for (i = 0; i < n; i++)
    {
        if (count == n)
        {
            cout << "\nP[" << P[i].P_ID << "]"
                 << "\t\t" << P[i].bt << "\t\t\t\t" << P[i].at << " \t\t\t\t" << P[i].ao << "\t\t\t\t\t" << P[i].wt << "\t\t\t\t" << P[i].tat << "\t\t\t\t\t" << P[i].ct;
        }
        else
        {
            cout << "\nP[" << P[i].P_ID << "]"
                 << "\t\t" << P[i].bt << "\t\t\t\t" << P[i].at << " \t\t\t\t" << P[i].wt << "\t\t\t\t" << P[i].tat << "\t\t\t\t\t" << P[i].ct;
        }
    }
    avwt /= i;
    avtat /= i;
    cout << "\n\nAverage Waiting Time:  " << avwt;
    cout << "\nAverage Turnaround Time:  " << avtat;
    cout << "\n\n";
}

//PRIORITY SCHEDULING ALGORITHM
void Priority()
{
    int pr[20], i, j, n, total = 0, pos, temp;
    float avg_wt = 0.0, avg_tat = 0.0;
    int is_completed[100];
    memset(is_completed, 0, sizeof(is_completed));

    Process P[100];
    cout << "\nEnter Total Number of Process:";
    cin >> n;

    for (i = 0; i < n; i++)
        P[i].P_ID = i + 1;

    cout << "\nEnter Burst Time, Arrival Time and Priority(higher the number higher the priority)\n";

    for (i = 0; i < n; i++)
    {
        cout << "\nP[" << i + 1 << "]\n";

        cout << "Burst Time: ";
        cin >> P[i].bt;

        cout << "Arrival Time: " cin >> P[i].at;

        cout << "Priority: ";
        cin >> pr[i];

        P[i].P_ID = i + 1;
    }

    int current_time = 0;
    int completed = 0;

    while (completed != n)
    {
        int index = -1;
        int max = -1;
        for (int i = 0; i < n; i++)
        {
            if (P[i].at <= current_time && is_completed[i] == 0)
            {
                if (pr[i] > max)
                {
                    max = pr[i];
                    index = i;
                }
                if (pr[i] == max)
                {
                    if (P[i].at < P[index].at)
                    {
                        max = pr[i];
                        index = i;
                    }
                }
            }
        }

        if (index != -1)
        {
            P[index].st = current_time;
            P[index].ct = P[index].st + P[index].bt;
            P[index].tat = P[index].ct - P[index].at;
            P[index].wt = P[index].tat - P[index].bt;

            avg_tat += P[index].tat;
            avg_wt += P[index].wt;

            is_completed[index] = 1;
            completed++;
            current_time = P[index].ct;
        }
        else
            current_time++;
    }

    cout << "\nProcess \tPriority    \tArrival Time     \tBurst Time   \tCompletion Time   \tWaiting Time    \tTurnAround Time";
    for (i = 0; i < n; i++)
    {
        cout << "\nP[" << P[i].P_ID << "]\t\t" << pr[i] << "\t\t\t" << P[i].at << "\t\t   " << P[i].bt << "\t\t   " << P[i].ct << "\t\t\t" << P[i].wt << "\t\t\t  " << P[i].tat;
    }

    avg_tat = (float)avg_tat / n;
    avg_wt = (float)avg_wt / n;
    cout << "\n\nAverage Waiting Time = " << avg_wt;
    cout << "\nAverage TurnAround Time = " << avg_tat << "\n\n";
    Gantt(P, n);
}

//ROUND ROBIN SCHEDULING ALGORITHM
//(Implemented by considering that process after completing its time quanta entering into ready queue and new process that enter into ready queue ,among both,the new process will enter first in Ready Queue.)
void RoundRobin()
{
    int n, count = 0, q, i, j, t = 0, f = 0, g = 0, complete = 0, temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0;
    double avwt = 0, avtat = 0;
    cout << "\nEnter total number of processes: ";
    cin >> n;

    Process P[100];

    for (i = 0; i < n; i++)
        P[i].P_ID = i + 1;

    cout << "\nEnter Process Burst Time:\n";
    for (i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "]:";
        cin >> P[i].bt;
    }

    cout << "\nEnter Process Arrival Time:\n";
    for (i = 0; i < n; i++)
    {
        cout << "P[" << i + 1 << "]:";
        cin >> P[i].at;
    }

    for (i = 0; i < n; i++)
    {
        if (P[i].at == 0)
        {
            count++;
        }
    }

    if (count == n)
    {
        cout << "All Processes has arrived at the same time.\nEnter Arrival Order:\n";
        for (i = 0; i < n; i++)
        {
            cout << "P[" << i + 1 << "]:";
            cin >> P[i].ao;
        }
    }

    cout << "\nEnter Time Quanta:\n";
    cin >> q;

    int rt[n];
    //Creating array which initially stores duplicates values of burst times and after that stores remaining time of each process
    for (i = 0; i < n; i++)
    {
        rt[i] = P[i].bt;
    }

    if (count == n) //Round Robin code for Case when Arrival Time is Same.
    {
        for (i = 0; i < n - 1; i++)
        {
            for (j = 0; j < n - 1 - i; j++)
            {
                if (P[j].ao > P[j + 1].ao)
                {
                    temp1 = P[j].at;
                    P[j].at = P[j + 1].at; //Arranging Based on Arrival Order
                    P[j + 1].at = temp1;

                    temp2 = P[j].P_ID;
                    P[j].P_ID = P[j + 1].P_ID;
                    P[j + 1].P_ID = temp2;

                    if (count == n)
                    {
                        temp3 = P[j].ao;
                        P[j].ao = P[j + 1].ao;
                        P[j + 1].ao = temp3;
                    }
                    temp4 = P[j].bt;
                    P[j].bt = P[j + 1].bt;
                    P[j + 1].bt = temp4;
                }
            }
        }

        while (complete != n)
        {
            for (i = 0; i < n; i++)
            {
                if (rt[i] <= q && rt[i] > 0)
                {
                    t = t + rt[i];
                    P[i].ct = t;
                    rt[i] = 0;
                    complete++;
                }
                else if (rt[i] > 0)
                {
                    rt[i] = rt[i] - q;
                    t = t + q;
                }
            }
        }

        for (i = 0; i < n - 1; i++)
        {
            for (j = 0; j < n - 1 - i; j++)
            {
                if (P[j].P_ID > P[j + 1].P_ID)
                {
                    temp1 = P[j].bt;
                    P[j].bt = P[j + 1].bt; //Disarranging
                    P[j + 1].bt = temp1;

                    temp2 = P[j].P_ID;
                    P[j].P_ID = P[j + 1].P_ID;
                    P[j + 1].P_ID = temp2;

                    if (count == n)
                    {
                        temp3 = P[j].ao;
                        P[j].ao = P[j + 1].ao;
                        P[j + 1].ao = temp3;
                    }
                    temp4 = P[j].at;
                    P[j].at = P[j + 1].at;
                    P[j + 1].at = temp4;
                }
            }
        }
    }
    else //Round Robin Code for Case when Arrival Time Is Different.
    {
        for (i = 0; i < n - 1; i++)
        {
            for (j = 0; j < n - 1 - i; j++)
            {
                if (P[j].at > P[j + 1].at)
                {
                    temp1 = P[j].at;
                    P[j].at = P[j + 1].at; //Arranging Based on Arrival Time
                    P[j + 1].at = temp1;

                    temp2 = P[j].P_ID;
                    P[j].P_ID = P[j + 1].P_ID;
                    P[j + 1].P_ID = temp2;

                    if (count == n)
                    {
                        temp3 = P[j].ao;
                        P[j].ao = P[j + 1].ao;
                        P[j + 1].ao = temp3;
                    }
                    temp4 = P[j].bt;
                    P[j].bt = P[j + 1].bt;
                    P[j + 1].bt = temp4;
                }
            }
        }

        Queue que1, que2, que3; //Que1 stores sorted Arrival time array
                                //Que2 stores Corresponding Burst time Of Processes based on Arrival time
                                //Que3 stores corresponding Indexes
        for (i = 0; i < n; i++)
        {
            que1.enQueue(P[i].at);
        }
        que2.enQueue(P[0].bt);
        que3.enQueue(0);
        i = 0;
        while (complete != n)
        {
            if (que1.peek() <= t)
            {
                que1.deQueue();
            }
            if (que2.peek() > 0 && que2.peek() <= q)
            {
                t = t + que2.peek();
                P[que3.peek()].ct = t;
                que2.deQueue();
                que3.deQueue();
                complete++;
                for (j = i + 1; j < n && rt[j] > 0; j++)
                {
                    if (que1.peek() <= t)
                    {
                        que1.deQueue();
                        que2.enQueue(rt[j]);
                        que3.enQueue(j);
                        i++;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else if (que2.peek() > 0 && que2.peek() > q)
            {

                t = t + q;
                f = que2.peek() - q;
                g = que3.peek();
                que2.deQueue();
                que3.deQueue();

                for (j = i + 1; j < n && rt[j] > 0; j++)
                {
                    if (que1.peek() <= t)
                    {
                        que1.deQueue();
                        que2.enQueue(rt[j]);
                        que3.enQueue(j);
                        i++;
                    }
                    else
                    {
                        break;
                    }
                }
                que2.enQueue(f);
                que3.enQueue(g);
            }
        }

        for (i = 0; i < n - 1; i++)
        {
            for (j = 0; j < n - 1 - i; j++)
            {
                if (P[j].P_ID > P[j + 1].P_ID)
                {
                    temp1 = P[j].bt;
                    P[j].bt = P[j + 1].bt; //Disarranging
                    P[j + 1].bt = temp1;

                    temp2 = P[j].P_ID;
                    P[j].P_ID = P[j + 1].P_ID;
                    P[j + 1].P_ID = temp2;

                    if (count == n)
                    {
                        temp3 = P[j].ao;
                        P[j].ao = P[j + 1].ao;
                        P[j + 1].ao = temp3;
                    }
                    temp4 = P[j].at;
                    P[j].at = P[j + 1].at;
                    P[j + 1].at = temp4;
                }
            }
        }
    }
    if (count == n)
    {
        cout << "\nProcess \tBurstTime \tArrivalTime \tArrival Order   \tWaitingTime   \tTurnAroundTime  \tCompletionTime";
    }
    else
    {
        cout << "\nProcess \tBurstTime \tArrivalTime  \tWaitingTime   \tTurnAroundTime  \tCompletionTime";
    }
    for (i = 0; i < n; i++)
    {
        P[i].wt = P[i].ct - P[i].bt - P[i].at;
        if (P[i].wt < 0)
        {
            P[i].wt = 0;
        }
        P[i].tat = P[i].bt + P[i].wt;
        avwt += P[i].wt;
        avtat += P[i].tat;
    }

    for (i = 0; i < n; i++)
    {
        if (count == n)
        {
            cout << "\nP[" << P[i].P_ID << "]"
                 << "\t\t" << P[i].bt << "\t\t\t\t" << P[i].at << " \t\t\t\t" << P[i].ao << "\t\t\t\t\t" << P[i].wt << "\t\t\t\t" << P[i].tat << "\t\t\t\t\t" << P[i].ct;
        }
        else
        {
            cout << "\nP[" << P[i].P_ID << "]"
                 << "\t\t" << P[i].bt << "\t\t\t\t" << P[i].at << " \t\t\t\t" << P[i].wt << "\t\t\t\t" << P[i].tat << "\t\t\t\t\t" << P[i].ct;
        }
    }
    avwt /= i;
    avtat /= i;
    cout << "\n\nAverage Waiting Time:  " << avwt;
    cout << "\nAverage Turnaround Time:  " << avtat;
    cout << "\n\n";
}

//Gantt Chart for all scheduling algorithms
void Gantt(Process P[], int n)
{
    int i, j;
    cout << "\n\n-----------GANTT CHART--------------\n\n";
    cout << " ";
    // print top bar
    for (i = 0; i < n; i++)
    {
        for (j = 0; j <= P[i].bt; j++)
            cout << "__";
        cout << " ";
    }
    cout << "\n\n|";

    // Printing process id in the middle
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < (P[i].bt - 1); j++)
            cout << " ";
        cout << "P[" << P[i].P_ID << "]";
        for (j = 0; j < (P[i].bt - 1); j++)
            cout << " ";
        cout << "|";
    }
    cout << "\n ";
    // Printing bottom bar
    for (i = 0; i < n; i++)
    {
        for (j = 0; j <= P[i].bt; j++)
            cout << "__";
        cout << " ";
    }
    cout << "\n"
         << endl;

    // Printing the timeline of the process
    cout << "0";
    for (i = 0; i < n; i++)
    {
        for (j = 0; j <= P[i].bt; j++)
            cout << "  ";
        if (P[i].tat > 9)
            cout << "\b\b"; // backspace : remove 1 space
        cout << P[i].tat << " ";
    }
    cout << "\n";
}
