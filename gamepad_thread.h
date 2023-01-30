#ifndef GAMEPAD_THREAD_H
#define GAMEPAD_THREAD_H
#include <iostream>
#include <QObject>
#include <Windows.h>
#include <Xinput.h>
#include <QThread>
using std::cout;
using std::endl;

struct Xbox_info{    float leftStickX =0 ;
                     float leftStickY=0;
                     float rightStickX=0;
                     float rightStickY=0;
                     float leftTrigger=0;
                     float rightTrigger=0;};


class Gamepad_Thread : public QThread
{
    Q_OBJECT
public:
    //explicit Gamepad_Thread(QObject *parent = nullptr);
private:
    int cId;
    XINPUT_STATE state;

    float deadzoneX;
    float deadzoneY;

public:
    explicit Gamepad_Thread() : deadzoneX(0.08f), deadzoneY(0.08f) {};

    Gamepad_Thread(float dzX, float dzY) : deadzoneX(dzX), deadzoneY(dzY) {};
    ~Gamepad_Thread();
    float leftStickX;
    float leftStickY;
    float rightStickX;
    float rightStickY;
    float leftTrigger;
    float rightTrigger;
    Xbox_info state_row;

    int  GetPort();
    XINPUT_GAMEPAD *GetState();
    bool CheckConnection();
    bool Refresh();
    bool IsPressed(WORD);
    bool IsPressedTrigger(BYTE);
signals:
    void JoySignal_row(Xbox_info); //test

protected:
    void run();

    void send_state_row(Xbox_info state_row);
};

#endif // GAMEPAD_THREAD_H
