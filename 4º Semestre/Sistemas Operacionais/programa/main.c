#include <stdio.h>
#include <pthread.h>
#include "nada.h"

int a = 0;
pthread_mutex_t count_mutex;

void chama_nada(int n){
    int i;
    for(i = 0; i < n; i++){
       nada();
    }
}

void *func(){
    int i;
    for(i = 0; i < 10000; i++){
        pthread_mutex_lock(&count_mutex);
        a++;
        pthread_mutex_unlock(&count_mutex);
        chama_nada(200);
    }
    return NULL;
}

int main(){
    int i;
    pthread_t t[8];
    pthread_mutex_init(&count_mutex, NULL);
    for(i = 0; i < 8; i++){
        pthread_create(&(t[i]), NULL, func, NULL);
        printf("Criou a thread %d.\n", i);
    }
    for(i = 0; i < 8; i++){
        pthread_join(t[i], NULL);
    }
    printf("%d", a);
    return 0;
}
