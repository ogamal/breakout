//
//  Breakout.cpp
//  ogamalBreakout
//
//  Created by Osama Attia on 9/21/14.
//  ogamal@iastate.edu
//

#include "Breakout.h"

using namespace std;

void recomputeFrame(int value);

Breakout::Breakout() {
    init();
}

Breakout::~Breakout() {

}

void Breakout::display(void) {

    // Clear buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Set OpenGL for 2D drawing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    glOrtho(0.0f, WINWIDTH, WINHEIGHT, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Draw my cool gradient background
    drawBackground();

    // Select which state of the game to display
    switch (gameState) {
        case INIT:
            // Init values
            init();
            break;
            
        case Menus:
            // TODO List menu
            break;
            
        case Gameplay:
            // Draw the game
            drawGame();
            // If no balls, player loses the game
            if (balls.size() <= 0 & lifesCount > 0) {
                newBall(-1, -1);
                lifesCount--;
                reward = 100;
            } else if (balls.size() <= 0) {
                // TODO - GAME OVER
            }
            
            // If no bricks, player wins the level
            if (bricks.size() <= 0 && level <= 2) {
                level++;
                initBricks();
            } else if (bricks.size() <= 0) {
                // TODO - PLAYER WON
            }
            break;
            
        case Scoreboard:
            // TODO
            break;
        
        default:
            break;
    }
    
    glutTimerFunc(TIMER, recomputeFrame, 0);
    
    glutSwapBuffers();
}

void recomputeFrame(int value) {
	glutPostRedisplay();
}

void Breakout::init(void) {
    // Reset game statistics
    score = 0;
    level = 1;
    reward = 100;
    lifesCount = 3;
    
    // Remove all balls
    balls.clear();
    
    // Remove all bricks
    bricks.clear();
    
    // Init bricks
    initBricks();
    
    // Add ball and paddle
    initPaddle();
    newBall(-1, -1);
    
    // Start game play
    gameState = Breakout::Gameplay;
}

void Breakout::drawBackground(void) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_QUADS);
    // Top color
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex2f(WINWIDTH, WINHEIGHT);
    glVertex2f(-WINWIDTH, WINHEIGHT);
    // Bottom color
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glEnd();
}

void Breakout::drawGame(void) {
    // // Draw coordinates for guidance
    // drawCoordinate();
    
    // Draw balls
    drawBalls();
    
    // Draw bricks
    drawBricks();
    
    // Draw paddle
    drawPaddle();
    
    // Draw game statistics (lifes, score)
    drawGameStats();

}

void Breakout::newBall(float x = -1, float y = -1) {
    Ball b1;
    if (x < 0 || y < 0) {
        b1.xpos = WINWIDTH / 2.0;
        b1.ypos = WINHEIGHT - 30.0f;
    } else {
        b1.xpos = x;
        b1.ypos = y;
    }
    if ((float) rand() / (RAND_MAX) < 0.5)
        b1.xvel = 5.0f;
    else
        b1.xvel = -5.0f;
    b1.yvel = -10.0f;
    b1.radius = BALL_RADIUS;
    b1.r = 0.4f + (float) rand() / (RAND_MAX);
    b1.g = 0.25f + (float) rand() / (RAND_MAX);
    b1.b = 0.4f + (float) rand() / (RAND_MAX);
    balls.push_back(b1);
}

