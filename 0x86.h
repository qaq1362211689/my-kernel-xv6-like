/*
 * 0x86.h
 *
 *  Created on: Mar 4, 2017
 *      Author: qaq13
 */

//��Ƕ����﷨
/*_asm_(������ģ�壺������֣����벿�֣��ƻ���������)
 *
 */
#include "types.h"

static inline uchar inb (ushort port){
	uchar data;
	asm volatile ("in %0,%1":"=a"(data):"d"(port));
	//"=a(data)"��ʾ��eax�Ĵ��������data���� // edx�����port����
	return data;
}

static inline uchar inl(ushort port){
	uchar data;
	asm volatile ("in %0,%1":"=a"(data):"d"(port));
	return data;
}
