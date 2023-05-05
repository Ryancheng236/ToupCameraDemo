#include "utils.h"

Utils::Utils(QObject *parent)
    : QObject{parent}
{

}



/**
 * @brief       QImage转Mat
 * @param QImage
 * @return
 */

cv::Mat QImageTocvMat(const QImage &image)
{
    cv::Mat frame;
    switch(image.format())
    {
    case QImage::Format_Grayscale8: //灰度图，每个像素点1个字节（8位）
    case QImage::Format_Indexed8: //Mat构造：行数，列数，存储结构，数据，step每行多少字节
                frame = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
    break;
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
                frame = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
    break;
    case QImage::Format_RGB888: //RR,GG,BB字节顺序存储
                frame = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
                cv::cvtColor(frame, frame, cv::COLOR_RGB2BGR); //opencv需要转为BGR的字节顺序
        break;
    }
    return frame;
}

/**
 * @brief       Mat转QImage
 * @param mat
 * @return
 */
QImage cvMatToQImage(const cv::Mat& mat)
{
    switch (mat.type()) {
    case CV_8UC1:{
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);

        image.setColorCount(256);
        for(int i = 0; i < 256; i++){
            image.setColor(i, qRgb(i, i, i));
        }

        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++){
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }

        return image;
    }
        break;
    case CV_8UC3:{
        const uchar *pSrc = (const uchar*)mat.data;
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);

        return image.rgbSwapped();
    }
        break;
    case CV_8UC4:{
        const uchar *pSrc = (const uchar*)mat.data;
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);

        return image.copy();
    }
        break;
    default:
        break;
    }

    return QImage();
}
