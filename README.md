For reference, when I say enter "make", I mean to enter it in your temrnial without the
quotes, so make.

// What It Does //
The kernel module simulates a magic 8 ball. So the user will think of a question, and
the driver will give an answer. It does this by randomly selecting one of the phrases
stored in an array and displaying it to userspace. 

// How To Run //
To compile, enter "make". To load the module, type "sudo insmod magic8ball.ko". You 
will probably be asked for your root password. To get a response from the driver, you
would need to enter "cat /dev/magic8ball". You can try and write to the driver by 
doing "echo "Hi" > /dev/magic8ball", but you should get a permission error. To unload 
the kernel module, type "sudo rmmod magic8ball.ko". There are messages that get printed
to the kernel log, and they can be accessed by typing "sudo dmesg | tail". Again, you 
may be asked for your root password. You can type "make clean" to cleanup and remove 
the executables in the directory. Below is some sample output.

--------------
SAMPLE OUTPUT:
--------------
vboxuser@DebianCMSC421:/usr/src/project3/part1$ make
make -C /lib/modules/5.15.67+/build M=/usr/src/project3/part1 modules
make[1]: Entering directory '/usr/src/linux-headers-5.15.67+'
  CC [M]  /usr/src/project3/part1/magic8ball.o
  MODPOST /usr/src/project3/part1/Module.symvers
  CC [M]  /usr/src/project3/part1/magic8ball.mod.o
  LD [M]  /usr/src/project3/part1/magic8ball.ko
make[1]: Leaving directory '/usr/src/linux-headers-5.15.67+'
vboxuser@DebianCMSC421:/usr/src/project3/part1$ sudo insmod magic8ball.ko
[sudo] password for vboxuser: 
vboxuser@DebianCMSC421:/usr/src/project3/part1$ cat /dev/magic8ball
You may rely on it.
vboxuser@DebianCMSC421:/usr/src/project3/part1$ cat /dev/magic8ball
It is decidedly so.
vboxuser@DebianCMSC421:/usr/src/project3/part1$ cat /dev/magic8ball
Outlook good.
vboxuser@DebianCMSC421:/usr/src/project3/part1$ cat /dev/magic8ball
Don't count on it.
vboxuser@DebianCMSC421:/usr/src/project3/part1$ echo "Hi" > /dev/magic8ball
bash: /dev/magic8ball: Permission denied
vboxuser@DebianCMSC421:/usr/src/project3/part1$ sudo rmmod magic8ball.ko
vboxuser@DebianCMSC421:/usr/src/project3/part1$ sudo dmesg | tail
[17395.344844] magic8ball successfully loaded
[17400.429167] magic8ball opened
[17400.429189] magic8ball released
[17401.641171] magic8ball opened
[17401.641192] magic8ball released
[17402.543970] magic8ball opened
[17402.543991] magic8ball released
[17403.763456] magic8ball opened
[17403.763478] magic8ball released
[17414.051250] unloading magic8ball
vboxuser@DebianCMSC421:/usr/src/project3/part1$ ls
magic8ball.c   magic8ball.mod    magic8ball.mod.o  Makefile       Module.symvers
magic8ball.ko  magic8ball.mod.c  magic8ball.o      modules.order  README.md
vboxuser@DebianCMSC421:/usr/src/project3/part1$ make clean
make -C /lib/modules/5.15.67+/build M=/usr/src/project3/part1 clean
make[1]: Entering directory '/usr/src/linux-headers-5.15.67+'
  CLEAN   /usr/src/project3/part1/Module.symvers
make[1]: Leaving directory '/usr/src/linux-headers-5.15.67+'
vboxuser@DebianCMSC421:/usr/src/project3/part1$ ls
magic8ball.c  Makefile  README.md
