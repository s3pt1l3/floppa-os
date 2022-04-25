#pragma once
#include "math.h"
#include "Framebuffer.h"
#include "simpleFonts.h"
#include <stdint.h>

class BasicRenderer {
	public:
		BasicRenderer(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_font);
		Point CursorPosition;
		Framebuffer* TargetFramebuffer;
		PSF1_FONT* PSF1_Font;
		uint32_t MouseCursorBuffer[16 * 16];
		uint32_t MouseCursorBufferAfter[16 * 16];
		unsigned int Color;
		unsigned int ClearColor;
		void Print(const char* str);
		void PutChar(char chr, unsigned int xOff, unsigned int yOff);
		void PutChar(char chr);
		void ClearChar();
		void Clear();
		void Next();
		void DrawOverlayMouseCursor(uint8_t* mouseCursor, Point position, uint32_t color);
		void PutPix(uint32_t x, uint32_t y, uint32_t color);
		uint32_t GetPix(uint32_t x, uint32_t y);
		void ClearMouseCursor(uint8_t* mouseCursor, Point position);
		void ClearCursorPosition();
		bool MouseDrawn;
};

extern BasicRenderer* GlobalRenderer;