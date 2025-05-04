# CP316-RTES-2025

CP316: Real-time Embedded Systems, IISc

## Toolchain installation

For linux, see [README.md](./Assignments/Assignment-1/files/README.md) in Assignment-1.

For macOS, instead of `brew install arm-none-eabi-gcc`, use

```shell
brew install --cask gcc-arm-embedded
```

Or alternatively, download the toolchain from [ARM's website](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads).

## Makefiles

The following version of `flash` takes into considerations the platform as well.
Just running `make` will build and flash to the `BBC micro:bit v2` board.

```make
TARGET = MICROBIT

#########################################
# Auto detect platform and flash
# To override the default FLASHDIR, use: `make flash FLASHDIR=/path/to/flash`

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
 IS_WSL := $(shell grep -qi microsoft /proc/version 2>/dev/null && echo 1 || echo 0)
 ifeq ($(IS_WSL),1) # WSL
  FLASHDIR ?= /mnt/c/Temp
 else # Native Linux
  FLASHDIR ?= /mnt/$(TARGET)
 endif
else ifeq ($(UNAME_S),Darwin) # macOS
 FLASHDIR ?= /Volumes/$(TARGET)
endif

flash: $(TARGET).hex
ifeq ($(UNAME_S),Linux)
ifeq ($(IS_WSL),1) # WSL
 /bin/cp $(TARGET).hex "$(FLASHDIR)"
 (cd "$(FLASHDIR)" && cmd.exe /c copy $(TARGET).hex E:)
else # Native Linux
 @if [ -d "$(FLASHDIR)" ]; then \
  /bin/cp $(TARGET).hex "$(FLASHDIR)"; \
  echo "Flashed to $(TARGET)"; \
 else \
  echo "Flash failed: Mount not found at $(FLASHDIR)"; \
 fi
endif
else ifeq ($(UNAME_S),Darwin) # macOS
 @if [ -d "$(FLASHDIR)" ]; then \
  /bin/cp $(TARGET).hex "$(FLASHDIR)"; \
  echo "Flashed to $(TARGET)"; \
 else \
  echo "Flash failed: Mount not found at $(FLASHDIR)"; \
 fi
else # Fallback
 @echo "Unknown platform: $(UNAME_S)"
 @exit 1
endif

#########################################
```
