#include "philnavimageprovider.h"

QImage PhilNavImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(id)
    Q_UNUSED(size);
    Q_UNUSED(requestedSize);

//    QString image_path("/Users/pbrocoum/Downloads/img.jpg");
//    image.load(image_path);
    return PhilNavImageProvider::image;
}
