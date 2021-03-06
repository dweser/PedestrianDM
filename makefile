#########################
##  Makefile diffusion ##
#########################

## objects
OBJECTS = main_pedestrianDM.o   \
		  parameters_xml.o      \
		  fn_neighbors.o        \
          two_spec_iter.o       \
          decision_strategies.o \
          fn_distance.o         \
          fn_file_print.o       \
          fn_phi.o              \
          init_functions.o      \
          str_fixed_length.o


## compiler check
# note: after OSX version 10.8, Apple shipped Macs with clang
# 	compiler as standard, not gcc
OS := $(shell uname)
ifeq ($(OS), Darwin)
	VERSIONGT8 := $(shell expr `sw_vers -productVersion | cut -d \. -f 2` \> 8)
	ifeq ($(VERSIONGT8), 1)
		CC = g++-6
	else
		CC = g++
	endif
else
	CC = g++
endif

## options for the compiler CFLAGs
# 	fopenmp    : include OpenMP
# 	02 		   : optimize
#	Iinclude   : search for headers in folder "include"
# 	-std=c++11 : ensure user is using c++11
FLAGS = -fopenmp -O2 -Iinclude -std=c++11
#LDFLAGS = -L/usr/openwin/lib
#LDLIBS  = -lX11 -lXext
## the name of the executable
EXEC = pedestrianDM

##----------------------------------------##
##            jobs for 'make'             ##
##----------------------------------------##

## Source tree:
#    Makefile
#    -- src/      *.cpp
#	 -- include/  *.hpp
#    -- build/    *.o *.mod
#    -- bin/      $(EXE)

## Paths
OBJDIR = build
EXECDIR = bin
vpath %.cpp src
vpath %.o $(OBJDIR)
# to help make find the object in the folder $(OBJDIR)
OBJECTS2 = $(addprefix $(OBJDIR)/, $(OBJECTS))

## commands
all: init clean $(EXEC)

$(EXEC): $(OBJECTS)
	@$(CC) $(FLAGS) -o $(EXECDIR)/$(EXEC) $(OBJECTS2)

## .o
%.o: %.cpp
	@$(CC) $(FLAGS) -c $^ -o $(OBJDIR)/$@ -J$(OBJDIR)

## create folder structure
init :
	@if [ ! -d 'data' ]; then \
		mkdir data; \
	fi
	@if [ ! -d 'bin' ]; then \
		mkdir bin; \
	fi
	@if [ ! -d 'build' ]; then \
		mkdir build; \
	fi 
	@if [ ! -d 'visualization' ]; then \
		mkdir visualization; \
	fi 

clean :
	@rm -rf $(OBJDIR)/*.mod;
	@rm -f $(OBJDIR)/*.o;
