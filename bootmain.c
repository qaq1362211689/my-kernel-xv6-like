/*
 * bootmain.c
 *
 *  Created on: Mar 3, 2017
 *      Author: qaq13
 */
#include "tpyes.h"
#include "elf.h"
#include "x86.h"

#define SECTSIZE 512 //sector size 512 Ӳ��������СΪ512�ֽ�

void bootmain(void){
	struct elfhdr *elf;
	struct proghdr *ph,*eph;
	void (*entry)(void);
	uchar *pa;

	elf = (struct elfhdr *)0x10000;
	//��ȡһ��ҳ���ڴ棬ҳ�Ĵ�СΪ4096bit
	readseg((uchar *)elf,4096,0);

	//�ж��Ƿ���elf��ʽ��
	if(elf->magic!=ELF_MAGIC)
		return ;//Ӧ���ǲ�Ӧ�÷��صģ����ﷵ����ô������bootasm.S����
	//�����Ѿ���4096�ֽڵ����ݶ����������ַΪ0x10000��
	//������Ҫ��ʼ����ELF�ļ��ĳ����
	//����phָ��Ľṹ���е�flag��־
	ph = (struct proghdr *)((uchar *)elf + elf -> phoff);//ͨ��ƫ�Ƶ�ַ���������ͷ��Ļ�����ַ
	eph = ph + elf -> phnum;//���������ͷ�����ڸ�����������ѭ���ֱ������
	for(;ph < eph;ph++){
		pa = (uchar *)ph -> paddr;
		readseg(pa,ph->filesz,ph->off);
		if(ph->memsz > ph->filesz)//�ڴ��С�����ļ���С��ʣ�µ���0����
			stosb(pa + ph -> filesz ,0,ph->memsz - ph->filesz);
	}
	static void waitdisk(void){
		//�ȴ����̾���
		//�Ʋ�0x1f7Ӧ����һ���˿ڣ�CPUͨ������˿������ͨѶ��ͨ��λ�����жϴ����Ƿ�׼������
		while((inb(0x1f7)& 0xC0) != 0x40);
	}
	static void readseg (){

	}
	static void readsect(){
		waitdisk();
	}
}
