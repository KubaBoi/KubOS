
static unsigned short videoIterator = 0;

void print(char* str) 
{
    static unsigned short* VideoMemory = (unsigned short*)0xb8000;

    for (int i = 0; str[i] != 0; i++) {
        VideoMemory[videoIterator] = (VideoMemory[videoIterator] & 0xFF00) | str[i];
        videoIterator++;
    }
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}


extern "C" void kernelMain(const void* multiboot_structure, unsigned int /*multiboot_magic*/) 
{
    print("Hello :)");

    char a[2] = {1, 0};
    while(a[0] > 0) {
        //print(a);
        a[0]++;
        a[0] = 2;
    }
}

extern "C" void inter() 
{
    print("Interrupt");
}