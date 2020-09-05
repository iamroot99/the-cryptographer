# Set flags for the C compiler
CC      = gcc
CFLAGS  = -Wall -Werror -Wno-unused-result -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -pedantic -O2#-g
LDLIBS  = -lm #-pg

.SUFFIXES: .c .o .d 

# Mention files that are not real
.PHONY: all clean tests

cryptographer_sources := $(shell find cryptographer_src -name "*.c")

sources := $(cryptographer_sources) cryptographer.c

cryptographer_objs := $(cryptographer_sources:.c=.o)

objects      := $(subst .c,.o,$(sources))
dependencies := $(subst .c,.d,$(sources))

# Build rules for the final executables
all: cryptographer

cryptographer: cryptographer.o $(cryptographer_objs)


# Rule to clean generated files
clean:
	rm -f $(objects)
	rm -f $(dependencies)
	rm -f cryptographer

ifneq "$(MAKECMDGOALS)" "clean"
  include $(dependencies)
endif

# Credits to GNU Make Manual
%.d: %.c
	@set -e;rm -f $@; \
	$(CC) -MM  $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$


