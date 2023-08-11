[![tstrassb's 42 stats](https://badge42.vercel.app/api/v2/clk7xyddm001108l1dlt4bjx7/stats?cursusId=21&coalitionId=354)](https://github.com/JaeSeoKim/badge42)

# Philosophers - Final Score [![tstrassb's 42 Philosophers Score](https://badge42.vercel.app/api/v2/clk7xyddm001108l1dlt4bjx7/project/3075704)](https://github.com/JaeSeoKim/badge42)

<h1 align="center">✋ BEWARE ✋</h1>

## If you are a 42 Student, do not copy/paste this project, it will be considered cheating and you will be grated -42.

# 42 Wolfsburg Cursus 
## Philosophers
## I never thought philosophy would be so deadly

# Contents

1. [Common Instructions](#common)
2. [Overview](#overview)
3. [Global rules](#global)
4. [Mandatory part](#manda)

# <a name="common">Common Instructions</a>

| Common Instructions | ![Logo_Monolith_small](https://user-images.githubusercontent.com/120580537/209333599-dc44418d-8ee7-42b6-8a4a-7ff328778d87.png) |
| ----- | ----- |
* Your project must be written in C.
* Your project must be written in accordance with the Norm. <br>If you have bonus files/functions, they are included in the norm check and you will receive a 0 if there is a norm error inside.
* Your functions should not quit unexpectedly (segmentation fault, bus error, double free, etc) apart from undefined behaviors. <br>If this happens, your project will be considered non functional and will receive a 0 during the evaluation.
* All heap allocated memory space must be properly freed when necessary. No leaks will be tolerated.
* If the subject requires it, you must submit a Makefile which will compile your source files to the required output <br>with the flags **-Wall**, **-Wextra** and **-Werror**, use cc, and your Makefile must not relink.
* Your **Makefile** must at least contain the rules **$(NAME)**, **all**, **clean**, **fclean** and **re**.
* To turn in bonuses to your project, you must include a rule bonus to your Makefile, which will add all the various headers, <br>librairies or functions that are forbidden on the main part of the project. <br>Bonuses must be in a different file **_bonus.{c/h}** if the subject does not specify anything else. <br>Mandatory and bonus part evaluation is done separately.
* If your project allows you to use your **libft**, you must copy its sources and its associated **Makefile** in a **libft** folder with its associated Makefile. Your project’s **Makefile** must compile the library by using its **Makefile**, then compile the project.
* We encourage you to create test programs for your project even though this work **won’t have to be submitted and won’t be graded**. <br>It will give you a chance to easily test your work and your peers’ work. You will find those tests especially useful during your defence. <br>Indeed, during defence, you are free to use your tests and/or the tests of the peer you are evaluating.
* Submit your work to your assigned git repository. Only the work in the git repository will be graded. <br>If Deepthought is assigned to grade your work, it will be done after your peer-evaluations. <br>If an error happens in any section of your work during Deepthought’s grading, the evaluation will stop.

<p align="right">
 <a href="https://github.com/Cerberus2290/Philosophers#-beware-">back to top</a>
</p>

# <a name="overview">Overview</a>

Here are the things you need to know if you want to succeed this assignment:

* One or more philosophers sit at a round table. <br>There is a large bowl of spaghetti in the middle of the table.
* The philosophers alternatively **eat**, **think**, or **sleep**. 
    * While they are eating, they are not thinking nor sleeping; 
    * while thinking, they are not eating nor sleeping; 
    * and, of course, while sleeping, they are not eating nor thinking.
* There are also forks on the table. **There are as many forks as philosophers**.
* Because serving and eating spaghetti with only one fork is very inconvenient, <br>a philosopher takes their right and their left forks to eat, one in each hand.
* When a philosopher has finished eating, they put their forks back on the table and start sleeping. <br>Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation.
* Every philosopher needs to eat and should never starve.
* Philosophers don’t speak with each other.
* Philosophers don’t know if another philosopher is about to die.
* No need to say that philosophers should avoid dying!

<p align="right">
 <a href="https://github.com/Cerberus2290/Philosophers#-beware-">back to top</a>
</p>

# <a name="global">Global rules</a>

You have to write a program for the mandatory part and another one for the bonus part (if you decide to do the bonus part). <br>They both have to comply with the following rules:

* Global variables are forbidden!
* Your program(s) should take the following arguments: <br>[number_of_philosophers] | [time_to_die] | [time_to_eat] | [time_to_sleep] | ([number_of_times_each_philosopher_must_eat] - OPTIONAL)
    * number_of_philosophers: The number of philosophers and also the number of forks.
    * time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the sim- ulation, they die.
    * time_to_eat (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
    * time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
    * number_of_times_each_philosopher_must_eat (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.
* Each philosopher has a number ranging from 1 to number_of_philosophers.
* Philosopher number 1 sits next to philosopher number number_of_philosophers. <br>Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.

About the logs of your program:

* Any state change of a philosopher must be formatted as follows:
    * **timestamp_in_ms X has taken a fork**
    * **timestamp_in_ms X is eating**
    * **timestamp_in_ms X is sleeping**
    * **timestamp_in_ms X is thinking**
    * **timestamp_in_ms X died**

*Replace **timestamp_in_ms** with the current timestamp in milliseconds and **X** with the philosopher number.*

* A displayed state message should not be mixed up with another message.
* A message announcing a philosopher died should be displayed no more than 10 ms <br>after the actual death of the philosopher.
* Again, philosophers should avoid dying!

## :heavy_exclamation_mark:</br>Your program must not have any **data races**</br>:heavy_exclamation_mark:

<p align="right">
 <a href="https://github.com/Cerberus2290/Philosophers#-beware-">back to top</a>
</p>

# <a name="manda">Mandatory part</a>

| ![Logo_Monolith_small](https://user-images.githubusercontent.com/120580537/209333599-dc44418d-8ee7-42b6-8a4a-7ff328778d87.png) | |
| ----- | ----- |
| Program name | philo |
| Turn in files | Makefile, *.h, *.c, in directory philo/ |
| Makefile | NAME, all, clean, fclean, re |
| Arguments | number_of_philosophers / time_to_die / <br>time_to_eat / time_to_sleep / [number_of_times_each_philosopher_must_eat] |
| External functions | memset, printf, malloc, free, write, <br>usleep, gettimeofday, pthread_create, <br>pthread_detach, pthread_join, pthread_mutex_init, <br>pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock |
| Libft authorized | No |
| Description | Philosophers with threads and mutexes |

The specific rules for the mandatory part are:

* Each philosopher should be a thread.
* There is one fork between each pair of philosophers. Therefore, if there are several philosophers, each philosopher has a fork on their left side and a fork on their right side. <br>If there is only one philosopher, there should be only one fork on the table.
* To prevent philosophers from duplicating forks, you should protect the forks state with a mutex for each of them.

<p align="right">
 <a href="https://github.com/Cerberus2290/Philosophers#-beware-">back to top</a>
</p>