#include "kernelUtil.h"
#include "memory/heap.h"
#include "scheduling/pit/pit.h"

extern "C" void _start(BootInfo* bootInfo) {
    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    //PageTableManager* pageTableManager = kernelInfo.pageTableManager;
    
    //asm("int $0x0e");
    while (true) {
        asm("hlt");
    } // stops crashing on real hardware
}