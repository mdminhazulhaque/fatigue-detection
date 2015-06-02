#ifndef EYEBALLCOLORDETECTOR_H
#define EYEBALLCOLORDETECTOR_H

#include <QObject>
#include "opencv2/opencv.hpp"
#include "rect.h"
#include "image.h"
#include "faceeyedetector.h"

#define WIDTH    EYE_ROI_RADIUS_W * 2
#define HEIGHT   EYE_ROI_RADIUS_H * 2

class EyeBallColorDetector : public QObject
{
    Q_OBJECT
public:
    explicit EyeBallColorDetector(QObject *parent = 0);

    void initialize(const cv::Mat& orignialFrame,
                    const cv::Point& eyeROIUpperLeft,
                    const cv::Mat& frame,
                    const Color& eyeSampleColor);

    void clearStatus();
    void doDetect();
    void getProjection();
    void getBoundingBox();
    int findCliffUp(const int* project, int size);
    int findCliffDown(const int* project, int size);
    void findCliffs(const int* project, int size);
    void markBoundingBox();
    void showProcessed();
    cv::Mat getOriginalFrame();
    int getCliffDiff();

private:
    int xMin;
    int xMax;
    int yMin;
    int yMax;
    int xProject[WIDTH];
    int yProject[HEIGHT];
    Image processed;
    cv::Mat originalFrame;
    cv::Point eyeROIUpperLeft;
    Color eyeSampleColor;
    int epsilon;
    cv::Rect boundingBox;
};

#endif // EYEBALLCOLORDETECTOR_H
