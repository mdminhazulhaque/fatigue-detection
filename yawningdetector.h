#ifndef YAWNINGDETECTOR_H
#define YAWNINGDETECTOR_H

#include <QObject>
#include "opencv2/opencv.hpp"
#include "color.h"
#include "util.h"
#include "defines.h"

class YawningDetector : public QObject
{
    Q_OBJECT
public:

    enum MouthStatus {
        MOUTH_STATUS_OK,
        MOUTH_STATUS_YAWN
    };

    explicit YawningDetector(QObject *parent = 0);

    void setOriginalFrame(const cv::Mat& frame);
    cv::Mat getOriginalFrame(void);
    void setMouthROI(const cv::Mat& frame);
    void setMouthROIUpperLeft(const cv::Point& mouthUpperLeft);
    void setMouthSampleColor(const Color& color);
    int findMouthDiff(const std::vector<cv::Point>& contour);
    void doDetect(const Color& color);

signals:
    void mouthStatus(int);

private:
    cv::Mat originalFrame;
    cv::Mat mouthROI;
    cv::Point mouthUpperLeft;
    Color mouthSampleColor;
    int yawningThresh;

};

#endif // YAWNINGDETECTOR_H
