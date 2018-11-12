
M_M_M: M_M_M.o
	gcc M_M_M.o -o M_M_M -pthread

Monte_Pi: Monte_Pi.o
	gcc Monte_Pi.o -o Monte_Pi -pthread

Box_Plot: Box_Plot.o
	gcc Box_Plot.o -o Box_Plot -pthread

Inverse_matrice: Inverse_matrice.o
	g++ Inverse_matrice.o -pthread

Merge_Thread: Merge_Thread.o
	gcc Merge_Thread.o -pthread

quick_thread: quick_thread.o
	gcc quick_thread.o -pthread

Prime_Thread: Prime_Thread.o
	gcc Prime_Thread.o -pthread

Sched: Sched.o
	gcc Sched.o -pthread


M_M_M.o: M_M_M.c
	gcc -c M_M_M.c -pthread

Monte_Pi.o: Monte_Pi.c
	gcc -c Monte_Pi.c -pthread

Box_Plot.o: Box_Plot.c
	gcc -c Box_Plot.c -pthread

Inverse_matrice.o: Inverse_matrice.cpp
	g++ -c Inverse_matrice.cpp -pthread

Merge_Thread.o: Merge_Thread.c
	gcc -c Merge_Thread.c -pthread

quick_thread.o: quick_thread.c
	gcc -c quick_thread.c -pthread

Prime_Thread.o: Prime_Thread.c
	gcc -c Prime_Thread.c -pthread

Sched.o: Sched.c
	gcc -c Sched.c -pthread

clean:
	rm *.o

