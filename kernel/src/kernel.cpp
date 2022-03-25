#include <stddef.h>
#include "BasicRenderer.h"
#include "cstr.h"
#include "efiMemory.h"

struct BootInfo {
    Framebuffer* framebuffer;
    PSF1_FONT* psf1_Font;
    void* mMap;
    uint64_t mMapSize;
    uint64_t mMapDecriptorSize;
};

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

    renderer.CursorPosition = { 0, renderer.CursorPosition.Y + 16 };

    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDecriptorSize;

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