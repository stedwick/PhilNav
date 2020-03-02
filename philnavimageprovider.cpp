#include "philnavimageprovider.h"

PhilNavImageProvider::PhilNavImageProvider() : QQuickImageProvider(QQuickImageProvider::Image) {}

QImage PhilNavImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(id)
    Q_UNUSED(size);
    Q_UNUSED(requestedSize);

    return PhilNavImageProvider::image;
}
