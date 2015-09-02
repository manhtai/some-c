//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

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

// paddle width and height
#define PADHEIGHT 7
#define PADWIDTH 37
#define YPAD HEIGHT - 3*PADHEIGHT
#define XPAD WIDTH/2 - PADWIDTH/2

// bricks gap
#define GAP 10

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points, int lives);
void changeScoreboard(GWindow window, GLabel label, string notice);
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

    // Init score board with points and lives
    updateScoreboard(window, label, points, lives);

    // initial velocity
    double xvelocity = drand48() + 2;
    double yvelocity = drand48() + 2;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // MOVE THE PADDLE!
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we heard one
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure the paddle follows top cursor
                double x = getX(event) - getWidth(paddle) / 2;
                setLocation(paddle, x, YPAD);
            }
        }

        // MAKE THE BALL LIVE!
        // move ball at random
        move(ball, xvelocity, yvelocity);

        // check collision
        GObject object = detectCollision(window, ball);

        // if it's the paddle, bounce off
        if (object == paddle)
        {
            yvelocity = -yvelocity;
        }

        // If it hit the brick, remove the brick
        else if (object != NULL && strcmp(getType(object), "GRect") == 0)
        {
            yvelocity = -yvelocity;
            removeGWindow(window, object);
            bricks--;
            if (bricks != 0)
                updateScoreboard(window, label, ++points, lives);
            else
                changeScoreboard(window, label, "YOU WIN!");
            continue;
        }

        // lost live when touch bottom edge of window
        else if (getY(ball) + getHeight(ball) > YPAD + PADHEIGHT)
        {
            updateScoreboard(window, label, points, --lives);
            if (lives != 0)
            {
                waitForClick();
                setLocation(ball, WIDTH/2, HEIGHT/2);
            }
            else
                changeScoreboard(window, label, "YOU LOSE!");
            continue;
        }

        // bounce off up edge of window
        else if (getY(ball) <= 0)
        {
            yvelocity = -yvelocity;
        }

        // bounce off right edge of window
        else if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            xvelocity = -xvelocity;
        }

        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            xvelocity = -xvelocity;
        }

        // linger before moving again
        pause(10);
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
    int bwidth = (WIDTH - (COLS + 1)*GAP) / COLS;
    int bheight = bwidth / 4;
    int xcor, ycor;
    char* colors[7] = {"CYAN", "GREEN", "MAGENTA", "ORANGE", "PINK", "RED", "YELLOW"};
    for (int c = 0; c < COLS; c++)
    {
        for (int r = 0; r < ROWS; r++)
        {
            char* color = colors[r % 7]; // We hardcode 7 here for now
            xcor = GAP + c*(bwidth + GAP);
            ycor = GAP + r*(bheight + GAP);
            GRect rect = newGRect(xcor, ycor, bwidth, bheight);
            setFilled(rect, true);
            setColor(rect, color);
            add(window, rect);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval oval = newGOval(WIDTH/2, HEIGHT/2, RADIUS*2, RADIUS*2);
    setFilled(oval, true);
    setColor(oval, "BLACK");
    add(window, oval);
    return oval;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect rect = newGRect(XPAD, YPAD, PADWIDTH, PADHEIGHT);
    setFilled(rect, true);
    setColor(rect, "BLUE");
    add(window, rect);
    return rect;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("");
    add(window, label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points, int lives)
{
    // update label
    char s[99];
    sprintf(s, "Points: %i, Lives: %i", 10*points, lives);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

// Change scoreboard to notify GAME OVER, and VICTORY
void changeScoreboard(GWindow window, GLabel label, string notice)
{
    // update label
    char s[99];
    sprintf(s, "%s", notice);
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
