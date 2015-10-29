# Breakout Game
Breakout game in C++ using OpenGL and GLUT libraries. This project was written as an assignment for Computer Graphics course.

Screenshot:
===========
![Breakout Game Screenshot](https://raw.github.com/ogamal/breakout/master/screenshot.jpgg)

Notes:
=======
- 2 Levels available (easy to add more)
- 3 Lives represented as hearts in the game bar (can be more than 3)
- Score displays on the top right of the game bar
- Scoring by hitting a brick or paddle (bonus if multiple bricks before hitting paddle again)
- Game is designed as a finite state machine
- Balls colors are random

Controls:
==========
- Mouse motion moves paddle
- LEFT/RIGHT keys move paddle
- N key starts new game
- Esc/Q keys exit game

Cheats:
========
- Mouse clicks generate new balls
- H key increases life
- Cheats are for testing purpose


Files:
=======
- main.cpp:
	* Program entry point
	* Init GLUT, OpenGL, and start Game

- config.h:
	* Includes game configurations/settings

- MyObjects.h:
	* Contains Ball, Paddle and Brick structs definitions

- Breakout.cpp, Breakout.h:
	* Most of the game control/display logic
	* Switch between game modes (menu, gameplay, game over, scoreboard)
	* Draw bricks/balls/paddle
	* Detect collisions
	* Keep score, life count

- MainMenu.cpp, MainMenu.h:
	* Display and control game's main menu

- screenshot.jpg:
	* Screenshot of the app on my Mac

- build/:
	* Xcode project and build folder
	* I tested my code under QT too using the CMake file

- CMakeLists.txt:
	* CMake file (can be used for QT or Xcode)

To Do:
=======
- Different ball angles when hitting paddle at different positions
- Game over screen
- Scoreboard screen
- Move hardcoded values from control logic to configuration file

Build and run project on Unix/Linux:
=====================================
- Run the following commands in terminal:
```
cd <breakout project path>
mkdir build
cd build
cmake -G Unix\ Makefiles ..
make
./ogamalBreakout
```

Build project for Xcode:
========================
- Run the following commands in terminal:
```
cd <breakout project path>
mkdir xcode_build
cd xcode_build
cmake -G XCode ..
```
- Now you can open the xcode project file in xcode_build folder
