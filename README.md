# Philosophers (42 - lvl 3)

## 1. Overview

Philosophers is a project of the common core in school 42.

The assignment involves a scenario where philosophers sit around a table with a bowl of spaghetti and forks. They alternate between eating, thinking, and sleeping. Philosophers can eat only if they have both adjacent forks. They put down forks after eating, then sleep and think. The simulation stops if a philosopher starves. The challenge is to ensure all philosophers eat without starving while handling synchronization and avoiding deadlock. 
Philosophers don't communicate, or know about others' states, or need to die. The main goal is to design a solution that prevents philosophers from starving.

![philos](https://docs.microsoft.com/en-us/cpp/parallel/concrt/media/dining_philosophersproblem.png?view=msvc-170&viewFallbackFrom=vs-2019)

## 2. Rules
The program accepts the following input arguments:

1. `number_of_philosophers`: This represents both the count of philosophers and the number of forks available.
2. `time_to_die` (in milliseconds): If a philosopher hasn't started eating within `time_to_die` milliseconds since their last meal or since the start of the simulation, they will die.
3. `time_to_eat` (in milliseconds): The duration it takes for a philosopher to finish eating. During this time, they must hold two forks.
4. `time_to_sleep` (in milliseconds): The time a philosopher spends sleeping.
5. `number_of_times_each_philosopher_must_eat` (optional): If specified, the simulation ends when all philosophers have eaten at least this many times. If not provided, the simulation stops when a philosopher dies.

- The output of the program looks something like this:
  - `timestamp_in_ms X has taken a fork`
  - `timestamp_in_ms X is eating`
  - `timestamp_in_ms X is sleeping`
  - `timestamp_in_ms X is thinking`
  - `timestamp_in_ms X died`
  Replace `timestamp_in_ms` with the current timestamp in milliseconds and `X` with the philosopher number.

## 3. The Project
We can separate this project into three parts!

### 3.1 Threating the input
For the first part of this, we need to make sure that the input is in its correct format.

Checking if there are at least 5 arguments and a maximum of 6. 

And then make sure that the arguments have only numbers.

### 3.2 Creating the Structs and Threads
To solve this problem I had to create two structs, one with all the data necessary and common to all philosophers and another for each philosopher. 

As for the threads we have one thread per philosopher (as stated in the subject) and a control thread. It is the control thread that checks if a philosopher died and then, 
stops the program.

### 3.3. Executing the program
With the threads created, we can run the program!

To ensure the aren't data races there are mutexes throughout the code. (You can check the mutexes in the header file)

To avoid deadlocks the philosophers  take the forks in a different order. Even philosophers take first the left fork, and then the right, the odd take the forks the other way around.

With all this, the philosophers can run smoothly.

## 4. Execution
To run the philosophers you just need to write make! 
Then ./philo. And there we go!

```
./philo 5 200 800 800 7
 ```

## Make Commands
```
make all - creates executable philo
make clean - cleans the objects
make fclean - cleans executable, also runs clean
make re - runs clean and fclean and then runs all to create the executable
 ```
 
 ## Links

[Theads in C](https://www.geeksforgeeks.org/thread-functions-in-c-c/)

[Multitheads in C](https://www.geeksforgeeks.org/multithreading-in-c/)

[Mutex in C](https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization)

[Greate explanation from 42 student (Jamshidbek2000)](https://www.youtube.com/watch?v=UGQsvVKwe90&t=2s)

Feel free to slack me: idias-al.
