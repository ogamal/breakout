//
//  config.h
//  ogamalBreakout
//
//  Created by Osama Attia on 9/21/14.
//  ogamal@iastate.edu
//

#ifndef ogamalBreakout_config_h
#define ogamalBreakout_config_h

// Force Redraw timer
#define TIMER 16.6          // 60 frame per second

// Window settings
#define WINTITLE "Breakout Game ~ By Osama Attia"
const int WINWIDTH  = 800;
const int WINHEIGHT = 600;

// Wall settings
const int WALLWIDTH = 700;                          // Wall width
const int WALLHEIGHT = 180;                         // Wall height
const float WALLX = (WINWIDTH - WALLWIDTH) / 2.0f;  // Wall start point(x)
const float WALLY = WALLX + 40;                     // Wall start point(y)
const int WALLSPACE = 3;                            // Space between bricks
const int WALLCOLS = 15;                            // Wall columns count
const int WALLROWS = 10;                            // Wall rows count

// Pedal Settings
const float PEDALWIDTH = 150.0f;
const float PEDALHEIGHT = 12.0f;

// Ball settings
const float BALL_RADIUS = 6.0f;
const int CIRCLE_SEGMENTS = 50; // used in drawing ball and the life/heart symbol

#endif
