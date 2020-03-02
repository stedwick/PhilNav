#include "philnavfilter.h"
#include "philnavimageprovider.h"

#include "private/qvideoframe_p.h"

QVideoFilterRunnable* PhilNavFilter::createFilterRunnable() {
    return new PhilNavFilterRunnable(this);
}

PhilNavFilterRunnable::PhilNavFilterRunnable(PhilNavFilter *creator) {
    m_filter = creator;
    m_dirty = false;
    m_frame = 0;
};

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
    input->unmap();

    m_image = m_image.copy(m_image.width()/4, m_image.height()/4, m_image.width()/2, m_image.height()/2);
    m_image = m_image.scaled(320, 180);
    m_image = m_image.convertToFormat(QImage::Format_BGR888);
    cv::Mat mat = QImage2CVMat(m_image);
    cv::cvtColor(mat, mat, cv::COLOR_BGR2HSV);

    cv::Mat mat_inrange;
    cv::inRange(mat, cv::Scalar(0, 0, 0), cv::Scalar(100, 100, 100), mat_inrange);
    cv::cvtColor(mat_inrange, mat_inrange, cv::COLOR_GRAY2BGR);
    QImage m_image_b = CVMat2QImage(mat_inrange);

//    PhilNavOpenCV pnocv;

    if (!m_dirty) {
//        cv::imwrite("/Users/pbrocoum/Downloads/img.jpg", mat_inrange);
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
