# Philosophers (42 - lvl 3)

## 1. Overview

Philosophers is a project of the common core in school 42.

The assignment involves a scenario where philosophers sit around a table with a bowl of spaghetti and forks. They alternate between eating, thinking, and sleeping. Philosophers can eat only if they have both adjacent forks. They put down forks after eating, then sleep and think. Simulation stops if a philosopher starves. The challenge is to ensure all philosophers eat without starving, while handling synchronization and avoiding deadlock. 
Philosophers don't communicate, know about others' state, or need to die. The main goal is to design a solution that prevents philosophers from starving.

## 2. Rules


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
