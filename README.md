# OS2018
Operating Systems Lab

Lab Assignment List

### Lab 1- Simulation of Scheduling alogrithms

1. First Come First Serve (FJFS)
2. Shortest Job First (SJF)
3. Shortest Remaining Time (SRT)
4. Round Robin (RR)
5. Priority Scheduling non Pre-emptive(NPE)
6. Priority Scheduling Pre-emptive(PE)
7. Highest Response Ratio Next (HRRN)
8. To create autogenarted Process list using files

### Lab 2- Sorting using different Aproaches

1. Using command Line Args
2. Simulating the Usage of Variable number of arguments *(**...** notation)*
3. Simulation of Template function/class

### Synchronisation 

1. Dining Phyilosohers *C implementation*
2. Readers Writers Problem *C Demo*
3. Jurrasic Park Problem *C implementation* </br>
  **Problem Statement:**
  Jurassic Park consists of a dinosaur museum and a park for safari tiding. There are *n* passengers and *m* single-passenger cars.     Passengers wander around the museum for a while, then line up to take a ride in a safari car. When a car is available, it loads the one   passenger it can hold and rides around the park for a random amount of time. If the m cars are all out riding passenger around, the       passenger who wants to ride waits; if a car is ready to load but there are no waiting passengers, then the car waits. Use semaphores to   synchronize the *n* passenger threads/processes and the *m* car threads/processes.

4. Sleeping TA Problem *C implementation* </br>
   **Problem Statement:**
 A university computer science department has a teaching assistant (TA) who
helps undergraduate students with their programming assignments during
regular office hours. The TA’s office is rather small and has room for only one
desk with a chair and computer. There are three chairs in the hallway outside
the office where students can sit and wait if the TA is currently helping another
student. When there are no students who need help during office hours, the
TA sits at the desk and takes a nap. If a student arrives during office hours
and finds the TA sleeping, the student must awaken the TA to ask for help. If a
student arrives and finds the TA currently helping another student, the student
sits on one of the chairs in the hallway and waits. If no chairs are available, the
student will come back at a later time.
Using POSIX threads, mutex locks, and semaphores, implement a solution
that coordinates the activities of the TA and the students. Details for this
assignment are provided below.
5. Banking Scenario *Python Implementation* </br>
  **Problem Statement:**
  Bank shall maintain an overall balance and there shall be three counters supported in the bank for credit or debit operations by customers. </br>
Number of customers accessing counters should be dynamic.  A withdrawal or credit transaction by a customer thread would update both his local account balance and a global overall bank balance. </br>
Synchronize the balance statistic (both local and global ) to allow across account (differing account
numbers / customers) and within account transactions. (Two different account withdrawals should not
violate the overall balance and the order of credit / debit operations should be synchronised in the case
of within account transactions.) </br>
The setup should also allow joint account holders (two transaction id’s over the same customer id) to
perform debit (sync issue) and debit operations. </br>
Differentiate multiple transactions by the same customer with a transaction id. 
Also support a shared token generator for use by the counters which shall be mapped on to transaction
ids/customer threads for performing the transaction. </br>
Adopt standard banking convention such as a minimum balance for each customer and an minimum
overall bank balance =  minimum balance of all customers.
  
### Threading
1. Sorting MultiThreaded Versions
   *  HeapSort *Python Implementation*
   *  MergeSort *C implementation*
   *  QuickSort *C implementation*
2. Matric Inversion *C++ Implementation*
3. Prime Number Generation *C implementation*
4. MonteCarlo Method PI value computation *C implementation*
