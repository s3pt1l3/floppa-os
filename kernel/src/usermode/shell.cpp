#include "shell.h"
#include "../BasicRenderer.h"
#include "../userinput/keyboard.h"
#include "../memory.h"
#include "calculator.h"
#include "../cstr.h"
#include <stdint.h>

Shell* shell;

extern "C" void Shell::print_f(char* str) {
	GlobalRenderer->Print(str);
}

extern "C" char* Shell::get_buffer() {
	return Shell::buffer;
}

extern "C" void Shell::set_buffer(char buf[1024]) {

	for (int i = 0; i < 1024; ++i) {
		Shell::buffer[i] = buf[i];
	}
}

void Shell::clear_buffer() {
	// memset(Shell::buffer, 0, sizeof(Shell::buffer));
	Shell::buffer[0] = '\0';
	Shell::index = 0;
}

void Shell::delete_last_sym() {
	Shell::index--;
	Shell::buffer[Shell::index] = 0;
}

void Shell::add_char_to_buffer(char chr) {
	char copy[1024];
	char* cur;
	int i = 0;
	for (cur = Shell::get_buffer(); *cur != '\0'; cur++) {
		copy[i] = *cur;
		i++;
	}

	copy[Shell::index] = chr;
	Shell::set_buffer(copy);
	Shell::index++;
}

bool Shell::is_command_entered() {
	return Shell::entered_command;
}

void Shell::set_is_command_entered(bool cond) {
	Shell::entered_command = cond;
}

void Shell::handle_command() {
	if (Shell::compare_strings(Shell::buffer, "test") == 0) {
		Shell::print_f(": command test handled");
	}
	


	else if (Shell::compare_strings(Shell::buffer, "calc") == 0) {
		Shell::set_is_command_entered(false);
		Shell::clear_buffer();
		shell->print_f("Enter exit to close programm");
		GlobalRenderer->Next();
		shell->print_f("FloppaOS Calculator />");
		while (true) {
			if (shell->is_command_entered()) {
				
				if (Shell::compare_strings(Shell::buffer, "exit") == 0) {
					break;
				}
				shell->print_f("Buffer: ");
				shell->print_f(Shell::get_buffer());
				GlobalRenderer->Next();

				int res = Calculator().evaluate(((char*)Shell::buffer));
				
				shell->print_f((char*)to_string((int64_t)res));
				Shell::clear_buffer();
				Shell::set_is_command_entered(false);
				GlobalRenderer->Next();
				
				shell->print_f("FloppaOS Calculator />");
			}
		}
	}
	
	Shell::set_is_command_entered(false);
	Shell::clear_buffer();
	GlobalRenderer->Next();
	shell->print_f("FloppaOS />");
}


int Shell::compare_strings(char a[], char b[])
{
	// A variable to iterate through the strings
	int i = 0;

	while (a[i] == b[i])
	{
		// If either of the strings reaches the end
		// we stop the loop
		if (a[i] == '\0' || b[i] == '\0')
			break;
		i++;
	}

	// We check if both the strings have been compared
	// till the end or not
	// If the strings are compared till the end they are equal
	if (a[i] == '\0' && b[i] == '\0')
		return 0;
	else
	{
		if (a[i] == '\0')
			return -1 * (b[i]);
		else if (b[i] == '\0')
			return a[i];
		else
			return (a[i] - b[i]);
	}
}

