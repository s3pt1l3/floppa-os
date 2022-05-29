#include "shell.h"
#include "../BasicRenderer.h"
#include "../userinput/keyboard.h"
#include "../memory.h"
#include "eval.h"
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
				int res = eval((char*)Shell::buffer);
				shell->print_f((char*)to_string((int64_t)res));
				Shell::clear_buffer();
				Shell::set_is_command_entered(false);
				GlobalRenderer->Next();
				
				shell->print_f("FloppaOS Calculator />");
			}
		}
	}
	else if (Shell::compare_strings(Shell::buffer, "about") == 0) {
		{
            shell->print_f("5PGPP####BBBBBBBBBBBGGGPP5J?77????777!!!!!~~~~~~~~~~~~~!!!!!!!!!!!7777777777777?JYPGPPGGPPPPP55YYYJJ");
            GlobalRenderer->Next();
            shell->print_f("..:^~!!77~!!!7??JJY5PPPPPPJ??JGBBBBBGGPPP555YYJJJ???7777!!!!!!!~~!!!!!!!!!!!!!JPB##BBBB######BBBGP5Y");
            GlobalRenderer->Next();
            shell->print_f(".....   .....::~77?7!!7??JYY55PPGGGGBBBBBBBGGGGPPP55Y!~^^~~~~~~~~~~!P##B##&&##BGP555Y5555YY");
            GlobalRenderer->Next();
            shell->print_f("..................... :~!?!. ..   ......:::^^~~!!7??JJYY5PPJ^:::::^^^^^^^?G#BGGGBPJ?!!~~~~~~~!!!!!");
            GlobalRenderer->Next();
            shell->print_f("^.                   ....^!7!:............ .             ...:...........:~P#BP5P5!^::::^^^^^^^^^^~~~");
            GlobalRenderer->Next();
            shell->print_f("G5?~:                     ^7~             ......................   ....^YBG5YY5P~.........::::::::::");
            GlobalRenderer->Next();
            shell->print_f("YY55J7!^.                  !!.                                  .   .~YGG5JJJYP! ..... .............");
            GlobalRenderer->Next();
            shell->print_f("JJJJJJJY55J7!!!!!!~~~^^^::^!77:..                                 .~YBG5J??JY5~            .........");
            GlobalRenderer->Next();
            shell->print_f("JJ???????YGBG5?!77777???7!!!!77!7?7777!!!!~~^^^^::::.....       :75BG5J??JJY5!");
            GlobalRenderer->Next();
            shell->print_f("YJJJ???777?YGBB57^^~~^^^^~!!~!7!~~~~~!!!!77777???????????777!!!YB#B5J??JJJYP?....");
            GlobalRenderer->Next();
            shell->print_f("5J???????77?JYP##BPYPPP7~~!!~!!!!7??7!!!!~~~~^^^^^^^^^^^~~!JY5B#BPYJJJJ??5PJ7?????????77!!!!~~^^::::");
            GlobalRenderer->Next();
            shell->print_f("GY?????????77?J5G##BPY?~^~!!!!!!7YPGPPGPPPPPPPP5555YYYJJ7?J5B#BP5JJ????YGP?^^^^~~^~~~~!~7YPPPPPP5555");
            GlobalRenderer->Next();
            shell->print_f("5G5J?7????7777?JYPB##BPJJYYYYYY55PPGGGBBGGBGPGPPPPPPGGGGGGB##BPYJ?????JPPYP55555YYYYJJJJJJJJJJJJJJJJ");
            GlobalRenderer->Next();
            shell->print_f("JYGGY???????77??JYPBBBBBGGPPPGGGGP5PPPBB##BGPPPGGGGPGGGGGBGGPP5YJ????JP5?YYJJJJJJYYYYY55YJ??????????");
            GlobalRenderer->Next();
            shell->print_f("JJJPPY???????77?JY55PGGPPPPPGBBG5JJY5PGGBBBGP5YYYYGGGBGGGGGPP5YYJ??JJJY?YY???????7??????????????????");
            GlobalRenderer->Next();
            shell->print_f("YYYYYG5?????????JY5PGPPPGPGB###GJ?JJY5PPBBGP5YYJJJYB###GGGBBBP5YJ??JJ?7?5JJJJJ??????????????????????");
            GlobalRenderer->Next();
            shell->print_f("YYYY55J?JJ??J??JYPPPPGGGBGPP#&#GJ?JYYY55PP555YYYJJYB&&BPPBBBBBBGP5YJJJJJYYP5YJJJJJJJJJJJJJJJJJJJJJJJ");
            GlobalRenderer->Next();
            shell->print_f("Y55YY???J?JJJJY5PPPGGGPPPPYYPBBGJ??YJJYY5555YYYYJJJG#B5555PPGPPGBGP5PP55555YYJJJJJJJJJJJJJJJJJJJJJJJ");
            GlobalRenderer->Next();
            shell->print_f("Y5555JJYYJJJYPPPPGP555P5555YYJ?77!7JJJYYY555YYYJ?77!?JY555PPP55PGBBB#B5555YYYYYJJJJJJJJJJJJJJJJJJJJJ");
            GlobalRenderer->Next();
            shell->print_f("YY55555PBGP5PGPPGGBBBBB##BB##PY7~~!?JJJYYYYYYJJJ7~~75PBBB##BB#GBGGGGB#G555YYYYYYYYYYYYYYYYYYYYYYYYYY");
            GlobalRenderer->Next();
            shell->print_f("JYY55555G&BPPGGPPYJYBGP#BBPBBG##7~!???JJYYYYYJJJ7~!B#B#GB##GGY!?5GGPB##PYYYYYYYYYYYYYYYYYYYYYYYYYYYY");
            GlobalRenderer->Next();
            shell->print_f("JJYY555PBBGGBGP5P5?!!J5GB#BBBG&@P!7?JJJJYYYYYJJJ7!Y&####BBPY77JPGP5PG##BPJJJJJJJJJJJJYYYYYYYYYYYYYYY");
            GlobalRenderer->Next();
            shell->print_f("JJJJY555PPPGBGP55PPP5J??JY5G#&&&#J77?JJJJY55YYJJ??G&&&&GYJJY5PPPP55PB###BPJJJJJJJJJJJJJJJJJYYYYYYYYY");
            GlobalRenderer->Next();
            shell->print_f("YYJJYYJ?5PGBBBGP5555PPP555YYPB&&#G5YJYY55PGGP5YY5PB&&#GP5PPP555555PGB####G5YY55YYYYYYYYYYYYYYYYYYYYY");
            GlobalRenderer->Next();
            shell->print_f("#BBBGY7JPGGGGBGPP5555555555PPG#&###PPPGGBGGGBGGGGB&###BGPPPP55PPGGGGBB###BGP5PBGGGP555555YYYY5555555");
            GlobalRenderer->Next();
            shell->print_f("####G??5GBGGPGGGGGPP555PPP5PGGBBB#&BBBBBBBBBBB##BB&BGBBGGPGPPPGBBGG#BBBBBBGP55GB#BBBBBBBBGGGGGGGGGGG");
            GlobalRenderer->Next();
            shell->print_f("####P7JPGGGPP5PGGGGGGGP5PPPPGGP55P#BB&##BBBBBB#&###5Y5PPGGGGPGGBBBBGGBGGBG5555P#########BBBBBBGGBBBB");
            GlobalRenderer->Next();
            shell->print_f("##BBP?Y5PGPP5555GBBBBGGPPGPPPPYJJYG####BBGGPGB##&&PYYYPGBBBBP5PGGGPPGBGGG55555P##&###########BBBBBGG");
            GlobalRenderer->Next();
            shell->print_f("#BBBPYY5GG55555YY5PGGP5PBB###GG5J?J5B&&&BPGGP#@&GY7?J5GGB#&##PP555PPGGGGPP55P5P#&&############BBBBBG");
            GlobalRenderer->Next();
            shell->print_f("##BBG5YY55555PP5YJJJYY5B##BGP55J?7!!7JG##B##B&#Y!~!!7JY55PG##BJ?JYPPPPPP555555G#&&&&##########BBBBGG");
            GlobalRenderer->Next();
            shell->print_f("###BG5YY5555PP55YJ?7!!?###BPGGPPJ7!!~~!JG#&&#P?~~~~!?YPGG##&&&YJJJY5PP5555555PB###&&&#########BBBBBG");
            GlobalRenderer->Next();
            shell->print_f("###BG5YYYYY55555YJJ???Y#&&#BBG55Y?7!!~~~!YB#Y!!!!!77?JY5PGB&&BYJ?JY55YYYY5PPPB###&#&&&#########BBBBB");
            GlobalRenderer->Next();
            shell->print_f("###BBPYYYYYYY555YJ???7?P&&#BBGPP5JJ?JJJJ??G#Y?JYYJYJY5G##&&&BPYYYYYYJJJJY55PG###&###&&&&##B#####BBBB");
            GlobalRenderer->Next();
            shell->print_f("####BG5YYYY5YYYYJJ?77??J5G&&##BGP5YJJJ??JY55YJJJJJY5PBB####BPYJ??JJJJJJYY55GB#######&&&&##BB####BBBB");
            GlobalRenderer->Next();
            shell->print_f("####BBP55YYYYYYYJJ???J???Y5PBBBBGP5J????J????JJ77?J55PGPPP5Y?????7???JYY5PGBB##&###&&&&#BBB##B###BBB");
            GlobalRenderer->Next();
            shell->print_f("&####BP555YYYYJJ?????7??77?JYJYJ?JJ777777777777!!!77?J5YJ??777777????YYPGGGB#######&&&&#B#BBBBBBBBBB");
            GlobalRenderer->Next();
            shell->print_f("######PYY555YJJ???777?777777?JJ?77!!!!!!!!!!!!!!777?JJ?7777777777?JJ5PGPPGB#######&&&###BBBBBBBBBBBB");
            GlobalRenderer->Next();
            shell->print_f("&&####BYJYY55YY??777777777777??JJJJ?????77?????JYYYYJ?7777777??JJYPPPBGGPG########&&&#####BBBBBBBGGB");
            GlobalRenderer->Next();
            shell->print_f("&&&&##B5YYYY55JJJ??777!!7!!!77777?JYYYYYY5555555YJ?777!777?JJYPGGPGPPPGBBBB#BB###&&&######BBBBBBGBBG");
            GlobalRenderer->Next();
            shell->print_f("&&&&###G5YYYYYYYJ????7777!!!!!!!!!77???JJYYYJJ?777!!!7?JYY5PPPPGGP5GGGG###BB##########BBBBBBBBGBBGGG");
            GlobalRenderer->Next();
            shell->print_f("&&&#&&&#PYYYYYYJJJJ??7777!!!!!!!!!!!!!!!!!7!!!!!!!!7?JY5555555PPGGPPBBBB###BB####BB###BBBB##BBBGGGGG");
            GlobalRenderer->Next();
            shell->print_f("&&&&&&&&BPYJYYYJJJJJ?777!!!~~~~~~~~!!!!~!!!!!!!!!77?JY555555PPPPGGGPB#BGBB##BB####BB#BBBBBB#BBGGGGGG");
            GlobalRenderer->Next();
            shell->print_f("&&&&&&&&#GYY55YYJJJJ?77!~~~~~~~~~~~~!!!!!!!!!777??JJYY5Y5555PPGPGGGBGBBBGB###BBB##BBBBGBBBBBBBBBGGGG");
            GlobalRenderer->Next();
            shell->print_f("#####B##BP555YYYYYJJ?77!!~~~~~~~~~!!777777777????JJYY555555PPPPPGBGBGGBGGBBB##BBBBBB#BGGGBBBBBBBBBBG");
            GlobalRenderer->Next();
            shell->print_f("BB###BBBPPPP555YYJJ???7!!!!~~~~!!!!7777777?????JJJYYYY5555PPPPPGGGGGGPGGGBBBBBBGGGBGBBBBGGGB##BBB##B");
            GlobalRenderer->Next();
            shell->print_f("GPPPP5555PGG555YYJJJ???77!!!!!!!!7777777777???JJJYYYY55555PPPGGGGGGPGPGGGBBBBBBGGGBGBBBBGGBBGGBBBBB#");
            GlobalRenderer->Next();
            shell->print_f("5YYYYYYYY5PP555YYYJJ??7777!!!!!!7777777777???JJJJYYY5Y5PPPPPPGPGGGGPPPGGG#BBGBBGGGGGGGBBBBBGGGBBBBBB");
            GlobalRenderer->Next();
		}
        shell->print_f("OS: FloppaOS alpha version");
        GlobalRenderer->Next();

	}
    else if (Shell::compare_strings(Shell::buffer, "help") == 0) {
        shell->print_f("calc - Runs calculator");
        GlobalRenderer->Next();
        shell->print_f("clear - Clears screen, cursor position");
        GlobalRenderer->Next();
        shell->print_f("about - Information about system");
        GlobalRenderer->Next();
        shell->print_f("devices - Information about devices");
        GlobalRenderer->Next();
    }
    else if (Shell::compare_strings(Shell::buffer, "clear") == 0) {
        Shell::clear_buffer();
        GlobalRenderer->ClearCursorPosition();
        GlobalRenderer->Clear();
    }
    else if (Shell::compare_strings(Shell::buffer, "devices") == 0) {
        shell->print_f("Device specifications");
        GlobalRenderer->Next();
        shell->print_f("Disk info: NO NAME FAT12");
        GlobalRenderer->Next();
        shell->print_f("Intel Corp 6 port SATA Controller [AHCI mode] - Mass Storage Controller - Serial ATA - AHCI 1.0");
        GlobalRenderer->Next();
        shell->print_f("Display: Display Conroller - VGA Compatible Controller - VGA Controller");
        GlobalRenderer->Next();
        shell->print_f("Intel Corp Express DRAM Controller");
    }
	else {
		shell->print_f("Command not found");
		
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

