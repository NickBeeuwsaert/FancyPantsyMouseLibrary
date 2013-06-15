LIBS = -L/opt/X11/lib -lX11
CFLAGS = -I/opt/X11/include
UNAME = $(shell uname -s)
ifeq ($(UNAME), Darwin)
	LIBS := $(LIBS) -Wl,-framework,Cocoa
endif
all: main.o MouseTool.o
	g++ main.o MouseTool.o -o main $(LIBS)
main.o: main.cpp
	g++ -c main.cpp $(CFLAGS)
MouseTool.o: MouseTool.cpp
	g++ -c MouseTool.cpp $(CFLAGS)
