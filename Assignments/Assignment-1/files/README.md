# Exercise 1: Bare

In this exercise, we will set up the tool chain and write a bare-metal code to print "hello, world!" message on UART.

## Part 1: Development environment

We will use command line programming environment in our exercises.
Before you start the exercise, you should have a Unix-like command-line environment, which could be one of the following:
- Single or dual boot Linux
- Linux installed on a Windows VM such as VirtualBox
- WSL (Windows Subsystem for Linux, also called Ubuntu under Windows)
- MacOS
You may choose distribution of your liking.
I have used WSL2 / Ubuntu with apt package manager.

### Step 1
Install the following tools (using sudo apt install in case of Ubuntu)
build-essential (gcc, make, git and others. Not be directly required for embedded programming but would come handy every once in a while.)
An editor of your liking, such as VS Code.

### Step 2
Install GCC ARM toolchain for AArch32 bare-metal target (arm-none-eabi)
Download from https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads
For x86_64 Linux (WSL, Vbox or Linux OS): arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi.tar.xz
For macOS (x86_64): arm-gnu-toolchain-14.2.rel1-darwin-x86_64-arm-none-eabi.pkg
For macOS (Apple silicon): arm-gnu-toolchain-14.2.rel1-darwin-arm64-arm-none-eabi.pkg

### Step 3
Untar in an appropriate directory (/usr/local or /opt – I have used /opt for example.)
Use bash terminal and type the following commands:
```bash
$ cd /opt
$ sudo tar xvf <path-to-downloaded-file.tar.xz>
```
You may create a short-cut to the installed toolchain directory:
```bash
$ cd opt
$ sudo ln -s arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi arm-gcc
```
Note: Ubuntu also provides installation of GNU ARM tool-chain using apt:
```bash
$ sudo apt install gcc-arm-none-eabi
```
apt installs the tool-chain in /usr along with the rest of the Linux programs.
I prefer to keep tool-chain separate, hence downloaded from the ARM website.
Downloading the toolchain with apt would work equally well.

### Step 4
Download terminal emulator PuTTY on Windows, minicom on Linux.

## Part 2: Build and run the code

This example contains the following files:
startup.c	Vector table, default ISRs, startup code
system.c	System initialization: initializes FPU and clock.
main.c		Application main
uart.h, uart.c	UART header file and code
microbit.h	Pin details of microbit board
bare.ld		Linker command file containing memory configuration of the processor
build.sh, clean.sh	Scripts build the code and cleanup binary files
myled.h		Stand-alone file to glow LEDs; useful for debugging
Build the program by running the script:
```bash
$ ./build.sh
```
The script generates tiny.hex, which should be dragged and dropped onto MICROBIT drive.
Run the terminal emulator.
In Windows, use Device Manager to find the COM port.
In Linux, `dmesg -y` should show the port such as /dev/ttyUSB.
Baud rate is set in uart.c to be 115200 bps.
You should see "hello, world!" printed on TTY and LED [0][0] turned on.

## Part 3: Modify the program

Modify the program to turn on one LED at a time from [0][0] position to [4][4] row-wise or column-wise direction.
Provide an appropriate delay to make it look like a running dot.
Use an editor of your choice to write / modify the program.

## Part 4: Answer the following questions

1. What is an object file? Total how many object files are generated in the code given here?

2. What is an executable program? How is it generated?

3. Understanding header files: Add the following line in build.sh:
$CC -E $CFLAGS main.c > main.i
- What does -E do?
- How many lines are there main.i? Where did these lines come from?
- Functions in myled.h are defined as static inline. What does static inline mean?

4. Look at bare.ld file. What are the sizes of flash and RAM on the chip?

5. Where are .text, .rodata, .data and .bss sections located, in flash or RAM? Why?

6. What are the start and end addresses of these sections? See in tiny.map.

7. What does crt_init function do in startup.c? How is it related to the linker command file?

8. What is a vector table? In which file would you find it?

9. Which entries in the vector table are used by this program?

10. What is the stack used for? What is its size? In which file is it reserved?
