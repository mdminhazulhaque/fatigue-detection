#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopWidget>
#include "opencv2/opencv.hpp"

#include "videoprocessor.h"

using namespace cv;

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
    ~Window();

public slots:
    void updateFrame(const QImage& frame);
    void finished();

private slots:
    void setFaceStatus(int status);
    void setEyeStatus(int status);
    void setMouthStatus(int status);
    void setProgress(int progress);

    void selectInputFile();
    void closeApplication();

private:
    Ui::Window *ui;
    VideoProcessor *vp;
    bool loaded;

    QPalette red;
    QPalette green;
    QPalette blue;
    QPalette yellow;
    QPalette grey;

};

#endif // WINDOW_H