void Breakout::drawBalls(void) {
    for (std::vector<Ball>::iterator it = balls.begin(); it != balls.end(); ) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // use GL_LINE if no fill
        glBegin(GL_POLYGON);
        glColor3f(it->r, it->g, it->b);
        for(int j = 0; j < CIRCLE_SEGMENTS; j++) {
            float const theta = 2.0f * 3.1415926f * (float)j / (float)CIRCLE_SEGMENTS;
            float const x = it->radius * cosf(theta);
            float const y = it->radius * sinf(theta);
            glVertex2f(x + it->xpos, y + it->ypos);
        }
        glEnd();
        
        // Set new position
        it->xpos += it->xvel;
        it->ypos += it->yvel;
        
        // Collision with left/right/top window sides
        if ( (it->xpos <= (2 * it->radius)) || (it ->xpos >= (WINWIDTH - 2 * it->radius)) ) {
            it->xvel *= -1;
        }
        if ( (it->ypos <= (2 * it->radius)) ) {
            it->yvel *= -1;
        }
        if (it->ypos >= (WINHEIGHT - 2 * it->radius)) {
            it = balls.erase(it);
            continue;
        }
        
        // Collission with the bricks
        for (std::vector<Brick>::iterator br = bricks.begin(); br != bricks.end(); ) {
            // Check collission between circle and vertical brick sides
            if (it->ypos >= br->ypos && it->ypos <= br->ypos + br->height) {
                // brick right edge and left point on circle
                if ((it->xpos - it->radius - br->xpos - br->width) <= 5 && (it->xpos - it->radius - br->xpos - br->width) >= 0) {
                    it->xvel *= -1;
                    br = hitBrick(br);
                    continue;
                }
                
                // brick left edge and right point on circle
                if ((it->xpos + it->radius - br->xpos) >= -5 && (it->xpos + it->radius - br->xpos) <= 0) {
                    it->xvel *= -1;
                    br = hitBrick(br);
                    continue;
                }
            }
            
            // Check collission between circle and horizontal brick sides
            if (it->xpos >= br->xpos && it->xpos <= br->xpos + br->width) {
                // brick bottom edge and top point on circle
                if ((it->ypos - it->radius - br->ypos - br->height) <= 10 && (it->ypos - it->radius - br->ypos - br->height) >= 0) {
                    it->yvel *= -1;
                    br = hitBrick(br);
                    continue;
                }
                
                // brick top edge and bottom point on circle
                if ((it->ypos + it->radius - br->ypos) >= -10 && (it->ypos + it->radius - br->ypos) <= 0) {
                    it->yvel *= -1;
                    br = hitBrick(br);
                    continue;
                }
            }
            
            GLfloat d;
            // Check collission with top left corner
            d = pow((it->xpos - br->xpos), 2.0) + pow((it->ypos - br->ypos), 2.0);
            if (d < it->radius + 5.0) {
                it->xvel *= -1;
                it->yvel *= -1;
                br = hitBrick(br);
                continue;
            }

            // Check collission with top right corner
            d = pow((it->xpos - br->xpos - br->width), 2.0) + pow((it->ypos - br->ypos), 2.0);
            if (d < it->radius + 5.0) {
                it->xvel *= -1;
                it->yvel *= -1;
                br = hitBrick(br);
                continue;
            }

            // Check collission with bottom left corner
            d = pow((it->xpos - br->xpos), 2.0) + pow((it->ypos - br->ypos - br->height), 2.0);
            if (d < it->radius + 5.0) {
                it->xvel *= -1;
                it->yvel *= -1;
                br = hitBrick(br);
                continue;
            }
            
            // Check collission with bottom right corner
            d = pow((it->xpos - br->xpos - br->width), 2.0) + pow((it->ypos - br->ypos - br->height), 2.0);
            if (d < it->radius + 5.0) {
                it->xvel *= -1;
                it->yvel *= -1;
                br = hitBrick(br);
                continue;
            }
            
            ++br; // next brick
        }
        
        // Check collission between paddle's top edge and bottom point on circle
        if (it->xpos >= paddle.xpos && it->xpos <= paddle.xpos + paddle.width) {
            if ((it->ypos + it->radius - paddle.ypos) >= -10 && (it->ypos + it->radius - paddle.ypos) <= 0) {
                it->yvel *= -1;
                reward = 100;
                score += reward;
                continue;
            }
        }
        
        ++it; // next ball
    }
}

void Breakout::initPaddle(void) {
    paddle.r = 0.2f;
    paddle.g = 0.5f;
    paddle.b = 1.0f;
    paddle.width = 150.0f;
    paddle.height = 12.0f;
    paddle.xpos = WINWIDTH / 2.0f - paddle.width / 2.0f;
    paddle.ypos = WINHEIGHT - 20.0f;
}

void Breakout::drawPaddle() {
    // Make sure paddle is larger than 25px
    if (paddle.width < 25) {
        paddle.width = 25;
    }
    
    glColor3f(paddle.r, paddle.g, paddle.b);
    glRectf(paddle.xpos, paddle.ypos, paddle.xpos + 5.0f, paddle.ypos + paddle.height);
    glRectf(paddle.xpos + 10.0f, paddle.ypos, paddle.xpos + paddle.width - 10.0f, paddle.ypos + paddle.height);
    glRectf(paddle.xpos + paddle.width - 5.0f, paddle.ypos, paddle.xpos + paddle.width, paddle.ypos + paddle.height);
}

