<h1 align="center">1337🇲🇦_Philosophers_42  Kaneki</h1>
<p align="center">
  <a href="https://github.com/KanekiEzz/1337_Philosophers_42">
    <img src="https://raw.githubusercontent.com/KanekiEzz/kaneki_badges/refs/heads/main/philosophersm.png" alt="42 Badge">
  </a>
</p>


---
## **🧠 Logic, Objective, and Explanation of `philo` Implementation**  

The `philo` project simulates the **Dining Philosophers Problem**, where multiple philosophers sit at a table and must alternate between eating, sleeping, and thinking while sharing limited resources (forks). The challenge is to avoid **deadlocks** and **race conditions** while following the **rules of concurrency**.

---

## **🌟 Objectives of the Implementation**
1. **Create and Manage Threads:**  
   Each philosopher is represented by a separate **thread** that runs in parallel.
2. **Use Mutexes for Synchronization:**  
   Forks are **shared resources**, so we use **mutexes** to prevent multiple philosophers from using the same fork at the same time.
3. **Implement the Philosopher’s Lifecycle:**  
   Each philosopher goes through a cycle of:
   - **Thinking** 🤔  
   - **Taking forks and Eating** 🍝  
   - **Sleeping** 😴  
4. **Monitor for Deaths:**  
   If a philosopher goes too long without eating (`time_to_die`), the simulation **stops immediately**.


---

## **🔗 Breakdown of the Implementation**

### **1️⃣ `philo.h` (Header File)**
Defines **structures** and **function prototypes**.

### **2️⃣ `utils.c` (Time and Printing Helpers)**
- `get_time()`: Returns the current timestamp in **milliseconds**.
- `smart_sleep()`: Ensures accurate sleeping **without blocking CPU**.
- `print_status()`: Prints actions of philosophers **safely** using `pthread_mutex_lock`.

### **3️⃣ `philo_routine.c` (Philosopher's Actions)**
- **Eating**:  
  - Locks **left fork**, prints status.  
  - Locks **right fork**, prints status.  
  - Updates **last meal time**, increases **meal count**.  
  - Sleeps for `time_to_eat`.  
  - Unlocks **both forks**.  

- **Thinking and Sleeping**:  
  - After eating, the philosopher sleeps (`time_to_sleep`).  
  - Then, it **thinks** before the next cycle.  

---

### **4️⃣ `monitor.c` (Death Monitoring)**
A **separate thread** continuously checks if any philosopher has **exceeded `time_to_die`** without eating.
- If a philosopher dies, the simulation **stops immediately**.

---

### **5️⃣ `philo_init.c` (Thread and Mutex Initialization)**
- **Initializes mutexes** for forks and print locking.
- **Creates philosopher threads**.
- Each thread runs `philosopher_routine()` in parallel.

---

### **6️⃣ `main.c` (Entry Point)**
- Parses **arguments**.
- Calls **`philo_init()`** to set up philosophers and forks.
- Starts a **monitor thread** to check for deaths.
- Waits for all threads to **finish** before cleaning up.

---

## **🚀 Key Features & Concurrency Handling**
✅ **Threads** manage philosophers independently.  
✅ **Mutexes** prevent **race conditions** on forks and printing.  
✅ **Monitor thread** ensures simulation **stops on death**.  
✅ **No global variables**, keeping it **memory-safe and modular**.  

---

## **🔥 Summary**
1. **Each philosopher** runs in a **separate thread**.
2. **Mutexes** manage fork access.
3. **A monitor thread** checks for starvation.
4. **Threads stop safely** when a philosopher dies.

---

## **📌 Next Steps**
Here's a **flowchart** explaining the logic of the `philo` project, including thread creation, philosopher routines, and monitoring.

---

### **🖼️ Flowchart Structure**
1. **Main Process**  
   - Parses arguments  
   - Initializes mutexes and threads  
   - Starts the monitor thread  

2. **Philosopher Routine (Each Thread)**
   - Thinks 🤔  
   - Picks up left fork 🍴  
   - Picks up right fork 🍴  
   - Eats 🍝  
   - Puts down forks 💤  
   - Sleeps  

3. **Monitor Thread (Checks for Starvation)**
   - Continuously checks if a philosopher has **exceeded `time_to_die`**
   - If a philosopher dies, the simulation **stops**  

---



Here’s your flowchart! 📊 This visually explains the logic behind the `philo` project, including the main process, philosopher threads, and the monitor system 🚀.

# Philosophers Thread Flow

## Main Thread
```



┌──────────────────────────────────────────────────┐
│                     Main Thread                  │
│ ───────────────────────────────────────────────  │
│  1. Initialize Data                              │
│  2. Start Philosopher Threads                    │
│  3. Start Monitor Thread                         │
│  4. Wait for Monitor Thread (pthread_join)       │
│  5. Cleanup Resources and Exit                   │
└──────────────────────────────────────────────────┘

                 ⬇️
──────────────────────────────────────────────────
⬇️ **Philosopher Threads (Each Philosopher)**  
──────────────────────────────────────────────────
┌────────────────────────┐
│  Philosopher 1 (Thread)│
│  - Takes Forks         │
│  - Eats                │
│  - Sleeps              │
│  - Thinks              │
│  - Repeats             │
└────────────────────────┘
                ⬇️
           (Locks and Unlocks Forks)

┌────────────────────────┐
│  Philosopher 2 (Thread)│
│  - Takes Forks         │
│  - Eats                │
│  - Sleeps              │
│  - Thinks              │
│  - Repeats             │
└────────────────────────┘
                ⬇️
           (Locks and Unlocks Forks)
... (Same for Philosopher 3, 4, N)
──────────────────────────────────────────────────

⬇️ **Monitor Thread** (Runs in Parallel)  
──────────────────────────────────────────────────
┌───────────────────────────────┐
│       Monitor Thread          │
│  - Checks If Any Philosopher  │
│    Has Starved (time_to_die)  │
│  - If One Dies 💀 → Stops All │
│  - If All Have Eaten → Stops │
│  - Uses `stop_simulation` 🚨  │
└───────────────────────────────┘
```
