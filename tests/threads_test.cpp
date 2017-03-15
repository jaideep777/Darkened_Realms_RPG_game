#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
using namespace std;

void * print_message_function( void *ptr );
#define MAX 10000

main()
{
     pthread_t threads[MAX];
	int numbers[MAX];
    /* Create independent threads each of which will execute function */
	for (int i = 0; i< MAX; ++i){
     	numbers[i] = i;
	}
	
	for (int i = 0; i< MAX; ++i){
     	pthread_create( &threads[i], NULL, print_message_function, (void*)&(numbers[i]));
	}
     /* Wait till threads are complete before main continues. Unless we  */
     /* wait we run the risk of executing an exit which will terminate   */
     /* the process and all threads before the threads have completed.   */

//     pthread_join( thread1, NULL);
//     pthread_join( thread2, NULL); 
	
	for (int i=20; i< 380; ++i){
		pthread_cancel(threads[i]);
	}
	
     int a;
     cin >> a;
}

void *print_message_function( void *ptr )
{
     int * n;
     n = (int *) ptr;
	while(1){
     cout << "Im Thread number: "<< *n << '\n';
     sleep(1);
    }
}
