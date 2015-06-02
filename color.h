#ifndef COLOR_H
#define COLOR_H

class Color
{
public:

    Color() {}
    Color(int r, int g, int b)
    {
        this->r=r;
        this->g=g;
        this->b=b;
    }

    bool operator== (const Color &pixel) const
    {
        return (pixel.r == r && pixel.g == g && pixel.b == b);
    }

    bool operator!= (const Color &pixel) const
    {
        return !(pixel.r == r && pixel.g == g && pixel.b == b);
    }

    int r;
    int g;
    int b;
};

#endif
