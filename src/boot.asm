global start
extern main

MAGIC_NUMBER  equ 0x1BADb002
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
start:
  cli                 ; Disable interrupts
  mov esp, stack_top  ; Initialize the stack
  cmp eax, 0x2BADB002 ; Check if we are booted from a multiboot capable bootloader
  jne error           ; If not, print "ERR" to the screen and stop execution

  ;; Setup GDT
  ;; Setup IDT
;  sti                 ; Enable interrups
  mov [0xb8000], dword 0x2f4b2f4f ; Print "OK" to the screen
  ;; call into C land
  push ebx
  push eax
  call main
	jmp done

error:
  mov dword [0xb8000], 0x4f524f45
  mov dword [0xb8004], 0x00004f52

done:
	cli ; Disable interrupts
	hlt ; Halt execution
	jmp done

