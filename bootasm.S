#include "asm.h"

#define SEG_KCODE 1 //kernel code
#define SEG_KDATA 2	//kernrl data+stack
#define CRO_PE    1	// protected mode enable bit
.code16
.globl start
start:
	cli				#disable interrupts
	xorw %ax,%ax	#make ax to zero
	movw %ax,%ds	#zero data segment
	movw %ax,%es	#zero extra segment
	movw %ax,%ss	#zero stack segment

seta20.1:			#set a20 through port 0x60 and port 0x64
	inb   $0x64,%al #read data from port 0x64.if it's busy,do above again and again
	testb $0xdl,%al #text bite if the result isn't zero,jump to run seta20.1
	jnz	  seta20.1  #jnz is short for jump if not zero
	movb  $0xdl,&al	#0xdl -> port 0x64
	outb  %al,$0x64	#write data to port0x64

seta20.2:
	inb   $0x64,%al	#waiting for not busy
	testb $0x2,%al
	jnz   seta20.2
	movb  $0xdf,%al
	outb  %al,0x60
#A20 enable!
#Switch from real mode to protection mode,using a bootstrap GDT
#and segment translation that makes virtual addresses
#identical to physical addresses, so that the
#effective memory map dose not change during the switch.
	lgdt gdtdesc
	movl %cro,%eax
	movl %eax,%cr0
