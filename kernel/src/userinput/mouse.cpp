#include "mouse.h"

uint8_t MousePointer[] = {
    0b00110000, 0b00000000,
    0b00101000, 0b00000000,
    0b00100100, 0b00000000,
    0b00100010, 0b00000000,
    0b00100001, 0b00000000,
    0b00100000, 0b10000000,
    0b00100000, 0b01000000,
    0b00100000, 0b00100000,
    0b00100000, 0b00010000,
    0b00100000, 0b00001000,
    0b00100000, 0b00000100,
    0b00100000, 0b01111100,
    0b00100010, 0b01000000,
    0b00100101, 0b00100000,
    0b00101001, 0b00100000,
    0b00110000, 0b11100000,
};


void MouseWait() {
    uint64_t timeout = 100000;
    while (timeout--) {
        if ((inb(0x64) & 0b10) == 0) {
            return;
        }
    }
}

void MouseWaitInput() {
    uint64_t timeout = 100000;
    while (timeout--) {
        if (inb(0x64) & 0b1) {
            return;
        }
    }
}

void MouseWrite(uint8_t value) {
    MouseWait();
    outb(0x64, 0xD4);
    MouseWait();
    outb(0x60, value);
}

uint8_t MouseRead() {
    MouseWaitInput();
    return inb(0x60);
}

uint8_t MouseCycle = 0;
uint8_t MousePacket[4];
bool MousePacketReady = false;
Point MousePosition;
Point MousePositionOld;

void HandlePS2Mouse(uint8_t data) {
    ProcessMousePacket();
    static bool skip = true;
    if (skip) {
        skip = false;
        return;
    }

    switch (MouseCycle) {
        case 0:
            if ((data & 0b00001000) == 0) break;
            MousePacket[0] = data;
            MouseCycle++;
            break;
        case 1:
            MousePacket[1] = data;
            MouseCycle++;
            break;
        case 2:
            MousePacket[2] = data;
            MousePacketReady = true;
            MouseCycle = 0;
            break;
    }
}

void ProcessMousePacket() {
    if (!MousePacketReady) return;

    bool xNegative, yNegative, xOverflow, yOverflow;

    if (MousePacket[0] & PS2XSign) {
        xNegative = true;
    }
    else xNegative = false;

    if (MousePacket[0] & PS2YSign) {
        yNegative = true;
    }
    else yNegative = false;

    if (MousePacket[0] & PS2XOverflow) {
        xOverflow = true;
    }
    else xOverflow = false;

    if (MousePacket[0] & PS2YOverflow) {
        yOverflow = true;
    }
    else yOverflow = false;

    if (!xNegative) {
        MousePosition.X += MousePacket[1];
        if (xOverflow) {
            MousePosition.X += 255;
        }
    }
    else
    {
        MousePacket[1] = 256 - MousePacket[1];
        MousePosition.X -= MousePacket[1];
        if (xOverflow) {
            MousePosition.X -= 255;
        }
    }

    if (!yNegative) {
        MousePosition.Y -= MousePacket[2];
        if (yOverflow) {
            MousePosition.Y -= 255;
        }
    }
    else
    {
        MousePacket[2] = 256 - MousePacket[2];
        MousePosition.Y += MousePacket[2];
        if (yOverflow) {
            MousePosition.Y += 255;
        }
    }

    if (MousePosition.X < 0) MousePosition.X = 0;
    if (MousePosition.X > GlobalRenderer->TargetFramebuffer->Width - 1) MousePosition.X = GlobalRenderer->TargetFramebuffer->Width - 1;

    if (MousePosition.Y < 0) MousePosition.Y = 0;
    if (MousePosition.Y > GlobalRenderer->TargetFramebuffer->Height - 1) MousePosition.Y = GlobalRenderer->TargetFramebuffer->Height - 1;

    GlobalRenderer->ClearMouseCursor(MousePointer, MousePositionOld);
    GlobalRenderer->DrawOverlayMouseCursor(MousePointer, MousePosition, 0xffffff);

    if (MousePacket[0] & PS2Leftbutton) {
        uint32_t color = GlobalRenderer->Color;
        GlobalRenderer->Color = 0xfcf2f2;
        GlobalRenderer->PutChar('#', MousePosition.X, MousePosition.Y);
        GlobalRenderer->Color = color;
        // GlobalRenderer->PutChar('#', MousePosition.X, MousePosition.Y);
    }
    if (MousePacket[0] & PS2Middlebutton) {

    }
    if (MousePacket[0] & PS2Rightbutton) {
        uint32_t color = GlobalRenderer->Color;
        GlobalRenderer->Color = 0xbf0099;
        GlobalRenderer->PutChar('#', MousePosition.X, MousePosition.Y);
        GlobalRenderer->Color = color;
    }

    MousePacketReady = false;
    MousePositionOld = MousePosition;
}

void InitPS2Mouse() {

    outb(0x64, 0xA8); //enabling the auxiliary device - mouse

    MouseWait();
    outb(0x64, 0x20); //tells the keyboard controller that we want to send a command to the mouse
    MouseWaitInput();
    uint8_t status = inb(0x60);
    status |= 0b10;
    MouseWait();
    outb(0x64, 0x60);
    MouseWait();
    outb(0x60, status); // setting the correct bit is the "compaq" status byte

    MouseWrite(0xF6);
    MouseRead();

    MouseWrite(0xF4);
    MouseRead();
}