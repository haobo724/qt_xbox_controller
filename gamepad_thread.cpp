#include "gamepad_thread.h"


int Gamepad_Thread::GetPort()
{
    return cId + 1;
}

XINPUT_GAMEPAD *Gamepad_Thread::GetState()
{
    return &state.Gamepad;
}

bool Gamepad_Thread::CheckConnection()
{
    int controllerId = -1;

    for (DWORD i = 0; i < XUSER_MAX_COUNT && controllerId == -1; i++)
    {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));

        if (XInputGetState(i, &state) == ERROR_SUCCESS)
            controllerId = i;
    }

    cId = controllerId;

    return controllerId != -1;
}

// Returns false if the controller has been disconnected
bool Gamepad_Thread::Refresh()
{
    if (cId == -1)
        CheckConnection();

    if (cId != -1)
    {
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        if (XInputGetState(cId, &state) != ERROR_SUCCESS)
        {
            cId = -1;
            return false;
        }

        float normLX = fmaxf(-1, (float)state.Gamepad.sThumbLX / 32767);
        float normLY = fmaxf(-1, (float)state.Gamepad.sThumbLY / 32767);

        leftStickX = (abs(normLX) < deadzoneX ? 0 : (abs(normLX) - deadzoneX) * (normLX / abs(normLX)));
        leftStickY = (abs(normLY) < deadzoneY ? 0 : (abs(normLY) - deadzoneY) * (normLY / abs(normLY)));

        if (deadzoneX > 0) leftStickX *= 1 / (1 - deadzoneX);
        if (deadzoneY > 0) leftStickY *= 1 / (1 - deadzoneY);

        float normRX = fmaxf(-1, (float)state.Gamepad.sThumbRX / 32767);
        float normRY = fmaxf(-1, (float)state.Gamepad.sThumbRY / 32767);

        rightStickX = (abs(normRX) < deadzoneX ? 0 : (abs(normRX) - deadzoneX) * (normRX / abs(normRX)));
        rightStickY = (abs(normRY) < deadzoneY ? 0 : (abs(normRY) - deadzoneY) * (normRY / abs(normRY)));

        if (deadzoneX > 0) rightStickX *= 1 / (1 - deadzoneX);
        if (deadzoneY > 0) rightStickY *= 1 / (1 - deadzoneY);

        leftTrigger = (float)state.Gamepad.bLeftTrigger / 255;
        rightTrigger = (float)state.Gamepad.bRightTrigger / 255;

        return true;
    }
    return false;
}

bool Gamepad_Thread::IsPressed(WORD button)
{
    return (state.Gamepad.wButtons & button) != 0 ;
}

bool Gamepad_Thread::IsPressedTrigger(BYTE Trigger)
{
    return (state.Gamepad.bLeftTrigger & Trigger) != 0 ;
}



void Gamepad_Thread::run()
{
    bool wasConnected = true;

    while (true)
    {
        Sleep(100);

        if (!this->Refresh())
        {
            if (wasConnected)
            {
                wasConnected = false;

                cout << "Please connect an Xbox controller." << endl;
            }
        }
        else
        {
            if (!wasConnected)
            {
                wasConnected = true;

                cout << "Controller connected on port " << this->GetPort() << endl;
            }
            //if (abs(this->leftStickX) >=0.1 || abs(this->leftStickY) >=0.1) cout << "Left thumb stick: (" << this->leftStickX << ", " << this->leftStickY << ")"<< endl;
            if (abs(this->rightStickX) >=0.01 || abs(this->rightStickY) >=0.01) cout << "Right thumb stick: (" << this->rightStickX << ", " << this->rightStickY << ")"<< endl;
            //if (abs(this->leftTrigger) >=0.1 || abs(this->rightTrigger) >=0.1) cout << "Left analog trigger: " << this->leftTrigger << "   Right analog trigger: " << this->rightTrigger << endl;

            if (this->IsPressed(XINPUT_GAMEPAD_A)) cout << "(A) button pressed" << endl;
            if (this->IsPressed(XINPUT_GAMEPAD_B)) cout << "(B) button pressed" << endl;
            if (this->IsPressed(XINPUT_GAMEPAD_LEFT_THUMB)) cout << "(LEFT_THUMB) button pressed" << endl;
            if (this->IsPressedTrigger(VK_PAD_LTRIGGER)) cout << "(VK_PAD_LTRIGGER) button pressed" << endl;
            state_row.leftStickX = leftStickX;
            state_row.rightStickX = rightStickX;
            state_row.leftStickY = leftStickY;
            state_row.rightStickY = rightStickY;
            state_row.leftTrigger = leftTrigger;
            state_row.rightTrigger = rightTrigger;
            Xbox_info* P_Member = &state_row;		//指向结构体的指针
            float i, * P;
            P = &P_Member->leftStickX;		//int类型的指针P指向结构体的第一个成员
                for (i = 0; i < sizeof(state_row) / sizeof(float); i++)
                {
                    if ((*P++) != 0){
                        send_state_row(state_row);

                    }
                }



        }
    }

}

void Gamepad_Thread::send_state_row(Xbox_info state_row)
{
    emit JoySignal_row(state_row);

}
