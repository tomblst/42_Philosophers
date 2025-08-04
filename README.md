# 🍝 Philosophers – Multithreading, Mutexes & Synchronization

`philosophers` is a classic **concurrency problem** from the 42 curriculum.  
The goal is to simulate the behavior of philosophers who alternate between **thinking**, **eating**, and **sleeping**, using **threads and mutexes** to avoid deadlocks and race conditions.

---

## 🧠 Project Goal

Create a simulation of the **Dining Philosophers Problem** using **pthreads** in C.  
Each philosopher has a fork and must eat using two forks (shared resources), and the challenge is to synchronize access to these forks in a **safe and efficient** manner.
---

## 🛠️ Skills & Concepts

- Multithreading (`pthread`)
- Mutexes (`pthread_mutex_t`)
- Avoiding deadlocks and starvation
- Time management and precision
- Clean data structuring
- Concurrent logging (mutex-protected output)

---

## ⚙️ How to Use

### 1. Clone & Compile

```bash
git clone https://github.com/yourusername/philosophers.git
cd philosophers
make
```
### 2. Run the simulation
```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
## 📌 Example
```
./philo 5 800 200 200
```
This launches 5 philosophers with:

  - 800ms before dying without eating
  - 200ms to eat
  - 200ms to sleep

Optional argument: if provided, the simulation ends when each philosopher has eaten that number of times.

## 🧾 Rules & Behavior

  - A philosopher must take two forks to eat.
  - If they don’t eat within time_to_die, they die.
  - They sleep for time_to_sleep, then think.
  - The simulation prints logs of each action with a timestamp.

Sample output:
```
200 2 has taken a fork
200 2 has taken a fork
200 2 is eating
200 1 has taken a fork
200 4 has taken a fork
200 4 has taken a fork
200 4 is eating
