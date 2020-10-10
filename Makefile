CC=g++
SOURCE=main.cpp Commands/*.cpp Helpers/*.cpp Parser/*.cpp
OBJSDIR=Objs
OBJS=$(wildcard $(OBJSDIR)/*.o)
CFLAGS=-std=gnu++20 -static
LINKFLAG=
OUT=eXtended.exe
default: compile

prep:
	if not exist $(OBJSDIR) mkdir $(OBJSDIR)

compile: prep Main
	$(CC) $(OBJS) -o $(OUT) $(LINKFLAG)

Main:
	del Objs\\*.o
	del $(OUT)
	$(CC) -c $(SOURCE) $(CFLAGS)
	move "*.o" $(OBJSDIR)\\

clean:
	del Objs\\*.o
	del $(OUT)