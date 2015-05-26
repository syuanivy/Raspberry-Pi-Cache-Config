
MEMORY
{
    ram : ORIGIN = 0x8000, LENGTH = 104857600
}

SECTIONS
{
    .text : { *(.text*) } > ram
    .bss : { *(.bss*) } > ram
}

