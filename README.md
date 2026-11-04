# OSI Communication Simulation

A C-based demonstration of seven-layer OSI encapsulation and decapsulation using TCP socket communication, with a Python terminal visualizer.

## Requirements
- GCC
- Python 3

## Compile
Run these commands:
gcc -Wall -c layers.c
gcc -Wall client.c layers.o -o client
gcc -Wall server.c layers.o -o server

## Run
Run:
python3 visualizer.py
