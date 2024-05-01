#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = g++

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
SRCS = lex.yy.cc StringTab.cc main.cpp copyright.h ErrorMsg.h FlexLexer.h StringTab.h

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
# OBJS = lex.yy.o StringTab.o main.o

# define the executable file 
MAIN = main

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

all:    $(MAIN) 
	@echo  Project1 has been compiled

lex.yy.cc: COOL.ll
	flex --nounistd --c++ --outfile=lex.yy.cc COOL.ll

$(MAIN): $(SRCS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(SRCS) $(LFLAGS) $(LIBS)

clean:
	$(rm) *.o $(MAIN)
