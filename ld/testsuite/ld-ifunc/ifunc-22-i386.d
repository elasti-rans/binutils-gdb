#ld: -m elf_i386
#as: --32 -mrelax-relocations=yes
#objdump: -dw
#target: x86_64-*-* i?86-*-*

.*: +file format .*

#...
0+8048090 <__start>:
[ 	]*[a-f0-9]+:	ff 93 0c 00 00 00    	call   \*0xc\(%ebx\)
[ 	]*[a-f0-9]+:	ff a3 0c 00 00 00    	jmp    \*0xc\(%ebx\)
[ 	]*[a-f0-9]+:	03 83 0c 00 00 00    	add    0xc\(%ebx\),%eax
[ 	]*[a-f0-9]+:	8b 83 0c 00 00 00    	mov    0xc\(%ebx\),%eax
[ 	]*[a-f0-9]+:	85 83 0c 00 00 00    	test   %eax,0xc\(%ebx\)
[ 	]*[a-f0-9]+:	c7 c0 b5 80 04 08    	mov    \$0x80480b5,%eax

0+80480b4 <foo>:
[ 	]*[a-f0-9]+:	c3                   	ret    

0+80480b5 <bar>:
[ 	]*[a-f0-9]+:	c3                   	ret    
#pass
