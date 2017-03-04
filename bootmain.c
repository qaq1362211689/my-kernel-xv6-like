/*
 * bootmain.c
 *
 *  Created on: Mar 3, 2017
 *      Author: qaq13
 */
#include "tpyes.h"
#include "elf.h"
#include "x86.h"

#define SECTSIZE 512 //sector size 512 硬盘扇区大小为512字节

void bootmain(void){
	struct elfhdr *elf;
	struct proghdr *ph,*eph;
	void (*entry)(void);
	uchar *pa;

	elf = (struct elfhdr *)0x10000;
	//读取一个页到内存，页的大小为4096bit
	readseg((uchar *)elf,4096,0);

	//判断是否是elf格式？
	if(elf->magic!=ELF_MAGIC)
		return ;//应该是不应该返回的，这里返回那么错误将由bootasm.S处理
	//现在已经将4096字节的数据读到了虚拟地址为0x10000处
	//接下来要开始加载ELF文件的程序段
	//忽略ph指向的结构体中的flag标志
	ph = (struct proghdr *)((uchar *)elf + elf -> phoff);//通过偏移地址计算出程序头表的基础地址
	eph = ph + elf -> phnum;//计算出程序头表的入口个数，下面用循环分别尝试入口
	for(;ph < eph;ph++){
		pa = (uchar *)ph -> paddr;
		readseg(pa,ph->filesz,ph->off);
		if(ph->memsz > ph->filesz)//内存大小大于文件大小，剩下的以0补齐
			stosb(pa + ph -> filesz ,0,ph->memsz - ph->filesz);
	}
	static void waitdisk(void){
		//等待磁盘就绪
		//推测0x1f7应该是一个端口，CPU通过这个端口与磁盘通讯，通过位运算判断磁盘是否准备就绪
		while((inb(0x1f7)& 0xC0) != 0x40);
	}
	static void readseg (){

	}
	static void readsect(){
		waitdisk();
	}
}
