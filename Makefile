#
# Makefile - build screenshot and screenshot.dll for Windows
#
#  Created by Max Lahey on 3/20/13.
#  MIT-License Copyright (c) 2013 Max Lahey.
#
CC=g++
LIBS    = -lgdi32 -lgdiplus
CFLAGS=-c -Wall

OFILES= screen_shooter.o screen_shot.o

all: screenshot.dll screenshot

screenshot: main.o $(OFILES)
	$(CC) $^ -o screenshot $(LIBS)

screenshot.dll: $(OFILES)
	$(CC) -shared -o $@ $^ $(LIBS) 

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

clean:
	rm -f screenshot *.o *.dll
