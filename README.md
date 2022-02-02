# Job-Scheduling-C-implementation

This is the C++ implementation of various job scheduling algorithms in the Operating Systems like FCFS, Round Robin and SJF.


**What is a job?**

In certain computer operating systems, a job is the unit of work that a computer operator (or a program called a job scheduler) gives to the operating system. For example, a job could be the running of an application program such as a weekly payroll program.



**What Does Job Scheduling Mean?**

Job scheduling is the process of allocating system resources to many different tasks by an operating system (OS). The system handles prioritized job queues that are awaiting CPU time and it should determine which job to be taken from which queue and the amount of time to be allocated for the job. This type of scheduling makes sure that all jobs are carried out fairly and on time.



**Why do we need scheduling?**

A typical process involves both I/O time and CPU time. In a uni programming system like MS-DOS, time spent waiting for I/O is wasted and CPU is free during this time. In multi programming systems, one process can use CPU while another is waiting for I/O. This is possible only with process scheduling.



**Objectives of Process Scheduling Algorithm**

          Max CPU utilization [Keep CPU as busy as possible]
          Fair allocation of CPU.
          Max throughput [Number of processes that complete their execution per time unit]
          Min turnaround time [Time taken by a process to finish execution]
          Min waiting time [Time a process waits in ready queue]
          Min response time [Time when a process produces first response]
  
  
  
**In scheduling, many different schemes are used to determine which specific job to run. Some parameters that may be considered are as follows:**

      Job priority
      Availability of computing resource
      License key if the job is utilizing a licensed software
      Execution time assigned to the user
      Number of parallel jobs permitted for a user
      Projected execution time
      Elapsed execution time
      Presence of peripheral devices
      Number of cases of prescribed events
      
      
      
**Below are different time with respect to a process**.

      Arrival Time: Time at which the process arrives in the ready queue.
      
      Completion Time: Time at which process completes its execution.
      
      Burst Time: Time required by a process for CPU execution.
      
      Turn Around Time: Time Difference between completion time and arrival time.
            Turn Around Time = Completion Time – Arrival Time
            
      Waiting Time(W.T): Time Difference between turn around time and burst time.
            Waiting Time = Turn Around Time – Burst Time




