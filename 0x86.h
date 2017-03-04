/*
 * 0x86.h
 *
 *  Created on: Mar 4, 2017
 *      Author: qaq13
 */

//内嵌汇编语法
/*_asm_(汇编语句模板：输出部分：输入部分：破坏描述部分)
 *
 */
#include "types.h"

static inline uchar inb (ushort port){
	uchar data;
	asm volatile ("in %0,%1":"=a"(data):"d"(port));
	//"=a(data)"表示将eax寄存器与变量data关联 // edx与变量port关联
	return data;
}

static inline uchar inl(ushort port){
	uchar data;
	asm volatile ("in %0,%1":"=a"(data):"d"(port));
	return data;
}
