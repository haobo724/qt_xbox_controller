#include "mainwindow.h"
#include "./ui_mainwindow.h"
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

    qRegisterMetaType<Xbox_info>("Xbox_info");//注册一种信号的参数类型
    connect(gamepad, SIGNAL(JoySignal_row(Xbox_info)), this, SLOT(display_slot_row(Xbox_info)));
    connect(this, SIGNAL(send_data2slider(float)), this, SLOT(on_horizontalSlider_valueChanged(float)));
    connect(this, SIGNAL(send_data2slider_2(float)), this, SLOT(on_horizontalSlider_2_valueChanged(float)));
    connect(this, SIGNAL(send_data2slider_3(float)), this, SLOT(on_horizontalSlider_3_valueChanged(float)));
    gamepad->start();
}

MainWindow::~MainWindow()
{
    delete ui;
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


void MainWindow::on_horizontalSlider_valueChanged(float value)
{
    float current_value = ui->horizontalSlider->value();
    current_value += value;
    ui->horizontalSlider->setValue(current_value);
    QString data = QString("%1").arg(current_value);
    ui->label->setText(data);

}

void MainWindow::on_horizontalSlider_2_valueChanged(float value)
{
    float current_value = ui->horizontalSlider_2->value();
    current_value += value;
    ui->horizontalSlider_2->setValue(current_value);
    QString data = QString("%1").arg(current_value);
    ui->label_2->setText(data);
}

void MainWindow::on_horizontalSlider_3_valueChanged(float value)
{
    float current_value = ui->horizontalSlider_3->value();
    current_value += value;
    ui->horizontalSlider_3->setValue(current_value);
    QString data = QString("%1").arg(current_value);
     ui->label_3->setText(data);
}

