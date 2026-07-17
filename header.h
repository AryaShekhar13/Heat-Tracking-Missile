#pragma once

struct obj{
    int mx = 0;
    int my = 0;
    int jx = 0;
    int jy = 0;
};

extern obj state;

void render(obj& state);