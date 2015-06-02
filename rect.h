#ifndef RECT_H
#define RECT_H

class Rect
{
public:
    Rect() {}

    Rect(int top, int bottom, int left, int right)
    {
        this->top = top;
        this->left = left;
        this->right = right;
        this->bottom = bottom;
    }

private:
    int top;
    int left;
    int right;
    int bottom;
};

#endif