void Breakout::drawBricks(void) {
    for (std::vector<Brick>::iterator it = bricks.begin(); it != bricks.end(); ++it) {
        glColor3f(it->r, it->g, it->b);
        glRectf(it->xpos, it->ypos, it->xpos + it->width, it->ypos + it->height);
        
        // Top cool triangle (kind of texture)
        glBegin(GL_QUADS);
        glColor3f(it->r-0.2f, it->g-0.2f, it->b-0.2f);
        glVertex2f(it->xpos, it->ypos);
        glColor3f(it->r-0.05f, it->g-0.05f, it->b-0.05f);
        glVertex2f(it->xpos + it->width, it->ypos);
        glColor3f(it->r-0.15f, it->g-0.15f, it->b-0.15f);
        glVertex2f(it->xpos + it->width, it->ypos + it->height);
        glVertex2f(it->xpos, it->ypos);
        glEnd();
    }
}

template <typename Iterator>
Iterator Breakout::hitBrick(Iterator brick) {
    score += reward;
    reward += 25;
//    system("afpqlay ../../cartoon008.wav");
    
    // Decrease brick health
    if (brick->health > 1) {
        brick->r = 0.95f;
        brick->g = 0.95f;
        brick->b = 0.95f;
        brick->health -= 1;
        return ++brick;
    } else {
        return bricks.erase(brick);
    }
}

void Breakout::initBricks(void) {
    if (level == 1)
        bricksLevel1();
    else if (level == 2)
        bricksLevel2();
}

void Breakout::bricksLevel1(void) {
    Brick newBrick;
    newBrick.r = 0.95f;
    newBrick.g = 0.95f;
    newBrick.b = 0.95f;
    newBrick.health = 1;
    newBrick.width = (WALLWIDTH - (WALLCOLS - 2) * WALLSPACE) / WALLCOLS;
    newBrick.height = (WALLHEIGHT - (WALLROWS - 2) * WALLSPACE) / WALLROWS;
    
    for (int i = 0; i < WALLROWS; ++i) {
        for (int j = 0; j < WALLCOLS; ++j) {
            // Set stronger bricks
            if (i+1 > ceil(WALLROWS / 2.0) - 2 && i < ceil(WALLROWS / 2.0) + 2 && j+2 > ceil(WALLCOLS / 2.0) - 3 && j < ceil(WALLCOLS / 2.0) + 3) {
                newBrick.r = 1.0f;
                newBrick.g = 0.5f;
                newBrick.b = 0.5f;
                newBrick.health = 2;
            } else {
                newBrick.r = 0.95f;
                newBrick.g = 0.95f;
                newBrick.b = 0.95f;
                newBrick.health = 1;
            }
            
            newBrick.xpos = WALLX + j * newBrick.width + j * WALLSPACE;
            newBrick.ypos = WALLY + i * newBrick.height + i * WALLSPACE;
            bricks.push_back(newBrick);
        }
    }
}

void Breakout::bricksLevel2(void) {
    Brick newBrick;
    newBrick.width = (WALLWIDTH - (WALLCOLS - 2) * WALLSPACE) / WALLCOLS;
    newBrick.height = (WALLHEIGHT - (WALLROWS - 2) * WALLSPACE) / WALLROWS;
    
    for (int i = 0; i < WALLROWS; i++) {
        for (int j = 0; j < WALLCOLS; j++) {
            // Set stronger bricks
            if (i == 1 || i == WALLROWS - 2 || j == 1 || j == WALLCOLS - 2) {
                newBrick.r = 1.0f;
                newBrick.g = 0.5f;
                newBrick.b = 0.5f;
                newBrick.health = 2;
            } else {
                newBrick.r = 0.95f;
                newBrick.g = 0.95f;
                newBrick.b = 0.95f;
                newBrick.health = 1;
            }
            
            newBrick.xpos = WALLX + j * newBrick.width + j * WALLSPACE;
            newBrick.ypos = WALLY + i * newBrick.height + i * WALLSPACE;
            bricks.push_back(newBrick);
        }
    }
}

