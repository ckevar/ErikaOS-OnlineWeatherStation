# This file should be included in the first line of the Makefile as: include usr.mk
GNU_ARM_ROOT = $(HOME)/.local/gcc-arm-none-eabi-10.3-2021.10

SRC_DIR:=src ui/src img/src
INC_DIR:=inc ui/inc img/inc

SRC:=$(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.c))
INC:=$(foreach dir, $(INC_DIR), -I$(dir))

CFLAGS += $(INC)
APP_SRCS += $(SRC)

