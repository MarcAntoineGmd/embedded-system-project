# Inputs : 
# 	- PROJECTNAME : the name of the library, that will get the "lib" prefix added.
# 	- PRJSRC : the `.cpp` files contained in the current directory, and in all sub-directories.
# Output :
# 	- A `.a` static library.

# Make (all): Finds all occurences of .cpp files in the current directory (recursively) and archives them in a static .a library, while putting the compiled files in a directory, by default : "build".


# Make clean : deletes recursively the "build" directory + the .a library

# Source : https://makefiletutorial.com/

######## AVR Static Library Makefile ########

MCU=atmega324pa
# Name of the static .a library
PROJECTNAME=Test
# The shell command in UNIX systems is recursive by default (no -r needed)
# The option -o <=> or
PRJSRC:= $(wildcard */*.cpp debug.cpp)
INC := $(addprefix -I, $(sort $(dir $(PRJSRC))))
LIBS=
OPTLEVEL=s

#### tools ####
CC=avr-gcc
AR=avr-ar

#### flags ####
CFLAGS=-I. $(INC) -MMD -mmcu=$(MCU) -O$(OPTLEVEL) \
       -std=c++14 -fshort-enums -funsigned-bitfields \
       -funsigned-char -Wall -DF_CPU=8000000UL

CXXFLAGS=-fno-exceptions

#### output ####
OBJDIR = build
LIBNAME=lib$(PROJECTNAME).a

#### sources ####
SRCDIRS=$(sort $(dir $(PRJSRC)))
VPATH=$(SRCDIRS)

OBJDEPS=$(addprefix $(OBJDIR)/,$(notdir $(PRJSRC:.cpp=.o)))

#### targets ####
.PHONY: all clean

all: $(OBJDIR) $(LIBNAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

#### build static library ####
$(LIBNAME): $(OBJDEPS)
	$(AR) -rcs $@ $^

#### compile C++ ####
$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

#### dependency files ####
-include $(OBJDIR)/*.d

#### clean ####
clean:
	rm -rf $(OBJDIR) $(LIBNAME)

	