#include <pthread.h>
#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

void* myturn(void *arg){
    int *iptr = (int*)malloc(sizeof(int));
    for(int i=0;i<8;i++){
        
        sleep(1);
        printf("MY TURN %d %d \n",i+1, *iptr);
        (*iptr)++;
    }
    return iptr;
}
void yourturn(){
    for(int i=0;i<3;i++){
        sleep(2);
        printf("YOUR TURN \n");

    }
}

int main(){
    pthread_t tid;
    int *result;
    pthread_create(&tid, NULL, myturn, NULL);
    yourturn();
    pthread_join(tid, (void *)&result);
    return 0;
}
