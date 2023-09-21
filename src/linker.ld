ENTRY(start)

SECTIONS {
  . = 1M;   /* Load the kernel code at 1M */

  .multiboot :
  {
    . = ALIGN(4096);
    *(.multiboot)
  }

  .text :
  {
    . = ALIGN(4096);
    *(.text)
  }
}
