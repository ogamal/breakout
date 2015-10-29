//
//  MyObjects.h
//  ogamalBreakout
//
//  Created by Osama Attia on 9/23/14.
//  ogamal@iastate.edu
//

#ifndef ogamalBreakout_MyObjects_h
#define ogamalBreakout_MyObjects_h

// Ball
struct Ball {
    GLfloat xpos, ypos;
    GLfloat xvel, yvel;
    GLfloat radius;
    GLfloat r, g, b;
};

// Paddle
struct Paddle {
    GLfloat xpos, ypos;
    GLfloat width, height;
    GLfloat r, g, b;
};

// Brick
struct Brick {
    GLfloat xpos, ypos;
    GLfloat width, height;
    GLfloat r, g, b;
    GLint health;
    GLint value;
};

#endif
