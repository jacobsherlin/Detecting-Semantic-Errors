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
INCLUDES = -I.

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
# LFLAGS = -L/home/newhall/lib  -L../lib

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
# LIBS = -lmylib -lm


#

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
RM = rm
OBJS = lex.yy.o tiger.tab.o main.o Print.o TypeChecking_student.o TypeChecking.o Env.o Absyn.o 
HEADERS = TypeChecking.h Types.h Env.h Absyn.h ErrorMsg.h Print.h SymbolTable.h FlexLexer.h SymbolTable.h

# define the C source files
#SRCS = lex.yy.cc COOL.tab.cc main.cpp dump.cpp TypeChecking_student.cpp TypeChecking.cpp

LIBS = libtypechecking.a
#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

all:    $(MAIN) 
	@echo  Project has been compiled
	$(RM) $(OBJS)

lex.yy.o: lex.yy.cc 
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LFLAGS) 

tiger.tab.o: tiger.tab.cc 
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LFLAGS) 

Print.o: Print.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LFLAGS) 

Env.o: Env.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LFLAGS) 

Absyn.o: Absyn.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LFLAGS)

TypeChecking_student.o: TypeChecking_student.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LFLAGS) 

TypeChecking.o: TypeChecking.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LFLAGS) 

main.o: main.cpp $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< $(LFLAGS) 
	
$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

clean:
	$(rm) *.o $(MAIN)
