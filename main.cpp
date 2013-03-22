/*
 * main.cpp
 * screenshot <filename>
 * 
 * Max Lahey, 3/20/13
 *
 * takes a (png) screenshot of active displays with proper orientation in virtual desktop space.
 */

#include <stdio.h>
#include <stddef.h>
#include "screen_shooter.h"

int main (int argc, char* argv[])
{
  if (argc != 2) {
    fprintf(stderr,"Error: screenshot takes one parameter\nUsage: screenshot <filename>");
    return 1;
  }
  ScreenShooter screen_shooter;
  Screenshot* screenshot = screen_shooter.take_screenshot();
  screenshot->write_png(argv[1]);

  delete screenshot;

  return 0;
}