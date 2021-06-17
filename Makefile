CC := gcc

SRC_DIR := "./src"

SRCS := $(shell find -name *.c -or -name *.cpp)

ASMS := $(shell find -name *.asm)

OBJS-$(GFILTER) += $(SRC_DIR/gblur.o)

all: build

build: gblur.o intrin_sandbox.o
	gcc -g -no-pie -m64 gblur.o intrin_sandbox.o -o build -march=skylake-avx512 -mavx

intrin_sandbox.o:
	gcc -g -m64 -c src/intrin_sandbox.c -march=skylake-avx512 -mavx

gblur.o: $(ASMS)
	nasm -felf64  src/gblur.asm -o gblur.o

clean:
	rm -f gblur.o
	rm -f intrin_sandbox.o
	rm -f build