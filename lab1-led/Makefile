
DEV_TYPE = Special
PROJECT  = test-01
TARGET   = $(PROJECT)
MCU      = atmega8

FUSE_H   = 0xCF
FUSE_L   = 0x1F


AVR_PROGR_PORT=COM3
AVR_PROGR=stk500pp
AVR_PROGR_PP=stk500pp

include $(EMLIB)/avr/base/makedefs

COMMON   = -mmcu=$(MCU)

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

ASFLAGS  = $(COMMON)
ASFLAGS += $(patsubst %,-I%,$(IPATH))
ASFLAGS += -x assembler-with-cpp

LDFLAGS  = $(COMMON)
LDFLAGS += -Wl,-gc-sections

VPATH   = .

IPATH   = .


$(BINDIR)/$(TARGET).elf: $(OBJDIR)/main.o

-include $(shell mkdir $(BINDIR)/dep 2>/dev/null) $(wildcard $(BINDIR)/dep/*)

