#include <stddef.h>
#include "BasicRenderer.h"
#include "cstr.h"

extern "C" void _start(Framebuffer* framebuffer, PSF1_FONT* psf1_font) {
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
    BasicRenderer renderer = BasicRenderer(framebuffer, psf1_font);

    renderer.Print(to_string((uint64_t)1234976));
    renderer.CursorPosition = { 0, 16 };
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

    return;
}