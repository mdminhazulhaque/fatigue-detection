#ifndef MATTOQIMAGE_H
#define MATTOQIMAGE_H

#include <QtCore>
#include <QDebug>
#include <QImage>

#include <opencv2/opencv.hpp>

QImage MatToQImage(const cv::Mat&);

#endif
