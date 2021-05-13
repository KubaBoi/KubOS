#include "BasicRenderer.h"

BasicRenderer* GlobalRenderer;

BasicRenderer::BasicRenderer(FrameBuffer* targetFrameBuffer, PSF1_FONT* psf1_font) {
    TargetFrameBuffer = targetFrameBuffer;
    PSF1_Font = psf1_font;
    Color = 0xffffffff;
    CursorPosition = {0,0};
}

void BasicRenderer::putChar(char chr, unsigned int xOff,unsigned int yOff) {
    unsigned int* pixPtr = (unsigned int*)TargetFrameBuffer->BaseAddress;
    char* fontPtr = (char*)PSF1_Font->glyphBuffer + (chr * PSF1_Font->psf1_Header->charsize);
    for (unsigned long y = yOff; y < yOff + 16; y++){
        for (unsigned long x = xOff; x < xOff + 8; x++){
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0){
                *(unsigned int*)(pixPtr + x + (y * TargetFrameBuffer->PixelsPerScanLine)) = Color;
            }
        }
        fontPtr++;
    }
}

void BasicRenderer::putChar(char chr) {
    putChar(chr, CursorPosition.X, CursorPosition.Y);
    CursorPosition.X += 8;
    if (CursorPosition.X + 8 > TargetFrameBuffer->Width) {
        CursorPosition.X = 0;
        CursorPosition.Y += 16;
    }
}

void BasicRenderer::Print(const char* str) {
    char* chr = (char*)str;
    while (*chr != 0) {
        putChar(*chr, CursorPosition.X, CursorPosition.Y);
        CursorPosition.X += 8;
        if (CursorPosition.X + 8 > TargetFrameBuffer->Width) {
            CursorPosition.X = 0;
            CursorPosition.Y += 16;
        }
        chr++;
    } 
}

void BasicRenderer::Next() {
    CursorPosition = {0, CursorPosition.Y + 16};
}

void BasicRenderer::Clear() {
    uint64_t fbBase = (uint64_t)TargetFrameBuffer->BaseAddress;
    uint64_t bytesPerScanline = TargetFrameBuffer->PixelsPerScanLine * 4;
    uint64_t fbHeight = TargetFrameBuffer->Height;
    uint64_t fbSize = TargetFrameBuffer->BufferSize;

    for (int verticalScanline = 0; verticalScanline < fbHeight; verticalScanline++) {
        uint64_t pixPtrBase = fbBase + (bytesPerScanline * verticalScanline);
        for (uint32_t* pixPtr = (uint32_t*)pixPtrBase; pixPtr < (uint32_t*)(pixPtrBase + bytesPerScanline); pixPtr++) {
            *pixPtr = ClearColor;
        }
    }
}

void BasicRenderer::ClearChar() {
    if (CursorPosition.X == 0) {
        CursorPosition.X = TargetFrameBuffer->Width;
        CursorPosition.Y -= 16;
        if (CursorPosition.Y < 0) CursorPosition.Y = 0;
    }

    unsigned int xOff = CursorPosition.X;
    unsigned int yOff = CursorPosition.Y;

    unsigned int* pixPtr = (unsigned int*)TargetFrameBuffer->BaseAddress;
    for (unsigned long y = yOff; y < yOff + 16; y++){
        for (unsigned long x = xOff - 8; x < xOff; x++){
            *(unsigned int*)(pixPtr + x + (y * TargetFrameBuffer->PixelsPerScanLine)) = ClearColor;
        }
    }

    CursorPosition.X -= 8;
    if (CursorPosition.X < 0) {
        CursorPosition.X = TargetFrameBuffer->Width;
        CursorPosition.Y -= 16;
        if (CursorPosition.Y < 0) CursorPosition.Y = 0;
    }
}

void BasicRenderer::PutPix(uint32_t x, uint32_t y, uint32_t color) {
    *(uint32_t*)((uint64_t)TargetFrameBuffer->BaseAddress + (x*4) + (y * TargetFrameBuffer->PixelsPerScanLine * 4)) = color;
}

uint32_t BasicRenderer::GetPix(uint32_t x, uint32_t y) {
    return *(uint32_t*)((uint64_t)TargetFrameBuffer->BaseAddress + (x*4) + (y * TargetFrameBuffer->PixelsPerScanLine * 4));
}
void BasicRenderer::ClearMouseCursor(uint8_t* mouseCursor, Point position) {
    if (!MouseDrawn) return;

    int xMax = 16;
    int yMax = 16;
    int differenceX = TargetFrameBuffer->Width - position.X;
    int differenceY = TargetFrameBuffer->Height - position.Y;

    if (differenceX < 16) xMax = differenceX;
    if (differenceY < 16) yMax = differenceY;

    for (int y = 0; y < yMax; y++) {
        for (int x = 0; x < xMax; x++) {
            int bit = y * 16 + x;
            int byte = bit / 8;
            if ((mouseCursor[byte] & (0b10000000 >> (x % 8)))) {
                if (GetPix(position.X + x, position.Y + y) == MouseCursorBufferAfter[x + y * 16]) {
                    PutPix(position.X + x, position.Y + y, MouseCursorBuffer[x + y * 16]);
                }
            }
        }
    }
}

void BasicRenderer::DrawOverlayMouseCursor(uint8_t* mouseCursor, Point position, uint32_t color) {
    int xMax = 16;
    int yMax = 16;
    int differenceX = TargetFrameBuffer->Width - position.X;
    int differenceY = TargetFrameBuffer->Height - position.Y;

    if (differenceX < 16) xMax = differenceX;
    if (differenceY < 16) yMax = differenceY;

    for (int y = 0; y < yMax; y++) {
        for (int x = 0; x < xMax; x++) {
            int bit = y * 16 + x;
            int byte = bit / 8;
            if ((mouseCursor[byte] & (0b10000000 >> (x % 8)))) {
                MouseCursorBuffer[x + y * 16] = GetPix(position.X + x, position.Y + y);
                PutPix(position.X + x, position.Y + y, color);
                MouseCursorBufferAfter[x + y * 16] = GetPix(position.X + x, position.Y + y);
            }
        }
    }

    MouseDrawn = true;
}