OS_ISO=$1
if [ "$2" == "-debug" ]; then
    echo "Run GDB to debug system:"
    echo "  target remote localhost:1234"
    qemu-system-i386 -nographic -s -S -boot d -cdrom $OS_ISO -m 1024
else
    qemu-system-i386 -nographic -boot d -cdrom $OS_ISO -m 2048
fi
