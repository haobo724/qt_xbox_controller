#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamepad_thread.h"
#include "record.h"
#include <string.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Gamepad_Thread *gamepad;
    Record *logWriter;

signals:
    void send_data2slider(float value);
    void send_data2slider_2(float value);
    void send_data2slider_3(float value);

private slots:
    void display_slot_row(Xbox_info state_row);


    void on_horizontalSlider_valueChanged(float value);
    void on_horizontalSlider_2_valueChanged(float value);
    void on_horizontalSlider_3_valueChanged(float value);
};
#endif // MAINWINDOW_H
