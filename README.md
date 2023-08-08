# Philosophers (42 - lvl 3)

## 1. Overview

Philosophers is a project of the common core in school 42.

The assignment involves a scenario where philosophers sit around a table with a bowl of spaghetti and forks. They alternate between eating, thinking, and sleeping. Philosophers can eat only if they have both adjacent forks. They put down forks after eating, then sleep and think. Simulation stops if a philosopher starves. The challenge is to ensure all philosophers eat without starving, while handling synchronization and avoiding deadlock. 
Philosophers don't communicate, know about others' state, or need to die. The main goal is to design a solution that prevents philosophers from starving.

## 2. Rules
Your(s) program(s) should take the following arguments:
number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]
◦ number_of_philosophers: The number of philosophers and also the number
of forks.
◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the sim-
ulation, they die.
◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
◦ number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.
• Each philosopher has a number ranging from 1 to number_of_philosophers.
• Philosopher number 1 sits next to philosopher number number_of_philosophers.
Any other philosopher number N sits between philosopher number N - 1 and philoso-
pher number N + 1.
6
Philosophers I never thought philosophy would be so deadly
About the logs of your program:
• Any state change of a philosopher must be formatted as follows:
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.
• A displayed state message should not be mixed up with another message.
• A message announcing a philosopher died should be displayed no more than 10 ms
after the actual death of the philosopher.
• Again, philosophers should avoid dy

## 3. The Project
To implement this project well we needed to create a few key elements: a lexer, a parser, an expander, a treatement for redirection and for commands/pipes.

## 4. Execution
To run the philosospher's you just need to run make! 
Then ./philo. And there we go!


## Make Commands
```
make all - creates executable minishell
make clean - cleans the objects
make fclean - clean executable and any library, also runs clean
make re - runs clean and fclean and then runs all to create the executable
 ```
 
 ## Links
 [42 Docs](https://harm-smits.github.io/42docs/projects/minishell)
 
 [Parsing tree](https://www.geeksforgeeks.org/parse-tree-and-syntax-tree/)
 
 [Shell Language](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
 
 [Writing a shell example](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
 
 Feel free to slack me: idias-al.
