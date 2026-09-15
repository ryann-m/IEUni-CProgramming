# Advanced C Coursework

> A collection of C coursework completed during my Computer Science studies at IE University in Madrid (2024–2026), before transferring to Worcester Polytechnic Institute to study Robotics Engineering.

## About

This repository contains selected C assignments and projects from my Advanced C coursework.

The repository is primarily an academic record of the work I completed during the course, so the organization is not intended to represent a polished software project. Some assignments are small exercises, while others are more complete programs covering topics such as memory management, pointers, data structures, file processing, testing, networking, and concurrency.

The focus here is the C code and what I built while learning the language. The build configuration was provided as part of the course setup and is included only where useful for reference.

## Coursework

| Project | Main topics | Files / examples |
| --- | --- | --- |
| **Error Handling** | Assertions, `errno`, error conditions | `errorHandler.c`, `errorHeader.h` |
| **Unit Testing** | Functions, headers, test cases | `name_length.c`, `name_length.h`, `test_name_length.c` |
| **Pointers** | Pointers, pointer arithmetic, null checks, passing by pointer | `pointersQuestions.c`, `pointersSwap.c` |
| **Pointer Casting** | Type conversion, pointer reinterpretation | `ptrCast.c`, `ptrCast2.c` |
| **Memory Layout** | Stack, heap, addresses, alignment | `pointersQuestions.txt` |
| **Dynamic Memory** | `malloc`, `realloc`, arrays, input handling | `mallocLibrary.c`, `mallocHeader.h`, `mallocTest.c` |
| **Structures and Testing** | Structs, functions, test cases | `rectangle.c`, `rectangleLib.c`, `rectangleTests.c`, `myRectangle.h` |
| **String Handling** | C strings, copying, concatenation | `strCat.c` |
| **File Processing** | File I/O, tokenization, sorting, word frequencies | `filePracticeLibrary.c`, `filePracticeMain.c`, `filePracticeHeader.h` |
| **Logging** | Enums, function pointers, file output | `logger.c`, `loggerHeader.h` |
| **Linked List** | Structs, dynamic allocation, traversal, callbacks | `linkedLib.c`, `linkedHeader.h`, `linkedTest.c` |
| **Concurrency** | Threads, work division, result aggregation | `concurrencyLib.c`, `concurrencyHeader.h`, `concurrencyMain.c`, `concurrencyTest.c` |
| **TCP Networking** | Sockets, client/server communication, HTTP-style messages | `tcp_time_client.c`, `tcp_time_server.c` |
| **UDP Networking** | Datagrams, `sendto`, `recvfrom`, client/server communication | `udp_echo_client.c`, `udp_echo_server.c` |

## What the Projects Cover

### Error Handling

Exercises focused on handling invalid operations and runtime errors using C mechanisms such as assertions and `errno`.

### Unit Testing

A small `name_length` library with a separate test file. The implementation counts the characters in a name while ignoring spaces, with tests covering empty strings and names containing spaces.

### Pointers and Memory

Several exercises work directly with addresses and pointers, including:

- passing values through pointers
- swapping values through pointers
- pointer arithmetic
- null-pointer checks
- examining memory layout
- pointer casting and reinterpretation

### Dynamic Memory Allocation

The dynamic-memory exercises use `malloc` and `realloc` to build an expandable integer array. The program accepts user input, grows the allocation as needed, and processes the resulting data.

### Structures and Linked Lists

The coursework includes several examples of using C structures with dynamically allocated memory.

The linked-list project defines a list and node structure, supports insertion and traversal, and frees the allocated nodes when the list is finished.

### File Processing

The file-processing assignment reads a text file, normalizes the text, separates it into words, counts word frequencies, sorts the results, and reports common output statistics.

A public-domain text file is included as example input for the assignment.

### Logging and Function Pointers

The logger project uses an enum for log levels and a function pointer so the same task can send messages to different logging functions, including console and file output.

### Concurrency

The concurrency project compares a single-threaded average with a multi-threaded implementation. The list is divided across worker threads, each thread calculates a partial sum, and the results are combined.

### Networking

The networking assignments contain both TCP and UDP client/server programs.

The TCP example creates a client and server that communicate over a socket and return a time response. The UDP example implements a simple echo client and server using datagrams.

## Testing

Several assignments include dedicated test files rather than only a `main` function. The coursework includes tests for examples such as:

- name-length behavior
- rectangle calculations
- linked-list traversal
- single-threaded vs. multi-threaded averages
- dynamic-memory functions

The test setup uses the testing support that was provided with the course.

## Build Setup

The repository contains CMake configuration files from the course environment. These were part of the instructor-provided setup rather than projects I designed myself.

Because this repository is primarily a record of coursework, the C source files are the main focus. Generated build directories, caches, and other machine-specific CMake output should not be treated as part of the projects.

## Repository Notes

- This repository is an archive of coursework, not an actively developed software product.
- Some assignments are intentionally small because they were written to practice one specific C concept.
- File names and folder structure reflect the way the coursework was completed.
- The code should be read in the context of the course exercises and requirements at the time.

## Background

**Name:** Ryann Mack

**Profile:** (https://github.com/ryann-m)

**Computer Science** — IE University, Madrid  
2024–2026

**Robotics Engineering** — Worcester Polytechnic Institute  
2026–Present

## Coursework Topics

**C programming · pointers · dynamic memory · structs · linked lists · function pointers · file I/O · unit testing · concurrency · TCP/IP networking · UDP networking**

---

*Academic coursework repository — primarily maintained as a record of previous work and learning progress.*