void Breakout::drawGameStats(void) {
    glBegin(GL_LINES);
    // Bottom right (red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(20.0f, 30.0f);
    glVertex2f(WINWIDTH - 20.0f, 30.0f);
    glEnd();
    
    float offset = 25.0f;
    for (int i = 0; i < lifesCount & i < 10; ++i) {
        drawLife(35 + offset * i, 15);
    }
    
    drawScore();
}

void Breakout::drawLife(float x, float y) {
    // Scale the heart symbol
    float const scale = 0.5f;
    
    // Heart symbol equations from Walfram Mathworld: http://mathworld.wolfram.com/HeartCurve.html
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.2f, 0.2f);
    for(int j = 0; j < CIRCLE_SEGMENTS; j++) {
        float const theta = 2.0f * 3.1415926f * (float)j / (float)CIRCLE_SEGMENTS;
        float const xx = scale * 16.0f * sinf(theta) * sinf(theta) * sinf(theta);
        float const yy = -1 * scale * (13.0f * cosf(theta) - 5.0f * cosf(2.0f * theta) - 2 * cosf(3.0f * theta) - cosf(4.0f * theta));
        glVertex2f(x + xx, y + yy);
    }
    glEnd();
}

void Breakout::drawScore(void) {
    glPushMatrix();
    // Write score word
    glColor3f(1.0f, 0.7f, 0.7f);
    glRasterPos2f(WINWIDTH - 120, 20);
    char buf[300], *p;
    p = buf;
    sprintf(buf, "Score: ");
    do glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p); while(*(++p));
    // Print the score
    p = buf;
    sprintf(buf, "           %d", score);
    glColor3f(1.0f, 0.2f, 0.2f);
    glRasterPos2f(WINWIDTH - 120, 20);
    do glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p); while(*(++p));
    glPopMatrix();
}

void Breakout::drawCoordinate(void) {
    glBegin(GL_LINES);
        // Top left (white)
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(20.0f, 10.0f);
        glVertex2f(20.0f, 30.0f);
        glVertex2f(10.0f, 20.0f);
        glVertex2f(30.0f, 20.0f);
    
        // Bottom right (red)
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(WINWIDTH - 20.0f, WINHEIGHT - 10.0f);
        glVertex2f(WINWIDTH - 20.0f, WINHEIGHT - 30.0f);
        glVertex2f(WINWIDTH - 10.0f, WINHEIGHT - 20.0f);
        glVertex2f(WINWIDTH - 30.0f, WINHEIGHT - 20.0f);
    glEnd();
}

void Breakout::reshape(int width, int height) {
    if (width != WINWIDTH || height != WINHEIGHT)
        glutReshapeWindow(WINWIDTH, WINHEIGHT);
}

void Breakout::mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        newBall(x, y);
    }
    
    // Force redraw
	glutPostRedisplay();
}

void Breakout::mouseMove(int x, int y) {
    y = WINHEIGHT - y;
    if (x - paddle.width / 2.0f >= 0 && x + paddle.width / 2.0f <= WINWIDTH) {
        paddle.xpos = x - paddle.width / 2.0f;
    } else if (x - paddle.width / 2.0f <= 0) {
        paddle.xpos = 0;
    } else if (x + paddle.width / 2.0f >= WINWIDTH) {
        paddle.xpos = WINWIDTH - paddle.width;
    }
	glutPostRedisplay();
}

void Breakout::keyStroke(unsigned char key, int x, int y) {
    switch (key) {
        case 'q': // Exit
            exit(0);
            break;
        case 'n': // New game
            init();
            break;
        case 'h':
            lifesCount++;
            break;
        case 27: // Esc button
            exit(0);
            break;
        default:
            break;
    }
}

void Breakout::specialKeyPos(int key, int x, int y) {
    switch(key)
	{
		case GLUT_KEY_LEFT:
            if (paddle.xpos > 0) {
                paddle.xpos -= 5.0f;
                paddle.xpos -= 5.0f;
                glutPostRedisplay();
                paddle.xpos -= 5.0f;
                paddle.xpos -= 5.0f;
                glutPostRedisplay();
            }
            break;
        case GLUT_KEY_RIGHT:
            if (paddle.xpos + paddle.width < WINWIDTH) {
                paddle.xpos += 5.0f;
                paddle.xpos += 5.0f;
                glutPostRedisplay();
                paddle.xpos += 5.0f;
                paddle.xpos += 5.0f;
                glutPostRedisplay();
            }
            break;
        default:
            break;
    }
}
