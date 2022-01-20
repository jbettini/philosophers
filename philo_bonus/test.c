#include "philo.h"

int main()
{
    int i = 5;
    int pid = fork();
    if (pid)
    {
        printf("before from child %d\n", i);
        i = 0;
        printf("after from child %d\n", i);
    }
    else
    {
        
        printf("before from parent %d\n", i);
    }
}