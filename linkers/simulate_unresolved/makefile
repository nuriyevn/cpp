PLATFORM=WINDOWS
LOGS_PREFIX=logs_${PLATFORM}
SLASH=/

all: with_foo without_foo without_foo_decl
	mkdir $(LOGS_PREFIX)
with_foo: with_foo.c
	gcc with_foo.c -o with_foo.exe && nm with_foo.exe > $(LOGS_PREFIX)with_foo.log
without_foo: without_foo.c
	gcc without_foo.c -o without_foo.exe && nm without_foo.exe > $(LOGS_PREFIX)without_foo.log
without_foo_decl: without_foo_decl.c
	gcc without_foo_decl.c -o without_foo_decl.exe && nm without_foo_decl.exe > $(LOGS_PREFIX)without_foo_decl.log 
clean:
	rm -f *.exe *.out *.o *.obj
