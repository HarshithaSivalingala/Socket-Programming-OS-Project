# Socket Programming with Multithreading

## Overview
This project demonstrates a socket programming implementation where a client can communicate with multiple servers simultaneously using the concept of multithreading. The client program manages multiple connections to different servers, enabling concurrent communication.

A notable feature is the controlled client termination process: clients exit gracefully only when the user inputs the command `exit`. This ensures a clean disconnection and resource release.

## Features
- **Multithreaded Communication**: Each client thread communicates independently with a server, enabling simultaneous server interactions.
- **Graceful Exit**: Clients terminate only upon receiving the `exit` command, ensuring stability and proper resource cleanup.

## Prerequisites
Ensure you have the following setup on your machine:
- **GCC Compiler** (for compiling the code)
- **POSIX Threads (pthreads)** (used for multithreading)
- **Linux/Unix Environment** (recommended for running the code)

## Installation and Usage

### Server Setup
1. Compile the server code:
   ```bash
   gcc -o server server.c -pthread
   ```
2. Run the server:
   ```bash
   ./server
   ```

### Client Setup
1. Compile the client code:
   ```bash
   gcc -o client client.c -pthread
   ```
2. Run the client:
   ```bash
   ./client
   ```

## Project Structure
- **server.c**: Implements the server-side logic, capable of handling multiple clients concurrently.
- **client.c**: Implements the client-side logic, supporting connections to multiple servers simultaneously using threads.





