/*
 * screen_shooter.h
 * Max Lahey, 3/20/13
 */

#ifndef _SCREEN_SHOOTER_H_
#define _SCREEN_SHOOTER_H_

#include "screen_shot.h"

struct SimplePoint {
  int x;
  int y;
};

BOOL CALLBACK monitor_count_enum_proc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);
BOOL CALLBACK monitor_info_enum_proc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);

/**
 * A ScreenShooter provides a facility to take one of more screenshots where a screenshot
 * includes a large image of ALL active displays on a computer.
 * 
 */
class ScreenShooter {
  public:
    ScreenShooter();
    ~ScreenShooter();

    // Allocate and take a new screenshot of all active screens. The caller
    // is responsible for its deletion.
    void take_single_screenshot();
    Screenshot* take_screenshot();

  public:
    static RECT* _display_rects;
  
  private:
    void calculate_bounds();
    void init_displays();
    int  monitor_count();
    
  private:
    int      _dsp_count;
    SimplePoint    _top_left;
    SimplePoint    _bottom_right;
};


#endif // _SCREEN_SHOOTER_H_