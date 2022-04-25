#include "shell.h"
#include "../BasicRenderer.h"

extern "C" void Shell::print_f(char* str) {
	GlobalRenderer->Print(str);
}