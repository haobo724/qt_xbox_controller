#include "videostream.h"
#include <QCameraViewfinder>
#include <QCameraInfo>
#include <QMediaMetaData>

#include <QDebug>
#include <QtWidgets>
VideoStream::VideoStream()
{
    //this->setAttribute(Qt::WA_StyledBackground, true);

    //QActionGroup *videoDevicesGroup = new QActionGroup(this);
    //videoDevicesGroup->setExclusive(true);
    const QList<QCameraInfo> availableCameras = QCameraInfo::availableCameras();
    for (const QCameraInfo &cameraInfo : availableCameras) {
        //QAction *videoDeviceAction = new QAction(cameraInfo.description(), videoDevicesGroup);
        //videoDeviceAction->setCheckable(true);
        //videoDeviceAction->setData(QVariant::fromValue(cameraInfo));
        qDebug()<<cameraInfo.deviceName();
       // if (cameraInfo == QCameraInfo::defaultCamera())
       //     videoDeviceAction->setChecked(true);

        //ui->menuDevices->addAction(videoDeviceAction);
    }

    //connect(videoDevicesGroup, &QActionGroup::triggered, this, &VideoStream::updateCameraDevice);
    //connect(ui->captureWidget, &QTabWidget::currentChanged, this, &VideoStream::updateCaptureMode);

    //setCamera(QCameraInfo::defaultCamera());





}

VideoStream::~VideoStream()
{
this->stopCamera();
}

void VideoStream::setCamera(QCameraViewfinder *viewfinder)
{
    const QCameraInfo &cameraInfo = QCameraInfo::defaultCamera();

    m_camera.reset(new QCamera(cameraInfo));
    m_imageCapture.reset(new QCameraImageCapture(m_camera.data()));




    m_camera->setViewfinder(viewfinder);
    //updateCameraState(m_camera->state());
    //updateLockStatus(m_camera->lockStatus(), QCamera::UserRequest);




    m_camera->start();

}

void VideoStream::stopCamera()
{
      m_camera->stop();
}
