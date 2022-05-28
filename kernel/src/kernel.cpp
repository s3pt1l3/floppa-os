#include "kernelUtil.h"
#include "memory/heap.h"
#include "scheduling/pit/pit.h"
#include "usermode/shell.h"
#include "scheduling/pit/pit.h"
#include "BasicRenderer.h"
#include "userinput/keyboard.h"


extern "C" void _start(BootInfo* bootInfo) {
    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    //PageTableManager* pageTableManager = kernelInfo.pageTableManager;
    
    PIT::Sleepd(5);
    GlobalRenderer->Clear();
    GlobalRenderer->ClearCursorPosition();

    
    shell->clear_buffer();

    //asm("int $0x0e");
    while (true) {
        if (shell->is_command_entered()) {
             shell->print_f("Command entered");
             shell->handle_command();
         }
        asm("hlt");
    } // stops crashing on real hardware
}