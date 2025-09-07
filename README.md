
Linux System Programming - 
Talking Directly to the Kernel


-- A man in the flying machine --



# System Calls

System programming starts and ends with system calls. System calls (often shortened
to syscalls) are function invocations made from user space - your text editor, favorite
game, and so on - into the kernel (the core internals of the system) in order to request
some service or resource from the operating system. System calls range from the familiar, such as read() and write(), to the exotic, such as get_thread_area() and
set_tid_address().
Linux implements far fewer system calls than most other operating system kernels. For
example, a count of the x86-64 architecture’s system calls comes in at around 300, com -
pared with the suspected thousands of system calls on Microsoft Windows. In the Linux
kernel, each machine architecture (such as Alpha, x86-64, or PowerPC) can augment
the standard system calls with its own. Consequently, the system calls available on one
architecture may differ from those available on another. Nonetheless, a very large subset
of system calls - more than 90 percent - is implemented by all architectures.

# Invoking System Calls

It is not possible to directly link user-space applications with kernel space. For reasons
of security and reliability, user-space applications must not be allowed to directly execute
kernel code or manipulate kernel data. Instead, the kernel must provide a mechanism
by which a user-space application can __signal__ the kernel that it wishes to invoke a system
call. The application can then trap into the kernel through this well-defined mechanism
and execute only code that the kernel allows it to execute. The exact mechanism varies
from architecture to architecture. On i386, for example, a user-space application __executes__ a software interrupt instruction, int, with a value of 0x80. This instruction causes
a switch into kernel space, the protected realm of the kernel, where the kernel executes
a software interrupt handler.

## More Explanation on Invoking System Calls

The application tells the kernel which system call to execute and with what parameters
via machine registers. System calls are denoted by number, starting at 0. On the i386
architecture, to request system call 5 (which happens to be open()), the user-space
application stuffs 5 in register eax before issuing the int instruction.
Parameter passing is handled in a similar manner. On i386, for example, a register is
used for each possible parameter - registers __ebx__, __ecx__, __edx__, __esi__, and __edi__ contain, in order,
the first five parameters. In the rare event of a system call with more than five parameters,
a single register is used to point to a buffer in user space where all of the parameters are
kept. Of course, most system calls have only a couple of parameters.
Other architectures handle system call invocation differently, although the spirit is the
same. As a system programmer, you usually do not need any knowledge of how the
kernel handles system call invocation. That knowledge is encoded into the standard
calling conventions for the architecture, and handled automatically by the compiler and
the C library.



*Created: $(date)*
*Whoami: Tarokh Yaghoubi*
