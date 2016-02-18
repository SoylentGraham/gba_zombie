echo off
d:
cd \
cd "code zombie"
del zombie.gba
del zombie.elf
echo compiling...
PATH=D:\gbadev\devkitadv\devkitadv\bin;%PATH%;
gcc -O3 -o zombie.elf core/*.c game/*.c media/map/*.c media/gfx/*.c
objcopy -O binary zombie.elf zombie.gba
