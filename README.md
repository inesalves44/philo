# Philosophers (42 - lvl 3)

## 1. Overview

Philosophers is a project of the common core in school 42.

The assignment involves a scenario where philosophers sit around a table with a bowl of spaghetti and forks. They alternate between eating, thinking, and sleeping. Philosophers can eat only if they have both adjacent forks. They put down forks after eating, then sleep and think. Simulation stops if a philosopher starves. The challenge is to ensure all philosophers eat without starving, while handling synchronization and avoiding deadlock. 
Philosophers don't communicate, know about others' state, or need to die. The main goal is to design a solution that prevents philosophers from starving.

![philos](https://austingwalters.com/wp-content/uploads/2014/05/Dining_philosophers4-right-987x1024.png)

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


## 4. Execution
To run the philosospher's you just need to run make! 
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
 [42 Docs](https://harm-smits.github.io/42docs/projects/minishell)
 
 [Parsing tree](https://www.geeksforgeeks.org/parse-tree-and-syntax-tree/)
 
 [Shell Language](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
 
 [Writing a shell example](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
 
 Feel free to slack me: idias-al.
