/*
 * screen_shooter.h
 * Max Lahey, 3/20/13
 */

#include <string>
#include <stdio.h>
#include <windows.h>

#include "mq.h" // MSMQ header file
#include <gdiplus.h>

#ifndef _SCREEN_SHOT_H_
#define _SCREEN_SHOT_H_

using namespace Gdiplus;

struct SimpleSize {
  int width;
  int height;
};

int get_encoder_clsid(const WCHAR* format, CLSID* pClsid);
wchar_t* char_str_to_wchar(const char * in);

/**
 * A Screenshot encapsulates an HBITMAP, containing a screenshot image.
 * 
 * Destruction of the Screenshot will release the context.
 */
class Screenshot {
  public:
    Screenshot(HBITMAP hBitmap, SimpleSize & size);
    ~Screenshot();
    
    // Write specified type encoded screenshot data to filename
    void write_png(const char* filename);
    void write_bmp(const char* filename);
    void write_jpeg(const char* filename);
    void write_gif(const char* filename);
    void write_tiff(const char* filename);
    
  private:
    void write(const char* filename, const char* encoder_type);
    
  private:
    HDC _bitmap_context;
    HBITMAP  _hBitmap;
    SimpleSize _size;
    ULONG_PTR _gdiplusToken;
};

#endif // _SCREEN_SHOT_H_
