//
//  Breakout.h
//  ogamalBreakout
//
//  Created by Osama Attia on 9/21/14.
//  ogamal@iastate.edu
//

#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#if defined(__APPLE__) || defined(MACOSX)
	#include <GLUT/glut.h>
#else
	#include "glut.h"
#endif

// My includes
#include "MyObjects.h"      // Game-specific objects
#include "config.h"         // Game configurations

class Breakout {

public:
    // Class Constructor/Destructor
	Breakout();
	~Breakout();
    
    // Public functions (handle GLUT calls)
	void display(void);
	void init(void);
	void reshape(int width, int height);
	void mouseClick(int button, int state, int x, int y);
	void mouseMove(int x, int y);
	void keyStroke(unsigned char key, int x, int y);
	void specialKeyPos(int key, int x, int y);
    
private:
    // Game statistics
    int score;
    int level;
    int reward;
    int lifesCount;
    
    // Possible ame mode
    enum State {INIT, Menus, Gameplay, Scoreboard};
    Breakout::State gameState;
    
    // Balls
    std::vector <Ball> balls;
    
    // Paddle
    Paddle paddle;
    
    // Bricks
    std::vector<Brick> bricks;
    
    // Private functions
    void drawBackground(void);
    void drawGame(void);
    void newBall(float x, float y);
    void drawBalls(void);
    void initPaddle(void);
    void drawPaddle(void);
    void initBricks(void);
    void bricksLevel1(void);
    void bricksLevel2(void);
    void drawBricks(void);
    template <typename Iterator>
    int wallCollision(Iterator it);
    template <typename Iterator>
    bool brickCollision(Iterator it, Iterator br);
    template <typename Iterator>
    Iterator hitBrick(Iterator brick);
    void drawLife(float x, float y);
    void drawGameStats(void);
    void drawScore(void);
    void drawCoordinate(void);
};

#endif // BREAKOUT_H
