#ifndef VIDEOSTREAM_H
#define VIDEOSTREAM_H

#include <QCameraViewfinder>
#include <QCamera>
#include <QCameraImageCapture>
#include <QScopedPointer>



class VideoStream : public QCamera
{
    Q_OBJECT
public:
    VideoStream();
    void setCamera( QCameraViewfinder *viewfinder);

    void startCamera();
    void stopCamera();



private:

    QScopedPointer<QCamera> m_camera;
    QScopedPointer<QCameraImageCapture> m_imageCapture;

};

#endif // VIDEOSTREAM_H






