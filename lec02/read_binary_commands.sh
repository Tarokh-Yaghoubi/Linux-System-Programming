
#!/bin/bash

find ./hello.o

if [ $? -eq 0 ]; then
	echo "============Running Examples============="
	sleep 3
	readelf -S hello.o
	objdump -h hello.o
	objdump -D hello.o
	objdump -d hello.o # By default it uses AT&T
	objdump -d -M intel hello.o # this is the intel format of the asm	
else
	echo "OBJECT-FILE DOES NOT EXIST"
fi

