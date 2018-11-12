#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

using namespace std;

int passenger , car;

sem_t mutex , ForCar;


int main ()
{
    printf("\n Enter inpout n and m");
    scanf("%d %d",&passenger , &car);
    int n = passenger;
    pthread_t ptid[n];

    sem_init(&mutex,0,1);
    sem_init(&ForCar,0,1);

    for(int i = 0 ; i < n ; ++i)
    {
        pthread_create(&ptid[i],NULL,GoDine)
    }
    return 0;
}


void * GoDino(void * args)
{
    while(passenger > 0)
    {
        int * i = (int *)args;
        // check_for_car(*i);
        if(car == 0)
        {
            sem_wait(&ForCar);
        }
    
        if(car > 0)
        {
            get_in_car(*i);
            sleep(1);
            get_out_car(*i);
        }
    }    
}

void get_in_car( int person )
{
    printf("\n %d is got his car",person);
    sem_wait(&mutex);
    passenger--;
    car--;
    printf(" now %d cars are left & %d passengers are there\n",passenger,car);
    sleep(1);
    sem_post(&mutex);
    
}

void get_out_car( int person )
{
    printf("\n %d is getting out of car",person);
    sem_wait(&mutex);
    car++;
    if( car - 1 == 0)
    sem_post(&ForCar);

    printf(" now %d cars are left & %d passengers are there\n",passenger,car);
    sem_post(&mutex);
    
}
void check_for_car(int person)
{
    if(car > 0)
    {
        sem_wait(&mutex);
        printf("\n %d is got his car",person);
        printf(" now %d cars are left %d persons are left",--passenger,--car);
    }
}