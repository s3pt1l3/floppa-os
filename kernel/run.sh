#!/bin/bash
OSNAME=FloppaOS
BUILDDIR=bin
OVMFDIR=../OVMFbin

cd ../gnu-efi/
make bootloader
cd ../kernel/
make kernel
make buildimg
qemu-system-x86_64 -drive format=raw,file=$BUILDDIR/$OSNAME.img -m 256M -cpu qemu64 -drive if=pflash,format=raw,unit=0,file=$OVMFDIR/OVMF_CODE-pure-efi.fd,readonly=on -drive if=pflash,format=raw,unit=1,file=$OVMFDIR/OVMF_VARS-pure-efi.fd -net none
read -p
