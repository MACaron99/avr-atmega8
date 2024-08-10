###############################################################################
# Makefile for the project AVR
###############################################################################

## General Flags
DEV_TYPE = Special
PROJECT  = test-04
TARGET   = $(PROJECT)
MCU      = atmega8

FUSE_H   = 0xCF
FUSE_L   = 0x1F


AVR_PROGR_PORT=COM3
AVR_PROGR=stk500pp
AVR_PROGR_PP=stk500pp

include $(EMLIB)/avr/base/makedefs

## Options common to compile, link and assembly rules
COMMON   = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS   = $(COMMON)
CFLAGS  += -DF_CPU=16000000UL
CFLAGS  += ${patsubst %,-I%,${subst :, ,${IPATH}}}
CFLAGS  += -ffreestanding -Os
CFLAGS  += -g -gdwarf-2
CFLAGS  += -std=gnu99 -W -Wall
CFLAGS  += -Wimplicit-fallthrough=0
CFLAGS  += -pedantic -Wstrict-prototypes
CFLAGS  += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS  += -mcall-prologues -fno-tree-scev-cprop
CFLAGS  += -ffunction-sections -fdata-sections
CFLAGS  += -Wp,-M,-MP,-MT,$(*F).o,-MF,$(BINDIR)/dep/$(@F).d

## Assembly specific flags
ASFLAGS  = $(COMMON)
ASFLAGS += $(patsubst %,-I%,$(IPATH))
ASFLAGS += -x assembler-with-cpp

## Linker flags
LDFLAGS  = $(COMMON)
LDFLAGS += -Wl,-gc-sections

## Objects that must be built in order to link
VPATH   = .                         \
          comm                      \
          lib                       \
          drivers                   \
          drivers/indicator         \
          system                    \
          proc                      

IPATH   =  .                        \
           comm                     \
           lib                      \
           drivers                  \
           drivers/indicator        \
           system                   \
           proc                     

##Link

$(BINDIR)/$(TARGET).elf: $(OBJDIR)/main.o

## Other dependencies
-include $(shell mkdir $(BINDIR)/dep 2>/dev/null) $(wildcard $(BINDIR)/dep/*)

