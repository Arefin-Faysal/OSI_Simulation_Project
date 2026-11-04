# OSI Communication Simulation

A beginner-friendly demonstration of how data travels through the
**seven layers of the OSI model**. This repository is based on an
existing project and includes additional work for TCP client-server
communication and a Python terminal visualizer.

## Credit and Attribution

**Original project:** [OSI Communication Simulation Project by
jsramesh1990](https://github.com/jsramesh1990/OSI_Communication_Simulation_Project)

The original project provided the starting point for this work. I do not
claim authorship of the original project or its existing code. My
contributions to this repository include updates to the C
layer-processing code, TCP client-server communication, and the Python
terminal visualizer. Please refer to the original repository for the
original project and its history.

## Project Overview

The project demonstrates two main processes:

-   **Encapsulation:** The client adds layer information to the message
    as it moves from the Application layer to the Physical layer.
-   **Decapsulation:** The server removes the layer information as the
    message moves from the Physical layer back to the Application layer.

The client sends the encapsulated message to the server through a TCP
socket. The Python visualizer runs the communication and displays the
sender and receiver layer flow in the terminal.

## Features

-   Demonstrates all seven OSI layers.
-   Uses C for encapsulation, decapsulation, and client-server
    communication.
-   Uses TCP sockets to transfer data between the client and server.
-   Includes a Python terminal visualizer.
-   Shows the sender and receiver layer flow.
-   Prints progress after every two OSI layers.

## Technologies Used

-   C
-   Python 3
-   TCP sockets
-   GCC
-   Linux or WSL

## Project Structure

``` text
OSI-communication/
├── client.c             # Client: connects and sends data
├── server.c             # Server: receives and decapsulates data
├── layers.c             # OSI layer functions
├── layers.h             # OSI layer function declarations
├── main.c               # Local OSI simulation entry point
├── visualizer.py        # Runs the client-server simulation and displays the flow
├── README.md             # Project documentation
└── .gitignore            # Files excluded from Git
```

## Requirements

Before running the project, install:

-   GCC compiler
-   Python 3
-   Git

The commands below are for Ubuntu or WSL.

### Install the required tools

``` bash
sudo apt update
sudo apt install build-essential python3 git
```

Check that the tools are installed:

``` bash
gcc --version
python3 --version
git --version
```

## Download the Project

Clone this repository:

``` bash
git clone https://github.com/Arefin-Faysal/OSI_Simulation_Project.git
```

Move into the project directory:

``` bash
cd OSI_Simulation_Project/OSI-communication
```

> If the repository opens directly into the project folder, use
> `cd OSI-communication` only if that folder exists.

## Compile the C Programs

Run these commands from the directory containing `layers.c` and
`client.c`:

``` bash
gcc -Wall -c layers.c
gcc -Wall client.c layers.o -o client
gcc -Wall server.c layers.o -o server
```

## Run the Simulation

Run the Python visualizer:

``` bash
python3 visualizer.py
```

The visualizer starts the server and client, sends a sample message, and
displays the OSI layer flow in the terminal.

## How the Simulation Works

1.  The client creates a message.
2.  The message passes through the seven OSI layers, from Application to
    Physical.
3.  Each layer adds its own layer information to the message.
4.  The client sends the encapsulated data to the server through a TCP
    socket.
5.  The server receives the data.
6.  The server removes the layer information from Physical to
    Application.
7.  The original message is displayed after decapsulation.

## Example Message

The simulation uses a sample message:

``` text
Hello from the OSI client!
```

The terminal output shows the sender-side encapsulation and
receiver-side decapsulation flow.

## Notes

-   The visualizer is terminal-based; it does not use a graphical
    interface.
-   This is an educational simulation of OSI layer processing, not a
    complete implementation of every real-world OSI protocol.
-   Run the commands from the project directory.
-   The original project is credited above; this repository describes
    the additional changes made here.

## Author / Contributor

**MD. Arefin Faysal**

GitHub: [Arefin-Faysal](https://github.com/Arefin-Faysal)
