#include "panic.h"
#include "BasicRenderer.h"

void Panic(const char* panicMessage) {
    GlobalRenderer->ClearColor = 0x00ff0000;
    GlobalRenderer->Clear();

    GlobalRenderer->CursorPosition = { 0, 0 };

    GlobalRenderer->Color = 0;

    GlobalRenderer->Print("Kernel Panic");

    GlobalRenderer->Next();
    GlobalRenderer->Next();

    GlobalRenderer->Print(panicMessage);
}