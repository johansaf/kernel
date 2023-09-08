global _start

extern main

MAGIC_NUMBER  equ 0x1BADB002
FLAGS         equ 0x0
CHECKSUM      equ -MAGIC_NUMBER

section .multiboot
align 4
dd MAGIC_NUMBER
dd FLAGS
dd CHECKSUM

section .bss
stack_bottom:
  resb 4096
stack_top:

section .text
bits 32
_start:
  mov esp, stack_top

  ; Print "OK" to the screen
  ; to show where we are in
  ; the boot process
  mov eax, 0xb8000
  mov [eax], dword 0x2f4b2f4f

  call main

done:   ; We shouldn't get here but just in case
  cli
  hlt
  jmp done
