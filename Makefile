CC = gcc
AS = nasm

SRCDIR = src
ISODIR = cdimage
UTILDIR = util

LDFLAGS = -T link.ld -melf_i386

CFLAGS = -g -c -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector
CFLAGS += -nostartfiles -nodefaultlibs -Wall

INC = -Iinclude/

ASFLAGS = -g -f elf32


OUTELF = kernel.elf
OUTSYM = kernel.sym
OUTISO = os.iso


OBJECTS = $(patsubst %.c, %.o, $(wildcard src/*.c))
OBJECTS += $(patsubst %.c, %.o, $(wildcard src/*/*.c))
ASMOBJECTS = $(patsubst %s, %o, $(wildcard src/*.s))


all: kernel iso
	@echo "Build complete"

clean:
	@echo "Cleaning objects..."
	@rm -f $(SRCDIR)/*.o
	@rm -f $(SRCDIR)/*/*.o
	@rm -rf $(ISODIR)
	@rm -f $(OUTELF)
	@rm -f $(OUTSYM)
	@rm -f $(OUTISO)
	@echo "Objects cleaned"

kernel: $(OUTELF)

$(OUTELF): $(ASMOBJECTS) $(OBJECTS)
	@echo "Linking Kernel..."
	@ld $(LDFLAGS) $(ASMOBJECTS) $(OBJECTS) -o $(OUTELF)
	@echo "Generating symbol file..."
	@objcopy --only-keep-debug $(OUTELF) $(OUTSYM)
	@objcopy --strip-debug $(OUTELF)

$(SRCDIR)/%.o: $(SRCDIR)/%.s
	@echo "AS" "$<"
	@$(AS) $(ASFLAGS) -o $@ $^

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	@echo "CC" "$<"
	@$(CC) $(CFLAGS) $(INC) -o $@ $^

iso: $(OUTISO)

$(OUTISO): $(OUTELF)
	@echo "Making CD image..."
	@mkdir -p $(ISODIR)/
	@cp -r $(UTILDIR)/boot/ $(ISODIR)/
	@cp $(OUTELF) $(ISODIR)/boot/
	@genisoimage \
		-R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 \
		-A os -input-charset utf8 -quiet -boot-info-table -o $(OUTISO) $(ISODIR)

.PHONY: all kernel iso
