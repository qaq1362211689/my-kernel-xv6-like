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
	 ushort type;      // 2 �ֽڣ��������ļ����ͣ��������£�
	                    //     0x0 : δ֪Ŀ���ļ���ʽ
	                    //     0x1 : ���ض�λ�ļ�
	                    //     0x2 : ��ִ���ļ�
	                    //     0x3 : ����Ŀ���ļ�
	                    //     0x4 : ת���ļ�
	                    //     0xff00 : �ض��������ļ�
	                    //     0xffff : �ض��������ļ�

	  ushort machine;   // 2 �ֽڣ��������иó�����Ҫ�ļ������ϵ�ܹ���
	                    // ��������ֻ��Ҫ֪�� 0x0 Ϊδָ����0x3 Ϊ x86 �ܹ�

	  uint version;     // 4 �ֽڣ���ʾ���ļ��İ汾��

	  uint entry;       // 4 �ֽڣ����ļ�����ڵ�ַ��û����ڣ��ǿ�ִ���ļ�����Ϊ 0

	  uint phoff;       // 4 �ֽڣ���ʾ���ļ��ġ�����ͷ����������ļ���λ�ã���λ���ֽ�

	  uint shoff;       // 4 �ֽڣ���ʾ���ļ��ġ�����ͷ����������ļ���λ�ã���λ���ֽ�

	  uint flags;       // 4 �ֽڣ��ض���������־

	  ushort ehsize;    // 2 �ֽڣ�ELF�ļ�ͷ���Ĵ�С����λ���ֽ�

	  ushort phentsize; // 2 �ֽڣ���ʾ����ͷ������һ����ڵĴ�С����λ���ֽ�

	  ushort phnum;     // 2 �ֽڣ���ʾ����ͷ�������ڸ�����
	                    // phnum * phentsize = ����ͷ�����С����λ���ֽڣ�

	  ushort shentsize; // 2 �ֽڣ�����ͷ������ڴ�С����λ���ֽ�

	  ushort shnum;     // 2 �ֽڣ�����ͷ������ڸ�����
	                    // shnum * shentsize = ����ͷ�����С����λ���ֽڣ�

	  ushort shstrndx;  // 2 �ֽڣ���ʾ�ַ��������ڵĽ���ͷ��������
};

//Program section header
//����ͷ��:��¼�˿�ִ���ļ������ε�λ���Լ����ط�ʽ

struct prohdr {	//The program header table tells the system how to create a process image.
	uint type;	//4-bite 	������
				//			1 PT_LOAD :������Ķ�
				//			2 PT_DYNAMIC :��̬������Ϣ
				//			3 PT_INTERP :ָ��Ҫ��Ϊ���ͳ�����õ��Կ��ַ���β��·������λ�úʹ�С
				//			4 PT_NOTE :ָ��������Ϣ��λ�úʹ�С
				//			5 PT_SHLIB :�������ͣ�������δָ��������
				//			6 PT_PHDR :ָ������ͷ�����ļ��������ڴ�ӳ���е�λ�úʹ�С
				//			7 PT_TLS : ָ���ֲ߳̾�����ģ��
	uint off;//4-bite,�εĵ�һ���ֽ����ļ��е�ƫ��
	uint vaddr; //4-bite,�εĵ�һ���ֽ����ڴ��е������ַ
	uint paddr;	//4-bite,�εĵ�һ���ֽ����ڴ��е������ַ(�����������ڴ涨λ�͵�ϵͳ)
	uint filesz;//4-bite,�����ļ��еĳ���
	uint memsz;	//4-bite,�����ڴ��еĳ���
	uint flags;	//4-bite,�α�־
				//		1:��ִ��
				//		2����д��
				//		4���ɶ�ȡ
	uint align;	//4-bite ,�����ļ����ڴ�����ζ���
};
