CC := gcc

SRC_DIR := "./src"

SRCS := $(shell find -name *.c -or -name *.cpp)

ASMS := $(shell find -name *.asm)

OBJS-$(GFILTER) += $(SRC_DIR/gblur.o)

all: build

build: gblur.o intrin_sandbox.o
	gcc -g gblur.o intrin_sandbox.o -o build -march=skylake-avx512 -mavx
	rm -f gblur.o
	rm -f intrin_sandbox.o

intrin_sandbox.o:
	gcc -g -m64 -c src/intrin_sandbox.c -march=skylake-avx512 -mavx

gblur.o: $(ASMS)
	# yasm --arch=x86 --oformat=elf64  src/gblur.asm -o gblur.o
	nasm -f elf64  src/gblur.asm -o gblur.o

clean:
	rm -f build