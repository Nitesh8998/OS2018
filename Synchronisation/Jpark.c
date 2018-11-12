#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>



int passenger , car;

sem_t mutex , ForCar;

void * GoDino(void * args);
void get_in_car( int person );
void get_out_car( int person );

int main ()
{
    printf("\n Enter inpout n and m\n");
    scanf("%d %d",&passenger , &car);
    int n = passenger;
    pthread_t ptid[n];

    sem_init(&mutex,0,1);
    sem_init(&ForCar,0,car);
    
    int* pipid = (int * ) malloc(sizeof(int)* n);

    for(int i = 0 ; i < n ; ++i )
    {
        pipid[i] = i + 1;
    }
    
    for(int i = 0 ; i < n ; ++i)
    {
        
        pthread_create(&ptid[i],NULL,(void *)GoDino, &pipid[i]);
        
        
        
    }

    for( int i = 0 ; i < n ; ++i)
    {
        pthread_join(ptid[i],NULL);
    }

    printf("\n All Have enjoyed the rides");

    return 0;
}


void * GoDino(void * args)
{
    
        int * i = (int *) args;
        // check_for_car(*i);
        // if(car == 0)
        // printf("\n %d waiting for his car",*i);
        //     sem_wait(&ForCar);
        // }
    
        // if(car > 0 && passenger)
        // {
        
        printf("\n Person %d  is gooing to look for his car",*i);
            get_in_car(*i );
            sleep(1);
            get_out_car(*i );
        // }
     
}

void get_in_car( int person )
{
    

    
    
    
    printf("\n %d is waiting for the car",person);
    sem_wait(&ForCar);
    
    sem_wait(&mutex);
    printf("\n %d got in his car",person);
    printf(" \n now %d cars are left & %d passengers are there",--car , --passenger);
    sleep(1);
    sem_post(&mutex);
    
}

void get_out_car( int person )
{
    printf("\n %d is getting out of car",person);
    sem_wait(&mutex);
    car++;

    sem_post(&ForCar);

    printf("\n now %d cars are left & %d passengers are there\n",car,passenger);
    sem_post(&mutex);
    
}
// void check_for_car(int person)
// {
//     if(car > 0)
//     {
//         sem_wait(&mutex);
//         printf("\n %d is got his car",person);
//         printf(" now %d cars are left %d persons are left",--passenger,--car);
//     }
// }