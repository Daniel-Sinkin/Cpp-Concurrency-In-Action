# Cpp-Concurrency-In-Action
Notes and working on the book of the same title

# Questions and Answers
## Theory
1. Define Thread
2. Define Process
3. Compare Thread and Process regarding
    1. Memory Use
    2. Context Switching behavior
    3. Application areas
4. Explain Concurrency
    1. Explain Hardware Concurrency
5. Explain Parallelism
    1. Data Parallelism
    2. Task Parallelism
6. What is the difference between Concurrency and Parallelism
7. What are the two goals of Parallelism
8. State Flynn's Taxonomy
9. Explain Simulatneous Multithreading (SMT)
10. Explain cc-NUMA
11. Compare how CPUs and GPUs work
12. What is BLAS?
13. State and interpret the Power Scaling Law for Clock Rate
14. State the Strong Scaling Law
15. State the Weak Scaling Law
16. State Moore's Law
    1. Moore's Law doesn't hold anymore, state the modern variant which does hold.

## 5.1
1. Explain what the multithreading-aware memory model in C++ is. Name its two aspects.
    - Structural Aspect, how things are laid out in memory.
    - Concurrency Aspect
2. All Data in C++ is made up of ... and each of twose occupy ... memory location.
    - Objects
    - At least one
3. Variables of fundamental types occuopy ... memory location.
    - Exactly one
4. Adjacent bit fields are part of ...
    - the same memory location
5. How are memory locations and concurrency related?
6. State what a data race is in terms of memory locations
    - Two threads access the SAME memory location, at least on of them is not atomic and
      at least one of them is a write.
7. Define what an atomic operation is
    - a indivisible operation which can't be observed before it's entirely done by another thread.
8. Which atomic variable is REQUIRED by the standard to ALWAYS be lock-free
    - `std::atomic_flag`
9. State all operations on std::atomic_flag
    - `test_and_set()`
    - `clear()`


## Coding
1. How to use std::thread, give simple basic example
    - We have some function f(int x) and then we can run it in a thread by creating a std::thread object and passing the function as first arg into the constructor and the function arg into the args after so for our example `std::thread my_thread{f, 5}`.
2. Is the order that threads run deterministic?
    - No, threads are scheduled in whatever the OS schedules them
3. What happens if you don't join(), why?
    - Terminates because the thread destructors called std::terminate
4. ScopedThread
    1. What is the benefit of ScopedThread?
        - A RAII guard for std::thread, is exception safe and makes it impossible to forget to join a thread.
    2. How to implement ScopedThread?
        - Move ownership of a thread into a ScopedThread class using std::move and join in the destructor.
    3. What should we check for in the constructor of ScopedThread?
        - Checking that the thread is actually joinable.
    4. What is the standard library implementaion called?
        - std::jthread
5. ThreadGuard
    1. What is a ThreadGuard and why would we use it?
        - Keeps a reference to a thread and joins it on leaving scope
        - Needs to outlive the thread otherwise it has a dangling reference
6. Explain the difference between ScopedThread and ThreadGuard, which one should be used?
    - ThreadGuard takes a reference and ScopedThread takes ownership of the thread.
    - ThreadGuard is error prone and should not be used.
7. Mutex
    1. What does Mutex Stand for and what are they used for?
        - (Mut)ual (Ex)clusion, it's a more fancy name for "lock"
    2. How to use Mutex in C++?
        - std::mutex, you can use .lock() to take access and .unlock() to release access.
    3. State some important Aspects to consider when using Mutexes
        - Wait Behavior, Use Case, Latency, CPU Usage, Fairness
8. How to use ScopedLock
    - It's templated over mutex type: `std::scoped_lock<std::mutex>`, just create a variable of that type and pass your mutex then it will be unlocked at the end.
    - `std::scoped_lock<std::mutex> _(mutex)`
9. Spinlock Mutex
    1. What is a SpinlockMutex
        - Burn CPU cycles while locked by continually running through
    2. How to implement it?
        - Use a `std::atomic_flag flag = ATOMIC_FLAG_INIT` and then do `flag.test_and_set` on acquire to check if we can release it and continue until you can.
10. What is the difference between ScopedLock and LockGuard, which one should you use?
    - ScopedLock came with C++17 and is more modern.
    - Behave the same on single mutex but std::scoped_lock supports multiple mutexes at the same time.
    - There is no real reason to use LockGuard if the used standard is at least C++17.

# References
* Herb Sutter Exceptional C++ 47 engineering puzzles
