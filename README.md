# Joydeep-Undergraduate-Research-GUI-Tic-Tac-Toe

This repo handles the GUI side for Joydeep's undergraduate research project; also known as the Human turn. This is written in QT or C++. Communicates with Python or Joydeep-Undergraduate-Research-AI through ZMQ. This documentation will assume you know the basics of C++ of headers and cpp files. Configuring the code to work with your machine will be essential. For example, certain file locations are configured to the creator's desktop: "/User/carolineyu/Documents/....". Change these paths/directories in the code (mainwindow.cpp) to match where your file locations will exist.

## Terminology
- AI: Artificial intelligence: the computer program
- GUI: Graphical User Interface
- Human: User who is using the program

## Downloads/Links to help
- **ZeroMQ/ZMQ** - Platform to connect C++ code to Python code
[[ZeroMQ]](http://zeromq.org/)
- **QT Open Source** - Open source framework that uses C++ to make applications and GUIs
[[QT Open Source download]](https://www1.qt.io/download-open-source/?hsCtaTracking=f977210e-de67-475f-a32b-65cec207fd03%7Cd62710cd-e1db-46aa-8d4d-2f1c1ffdacea)
- **ScribbleArea** - A QT class that acts as a canvas for the user to draw on a canvas
[[ScribbleArea]](http://doc.qt.io/qt-5/qtwidgets-widgets-scribble-example.html)
- **ZMQ Basics: Hello World for C++**
[[Hello World C++ ZMQ Example]](http://zguide.zeromq.org/cpp:hwclient)

## How to Play
1. Press the green play button in the QT IDE.
2. Draw an X or O in one of the squares. DO NOT DRAW IN MORE THAN ONE SQUARE. Also if the user were to choose O, it must look like the O in the **/train/O/** folder. Please provide more training data and create the model to fit the training data.
3. Press "CTRL + S" to save the game board. Do not be afraid if the GUI hangs, ZMQ sockets make the GUI hang because it is waiting for the Python code's response. It will automatically save in the folder **/board/** as 9 separate "game(insert square number).png"s.
4. Start up the python script from Joydeep-Undergraduate-Research-AI inside Pycharm. If the code shows the board state and says "Press Enter to continue...", then the game has moved.
5. Check back on the GUI. The computer should have moved.
6. Draw an X or O again
7. CTRL + S or save the drawing.
8. Go back to Pycharm IDE and Press Enter.
9. Repeat steps 5-9.


## How ZMQ works
In this code, we are using a socket to communicate Python to C++ and vice versa. They are both binded to TCP port of your local host: **tcp://127.0.0.1:5555** *(line 13 in mainwindow.cpp)*. You can follow this [Hello World C++ ZMQ Example](http://zguide.zeromq.org/cpp:hwclient) to find out how a simple socket works. Whenever the user saves (or ctrl+s), ZMQ sends a request message from QT/C++ to Python to tell them the human has moved; the GUI hangs while it waits for a reply message from Python to C++/QT. The ZMQ reply message would reply back with the image of the square the AI moved. If it marked "game1.png", that means that it marked square 1, or (0,0). If it marked "game2.png", it marked square 2, or (0,1), etc. The GUI stops hanging and the user can write again. This cycle repeats until the user has won, computer has won, or they end with a draw. 

## Structure of Code
- **Joydeep_Project.pro** handles dependencies, configures ZMQ to your computer
- **mainwindow.h** the header file to store declarations of private and public variables, methods, slots, and includes for mainwindow.cpp. This also has the #include for *system*, part of C++ that allows it to execute terminal or shell commands without having the user type it in the terminal *(however system is making the GUI hang even though it is correctly executing the python script. I commented it out for now and you will have to start up the python script manually)*
- **scribblearea.h** the header file to store declarations or private and public variables, methods, slots, and includes for scribblearea.cpp
- **main.cpp**: cpp file for QT application. The bare bones and where the main method exists.
- **mainwindow.cpp** cpp file for buttons, canvas, menu, buttons, triggers for buttons, etc.
- **scribblearea.cpp** cpp file for users to draw on canvas and also handles paint events, etc.


## Major Bugs
- QT/C++ Bug (GUI): As said before, *system*, or executing shell/terminal commands within the C++ code makes the GUI hang even though it is correctly executing the python script. You can confirm this because the QT IDE prints out the Python code's print statements, but starts hanging halfway through the execution. I've commented out the command execution code part for now until you choose to uncomment it and play around with it so you'll have to start up the python script manually and press Enter after you draw and save. Therefore, this code is not automated.
- Python Bug (AI): Code does not play tic tac toe optimally. Please look at the minimax algorithm within the Python code, or Joydeep-Undergraduate-Research-AI, to debug why it's not doing so. I've also provided a tutorial about how minimax works and the pseudocode I followed under the downloads/links inside the Joydeep-Undergraduate-Research-AI repo. Through the print statements, you can see it trying different game states to see what's the optimal path, but it always just ends up choosing the next available free position, or next square.
