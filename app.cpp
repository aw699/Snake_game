#include <graphics.h>
#include <climits>
#include <queue>
#include <ctime>
#include <stdio.h>
using namespace std;
//because screen size is 630*630 and there will be 35*35 cell so size will be 630/35=18

const int cell_size = 18;


//every array element will represent a body,apple,wall or empty cell;
const int empty = 0;
const int body = 1;
const int apple = 2;
const int wall = 3;
enum directions{UP, DOWN ,LEFT, RIGHT};
directions snake_drirection = LEFT;
string crunch = "apple_crunch.wav";
string game_over_sound = "game_over.wav";

int speeds[3] = {40000000, 25000000, 10000000};
int snake_speed = speeds[1];

int score = 0;
enum modes{OPENAREA, LEVELSMODE};
modes gamemode = OPENAREA;

struct Location
{
  int r;
  int c;
};

queue <Location> snake_body;

int board[35][35] =
{
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3}
};

int OPENBOARD[35][35] =
{
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

};

int LEVEL2[35][35] =
{
    {3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3},
    {0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0},//////
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},/////
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},////
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//////
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},///////
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},/////
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},///////
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},/////
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},////////
    {3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3}

};

void draw_wall(int row,int col)
{
    int left = col*cell_size; // because every border is higher than last one by 18 pixels starting from 0 to 630
    int top = row*cell_size;
    int right = left+cell_size;
    int bottom = top+cell_size;

    //brick color
    setfillstyle(SOLID_FILL, LIGHTRED);
    bar(left, top, right, bottom);

    //brick line as described in pdf.
    /*
    *__________
    |       |
    *----------
    |   |
    *-----------
    five streight lines
    */

    setcolor(COLOR(200,200,200));
    setlinestyle(SOLID_LINE, 1, NORM_WIDTH);
    line(left, top+9, left+17, top+9);//middle line
    line(left+12, top, left+12,top+9);
    line(left+4, top+9, left+4,bottom);
    line(left, bottom, right-1,bottom);
    line(left, top, right-1,top);
}

void draw_apple(int row,int col)
{
    int left = col*cell_size;
    int top = row*cell_size;
    readimagefile("apple.ico", left, top, left+16, top+16);
}

void draw_body(int row,int col)
{
    int left = col*cell_size;
    int top = row*cell_size;
    setfillstyle(SOLID_FILL, YELLOW);
    bar(left+1, top+1, left+16, top+16);

}

void erase_snake_body(int row,int col)
{
    int left = col*cell_size;
    int top = row*cell_size;
    setfillstyle(SOLID_FILL, BLACK);
    bar(left, top, left+18, top+18);

}


void draw_board()
{
    for(int row=0;row<35;row++)
    {
        for(int col=0;col<35;col++)
        {
            switch(board[row][col])
            {
            case body:
                draw_body(row,col);
                break;
            case apple:
                draw_apple(row,col);
                break;
            case wall:
                draw_wall(row,col);
            }
        }
    }
}

void init_snake()
{
    Location loc;
    loc.r = 17;
    loc.c = 30;

    for(int i =0;i<5;i++)
    {
        board[loc.r][loc.c] = 1;
        snake_body.push(loc);
        loc.c--;
    }
}
void apply();
void move_snake()
{
    Location head = snake_body.back();
    switch(snake_drirection)
    {
    case UP:
        head.r-=1;
        if(head.r <0) head.r = 34;
        break;
    case DOWN:
        head.r+=1;
        if(head.r >34) head.r = 0;
        break;
    case LEFT:
        head.c-=1;
        if(head.c <0) head.c = 34;
        break;
    case RIGHT:
        head.c+=1;
        if(head.c >34) head.c = 0;
        break;
    }
    snake_body.push(head);
    draw_body(head.r, head.c);
    apply();
    board[head.r][head.c] = 1;

}

void change_snake_direction(char ch)
{
    switch(ch)
    {
    case KEY_UP:
        if(snake_drirection != DOWN)snake_drirection = UP;
        break;
    case KEY_DOWN:
        if(snake_drirection != UP)snake_drirection = DOWN;
        break;
    case KEY_LEFT:
        if(snake_drirection != RIGHT)snake_drirection = LEFT;
        break;
    case KEY_RIGHT:
        if(snake_drirection != LEFT)snake_drirection = RIGHT;
        break;
    }
}

void check_input()
{
    if(kbhit())
    {
        int ch = getch();
        if(ch == 0)
        {
            ch = getch();
            change_snake_direction(ch);
        }
    }
}

void create_apple()
{
    srand(time(0));
    Location loc;
    loc.r = rand()%33 +1;
    loc.c = rand()%33 +1;
    while(board[loc.r][loc.c] != empty)
    {
        loc.r = rand()%33 +1;
        loc.c = rand()%33 +1;
    }
    board[loc.r][loc.c] = 2;
    draw_apple(loc.r,loc.c);
}
bool gameover = false;

