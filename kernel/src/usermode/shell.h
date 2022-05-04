#pragma once

class Shell {
	private:
		char buffer[1024];
		int index = 0;
		bool entered_command;
		void get_command();
		int compare_strings(char a[], char b[]);
	public:
		void set_buffer(char buf[1024]);
		char* get_buffer();
		void print_f(char* str);
		void input(char chr);
		void clear_buffer();
		void add_char_to_buffer(char chr);
		bool is_command_entered();
		void set_is_command_entered(bool cond);
		void handle_command();
};

extern Shell* shell;