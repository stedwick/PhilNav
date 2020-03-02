#ifndef PHILNAVOPENCV_H
#define PHILNAVOPENCV_H

#include <QObject>
#include <QImage>

#include "opencv2/opencv.hpp"

class PhilNavOpenCV : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QImage qimage MEMBER m_qimage WRITE setQimage NOTIFY qimageChanged)
    Q_PROPERTY(cv::Mat cvmat MEMBER m_cvmat WRITE setCvmat NOTIFY cvmatChanged)

public:

public slots:
    void setQimage(QImage &src);
    void setCvmat(cv::Mat &src);

signals:
    void qimageChanged();
    void cvmatChanged();

private:
    QImage m_qimage;
    cv::Mat m_cvmat;
};

#endif // PHILNAVOPENCV_H
