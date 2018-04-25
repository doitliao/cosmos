/* Part of Cosmos by OpenGenus Foundation */

#include <stdio.h>
#ifdef __linux__
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#elif _WIN32
#include <windows.h>
#include <process.h>
#else
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#endif

#ifdef __linux__
void *routine(void *a)
#elif _WIN32
void routine(void *a)
#else
void *routine(void *a)
#endif
{
    int n = *(int *) a;
	#ifdef __linux__
	sleep(n);
	#elif _WIN32
    Sleep(n);
	#else
	sleep(n);
	#endif
    printf("%d ", n);
    return NULL;
}

#ifdef __linux__
void sleepSort(int arr[], int n)
{
	int i;

	pthread_t * tids = (pthread_t*) malloc(sizeof(pthread_t) * n);
	for (i = 0; i < n; i++) {
		pthread_create(&tids[i], NULL, routine, &arr[i]);
	}

	for (i = 0; i < n; i++) {
		pthread_join(tids[i], NULL);
	}
}
#elif _WIN32
void sleepSort(int arr[], int n)
{
    int i;
    HANDLE threads[n];
    for (i = 0; i < n; i++)
        threads[i] = (HANDLE)_beginthread(&routine, 0, &arr[i]);
    WaitForMultipleObjects(n, threads, TRUE, INFINITE);
    return;
}
#else
void sleepSort(int arr[], int n)
{
	int i;
	pthread_t * tids = (pthread_t*) malloc(sizeof(pthread_t) * n);

	for (i = 0; i < n; i++) {
		pthread_create(&tids[i], NULL, routine, &arr[i]);
	}

	for (i = 0; i < n; i++) {
		pthread_join(tids[i], NULL);
	}
}
#endif

int main()
{
    int arr[] = {12, 23, 42, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    sleepSort (arr, n);

    return 0;
}
