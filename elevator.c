#include <REG51.H>
#include <stdio.h>

int floor, rotation, speed;

rotation = 10; // Number of rotations per floor
speed = 10;    // Motor rotation speed (0 max, 32000 min)

wait(c) {
    int i, j;
    if (c == 0) {
        for (i = 0; i < 500; i++) {
            for (j = 0; j < speed; j++) {
                ;
            }
        }
    }
    return;
}

// Elevator going up
up(b) {
    int i, j;
    for (i = 1; i <= b; i++) {
        for (j = 0; j <= 10; j++) {
            P3 = 1;
            wait(0);
            P3 = 2;
            wait(0);
            P3 = 4;
            wait(0);
            P3 = 8;
            wait(0);
        }
        P2 = floor + i;
    }
    floor = floor + b;
    return;
}

// Elevator going down
down(b) {
    int i, j;
    for (i = 1; i <= b; i++) {
        for (j = 0; j <= rotation; j++) {
            P3 = 8;
            wait(0);
            P3 = 4;
            wait(0);
            P3 = 2;
            wait(0);
            P3 = 1;
            wait(0);
        }
        P2 = floor - i;
    }
    floor = floor - b;
    return;
}

control(a) {
    int difference;
    if (a > floor) {
        difference = a - floor;
        up(difference);
    }
    if (a < floor) {
        difference = floor - a;
        down(difference);
    }
    return;
}

main() {
    int floor1;
    floor = 1;
    P2 = floor;
    while (1) {
        if (P0 == 1) {
            floor1 = 1;
            control(1);
        }
        if (P0 == 2) {
            floor1 = 2;
            control(2);
        }
        if (P0 == 4) {
            floor1 = 3;
            control(3);
        }
        if (P0 == 8) {
            floor1 = 4;
            control(4);
        }
        if (P0 == 16) {
            floor1 = 5;
            control(5);
        }
    }
}