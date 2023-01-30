#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->horizontalSlider->setRange(-100,100);
    ui->horizontalSlider->setValue(0);
    ui->label->setText( QString::number(ui->horizontalSlider->value()));

    ui->horizontalSlider_2->setRange(-100,100);
    ui->horizontalSlider_2->setValue(0);
    ui->label_2->setText( QString::number(ui->horizontalSlider_2->value()));

    ui->horizontalSlider_3->setRange(-100,100);
    ui->horizontalSlider_3->setValue(0);
    ui->label_3->setText( QString::number(ui->horizontalSlider_3->value()));

    gamepad = new Gamepad_Thread();
    logWriter = new Record();
    logWriter->start();
    // color block
    updateColor();

    qRegisterMetaType<Xbox_info>("Xbox_info");//注册一种信号的参数类型
    connect(gamepad, SIGNAL(JoySignal_row(Xbox_info)), this, SLOT(display_slot_row(Xbox_info)));

    connect(this, SIGNAL(send_data2slider(float)), this, SLOT(hs1valuechanged(float)));
    connect(this, SIGNAL(send_data2slider_2(float)), this, SLOT(hs2valuechanged(float)));
    connect(this, SIGNAL(send_data2slider_3(float)), this, SLOT(hs3valuechanged(float)));
    /*
    QIcon icon =  QIcon("C:/Study/qtApp/qt_xbox/icons/caret-up.svg");
    ui->pushButton_4->setIcon(icon);
    */
    Camera = new VideoStream();
    ui->camera_widget->show();
    Camera->setCamera(ui->camera_widget);

    gamepad->start();
}

MainWindow::~MainWindow()
{
    gamepad->requestInterruption();
    gamepad->quit();
    gamepad=nullptr;
    Camera->stopCamera();

    delete gamepad;
    delete logWriter;
    delete Camera;
    delete ui;

}

int MainWindow::slider2colorspace(float value)
{
    int color_channel = 255*((value + 100)/200);
    return color_channel;
}

void MainWindow::updateColor()
{
    QString red = QString::number(slider2colorspace(ui->horizontalSlider->value()));
    QString green = QString::number(slider2colorspace(ui->horizontalSlider_2->value()));
    QString blue = QString::number(slider2colorspace(ui->horizontalSlider_3->value()));
    QString style ="background-color: rgb("+red+", "+green+", "+blue+");";
    ui->lb_color->setStyleSheet(style);
}

void MainWindow::display_slot_row(Xbox_info state_row)
{
    float data_triggerL = state_row.leftTrigger;
    float data_triggerR = state_row.rightTrigger;
    float data_trigger = -data_triggerL+data_triggerR;
    float data_float1 = state_row.leftStickX;
    float data_float2 = state_row.rightStickX;

    emit send_data2slider(data_float1);
    emit send_data2slider_2(data_float2);
    emit send_data2slider_3(data_trigger);

}


void MainWindow::hs1valuechanged(float value)
{
    float current_value = ui->horizontalSlider->value()+ value;
    ui->horizontalSlider->setValue(current_value);
    QString data = QString("%1").arg(current_value);
    ui->label->setText(data);
    // color block
    updateColor();
    // log block
    QString movedValue= QString("%1").arg(value);
    data = "LeftStick moved on X: " + movedValue+" , Now at Positon: "
            + data+" | ";
    logWriter->addText(data.toStdString());

}


void MainWindow::on_horizontalSlider_valueChanged()
{
    float current_value = ui->horizontalSlider->value();
    ui->horizontalSlider->setValue(current_value);
    QString data = QString("%1").arg(current_value);
    ui->label->setText(data);
    // color block
    updateColor();
    // log block
    QString movedValue= QString("%1").arg(0);
    data = "LeftStick moved on X: " + movedValue+" , Now at Positon: "
            + data+" | ";
    logWriter->addText(data.toStdString());

}


void MainWindow::hs2valuechanged(float value)
{
    float current_value = ui->horizontalSlider_2->value()+ value;
    ui->horizontalSlider_2->setValue(current_value);
    QString data = QString("%1").arg(current_value);
    ui->label_2->setText(data);
    // color block
    updateColor();
    // log block
    QString movedValue = QString("%1").arg(value);
    data = "RightStick moved on X: " + movedValue+" , Now at Positon: "
            + data+" | ";
    logWriter->addText(data.toStdString());

}

void MainWindow::hs3valuechanged(float value)
{
    float current_value = ui->horizontalSlider_3->value()+ value;
    ui->horizontalSlider_3->setValue(current_value);
    QString data = QString("%1").arg(current_value);
    ui->label_3->setText(data);
    // color block
    updateColor();
    // log block
    QString movedValue= QString("%1").arg(value);
    data = "Trigger moved:" + movedValue+" , Now at Positon: "
            + data +" | ";
    logWriter->addText(data.toStdString());


}

void MainWindow::on_pbnCP_clicked()
{
    ui->lbCP->setText("hi");
}


void MainWindow::on_pb_endexam_clicked()
{
    bool status = ui->pbnCP->isEnabled();
    qDebug()<<status;
    ui->pbnCP->setEnabled(!status);
}

