#ifndef EYEANALYZER_H
#define EYEANALYZER_H

#include <QObject>
#include "opencv2/opencv.hpp"
#include "image.h"
#include "ringbuffer.h"
#include "util.h"
#include <stdio.h>

#define EYE_OPEN   0
#define EYE_CLOSED 1

class EyeAnalyzer : public QObject
{
    Q_OBJECT
public:

    enum EyeStatus {
        EYE_STATUS_NONE,
        EYE_STATUS_BLINK,
        EYE_STATUS_WARNING,
        EYE_STATUS_CLOSED
    };

    explicit EyeAnalyzer(QObject *parent = 0);
    void doAnalyze(void);
    void setCliffDiff(int diff);
    void setOriginalFrame(const cv::Mat& frame);
    cv::Mat getOriginalFrame(void);
    void clearStatus(void);

signals:
    void eyeStatus(int);

private:
    int cliffDiff;
    int lastCliffDiff;
    RingBuffer last10EyePixel;
    RingBuffer last50EyePixel;
    cv::Mat originalFrame;
    int blinkRate;
    bool isEyeBlinked;
    bool isEyeClosed;
    int eyeCloseThresh;
    int currState;
    int lastState;
    int showBlink;
    void getEyeStatus();
};

#endif // EYEANALYZER_H
