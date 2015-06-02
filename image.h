#ifndef IMAGE_H
#define IMAGE_H

#include "opencv2/opencv.hpp"
#include "rect.h"
#include "color.h"

class Image
{
private:

    cv::Mat img;

public:
    Image(void);
    Image(const cv::Mat& frame);
    Image(int w, int h, int type);
    Image(int w, int h, int type, const cv::Scalar& s);
    ~Image(void);

    void operator()(const cv::Mat& frame);
    cv::Mat& getImage()
    {
        return img;
    }

    int getWidth() const
    {
        return img.cols;
    }

    int getHeight() const
    {
        return img.rows;
    }

    Color getColor(int x, int y) const;
    int getR(int x, int y) const;
    int getG(int x, int y) const;
    int getB(int x, int y) const;

    void setColor(int x, int y, Color& c);
    void setColor(int x, int y, int r, int g, int b);

    int getGrayscale(int x, int y);
    void setGrayscale(int x, int y, int v);

    void rescale(double scaleFactor);
};

#endif
