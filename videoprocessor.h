#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H

#include <QThread>
#include <stdexcept>

#include "opencv2/opencv.hpp"

#include "mattoqimage.h"

#include "faceeyedetector.h"
#include "eyeanalyzer.h"
#include "eyeballcolordetector.h"
#include "yawningdetector.h"

class VideoProcessor : public QThread
{
    Q_OBJECT
public:
    explicit VideoProcessor(QObject *parent = 0);
    void run();
    void initCapture(QString videoFile);
    void initCapture(int index);

signals:
    void sendFrame(const QImage&);
    void finished();
    void progress(int);

private:
    cv::VideoCapture video;
    cv::Mat frame;
    unsigned int totalFrames;
    unsigned int processedFrames;
    bool camera;

public:
    FaceEyeDetector *faceEyeDetector;
    EyeAnalyzer *eyeAnalyzer;
    EyeBallColorDetector *eyeBallColorDetector;
    YawningDetector *yawningDetector;
};

#endif
