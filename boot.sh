OS_ISO=$1
if [ "$2" == "-debug" ]; then
    echo "Run GDB to debug system:"
    echo "  target remote localhost:1234"
    qemu-system-i386 -s -S -boot d -cdrom $OS_ISO -m 512
else
    qemu-system-i386 -boot d -cdrom $OS_ISO -m 512
fi
