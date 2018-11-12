#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>



#define SLP 1
#define AWK 0
#define NO 1
#define YES 0 

sem_t chairs, TA,mutex;

int avail_chairs = 3 , stud_left ,TA_State = SLP , TA_Helping = NO;

void wake_up();
void * GoAsk(void * args);
void * GoHelp(void * args);
void get_cleared( int stud);

int main(int argc, char const *argv[])
{
    sem_init(&mutex,0,1);
    sem_init(&chairs,0,3); 
    sem_init(&TA,0,1);
    int n;
    printf("\n Enter the number of students\n");
    scanf("%d",&n);
    stud_left = n;


    int* sid = (int * ) malloc(sizeof(int)* n);

    for(int i = 0 ; i < n ; ++i )
    {
        sid[i] = i + 1;
    }

    pthread_t stid[n], tatid;

    pthread_create(&tatid,NULL,(void*)GoHelp,NULL);

    for(int i = 0 ; i < n ; ++i)
    {
        
        pthread_create(&stid[i],NULL,(void *)GoAsk, &sid[i]);
        
        
        
    }
    

    for( int i = 0 ; i < n ; ++i)
    {
        // if(!stud_left)
        // pthread_join(tatid,NULL);

        pthread_join(stid[i],NULL);
    }

    pthread_join(tatid,NULL);

    printf("\n All have finished their assignments!! \n");


    return 0;
}

// for the students
void * GoAsk ( void * args)
{
    int * i = (int * ) args;
    if(TA_State == SLP)
    {
        wake_up();
    }

    get_cleared(*i);
    // asking(*i);
    // sleep(1);
    // done(*i);
    pthread_exit(0);
}

// void asking( int stud)
// {
//     printf("stud %d started asking the TA");
//     sem_wait(&TA);
// }

void wake_up( )
{
      sem_wait(&mutex);
        TA_State = AWK;
        TA_Helping = YES;
        //printf("Woke the TA ans TA_state : %d" , TA_State);
        printf("\n Woke the TA");
        sem_post(&mutex);
    

}

// for the TA thread
void * GoHelp ( void * args)
{
    while(stud_left)
    {// people need not come even if they exists
        if(avail_chairs == 3 && TA_Helping == NO)
        {
            sem_wait(&mutex);
            TA_State = SLP;
            //printf("\n TA slept");
            sem_post(&mutex);
        }

        sleep(0.5);
    }
    sleep(2);
    printf("\nNo more students left TA is going to sleep");
    TA_State = SLP , TA_Helping = NO;
    pthread_exit(0);
}

void get_cleared( int stud)
{
    //    if (TA_Helping == YES)
    //     {
            if(!avail_chairs)
            printf("\nNo chairs will %d stud come back later",stud);

            else
            {
                

            

            sem_wait(&chairs);
            sem_wait(&mutex);
            printf("\n%d is waiting in chair %d",stud , avail_chairs--);
            
            sem_post(&mutex);
            }
            // sem_wait(&mutex);
            // avail_chairs -= 1 ;
            // sem_post(&mutex);
        // }
    
            
        // if( TA_Helping == NO)
        // {
            sem_wait(&TA);

            if(avail_chairs < 3)
            {
                sem_wait(&mutex);
                avail_chairs += 1 ;
                printf("\n Chair freed now chairs available: %d",avail_chairs);
                sem_post(&mutex);
                sem_post(&chairs);
            }
             if(TA_State == SLP)
             {
                wake_up();
             }
            sem_wait(&mutex);
            
            printf("\nstud %d id getting his Getting doubt cleared TA state:%d and helping TA_help: %d",stud,TA_State,TA_Helping);
            
            printf("\n stud %d got his dowbts cleared",stud);
            stud_left -= 1 ;
            printf("\n now %d number of students are left ",stud_left);
            
            printf("Post to TA success");
            TA_Helping = NO;
            sem_post(&mutex);
            sem_post(&TA);
        // }
        sleep(1);
        if(TA_State == SLP)
        printf("\nimpatient and lazy TA Slept:P");

}

