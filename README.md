# Lab Assignment: Multi-threaded Bank Teller Simulation

## Overview

This lab assignment is designed to teach students about parallel processing and synchronization in a multi-threaded environment using semaphores. The goal is to simulate a banking scenario with multiple tellers serving several customers using a semaphore to control access to the shared resources (the tellers).

## Objectives

- Implement parallel processing through multi-threading.
- Understand and implement the locking process to manage access to shared resources.

## Problem Statement

We need to simulate a bank with 3 tellers and 10 customers. Each teller can only serve one customer at a time. Customers arrive and wait in a queue until a teller is available. The service time for each customer is random, ranging from 1 to 30 seconds.

## Solution Description

The provided C program creates a multi-threaded simulation where each customer is represented by a thread. A semaphore controls the access to the tellers, ensuring that only a fixed number of customers (equal to the number of tellers) can be served at any given time.

### Files

- `a4.c`: The main C program file that contains the multi-threaded simulation.
- `Makefile`: A makefile for compiling the program with the necessary flags and libraries.
- `README.md`: This file, which describes the lab and the solution.

### Compilation and Execution

To compile the program, run the following command in the terminal:

```bash
make
```
