LDFLAGS = -T link.ld -melf_i386
CFLAGS = -g -c -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		 -nostartfiles -nodefaultlibs -Wall
ASFLAGS = -g -f elf32

CC = gcc
AS = nasm

SRCDIR := src
OBJDIR := build
ISODIR := iso

OUTFILE := kernel.elf
OUTSYM := kernel.sym
OUTISO := os.iso

OBJECTS = $(OBJDIR)/boot.o $(OBJDIR)/main.o

all: clean $(OBJDIR) $(ISODIR) kernel iso

clean:
	- rm -f $(OBJDIR)/*.o
	- rm -rf $(OBJDIR)
	- rm -rf $(ISODIR)
	- rm -f $(OUTFILE)
	- rm -f $(OUTSYM)
	- rm -f $(OUTISO)

$(OBJDIR):
	mkdir -p $@

$(ISODIR):
	mkdir -p $@

kernel: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o $(OUTFILE)
	objcopy --only-keep-debug $(OUTFILE) $(OUTSYM)
	objcopy --strip-debug $(OUTFILE)

$(OBJDIR)/%.o: $(SRCDIR)/%.s
	$(AS) $(ASFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ $^

iso: kernel
	mkdir -p $(ISODIR)/boot/grub
	cp stage2_eltorito $(ISODIR)/boot/grub/
	cp menu.lst $(ISODIR)/boot/grub/
	cp $(OUTFILE) $(ISODIR)/boot/
	genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 \
		-A os -input-charset utf8 -quiet -boot-info-table -o $(OUTISO) iso
