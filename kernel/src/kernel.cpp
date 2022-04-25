#include "kernelUtil.h"
#include "memory/heap.h"
#include "scheduling/pit/pit.h"
#include "usermode/shell.h"
#include "scheduling/pit/pit.h"
#include "BasicRenderer.h"

extern "C" void _start(BootInfo* bootInfo) {
    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    //PageTableManager* pageTableManager = kernelInfo.pageTableManager;
    
    PIT::Sleepd(5);
    GlobalRenderer->Clear();
    GlobalRenderer->ClearCursorPosition();

    Shell *shell = new Shell();
    shell->print_f("FloppaOS />");

    //asm("int $0x0e");
    while (true) {
        if (GlobalRenderer->CursorPosition.X == 89) {

        }
        asm("hlt");
    } // stops crashing on real hardware
}