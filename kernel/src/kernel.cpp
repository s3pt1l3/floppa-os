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
    shell->clear_buffer();
    GlobalRenderer->Clear();
    GlobalRenderer->ClearCursorPosition();

    //asm("int $0x0e");
    while (true) {
        if (shell->is_command_entered()) {
             shell->handle_command();
         }
        asm("hlt");
    } // stops crashing on real hardware
}