#include "philnavopencv.h"

void PhilNavOpenCV::setQimage(QImage &src) {
    if (m_qimage != src) {
        m_qimage = src;
        emit qimageChanged();
    }
}

void PhilNavOpenCV::setCvmat(cv::Mat &src) {
    cv::Mat diff;
    cv::compare(m_cvmat, src, diff, cv::CMP_NE);
    int nz = cv::countNonZero(diff);
    if (nz != 0) {
        m_cvmat = src;
        emit cvmatChanged();
    }
}
