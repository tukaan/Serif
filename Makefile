OS := $(shell uname -s | tr [:upper:] [:lower:])
ARCH := $(shell uname -m | grep 64)


ifeq ($(ARCH), )
	ARCH = x32
else
	ARCH = x64
endif

ifeq ($(shell uname -s | grep mingw), )
	OS = windows
endif


ifeq ($(OS), linux)
	DLL = libserif_linux_$(ARCH).so
	SOURCE = src/serif_linux.c
	PLAT_OPTIONS = \
		-Wl,--no-undefined \
		-I/usr/include/tcl \
		-ltclstub8.6 \
		-lfontconfig
else ifeq ($(OS), darwin)
	DLL = libserif_mac_$(ARCH).dylib
	SOURCE = src/serif_mac.c
	PLAT_OPTIONS = \
		-framework CoreFoundation \
		-framework CoreText \
		-I/usr/local/opt/tcl-tk/include \
		-L/usr/local/opt/tcl-tk/lib \
		-ltclstub8.6
else ifeq ($(OS), windows)
	DLL = libserif_win_$(ARCH).dll
	SOURCE = src/serif_win.c
	PLAT_OPTIONS = \
		-IC:\ActiveTcl\include \
		-lgdi32 \
		-ltclstub86
endif


OPTIONS = -shared -O3 -Wall -fPIC


$(DLL): $(SOURCE)
	mkdir -p build
	gcc $(SOURCE) $(OPTIONS) $(PLAT_OPTIONS) -DUSE_TCL_STUBS -o build/$(DLL)