void change_score()
{
    setcolor(WHITE);
    settextstyle(0,0,0);
    char tscore[50];
    sprintf(tscore, "SCORE : %d", score);
    outtextxy(10, 640, tscore);
}
void show_score_box()
{
    setcolor(WHITE);
    bar(0, 631, 630, 633);

    change_score();
    setcolor(WHITE);
    settextstyle(0,0,0);
    char current_mode[50];
    if(gamemode == LEVELSMODE)
    {
        outtextxy(350, 640, "Game mode : LEVELS_MODE");
    }else
    {
        outtextxy(350, 640, "Game mode : OPEN_AREA");
    }

    if(gamemode == LEVELSMODE)outtextxy(120 , 640, "/10");

}

void check_score()
{
    if(score == 10)
    {
        cleardevice();
        settextstyle(1, 0, 1);
        outtextxy(200, 270, "LEVELING UP ^^^^");
        {
            for(int i=0;i<=35;i++)
            {
                for(int j=0;j<=35;j++)
                {
                    board[i][j] = LEVEL2[i][j];
                }
            }
        }
        while(!snake_body.empty())
        {
            snake_body.pop();
        }
        init_snake();
        delay(1000);////
        cleardevice();
        show_score_box();
        snake_drirection = LEFT;
        draw_board();
        create_apple();
    }
}

void apply()
{
    Location head = snake_body.back();
    switch(board[head.r][head.c])
    {
    case wall:
    case body:
        gameover = true;
        break;
    case apple:
        PlaySound(crunch.c_str(), NULL, SND_ASYNC);
        score++;
        change_score();
        create_apple();
        if(gamemode == LEVELSMODE) check_score();
        break;
    default:
        {
            Location tail = snake_body.front();
            snake_body.pop();
            erase_snake_body(tail.r,tail.c);
            board[tail.r][tail.c] = 0;
        }
    }
}

int main()
{
    initwindow(35 *cell_size, 37*cell_size, "Snake game", 100, 50);


    readimagefile("credits.jpg", 0 ,0 ,630,630);
    while(!kbhit());
    cleardevice();
    char x = getch();

    outtextxy(250, 60, "Choose Mode:");
    outtextxy(100, 120, "OPEN AREA                                                         LEVELS MODE");
    outtextxy(100, 140, "[PRESS \"O\"]                                                        [PRESS \"L\"]");




    outtextxy(230, 220, "Choose Snake Speed:");
    outtextxy(100, 260, "SLOW                                     NORMAL                             QUICK");
    outtextxy(100, 280, "Press [1]                                Press [2]                             Press [3]");
    outtextxy(230, 500, "Press ENTER to start!");


    setcolor(GREEN);
    rectangle(95, 110, 185, 170);//First mode
    rectangle(280, 250, 360, 310);//Normal speed
    setcolor(WHITE);
    rectangle(390, 110, 510, 170);// second mode
    rectangle(90, 250, 170, 310);//slow speed
    rectangle(450, 250, 535, 310);//high speed



    bool started = false;
    while(!started)
    {
        if(kbhit)
        {
            char c = getch();
            switch(c)
            {
            case '0'://levels mode
                setcolor(WHITE);
                rectangle(95, 110, 185, 170);
                setcolor(GREEN);
                rectangle(390, 110, 510, 170);// second mode
                gamemode = LEVELSMODE;
                break;
            case '9':
                setcolor(GREEN);
                rectangle(95, 110, 185, 170);
                setcolor(WHITE);
                rectangle(390, 110, 510, 170);// second mode
                gamemode = OPENAREA;
                break;
            case '1':
                setcolor(GREEN);
                rectangle(90, 250, 170, 310);//slow speed
                setcolor(WHITE);
                rectangle(280, 250, 360, 310);//Normal speed
                rectangle(450, 250, 535, 310);//high speed
                snake_speed = speeds[0];
                break;
            case '2':
                setcolor(GREEN);
                rectangle(280, 250, 360, 310);//Normal speed
                setcolor(WHITE);
                rectangle(90, 250, 170, 310);//slow speed
                rectangle(450, 250, 535, 310);//high speed
                snake_speed = speeds[1];
                break;
            case '3':
                setcolor(GREEN);
                rectangle(450, 250, 535, 310);//high speed
                setcolor(WHITE);
                rectangle(280, 250, 360, 310);//Normal speed
                rectangle(90, 250, 170, 310);//slow speed
                snake_speed = speeds[2];
                break;
            case 13:
                started = true;
                break;
            }
        }
    }
    cleardevice();
    if(gamemode == OPENAREA)
    {
        for(int i=0;i<=35;i++)
        {
            for(int j=0;j<=35;j++)
            {
                board[i][j] = OPENBOARD[i][j];
            }
        }
    }
    show_score_box();
    draw_board();
    init_snake();
    create_apple();
    int gameTimer = 0;

    while(!gameover)
    {
        gameTimer++;
        if(gameTimer == INT_MAX)
            gameTimer =0;

        if(gameTimer%snake_speed == 0)
        {
            move_snake();
            check_input();
        }

    }

    settextstyle(1, 0, 1);
    setcolor(RED);
    outtextxy(100,100, "Game Over!");
    char arr[50];
    sprintf(arr, "Your score is : %d", score);
    outtextxy(350, 100, arr);
    PlaySound(game_over_sound.c_str(), NULL, SND_SYNC);
    while(!kbhit());
    return 0;
}
