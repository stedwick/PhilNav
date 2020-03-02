#ifndef PHILNAVFILTER_H
#define PHILNAVFILTER_H

#include <QAbstractVideoFilter>
#include <QSettings>

#include "opencv2/opencv.hpp"

class PhilNavFilter : public QAbstractVideoFilter
{
    Q_OBJECT
public:
    QVideoFilterRunnable *createFilterRunnable();

signals:
    void frameProcessed();
    // void cursorDetected(float x, float y);

public slots:

};

class PhilNavFilterRunnable : public QVideoFilterRunnable
{
public:
    PhilNavFilterRunnable(PhilNavFilter *creator);
    QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags);

protected:
    cv::Mat QImage2CVMat(QImage &src);
    QImage CVMat2QImage(cv::Mat &src);

private:
    PhilNavFilter *m_filter;
    QImage m_image;
    bool m_dirty;
    int m_frame;
    QSettings settings;
};

#endif // PHILNAVFILTER_H
