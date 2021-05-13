#pragma once
#include "../efiMemory.h"
#include <stdint.h>
#include "../Bitmap.h"
#include "../memory.h"

class PageFrameAllocator {
private:
    void InitBitmap(size_t bitmapSize, void* bufferAddress);
    void ReservePage(void* address);
    void UnreservePage(void* address);
    void ReservePages(void* address, uint64_t paegCount);
    void UnreservePages(void* address, uint64_t paegCount);

public:
    void ReadEFIMemoryMap(EFI_MEMORY_DESCRIPTOR* mMap,
     size_t mMapSize,
     size_t mMapDescriptorSize);
    void FreePage(void* address);
    void LockPage(void* address);
    void FreePages(void* address, uint64_t paegCount);
    void LockPages(void* address, uint64_t paegCount);
    void* RequestPage();
    uint64_t GetFreeRAM();
    uint64_t GetUsedRAM();
    uint64_t GetReservedRAM();

    Bitmap PageBitmap;
};

extern PageFrameAllocator GlobalAllocator;