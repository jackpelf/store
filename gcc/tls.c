#include <stdlib.h>    
#include <stdio.h>    
#include <malloc.h>    
#include <string.h>    
#include <pthread.h>    
int main(int argc, char **argv)    
{    
    static pthread_key_t thread_key1;    
    static pthread_key_t thread_key2;    
    static pthread_key_t thread_key3;    
    char *addr1 = (char *)malloc(5);    
    char *addr2 = (char *)malloc(42343232);    
    pthread_key_create (&thread_key1, NULL);    
    pthread_key_create (&thread_key2, NULL);    
    pthread_key_create (&thread_key3, NULL);    
    pthread_setspecific (thread_key1, addr1);    
    pthread_setspecific (thread_key2, addr2);    
    pthread_setspecific (thread_key3, "1111111111");    

    printf("threadkey1: %p\n", addr1);    
    printf("threadkey2: %p\n", addr2);    
    printf("ok\n");    
    sleep(32423);
}    
