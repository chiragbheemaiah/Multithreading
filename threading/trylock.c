#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t mutex;
// trylock - checksif lock is available, if not exits!
void* routine(){
    if(pthread_mutex_trylock(&mutex) == 0){
        printf("Got lock! \n");
        sleep(3);
        pthread_mutex_unlock(&mutex);
    }else{
        printf("Did not get lock :(\n");
    }
}
int main(int argc, char* argv[]){

    pthread_t th[4];
    pthread_mutex_init(&mutex, NULL);
    for(int i=0;i<4;i++){
        if(pthread_create(&th[i], NULL, &routine, NULL)){
            return -1;
        }
    }
    for(int i=0;i<4;i++){
        if(pthread_join(th[i], NULL)){
            return -2;
        }
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}