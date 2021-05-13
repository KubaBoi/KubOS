#pragma once
#include "math.h"
#include "FrameBuffer.h"
#include "SimpleFont.h"
#include <stdint.h>

class BasicRenderer{
public:
    BasicRenderer(FrameBuffer* targetFrameBuffer,
     PSF1_FONT* psf1_font);

    Point CursorPosition;
    FrameBuffer* TargetFrameBuffer;
    PSF1_FONT* PSF1_Font;
    uint32_t MouseCursorBuffer[16 * 16];
    uint32_t MouseCursorBufferAfter[16 * 16];
    unsigned int Color;
    unsigned int ClearColor;

    void putChar(char chr, unsigned int xOff, unsigned int yOff);
    void putChar(char chr);
    void PutPix(uint32_t x, uint32_t y, uint32_t color);
    uint32_t GetPix(uint32_t x, uint32_t y);
    void Print(const char* str);
    void ClearChar();
    void Clear();
    void ClearMouseCursor(uint8_t* mouseCursor, Point position);
    void Next();
    void DrawOverlayMouseCursor(uint8_t* mouseCursor, Point position, uint32_t color);
    bool MouseDrawn;
};

extern BasicRenderer* GlobalRenderer;