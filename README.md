# 🧠 Philosophers

## 🧾 Project Description

This project is an implementation of the **Dining Philosophers Problem**, a classic in concurrent programming. It involves:

- **Threads** (one per philosopher)  
- **Mutexes** (one per fork)  
- **Synchronization** to avoid deadlocks or starvation  
- A **monitor** that checks if a philosopher dies  

The goal is to make philosophers eat, think, and sleep **without anyone starving** and **without deadlock**.

---

## 🗃️ Files

- `sources/` : all the `.c` files organized  
- `Makefile` : to automatically compile the project  
- `philo` : the generated executable  

---

## ⚙️ Compilation

#### ▶️ To compile the project:

```bash
make
```
▶️ To recompile the project:

```bash
make re
```
🧹 To clean only .o files:

```bash
make clean
```
🧹 To clean .o files and the executable:

```bash
make fclean
```
####  🚀 Usage :

```bash
./philo.a [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]

```
###  🧩 Parameters :

number_of_philosophers	Number of philosophers (and forks)
time_to_die	Max time without eating before death (in ms)
time_to_eat	Time to eat (in ms)
time_to_sleep	Time to sleep (in ms)
number_of_times_each_philosopher_must_eat (optional)	If provided, the simulation ends when each philosopher has eaten this many times


