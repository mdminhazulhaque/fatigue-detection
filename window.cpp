#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window)
{
    loaded = false;
    ui->setupUi(this);
    setWindowTitle("Fatigue Estimation");

    vp = new VideoProcessor(this);

    /** connections **/
    connect(ui->bBrowseInput, SIGNAL(clicked()), this, SLOT(selectInputFile()));
    connect(ui->bStop, SIGNAL(clicked()), vp, SLOT(terminate()));
    connect(ui->bPlay, SIGNAL(clicked()), vp, SLOT(start()));
    connect(ui->bClose, SIGNAL(clicked()), this, SLOT(closeApplication()));

    connect(vp, SIGNAL(sendFrame(QImage)), this, SLOT(updateFrame(QImage)));
    connect(vp, SIGNAL(finished()), this, SLOT(finished()));
    connect(vp, SIGNAL(progress(int)), this, SLOT(setProgress(int)));

    connect(vp->eyeAnalyzer, SIGNAL(eyeStatus(int)), this, SLOT(setEyeStatus(int)));
    connect(vp->faceEyeDetector, SIGNAL(faceStatus(int)), this, SLOT(setFaceStatus(int)));
    connect(vp->yawningDetector, SIGNAL(mouthStatus(int)), this, SLOT(setMouthStatus(int)));

    setGeometry(QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    this->size(),
                    qApp->desktop()->availableGeometry()));
}

Window::~Window()
{
    closeApplication();
    delete ui;
}

void Window::updateFrame(const QImage &frame)
{
    ui->videoFrame->setPixmap(QPixmap::fromImage(frame));
}

void Window::finished()
{
    ui->videoFrame->clear();
    QMessageBox::information(this,
                             "Attention!",
                             "Playback ended");
    closeApplication();
}

void Window::setFaceStatus(int status)
{
    switch (status)
    {
    case FaceEyeDetector::FACE_STATUS_NONE:
        ui->face->setStyleSheet("QPushButton {background-color: #f00}");
        ui->eye->setStyleSheet("QPushButton {background-color: #ccc}");
        ui->mouth->setStyleSheet("QPushButton {background-color: #ccc}");
        break;
    case FaceEyeDetector::FACE_STATUS_FOUND:
        ui->face->setStyleSheet("QPushButton {background-color: #0f0}");
        break;
    default:
        break;
    }
}

void Window::setEyeStatus(int status)
{
    switch (status)
    {
    case EyeAnalyzer::EYE_STATUS_NONE:
        ui->eye->setStyleSheet("QPushButton {background-color: #ccc}");
        break;
    case EyeAnalyzer::EYE_STATUS_BLINK:
        ui->eye->setStyleSheet("QPushButton {background-color: #0f0}");
        break;
    case EyeAnalyzer::EYE_STATUS_WARNING:
        ui->eye->setStyleSheet("QPushButton {background-color: #ff0}");
        break;
    case EyeAnalyzer::EYE_STATUS_CLOSED:
        ui->eye->setStyleSheet("QPushButton {background-color: #f00}");
        break;
    default:
        break;
    }
}

void Window::setMouthStatus(int status)
{
    switch (status)
    {
    case YawningDetector::MOUTH_STATUS_OK:
        ui->mouth->setStyleSheet("QPushButton {background-color: #0f0}");
        break;
    case YawningDetector::MOUTH_STATUS_YAWN:
        ui->mouth->setStyleSheet("QPushButton {background-color: #ff0}");
        break;
    default:
        break;
    }
}

void Window::setProgress(int progress)
{
    ui->progress->setValue(progress);
}

void Window::selectInputFile()
{
    //loaded = true;
    //vp->initCapture("/home/minhaz/asma/video_normal.mkv");
    //vp->initCapture(0);
    //vp->initCapture("/home/minhaz/asma/video_sleep.mkv");
    //return;

    QString inputFile = QFileDialog::getOpenFileName(this,
                                                     tr("Select Video File"),
                                                     QDir::homePath());
    if(inputFile.isEmpty())
        return;
    else
    {
        loaded = true;
        ui->input->setText(inputFile);
        vp->initCapture(inputFile);
    }
}

void Window::closeApplication()
{
    if(vp->isRunning())
    {
        vp->terminate();
        vp->wait();
    }
    qApp->quit();
}
