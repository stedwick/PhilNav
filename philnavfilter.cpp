#include "philnavfilter.h"
#include "philnavimageprovider.h"

QVideoFilterRunnable* PhilNavFilter::createFilterRunnable() {
    return new PhilNavFilterRunnable(this);
}

QVideoFrame PhilNavFilterRunnable::run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags)
{
    Q_UNUSED(surfaceFormat);
    Q_UNUSED(flags);


    input->map(QAbstractVideoBuffer::ReadOnly);

    m_image = qt_imageFromVideoFrame(*input);
    m_image = m_image.copy(m_image.width()/4, m_image.height()/4, m_image.width()/2, m_image.height()/2);
    m_image = m_image.scaled(320, 180);

    m_image = m_image.convertToFormat(QImage::Format_Grayscale8);
    // m_image = m_image.mirrored();

    input->unmap();

#ifdef QT_DEBUG
    QString image_path("/Users/pbrocoum/Downloads/img.jpg");
    if (!m_dirty) {
        m_image.save(image_path);
    }
#endif

    PhilNavImageProvider::image = m_image.copy();
    m_dirty = true;
    emit m_filter->frameProcessed();

    return *input;
}
