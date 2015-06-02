#include "eyeanalyzer.h"

EyeAnalyzer::EyeAnalyzer(QObject *parent) :
    QObject(parent),
    last10EyePixel(50),
    last50EyePixel(100)
{
    eyeCloseThresh = 5;
    isEyeBlinked = false;
    isEyeClosed = false;
    cliffDiff = 1;
    lastCliffDiff = 2;
    lastState = EYE_OPEN;
    currState = EYE_OPEN;
    showBlink = 0;
}

void EyeAnalyzer::setCliffDiff(int diff) {
    this->cliffDiff = diff;
}

void EyeAnalyzer::doAnalyze(void) {
    clearStatus();
    getEyeStatus();
}

void EyeAnalyzer::getEyeStatus() {
    int i = 0;
    int eyeCloseCount = 0;
    int eyeBlinkCount = 0;

    // Blinking and closing detection
    if (cliffDiff < eyeCloseThresh)
    {
        isEyeClosed = true;
        currState = EYE_CLOSED;
    }
    else
    {
        isEyeClosed = false;
        currState = EYE_OPEN;
    }

    if (currState == EYE_OPEN && lastState == EYE_CLOSED)
    {
        isEyeBlinked = true;
        showBlink = 5;
        emit eyeStatus(EYE_STATUS_WARNING);
    }
    else
    {
        isEyeBlinked = false;
    }

    lastCliffDiff = cliffDiff;
    lastState = currState;

    if (showBlink > 0)
    {
        emit eyeStatus(EYE_STATUS_BLINK);
        //util::printText(originalFrame, text, cv::Scalar(255, 255, 0), cv::Point(10, 20));
        showBlink--;
    }

    // Ring buffers
    last10EyePixel.put((int)isEyeClosed);
    last50EyePixel.put((int)isEyeBlinked);

    // Statistic
    // Sleep
    if (last10EyePixel.isFull() == true) {
        for (i = 0; i < last10EyePixel.getSize(); i++) {
            if (last10EyePixel.getBase()[i] == (int)true && i != last10EyePixel.getRearIndex()) {
                eyeCloseCount++;
            }
        }

        if (eyeCloseCount >= last10EyePixel.getSize() * 0.8) {
            emit eyeStatus(EYE_STATUS_CLOSED);
            //util::printText(originalFrame, text, cv::Scalar(0, 0, 255), cv::Point(10, 50));
        }
    }

    // Blinking rate
    if (last50EyePixel.isFull() == true)
    {
        for (i = 0; i < last50EyePixel.getSize(); i++)
        {
            if (last50EyePixel.getBase()[i] == (int)true && i != last50EyePixel.getRearIndex())
            {
                eyeBlinkCount++;
            }
        }

        blinkRate = eyeBlinkCount;
        //sprintf(text_c_str, "Blink rate = %d / 100 frame", blinkRate);
        //text.assign(text_c_str);
        //if(blinkRate <= 7)
            //util::printText(originalFrame, text, cv::Scalar(255, 255, 0), cv::Point(10, 90));
        //else
            //util::printText(originalFrame, text, cv::Scalar(0, 0, 255), cv::Point(10, 90));
        //std::cout << text << std::endl;
    }
}

void EyeAnalyzer::setOriginalFrame(const cv::Mat& frame) {
    frame.copyTo(originalFrame);
}

cv::Mat EyeAnalyzer::getOriginalFrame() {
    return originalFrame;
}

void EyeAnalyzer::clearStatus(void) {
    isEyeBlinked = false;
    isEyeClosed = false;
}
