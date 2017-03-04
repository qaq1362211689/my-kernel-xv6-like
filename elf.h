/*
 * elf.h
 *
 *  Created on: Mar 3, 2017
 *      Author: qaq13
 */

//!!
//!!
//!!
//0x464c457f is unlike xv6 code.if have any questions .check there!
//!!
//!!
//!!
//format of an elf executable file
#define ELF_MAGIC 0x464c457f //ELF header more detailed in wikipedia
//0x7f followed by ELF(45,4c,46)

struct elfhd{
	uint magic;     	//4 bite store 7f,"ELF" represent this is ELF format
	uchar elf[12];		// 12 bite in total
						//0:|  1 -> 32-bit  2-> 64-bit
						//1:data encoding mode |  0 -> invalid  1 -> little endian  2 -> big endian
						//2:just version ,fix 0x1
						//3:operating system structure
						//4:operating system version
						//5~15 fixed 0
	 ushort type;      // 2 字节，表明该文件类型，意义如下：
	                    //     0x0 : 未知目标文件格式
	                    //     0x1 : 可重定位文件
	                    //     0x2 : 可执行文件
	                    //     0x3 : 共享目标文件
	                    //     0x4 : 转储文件
	                    //     0xff00 : 特定处理器文件
	                    //     0xffff : 特定处理器文件

	  ushort machine;   // 2 字节，表明运行该程序需要的计算机体系架构，
	                    // 这里我们只需要知道 0x0 为未指定；0x3 为 x86 架构

	  uint version;     // 4 字节，表示该文件的版本号

	  uint entry;       // 4 字节，该文件的入口地址，没有入口（非可执行文件）则为 0

	  uint phoff;       // 4 字节，表示该文件的“程序头部表”相对于文件的位置，单位是字节

	  uint shoff;       // 4 字节，表示该文件的“节区头部表”相对于文件的位置，单位是字节

	  uint flags;       // 4 字节，特定处理器标志

	  ushort ehsize;    // 2 字节，ELF文件头部的大小，单位是字节

	  ushort phentsize; // 2 字节，表示程序头部表中一个入口的大小，单位是字节

	  ushort phnum;     // 2 字节，表示程序头部表的入口个数，
	                    // phnum * phentsize = 程序头部表大小（单位是字节）

	  ushort shentsize; // 2 字节，节区头部表入口大小，单位是字节

	  ushort shnum;     // 2 字节，节区头部表入口个数，
	                    // shnum * shentsize = 节区头部表大小（单位是字节）

	  ushort shstrndx;  // 2 字节，表示字符表相关入口的节区头部表索引
};

//Program section header
//程序头表:记录了可执行文件各个段的位置以及加载方式

struct prohdr {	//The program header table tells the system how to create a process image.
	uint type;	//4-bite 	段类型
				//			1 PT_LOAD :可载入的段
				//			2 PT_DYNAMIC :动态链接信息
				//			3 PT_INTERP :指定要作为解释程序调用的以空字符结尾的路径名的位置和大小
				//			4 PT_NOTE :指定辅助信息的位置和大小
				//			5 PT_SHLIB :保留类型，但具有未指定的语义
				//			6 PT_PHDR :指定程序头表在文件及程序内存映像中的位置和大小
				//			7 PT_TLS : 指定线程局部储存模板
	uint off;//4-bite,段的第一个字节在文件中的偏移
	uint vaddr; //4-bite,段的第一个字节在内存中的虚拟地址
	uint paddr;	//4-bite,段的第一个字节在内存中的物理地址(适用于物理内存定位型的系统)
	uint filesz;//4-bite,段在文件中的长度
	uint memsz;	//4-bite,段在内存中的长度
	uint flags;	//4-bite,段标志
				//		1:可执行
				//		2：可写入
				//		4：可读取
	uint align;	//4-bite ,段在文件及内存中如何对齐
};
