#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = g++
rm = rm

# define any compile-time flags
CFLAGS = -Wall -g -w

# define any directories containing header files other than /usr/include
#
INCLUDES = -I/home/newhall/include  -I.

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
# LFLAGS = -L/home/newhall/lib  -L../lib

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
# LIBS = -lmylib -lm

# define the C source files
SRCS = lex.yy.cc COOL.tab.cc StringTab.cc main.cpp 

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = lex.yy.o StringTab.o main.o COOL.tab.o

# define the executable file 
MAIN = main

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

all:    $(MAIN) 
	@echo  Project1 has been compiled

COOL.tab.cc COOL.tab.hh lex.yy.cc: COOL.yy
	bison --defines COOL.yy

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LFLAGS) $(LIBS)
	$(rm) *.o

lex.yy.o: lex.yy.cc 
	$(CC) $(CFLAGS) $(INCLUDES)  -c -o $@ $<

COOL.tab.o: COOL.tab.cc
	$(CC) $(CFLAGS) $(INCLUDES)  -c -o $@ $<
	
main.o: main.cpp
	$(CC) $(CFLAGS) $(INCLUDES)  -c -o $@ $<

StringTab.o: StringTab.cc
	$(CC) $(CFLAGS) $(INCLUDES)  -c -o $@ $<

clean:
	$(rm) COOL.tab.cc *.o $(main)

