

#!/bin/bash 

FILENAME="linux.txt"

echo "Hey There! Starting Linux System Programming" >> $FILENAME

ls -li $FILENAME

# making a hardlink - two filenames pointing to the same INODE

ln $FILENAME hardlink.txt

sleep 2

# NOW, these two have the same INODE, cause hardlink.txt is pointing at
# the same INODE table

echo "\\\\\\\\\\\\\\DATA-AFTER-HARD-LINK\\\\\\\\\\\\\\\\"

ls -li $FILENAME hardlink.txt


