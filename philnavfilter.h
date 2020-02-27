#ifndef PHILNAVFILTER_H
#define PHILNAVFILTER_H

#include <QAbstractVideoFilter>
#include "private/qvideoframe_p.h"

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
    PhilNavFilterRunnable(PhilNavFilter *creator) {
        m_filter = creator;
    };
    QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags);

private:
    PhilNavFilter *m_filter;
    QImage m_image;
};

#endif // PHILNAVFILTER_H
