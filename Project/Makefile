#Created by LaFrance and Iveth - CSE 140
#This makefile will help in our pursuits to complete our CPU Project
#Resources: https://cs.colby.edu/maxwell/courses/tutorials/maketutor/ & https://www3.nd.edu/~zxu2/acms60212-40212/Makefile.pdf

#to use:
# first type in: $ make (if no errors occur after changing code)
# next: ./output (to see output of code)
# to clear: $make clean (then repeat first step again)

CC=gcc #C Compiler
CFLAGS= -c -Wall #C Options passed to the Compiler
#OBJECTS = Single_Cycle_MIPS_CPU.o Decoder.o #refers to the the .c files to be compiled

all:output #the entire program to be compiled: output refers to the output file to record the output of execution

# First Version: April 7th 2022:

#Adding FunctionHandler
# output:Single_Cycle_MIPS_CPU.o Decoder.o Execute.o
# 	$(CC)Single_Cycle_MIPS_CPU.o Decoder.o Execute.o -o output

#Test output for old file:
# output:old_single_cycle.o Decoder.o Execute.o
# 	$(CC)old_single_cycle.o Decoder.o Execute.o -o output

#to test the old file:
# old_single_cycle.o:old_single_cycle.c
# 	$(CC)$(CFLAGS) old_single_cycle.c

#################################################################################
# Final Version 5/4/2022
# same as saying $gcc Single_Cycle_MIPS_CPU.c Decoder.c -o output (current Version)
output:Single_Cycle_MIPS_CPU.o FunctionHandler.o 
	$(CC)Single_Cycle_MIPS_CPU.o FunctionHandler.o -o output

#individual parts to be compiled (current version):
Single_Cycle_MIPS_CPU.o:Single_Cycle_MIPS_CPU.c
	$(CC)$(CFLAGS) Single_Cycle_MIPS_CPU.c

FunctionHandler.o:FunctionHandler.c
	$(CC)$(CFLAGS) FunctionHandler.c

# Execute.o:Execute.c
# 	$(CC)$(CFLAGS) Execute.c

##################################################################################

# Second Version: April 7th 2022 -- Didnt really work

# output:$(OBJECTS) #same as saying $gcc Single_Cycle_MIPS_CPU.c Decoder.c -o output
# 	$(CC)$(CFLAGS) -o output

# %.o:%.c #Suffix Rule (This tells that .o files are made from .c files)
# 	$(CC)$(CFLAGS) $<

clean:
	rm -f *.o