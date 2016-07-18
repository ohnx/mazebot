#include "Maze.h"

Maze Maze_new(Matrix d) {
    Maze m = calloc(sizeof(Maze_nonptr), 1);
    m->data = Matrix_dup(d);
    return m;
}

int *Maze_getLocation(Maze m, int *pos) {
    int x, y, *r;
    /* codes are 0 = up, 1 = right, 2 = down, 3 = left */
    x = pos[0];
    y = pos[1];
    r = calloc(sizeof(int), 4);
    if (x == 0) {
        /* leftmost, left is negative */
        r[3] = -1;
    } else {
        /* not leftmost, left is just x-1 */
        r[3] = Matrix_getAt(m->data, x-1, y);
    }
    
    if (x == (m->data)->r-1) {
        /* rightmost, right is negative */
        r[1] = -1;
    } else {
        /* not rightmost, right is just x+1 */
        r[1] = Matrix_getAt(m->data, x+1, y);
    }
    
    if (y == 0) {
        /* topmost, top is negative */
        r[0] = -1;
    } else {
        /* not topmost, top is just y-1 */
        r[0] = Matrix_getAt(m->data, x, y-1);
    }
    
    if (y == (m->data)->c-1) {
        /* bottommost, bottom is negative */
        r[2] = -1;
    } else {
        /* not bottommost, bottom is just y+1 */
        r[0] = Matrix_getAt(m->data, x, y+1);
    }
    return r;
}

int Maze_canMoveHere(Maze m, int *pos) {
    return !Matrix_getAt(m->data, pos[0], pos[1]);
}