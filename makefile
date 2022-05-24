
OSNAME = KubOS

GCCPARAMS = -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings
ASPARAMS = --32
LDPARAMS = -melf_i386

objects = loader.o kernel.o


%.o: %.cpp
	gcc $(GCCPARAMS) -c -o $@ $<

%.o: %.s
	as $(ASPARAMS) -o $@ $<

$(OSNAME).bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

$(OSNAME).iso: $(OSNAME).bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $(OSNAME).bin iso/boot/$(OSNAME).bin
	echo 'set timeout=0'                      > iso/boot/grub/grub.cfg
	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "KubOS" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/$(OSNAME).bin'    >> iso/boot/grub/grub.cfg
	echo '  boot'                            >> iso/boot/grub/grub.cfg
	echo '}'                                 >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$(OSNAME).iso iso

.PHONY: clean
clean:
	rm -rf obj $(OSNAME).bin $(OSNAME).iso

.PHONY: cleanAll
cleanAll:
	rm -rf obj $(OSNAME).bin $(OSNAME).iso
	rm -r iso
