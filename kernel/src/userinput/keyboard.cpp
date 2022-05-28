#include "keyboard.h"
#include "../memory.h"
#include "../usermode/shell.h"

bool isLeftShiftPressed;
bool isRightShiftPressed;

void HandleKeyboard(uint8_t scancode) {
    switch (scancode) {
        case LeftShift:
            isLeftShiftPressed = true;
            return;
        case LeftShift + 0x80:
            isLeftShiftPressed = false;
            return;
        case RightShift:
            isRightShiftPressed = true;
            return;
        case RightShift + 0x80:
            isRightShiftPressed = false;
            return;
        case Enter:
            GlobalRenderer->Next();
            shell->add_char_to_buffer('\0');
            shell->set_is_command_entered(true);
            return;
        case Spacebar:
            GlobalRenderer->PutChar(' ');
            shell->add_char_to_buffer(' ');
            return;
        case BackSpace:
            shell->delete_last_sym();
            GlobalRenderer->ClearChar();
            return;
    }

    char ascii = QWERTYKeyboard::Translate(scancode, isLeftShiftPressed || isRightShiftPressed);

    if (ascii != 0) {
        GlobalRenderer->PutChar(ascii);
        shell->add_char_to_buffer(ascii);
    }

}