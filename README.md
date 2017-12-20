# Joydeep-Undergraduate-Research-GUI-Tic-Tac-Toe

This repo handles the GUI side for Joydeep's undergraduate research project; also known as the Human turn. This is written in QT or C++. Communicates with Python or Joydeep-Undergraduate-Research-AI through ZMQ. This documentation will assume you know the basics of C++ of headers and cpp files. Configuring the code to work with your machine will be essential; for example, certain file locations are configured to the creator's desktop: "/User/carolineyu/Documents/....". Change these paths/directories in the code (mainwindow.cpp) to match where your file locations will exist.

## Terminology
- AI: Artificial intelligence: the computer program
- GUI: Graphical User Interface
- Human: User who is using the program

## Downloads/Links to help
- **ZeroMQ/ZMQ** - Platform to connect C++ code to Python code
[[ZeroMQ download]](http://zeromq.org/area:download)
- **Minimax Algorithm** - A tutorial I followed to implement the minimax algorithm
[[Minimax Algorithm]](http://www.sarathlakshman.com/2011/04/29/writing-a-tic-tac)
- **ScirrbleArea** - A QT class that acts as a canvas for the user to draw on a canvas
## Documentation


## How to Play


## How ZMQ works
In this code, we are using a socket to communicate Python to C++ and vice versa. They are both binded to TCP port: **tcp://127.0.0.1:5555** *(line 13 in mainwindow.cpp)*. You can follow this [Hello World C++ ZMQ Example](http://zguide.zeromq.org/cpp:hwclient) to find out how a simple socket works. Whenever the user saves (or ctrl+s), ZMQ sends a request message from QT/C++ to Python to tell them the human has moved; the GUI hangs while it waits for a reply message from Python to C++/QT. The ZMQ reply message would reply back with the image of the square the AI moved. If it marked "game1.png", that means that it marked square 1, or (0,0). If it marked "game2.png", it marked square 2, or (0,1), etc. The GUI stops hanging and the user can write again. This cycle repeats until the user has won, computer has won, or they end with a draw. 

## Structure of Code
- **Joydeep_Project.pro** handles dependencies, configures ZMQ to your computer
- **mainwindow.h** the header file to store declarations of private and public variables, methods, slots, and includes for mainwindow.cpp. This also has the #include for *system*, part of C++ that allows it to execute terminal or shell commands without having the user type it in the terminal
- **scribblearea.h** the header file to store declarations or private and public variables, methods, slots, and includes for scribblearea.cpp
- **main.cpp**: cpp file for QT application. The bare bones and where the main method exists.
- **mainwindow.cpp** cpp file for buttons, canvas, menu, buttons, triggers for buttons, etc.
- **scribblearea.cpp** cpp file for users to draw on canvas and also handles paint events, etc.



## Major Bugs

