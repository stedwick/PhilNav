#include "philnavfilter.h"

QVideoFilterRunnable* PhilNavFilter::createFilterRunnable() {
    return new PhilNavFilterRunnable(this);
}

QVideoFrame PhilNavFilterRunnable::run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags)
{
    Q_UNUSED(surfaceFormat);
    Q_UNUSED(flags);

    input->map(QAbstractVideoBuffer::ReadOnly);

    m_image = qt_imageFromVideoFrame(*input);
    m_image = m_image.convertToFormat(QImage::Format_Grayscale8);
    m_image = m_image.mirrored();

    input->unmap();

    emit m_filter->frameProcessed();

    return *input;
}
