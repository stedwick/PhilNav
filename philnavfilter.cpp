#include "philnavfilter.h"
#include "philnavimageprovider.h"

QVideoFilterRunnable* PhilNavFilter::createFilterRunnable() {
    return new PhilNavFilterRunnable(this);
}

QVideoFrame PhilNavFilterRunnable::run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags)
{
    Q_UNUSED(surfaceFormat);
    Q_UNUSED(flags);

    m_frame++;
    if (m_frame > 0) {
        m_dirty = false;
        m_frame = 1;
    }

    input->map(QAbstractVideoBuffer::ReadOnly);

    m_image = qt_imageFromVideoFrame(*input);
    m_image = m_image.copy(m_image.width()/4, m_image.height()/4, m_image.width()/2, m_image.height()/2);
    m_image = m_image.scaled(320, 180);

    m_image = m_image.convertToFormat(QImage::Format_BGR888);
    cv::Mat mat = QImage2CVMat(m_image);
    cv::cvtColor(mat, mat, cv::COLOR_BGR2GRAY);
    cv::cvtColor(mat, mat, cv::COLOR_GRAY2BGR);
    QImage m_image_b = CVMat2QImage(mat);

    input->unmap();

    if (!m_dirty) {
        PhilNavImageProvider::image = m_image_b;

        emit m_filter->frameProcessed();
        m_dirty = true;
    }

    return *input;
}

cv::Mat PhilNavFilterRunnable::QImage2CVMat(QImage &src)
{
    cv::Mat dest(src.height(), src.width(), CV_8UC3, src.bits(), src.bytesPerLine());
    return dest;
}

QImage PhilNavFilterRunnable::CVMat2QImage(cv::Mat &src)
{
    QImage dest(src.data, src.cols, src.rows, src.step, QImage::Format_BGR888);
    return dest;
}
