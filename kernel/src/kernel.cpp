#include "kernelUtil.h"

extern "C" void _start(BootInfo* bootInfo) {
    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;

    GlobalRenderer->Print("FloppaOS");

    while (true) {
        ProcessMousePacket();
    }

    //asm("int $0x0e");
    while (true); // stops crashing on real hardware
}