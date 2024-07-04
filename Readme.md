# Philosophers

## Overview
Philosophers is a project that simulates the classic computer science problem known as the "Dining Philosophers Problem". This project demonstrates synchronization issues and the methods to handle concurrent processes.
Features

-   Simulates the Dining Philosophers problem.
-   Uses mutexes and threads in the main project to manage concurrent access.
-   The bonus project uses processes and semaphores for synchronization.
-   Provides visualization of philosophers' states (thinking, eating, or waiting).

## Prerequisites

-   A Unix-like operating system.
-   GCC (GNU Compiler Collection) installed.
-   Basic knowledge of C programming and concurrency.

## Installation
```
git clone https://github.com/jbettini/Philosophers.git
cd Philosophers
make
```


## Usage

Run the compiled executable with the following syntax:
```
./philosophers [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat (optional)]
c

### Example:
```
./philosophers 5 800 200 200
```

## Project Structure

-   src/: Source files.
-   include/: Header files.
-   Makefile: Build configuration.
-   bonus/: Contains the implementation using processes and semaphores.