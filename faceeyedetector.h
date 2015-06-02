#ifndef FACEEYEDETECTOR_H
#define FACEEYEDETECTOR_H

#include <QObject>

#include "opencv2/opencv.hpp"
#include "image.h"
#include "ringbuffer.h"
#include "defines.h"
#include "util.h"

class FaceEyeDetector : public QObject
{
    Q_OBJECT
public:

    enum FaceStatus {
        FACE_STATUS_NONE,
        FACE_STATUS_FOUND
    };

    explicit FaceEyeDetector(QObject *parent = 0);
    bool setFaceCascade(std::string face_cascade_name);
    bool setEyeCascade(std::string eyes_cascade_name);
    bool setMouthCascade(std::string mouth_cascade_name);
    void setFrame(cv::Mat inputFrame);
    cv::Mat getEyeBallROI();
    Color getEyeSampleColor();
    Color getMouthSampleColor();
    cv::Mat getOriginalFrame();
    cv::Point getEyeROIUpperLeft();
    cv::Mat getMouthROI();
    cv::Point getMouthROIUpperLeft();
    void doDetect();

signals:
    void faceStatus(int);

private:
    cv::Mat frame;
    cv::Mat faceROI;
    cv::Mat eyeBallROI;
    cv::Point eyeCenter;
    Color eyeSampleColor;
    Color mouthSampleColor;
    cv::Mat mouthROI;
    cv::Point mouthUpperLeft;
    std::vector<cv::Rect> faces;
    std::vector<cv::Rect> eyes;
    std::vector<cv::Rect> mouth;
    cv::CascadeClassifier face_cascade;
    cv::CascadeClassifier eyes_cascade;
    cv::CascadeClassifier mouth_cascade;
};

#endif // FACEEYEDETECTOR_H
