# Operating Systems Laboratory Exercises

This repository contains detailed reports and source code from the **Operating Systems Laboratory** course completed by Angelos Nikolaos Potamianos during the academic year 2022-2023. The projects focus on various aspects of operating systems, including shell scripting, process management, inter-process communication, and scheduling algorithms.

## Table of Contents
- [Overview](#overview)
- [Environment Setup](#environment-setup)
- [Exercises](#exercises)
  - [Project 1 - Shell Scripting and Process Communication](#project-1---shell-scripting-and-process-communication)
  - [Project 2 - Process Scheduling and Message Queues](#project-2---process-scheduling-and-message-queues)
- [Conclusions](#conclusions)
- [Author](#author)
- [License](#license)

## Overview

This repository provides detailed implementations and reports on various operating system concepts such as shell scripting, process communication, and scheduling. The exercises explore how to efficiently manage processes, perform scheduling, and synchronize tasks using semaphores and message queues. Both projects were carried out using **Kali Linux** on a **VirtualBox VM** to simulate real-world operating system environments.

## Environment Setup

To replicate the exercises, follow these steps to set up the required environment:

1. **Virtual Machine Setup**:
   - Use **Oracle VM VirtualBox** to create a virtual environment.
   - Download and install **Kali Linux 2022.3** (64-bit version).

2. **Install Required Packages**:
   - Install GCC, Make, and other build tools for compiling C code.
   - Use standard UNIX libraries such as `<sys/wait.h>`, `<mqueue.h>`, and `<unistd.h>` for process management and message queues.

3. **Execution**:
   - Compile and run the programs inside the VM, ensuring that the environment mimics the conditions described in the reports.

## Exercises

### Project 1 - Shell Scripting and Process Communication

**Objective**: This project involved writing shell scripts to manipulate log files, extract relevant information, and manage process communication using semaphores. The project also includes scheduling algorithm implementations and performance comparisons.

**Key Features**:
- **Shell Scripting**: Scripts were created to process `.log` files using various commands, such as:
  - **User Filtering**: Extract and display log entries based on a specific user (e.g., `admin`, `president`).
  - **Method Filtering**: Display log entries based on HTTP methods (e.g., `GET`, `POST`).
  - **Browser Detection**: Count the occurrences of different browsers (e.g., `Mozilla`, `Chrome`, `Safari`) in the log files.
  - **IP Protocol Filtering**: Display entries for either IPv4 or IPv6 based on user input.
  
- **Inter-Process Communication**:
  - Semaphores were implemented to synchronize and manage process execution.
  - **Task Synchronization**: Managed with semaphores to ensure that processes run in the correct sequence and avoid deadlocks.

- **Scheduling Algorithms**:
  - **First-Come First-Served (FCFS)**: Non-preemptive algorithm that executes processes in the order they arrive.
  - **Shortest Job First (SJF)**: Chooses the process with the shortest execution time.
  - **Shortest Remaining Time First (SRTF)**: A preemptive version of SJF.
  - **Round Robin (RR)**: Processes are executed in a cyclic order based on a time quantum.

The performance of these algorithms was compared based on **waiting time**, **turnaround time**, and **response time**.

📄 [Project 1 Report]([./Project-Report.pdf](https://github.com/nickpotamianos/Operating-Systems-Lab-Project/blob/main/Exercise%201/Project%20Report.pdf))

### Project 2 - Process Scheduling and Message Queues

**Objective**: The second project explores process scheduling and inter-process communication using message queues to distribute and parallelize tasks. It focuses on using multiple processes to compute the integral of a function over a specified range.

**Key Features**:
- **Process Scheduling**:
  - Implemented FCFS, SJF, and RR algorithms to manage processes.
  - Compared their performance on the basis of average waiting time, turnaround time, and CPU burst time.

- **Parallel Processing**:
  - **Message Queues**: Processes communicate using message queues, sending computed results back to the parent process.
  - **Forking**: The parent process forks multiple child processes, each responsible for computing part of the integral. Results are aggregated using a message queue.

- **Numerical Integration**:
  - The integral of the function `f(x) = log(x) * sqrt(x)` was calculated in parallel, using the trapezoidal rule to divide the workload among multiple processes.

- **Performance Metrics**:
  - The time taken for the entire computation was measured and compared for different numbers of processes, illustrating the effectiveness of parallel computation using process scheduling.

📄 [Project 2 Report]([./Exercise 2/](https://github.com/nickpotamianos/Operating-Systems-Lab-Project/blob/main/Exercise%202/Project-Report.pdf))

## Conclusions

The projects demonstrated the power of process scheduling and communication in real-world operating systems. By analyzing different scheduling algorithms, it was clear that each algorithm has its own strengths and weaknesses, depending on the context of the task. Message queues provided an efficient way to handle inter-process communication, enabling parallel computation and improving performance in multi-tasking environments.

## Author

**Angelos Nikolaos Potamianos**  
Student ID: 1084537  
Email: up1084537@upnet.gr

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
