#include <stddef.h>
#include <stdint.h>
#include "BasicRenderer.h"
#include "cstr.h"
#include "efiMemory.h"
#include "memory.h"
#include "Bitmap.h"
#include "paging/PageFrameAllocator.h"
#include "paging/PageMapIndexer.h"
#include "paging/paging.h"
#include "paging/PageTableManager.h"

struct BootInfo {
    Framebuffer* framebuffer;
    PSF1_FONT* psf1_Font;
    EFI_MEMORY_DESCRIPTOR* mMap;
    uint64_t mMapSize;
    uint64_t mMapDecriptorSize;
};

extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

extern "C" void _start(BootInfo* bootInfo) {
    /*BasicRenderer renderer;
    renderer.CursorPosition = { 15, 50 };
    //Print(framebuffer, psf1_font, 0xe039e6, "FloppaOS");
    char* str = (char*)"FloppaOS";
    for (size_t i = 0; i < 8; ++i) {
        char k = str[i];
        if (i % 2 == 0) {
            
            renderer.Print(framebuffer, psf1_font, 0xe039e6, &k);
        }
        else
        {
            renderer.Print(framebuffer, psf1_font, 0xf2f2f2, &k);
        }
    }*/
    BasicRenderer renderer = BasicRenderer(bootInfo->framebuffer, bootInfo->psf1_Font);

    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDecriptorSize;
    
    GlobalAllocator = PageFrameAllocator();
    
    GlobalAllocator.ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDecriptorSize);

    uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages = (uint64_t)kernelSize / 4096 + 1;

    GlobalAllocator.LockPages(&_KernelStart, kernelPages);
    
    PageTable* PML4 = (PageTable*)GlobalAllocator.RequestPage();
    memset(PML4, 0, 0x1000);

    PageTableManager pageTableManager = PageTableManager(PML4);

    for (uint64_t t = 0; t < GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mMapDecriptorSize); t+=0x1000) {
        pageTableManager.MapMemory((void*)t, (void*)t);
    }

    uint64_t fbBase = (uint64_t)bootInfo->framebuffer->BaseAddress;
    uint64_t fbSize = (uint64_t)bootInfo->framebuffer->BufferSize + 0x1000;
    for (uint64_t t = fbBase; t < fbBase + fbSize; t += 4096) {
        pageTableManager.MapMemory((void*)t, (void*)t);
    }

    asm("mov %0, %%cr3" : : "r" (PML4));


    /*
        renderer.CursorPosition = { 0, renderer.CursorPosition.Y + 16 };
    renderer.Print("Free RAM: ");
    renderer.Print(to_string(allocator.GetFreeRAM() / 1024));
    renderer.Print(" KB ");
    renderer.CursorPosition = { 0, renderer.CursorPosition.Y + 16 };

    renderer.Print("Used RAM: ");
    renderer.Print(to_string(allocator.GetUsedRAM() / 1024));
    renderer.Print(" KB ");
    renderer.CursorPosition = { 0, renderer.CursorPosition.Y + 16 };

    renderer.Print("Reserved RAM: ");
    renderer.Print(to_string(allocator.GetReservedRAM() / 1024));
    renderer.Print(" KB ");
    renderer.CursorPosition = { 0, renderer.CursorPosition.Y + 16 };

    for (int t = 0; t < 20; t++) {
        void* address = allocator.RequestPage();
        renderer.Print(to_hstring((uint64_t)address));
        renderer.CursorPosition = { 0, renderer.CursorPosition.Y + 16 };
    }

    */

    /*
    for (int i = 0; i < mMapEntries; i++) {
        EFI_MEMORY_DESCRIPTOR* descriptor = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)bootInfo->mMap + (i * bootInfo->mMapDecriptorSize));
        renderer.CursorPosition = { 0, renderer.CursorPosition.Y + 16 };
        renderer.Print(EFI_MEMORY_TYPE_STRINGS[descriptor->type]);
        renderer.Color = 0xDC758F;
        renderer.Print(" ");
        renderer.Print(to_string(descriptor->numPages * 4096 / 1024));
        renderer.Print(" KB");
        renderer.Color = 0xffffffff;

    }
    */
    
    /*
    renderer.Print(to_string((int64_t)-1234976));
    renderer.CursorPosition = { 0, 32 };
    renderer.Print(to_string((double)-13.14));
    renderer.CursorPosition = { 0, 48 };
    renderer.Print(to_hstring((uint64_t)0xF0));
    renderer.CursorPosition = { 0, renderer.CursorPosition.Y + 16 };
    renderer.Print(to_hstring((uint32_t)0xF0));
    renderer.CursorPosition = { 0, renderer.CursorPosition.Y + 16 };
    renderer.Print(to_hstring((uint16_t)0xF0));
    renderer.CursorPosition = { 0, renderer.CursorPosition.Y + 16 };
    renderer.Print(to_hstring((uint8_t)0xF0));

    */
    return;
}