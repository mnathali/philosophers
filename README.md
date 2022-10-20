# philosophers
## Description

The project is about solving much known problem of dining philosophers. While solving problem we have introduced to mutex and semaphore concepts.
To do this we create a model of this situation.
In mandatory part there are threads that created using pthread_create(3) function and tese threads are our philosophers.
To start eating each philosopher should take two forks. Because there is a fork between each philosopher, they can not eat at the same time.
In this simulation forks are mutexes for mandatory part and semaphores for bonus part.
But for bonus part we create child proccesses using fork(2) to imitate a new philosopher instead of threads.

## Compilling and launch

In each folder there is a Makefile. Use it to create binary.

To right launch the program it should take as paremeters some information:

◦ number_of_philosophers.

◦ time_to_die (in milliseconds).
  
◦ time_to_eat (in milliseconds).
  
◦ time_to_sleep (in milliseconds).
  
◦ number_of_times_each_philosopher_must_eat (optional argument).
  
Example: ```./philo 5 800 200 200```
  
## interesting feature
  
In bonus part i use semaphores not only to create a bunch of forks but to communicate child proccesses with it's parent and between each other.
It made it possible to change a semaphore by child process to indicate that one of the childs died or have eaten enough times.
Then parent blocks semaphores that represent forks and philosophers wait until parent don't let them left it's routine cycle.
So proccesses can communicate with each other using semaphores even if they dont have shared data.
