#Defining compiler
ifeq ($(CC), gcc)
CC=gcc
else ifeq ($(CC), g++)
CC=g++
else
$(info ***COMPILER UNSPECIFIED***)
CC=
endif

#Defining OS
ifeq ($(PLATFORM), WINDOWS)
PLATFORM=WINDOWS
else ifeq ($(PLATFORM), LINUX)
PLATFORM=LINUX
else
$(info ***PLATFORM UNSPECIFIED***)
PLATFROM=
endif

LOGS_PREFIX=logs_${PLATFORM}

all: with_foo without_foo without_foo_decl
	#mkdir $(LOGS_PREFIX) 2> /dev/null
with_foo: with_foo.c
	$(CC) with_foo.c -o with_foo_$(CC).exe && nm with_foo_$(CC).exe > $(LOGS_PREFIX)with_foo$(CC).log
without_foo: without_foo.c
	$(CC) without_foo.c -o without_foo_$(CC).exe && nm without_foo_$(CC).exe > $(LOGS_PREFIX)without_foo$(CC).log
without_foo_decl: without_foo_decl.c
	$(CC) without_foo_decl.c -o without_foo_decl_$(CC).exe && nm without_foo_decl_$(CC).exe > $(LOGS_PREFIX)without_foo_decl$(CC).log 
clean:
	rm -f *.exe *.out *.o *.obj  logs_${PLATFORM}*
