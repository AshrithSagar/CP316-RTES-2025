# README-RTX

## Part 1: Prepare RTX source

1. Download `CMSIS_5` repository from <https://github.com/ARM-software/CMSIS_5>

   You should select the `master` branch -- default is ‘`develop`’ branch.

2. Create a project directory and unzip from its downloaded directory.

    ```shell
    mkdir mbit_rtx
    cd mbit_rtx
    unzip ~/Downloads/CMSIS_5-master.zip
    ```

3. Create a directory and copy the rtx source files:

    ```shell
    mkdir rtx
    cd rtx

    # RTX source code and internal header files
    cp ../CMSIS_5-master/CMSIS/RTOS2/RTX/Source/*.c .
    cp ../CMSIS_5-master/CMSIS/RTOS2/RTX/Source/*.h .
    cp ../CMSIS_5-master/CMSIS/RTOS2/RTX/Include/* .

    # RTX main header file
    cp ../CMSIS_5-master/CMSIS/RTOS2/Include/cmsis_os2.h .

    # We use SysTick for timer tick
    cp ../CMSIS_5-master/CMSIS/RTOS2/Include/os_tick.h .
    cp ../CMSIS_5-master/CMSIS/RTOS2/Source/os_systick.c .

    # OS configuration file and stubs
    cp ../CMSIS_5-master/CMSIS/RTOS2/RTX/Config/RTX_Config.h .
    cp ../CMSIS_5-master/ CMSIS/RTOS2/RTX/Config/RTX_Config.c .

    # architecture specific header files
    mkdir arch

    # compiler and architecture specific header files
    cp ../CMSIS_5-master/CMSIS/Core/Include/cmsis_version.h arch
    cp ../CMSIS_5-master/CMSIS/Core/Include/cmsis_compiler.h arch
    cp ../CMSIS_5-master/CMSIS/Core/Include/cmsis_gcc.h arch
    cp ../CMSIS_5-master/CMSIS/Core/Include/core_cm4.h arch
    cp ../CMSIS_5-master/CMSIS/Core/Include/mpu_armv7.h arch

    # Cortex-M4 device specific header files
    cp ../CMSIS_5-master/Device/ARM/ARMCM4/Include/ARMCM4.h arch
    cp ../CMSIS_5-master/Device/ARM/ARMCM4/Include/ARMCM4_FP.h arch
    cp ../CMSIS_5-master/Device/ARM/ARMCM4/Include/system_ARMCM4.h arch

    # assembly files for exception handlers
    cp ../CMSIS_5-master/CMSIS/RTOS2/RTX/Source/GCC/irq_armv7m.S .
    ```

4. Create `RTE_Components.h` with the following lines:

    ```c
    # ifndef CMSIS_device_header
    # define CMSIS_device_header "ARMCM4_FP.h"
    # endif
    ```

5. Turn off round-robin scheduling in `RTX_Config.h`:

    ```c
    # define OS_ROBIN_ENABLE             0
    ```

## Part 2: Integrate with BSP and make

1. Download `make+bsp.tgz` from Teams and untar it in the project root directory.

    ```shell
    cd <path to mbit-rtx>
    tar xvfz ~/Downloads/make+bsp.tgz
    mv make+bsp/* ./
    rmdir make+bsp
    ```

2. Check rules for `.S` file.

3. Create rtx/Makefile

4. Change main Makefile.

5. If you get a linker error about `ARM.extab` and `eh_frames` sections, add them after `.rodata`.

6. Build and run BSP main code.

## Part 3: Write main code with RTX

1. Rewrite the main code using OS timer instead of software timer.
    Remove timer from BSP.

2. Build and run the rewritten BSP program.

3. Build and run sample program with multiple threads.
