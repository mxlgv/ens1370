CC = clang
LD = lld-link
DLLTOOL = llvm-dlltool

TINYDDK = tinyddk

CCFLAGS = -Os -std=c99 -target i386-pc-win32 -ffreestanding -fno-builtin-putchar -c -Itinyddk/include
LDFLAGS = /nodefaultlib /entry:drvEntry /subsystem:native /dll /merge:.rdata=.text /safeseh:no

DRV = ens1370.sys
CORE = $(TINYDDK)/core.lib

OBJS = main.o \
	   $(TINYDDK)/printf.o \
	   $(TINYDDK)/memcpy.o

all: $(DRV)

$(DRV): $(OBJS) $(CORE)
	$(LD) $(LDFLAGS) $(CORE) $(OBJS) /out:$@

$(CORE): $(TINYDDK)/core.def
	$(DLLTOOL) -m i386 -d $< -l $@

%.o: %.c
	$(CC) $(CCFLAGS) -o $@ $<

%.o: %.S
	$(CC) $(CCFLAGS) -o $@ $<

clean:
	$(BASH) rm -f $(DRV) $(CORE) $(OBJS) *.lib
