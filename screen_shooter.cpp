/*
 * screen_shooter.cpp
 * Max Lahey, 3/20/13
 */

#include "screen_shooter.h"
#include <string>
#include <gdiplus.h>
#include <windows.h>
#include <winuser.h>

#define max(a,b) \
({ __typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
_a > _b ? _a : _b; })

#define min(a,b) \
({ __typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
_a < _b ? _a : _b; })

RECT* ScreenShooter::_display_rects;

/* monitor_count_enum_proc helps monitor_count get number of displays */
BOOL CALLBACK monitor_count_enum_proc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
  int *count = (int*)dwData;
  (*count)++;
  return TRUE;
}

/* monitor_info_enum_proc stores the display information in its indexed struct */
BOOL CALLBACK monitor_info_enum_proc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
  int * count = (int*)dwData;
  
  // extract dimensions of monitor from MONITOR INFO
  MONITORINFO mi;
  mi.cbSize = sizeof(mi);
  GetMonitorInfo(hMonitor, &mi);

  ScreenShooter::_display_rects[*count] = mi.rcMonitor;
  (*count)++;
  return TRUE;
}

ScreenShooter::ScreenShooter() {
    init_displays();
    calculate_bounds();
  }

ScreenShooter::~ScreenShooter() {
    free(_display_rects);
}

int ScreenShooter::monitor_count() {
  int Count = 0;
  if (EnumDisplayMonitors(NULL, NULL, monitor_count_enum_proc, (LPARAM)&Count))
    return Count;
  return -1;//signals an error
}

Screenshot* ScreenShooter::take_screenshot() {
  HBITMAP combined_image;

  // calculate size of final image
  SimpleSize final_size;
  final_size.width = _bottom_right.x - _top_left.x;
  final_size.height = _bottom_right.y - _top_left.y;

  // Copies bitmap data from desktop window device context into a memory device context where it can be captured into combined_image
  HDC scrContext = GetDC(GetDesktopWindow());
  HDC memContext = CreateCompatibleDC(scrContext);
  combined_image = CreateCompatibleBitmap(scrContext, final_size.width, final_size.height);
  SelectObject(memContext, combined_image);
  BitBlt(memContext, 0, 0, final_size.width, final_size.height, scrContext, _top_left.x, _top_left.y, SRCCOPY);
  
  Screenshot* screenshot = new Screenshot(combined_image, final_size);

  // gotta keep things tidy
  ReleaseDC(0, memContext);
  ReleaseDC(0, scrContext);

  return screenshot;
}

/* Calculate the _top_left and _bottom_right corners of our virtual display. Must be called after init_displays. */
void ScreenShooter::calculate_bounds() {  
  _top_left.x = 0;
  _top_left.y = 0;
  _bottom_right.x = 0;
  _bottom_right.y = 0;
  for(int i = 0; i < _dsp_count; i++)
  {
      RECT bounds = _display_rects[i];

      _top_left.x     = min(_top_left.x, bounds.left);
      _top_left.y     = min(_top_left.y, bounds.top);
      _bottom_right.x = max(_bottom_right.x, bounds.right);
      _bottom_right.y = max(_bottom_right.y, bounds.bottom);
  }
}

/* Initialize the array and size of the Active Displays */
void ScreenShooter::init_displays() {
    /* How many active displays do we have? */
    _dsp_count = monitor_count();

    /* Allocate enough memory to hold display information */
    _display_rects = (RECT *) calloc((size_t) _dsp_count, sizeof(RECT));

    /* Populate displays information */
    int count = 0;
    EnumDisplayMonitors(NULL, NULL, monitor_info_enum_proc, (LPARAM)&count);
}