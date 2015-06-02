#include "yawningdetector.h"

YawningDetector::YawningDetector(QObject *parent) :
    QObject(parent)
{
#ifdef VIDEO_MODE
    yawningThresh = 70;
#else
    yawningThresh = 30;
#endif
}

void YawningDetector::setOriginalFrame(const cv::Mat& frame)
{
    frame.copyTo(originalFrame);
}

cv::Mat YawningDetector::getOriginalFrame()
{
    return originalFrame;
}

void YawningDetector::setMouthROI(const cv::Mat& frame)
{
    frame.copyTo(mouthROI);
}

void YawningDetector::setMouthROIUpperLeft(const cv::Point& mouthUpperLeft)
{
    this->mouthUpperLeft = mouthUpperLeft;
}

void YawningDetector::setMouthSampleColor(const Color& color)
{
    this->mouthSampleColor = color;
}

void YawningDetector::doDetect(const Color& color)
{
    emit mouthStatus(MOUTH_STATUS_OK);
    return;

    if(!mouthROI.data)
        return;

    cv::Mat mouthROIGray(mouthROI);

    for(int j = 0; j < mouthROI.rows; j++)
    {
        for(int i = 0; i < mouthROI.cols; i++)
        {
            if((util::getB(mouthROI, cv::Point(i, j)) < color.b) &&
                    (util::getG(mouthROI, cv::Point(i, j)) < color.g) &&
                    (util::getR(mouthROI, cv::Point(i, j)) < color.r))
            {
                util::setMatColor(mouthROIGray, cv::Point(i, j), cv::Scalar(255, 255, 255));
            }
            else
            {
                util::setMatColor(mouthROIGray, cv::Point(i, j), cv::Scalar(0, 0, 0));
            }
        }
    }

    cv::cvtColor(mouthROIGray, mouthROIGray, CV_RGB2GRAY);
    //blur(mouthROIGray, mouthROIGray, cv::Size(3,3));
    //cv::erode(mouthROIGray, mouthROIGray, cv::Mat());
    //cv::dilate(mouthROIGray, mouthROIGray, cv::Mat());

    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(mouthROIGray, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    if(contours.size() > 0)
    {
        int maxLength = 0;
        int maxIndex = 0;

        for(int k = 0; k < (int)contours.size(); k++)
        {
            //cv::drawContours(mouthROIGray, contours, k, cv::Scalar(0,255,255), 1, CV_AA);

            //imshow("mouth", mouthROIGray);

            if((int)contours[k].size() > maxLength)
            {
                maxLength = contours[k].size();
                maxIndex = k;
            }
        }

        if(maxLength > 30)
        {
            /*
            for(int i = 0; i < maxLength; i++)
            {
                int j = (i + 1) % maxLength;
                cv::line(mouthROIGray,
                         (contours[maxIndex])[i],
                         (contours[maxIndex])[j],
                         CV_RGB(0, 0, 255),
                         2, 8, 0);
                cv::line(originalFrame,
                         cv::Point((contours[maxIndex])[i] + mouthUpperLeft),
                         cv::Point((contours[maxIndex])[j] + mouthUpperLeft),
                         CV_RGB(0, 255, 0),
                         2, 8, 0);
            }
            */

            int mouthDiff = findMouthDiff(contours[maxIndex]);

            if(mouthDiff > yawningThresh)
            {
                emit mouthStatus(MOUTH_STATUS_YAWN);
            }
        }
    }
    else
        emit mouthStatus(MOUTH_STATUS_OK);
}

int YawningDetector::findMouthDiff(const std::vector<cv::Point>& contour)
{
    int minY = FRAME_HEIGHT;
    int maxY = 0;
    for(int i = 0; i < (int)contour.size(); i++)
    {
        if(contour[i].y < minY)
        {
            minY = contour[i].y;
        }
        if(contour[i].y > maxY)
        {
            maxY = contour[i].y;
        }
    }

    return maxY - minY;
}
