#include "videoprocessor.h"

VideoProcessor::VideoProcessor(QObject *parent) : QThread(parent)
{
    faceEyeDetector = new FaceEyeDetector;
    eyeAnalyzer = new EyeAnalyzer;
    eyeBallColorDetector = new EyeBallColorDetector;
    yawningDetector = new YawningDetector;

#ifdef Q_OS_WIN
    faceEyeDetector->setFaceCascade("haarcascade_frontalface_alt_tree.xml");
    faceEyeDetector->setEyeCascade("haarcascade_eye_tree_eyeglasses.xml");
    faceEyeDetector->setMouthCascade("haarcascade_mcs_mouth.xml");
#else
    faceEyeDetector->setFaceCascade("/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt_tree.xml");
    faceEyeDetector->setEyeCascade("/usr/local/share/OpenCV/haarcascades/haarcascade_eye_tree_eyeglasses.xml");
    faceEyeDetector->setMouthCascade("/usr/local/share/OpenCV/haarcascades/haarcascade_mcs_mouth.xml");
#endif
}

void VideoProcessor::run()
{
    int b = 80;
    int g = 80;
    int r = 110;

    while(video.read(frame))
    {
        if(!camera)
        {
            processedFrames++;
            emit progress(processedFrames*100/totalFrames);
        }

        faceEyeDetector->setFrame(frame);
        faceEyeDetector->doDetect();

        eyeBallColorDetector->initialize(faceEyeDetector->getOriginalFrame(),
                                        faceEyeDetector->getEyeROIUpperLeft(),
                                        faceEyeDetector->getEyeBallROI(),
                                        faceEyeDetector->getEyeSampleColor());
        eyeBallColorDetector->doDetect();

        eyeAnalyzer->setOriginalFrame(eyeBallColorDetector->getOriginalFrame());
        eyeAnalyzer->setCliffDiff(eyeBallColorDetector->getCliffDiff());
        eyeAnalyzer->doAnalyze();

        yawningDetector->setOriginalFrame(eyeAnalyzer->getOriginalFrame());
        yawningDetector->setMouthROI(faceEyeDetector->getMouthROI());
        yawningDetector->setMouthROIUpperLeft(faceEyeDetector->getMouthROIUpperLeft());
        yawningDetector->setMouthSampleColor(faceEyeDetector->getMouthSampleColor());
        yawningDetector->doDetect(Color(r, g, b));
        yawningDetector->getOriginalFrame().copyTo(frame);

        emit sendFrame(MatToQImage(frame).scaled(640,420));

        msleep(30);
    }

    emit finished();
}

void VideoProcessor::initCapture(QString videoFile)
{
    if(video.isOpened())
        video.release();

    if(video.open(videoFile.toStdString()))
    {
        totalFrames = video.get(CV_CAP_PROP_FRAME_COUNT);
        processedFrames = 0;
        camera = false;
    }
    else
        throw std::runtime_error("Unable to init VideoCapture from file");
}

void VideoProcessor::initCapture(int index)
{
    if(video.isOpened())
        video.release();

    if(video.open(index))
    {
        camera = true;
    }
    else
        throw std::runtime_error("Unable to init VideoCapture from device");
}
