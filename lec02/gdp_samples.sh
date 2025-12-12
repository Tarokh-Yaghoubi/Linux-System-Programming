
#!/bin/bash

find ./dynamicexe 

if [ $? -eq 0 ]; then
	gdb -q ./dynamicexe
fi
