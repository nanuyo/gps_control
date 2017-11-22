PWD     	:= $(shell pwd)
TARGET      ?= arm-linux
CROSS_COMPILE   ?= $(TARGET)-
CPP     	:= $(CROSS_COMPILE)g++
CC      	:= $(CROSS_COMPILE)gcc
AR      	:= $(CROSS_COMPILE)ar
RANLIB      := $(CROSS_COMPILE)ranlib
INSTALL_DIR	?= ../rootfs/usr/bin

INC     	= -I $(KERNEL_DIR)/src/include
INC		+= -I $(MIDDLEWARE_INS_DIR)/include
INC		+= -I $(AUTOCONF_DIR)
INC 		+= -I$(PWD)

LIB		= -L $(MIDDLEWARE_INS_DIR)/lib

CFLAGS      := -Wall -g -O2 $(EXTRA_CFLAGS) $(INC) $(LIB)

LDFLAGS		:= $(EXTRA_LDFLAGS) -lm -Wl,--as-needed

targets = gps_ctrl
#targets += uart_ctrl

.PHONY : clean distclean all
%.o : %.c
	$(CC) $(CFLAGS) -c $<

all: $(targets)

gps_ctrl: gps.o nmea.o serial.o gps_logger.o bma2x2.o bma2x2_support.o
	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS)

#uart_ctrl: uart_ctl.o $(SNX_GPIO_LIB)
#	$(CC) $(CFLAGS) -o $@ $+ $(LDFLAGS) 
	
.PHONY: install
install:
	@ if [ ! -d $(INSTALL_DIR) ]; \
	then \
	install -d $(INSTALL_DIR); \
	fi
	install -c $(targets) $(INSTALL_DIR)

clean:
	rm -f *.o *.yuv *.bak *.a *.out *.so $(targets)

distclean : clean
	rm -f $(targets)
