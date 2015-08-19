//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

//Paddle Size
#define WPADDLE 50
#define HPADDLE 10

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    updateScoreboard(window, label, points);
    
    double xvelocity = drand48() + 2;
    double yvelocity = 2;
    
    waitForClick();
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // TODO
        
        //Paddle Movement
        GEvent mousemove = getNextEvent(MOUSE_EVENT);
        if (mousemove != NULL)
        {
            if(getEventType(mousemove) == MOUSE_MOVED)
            {
                double x = getX(mousemove) - getWidth(paddle)/2;
                if(getX(mousemove) < (1 + WIDTH - getWidth(paddle)/2) && getX(mousemove) > getWidth(paddle)/2 - 1)
                {
                    setLocation(paddle, x, getY(paddle));
                }
            }
        }
        
        move(ball, xvelocity, yvelocity);
        pause(10);
        
        if(getX(ball) + getWidth(ball) >= getWidth(window))
            xvelocity = -xvelocity;
        if(getX(ball) <= 0)
            xvelocity = -xvelocity;
        if(getY(ball) <= 0)
            yvelocity = -yvelocity;
        
        GObject object = detectCollision(window, ball);
        
        if(object != NULL)
        {
            if(strcmp(getType(object), "GRect") == 0)
            {
                if(object == paddle)
                {
                    if(yvelocity > 0)
                    {
                        yvelocity = -yvelocity;
                    }
                }
                else
                yvelocity = -yvelocity;
                
                if(object != paddle)
                {
                    removeGWindow(window, object);
                    bricks--;
                    points++;
                    updateScoreboard(window, label, points);
                }
                
            }
        }
        
        
        
        if(getY(ball) + getHeight(ball) >= getHeight(window))
        {
            lives--;
            setLocation(ball, 190, 290);
            waitForClick();
        }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // TODO
    int xbrick = 0;
    int ybrick = 0;
    GRect brick;
    
    for (int i = 0; i < ROWS; i++)
    {
        ybrick = 45 + i * 20;
        for (int j = 0; j < COLS; j++)
        {
            xbrick = j * 40;
            GRect brick= newGRect(xbrick + 4, ybrick + 4, 32, 12);
            if(i == 0)
            setColor(brick, "RED");
            if(i == 1)
            setColor(brick, "ORANGE");
            if(i == 2)
            setColor(brick, "YELLOW");
            if(i == 3)
            setColor(brick, "GREEN");
            if(i == 4)
            setColor(brick, "CYAN");    
                
            setFilled(brick, true);
            add(window, brick);
        }
    }
    
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    GOval ball = newGOval(190, 290, RADIUS*2, RADIUS*2);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO
    GRect paddle = newGRect(175, 515, WPADDLE, HPADDLE);
    setColor(paddle, "BLUE");
    setFilled(paddle, true);
    
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-36");
    add(window, label);
    
    
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[3];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
