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
    if (m_frame > 3) {
        m_dirty = false;
        m_frame = 1;
    }

    input->map(QAbstractVideoBuffer::ReadOnly);

    m_image = qt_imageFromVideoFrame(*input);
    m_image = m_image.copy(m_image.width()/4, m_image.height()/4, m_image.width()/2, m_image.height()/2);
    m_image = m_image.scaled(320, 180);
    m_image = m_image.convertToFormat(QImage::Format_Grayscale8);

    input->unmap();

    if (!m_dirty) {
//        QString image_path("/Users/pbrocoum/Downloads/img.jpg");
//        m_image.save(image_path);
        PhilNavImageProvider::image = m_image;

        emit m_filter->frameProcessed();
        m_dirty = true;
    }

    return *input;
}
