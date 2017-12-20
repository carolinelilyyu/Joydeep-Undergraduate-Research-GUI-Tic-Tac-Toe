# Joydeep-Undergraduate-Research-GUI-Tic-Tac-Toe

This repo handles the GUI side for Joydeep's undergraduate research project; also known as the Human turn. This is written in QT or C++. Communicates with Python or Joydeep-Undergraduate-Research-AI through ZMQ. This documentation will assume you know the basics of C++ of headers and cpp files. 

## Terminology
- AI: Artificial intelligence: the computer program
- GUI: Graphical User Interface
- Human: User who is using the program

## Downloads/Links to help
- **ZeroMQ/ZMQ** - Platform to connect C++ code to Python code
[[ZeroMQ download]](http://zeromq.org/area:download)
- **Minimax Algorithm** - A tutorial I followed to implement the minimax algorithm
[[Minimax Algorithm]](http://www.sarathlakshman.com/2011/04/29/writing-a-tic-tac)

## Documentation

## How to Play

## How ZMQ works
In this code, we are using a socket to communicate Python to C++ and vice versa. They are both binded to TCP port: **tcp://127.0.0.1:5555** *(line 13 in mainwindow.cpp)*. You can follow this [Hello World C++ ZMQ Example](http://zguide.zeromq.org/cpp:hwclient) to find out how a simple socket works. Whenever the user saves (or ctrl+s), ZMQ sends a request message to Python to tell them the user has moved
## Structure of Code

## Reconfigure to work with your computer

## Major Bugs

