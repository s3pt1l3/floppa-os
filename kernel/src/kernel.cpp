#include "kernelUtil.h"

extern "C" void _start(BootInfo* bootInfo) {
    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;

    GlobalRenderer->Print("FloppaOS >");

    GlobalRenderer->Next();
    GlobalRenderer->Print(to_hstring((uint64_t)bootInfo->rsdp));

    //asm("int $0x0e");
    while (true); // stops crashing on real hardware
}