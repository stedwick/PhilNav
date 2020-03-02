#ifndef PHILNAVIMAGEPROVIDER_H
#define PHILNAVIMAGEPROVIDER_H

#include <QQuickImageProvider>

class PhilNavImageProvider : public QQuickImageProvider
{
public:
    PhilNavImageProvider();
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);

    static QImage image;
};

#endif // PHILNAVIMAGEPROVIDER_H
