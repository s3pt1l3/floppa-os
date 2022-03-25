#include "kernelUtil.h"

extern "C" void _start(BootInfo* bootInfo) {

    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;
    BasicRenderer renderer = BasicRenderer(bootInfo->framebuffer, bootInfo->psf1_Font);

    renderer.Print("FloppaOS");

    while (true); // stops crashing on realhardware
}