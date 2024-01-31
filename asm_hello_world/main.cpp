
extern "C" void main()
{
    int res;
    __asm__ (
        "loop:"
        "lodsb"
        "or %al, %al"
        "jz halt"
        "int $0x10"
        "jmp loop"(res)
    );
}