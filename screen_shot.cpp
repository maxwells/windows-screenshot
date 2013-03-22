/*
 * screen_shooter.h
 * Max Lahey, 3/20/13
 */

#include "screen_shot.h"

using namespace Gdiplus;

Screenshot::Screenshot(HBITMAP hBitmap, SimpleSize & size) { 
  fprintf(stderr,"Screenshot Constructor Called\n");
  _hBitmap = hBitmap;
  _size = size;

  GdiplusStartupInput gdiplusStartupInput;
  GdiplusStartup(&_gdiplusToken, &gdiplusStartupInput, NULL);

}

Screenshot::~Screenshot() {
  DeleteObject(_hBitmap);
  GdiplusShutdown(_gdiplusToken);
}

/* write_png takes a filepath and writes the bitmap data as a png into it. */
void Screenshot::write_png(const char* filepath) {
  write(filepath, "image/png");
}

/* write_jpeg takes a filepath and writes the bitmap data as a jpeg into it. */
void Screenshot::write_jpeg(const char* filepath) {
  write(filepath, "image/jpeg");
}

/* write_bmp takes a filepath and writes the bitmap data as a bmp into it. */
void Screenshot::write_bmp(const char* filepath) {
  write(filepath, "image/bmp");
}

/* write_gif takes a filepath and writes the bitmap data as a gif into it. */
void Screenshot::write_gif(const char* filepath) {
  write(filepath, "image/gif");
}

/* write_tiff takes a filepath and writes the bitmap data as a tiff into it. */
void Screenshot::write_tiff(const char* filepath) {
  write(filepath, "image/tiff");
}

/* write takes a filepath and encoder type (as char*) and writes the bitmap data of this screenshot into the specified path */
void Screenshot::write(const char* filepath, const char* encoder_type)
{
  Gdiplus::Bitmap bmp(_hBitmap,(HPALETTE)0);
  CLSID pngClsid;
  wchar_t* encoder_type_wide = char_str_to_wchar(encoder_type);
  get_encoder_clsid(encoder_type_wide, &pngClsid);

  wchar_t* filepath_wide = char_str_to_wchar(filepath);
  bmp.Save(filepath_wide,&pngClsid,NULL);
  delete[] filepath_wide;
  delete[] encoder_type_wide;
}

/* Some Gdiplus functions take wide char arrays; provides a conversion from char[] to wchar_t[] */
wchar_t* char_str_to_wchar(const char * in) {
  size_t size = strlen(in)+1;
  wchar_t* out = new wchar_t[size];
  mbstowcs(out, in, size);
  return out;
}

/* GetEncoderClsid is a helper method for write_png
  --> it returns an encoder class id that Gdiplus needs to save a Bitmap in another format.
  Borrowed from MSDN */
int get_encoder_clsid(const WCHAR* format, CLSID* pClsid)
{
  UINT  num = 0;          // number of image encoders
  UINT  size = 0;         // size of the image encoder array in bytes

  ImageCodecInfo* pImageCodecInfo = NULL;

  GetImageEncodersSize(&num, &size);
  if(size == 0)
    return -1;  // Failure
  fprintf(stderr,"%i Image Encoders\n", size);

  pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
  if(pImageCodecInfo == NULL)
    return -1;  // Failure

  GetImageEncoders(num, size, pImageCodecInfo);
  fprintf(stderr,"Got image encoders\n");
  
  for(UINT j = 0; j < num; ++j)
  {
    if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
    {
      *pClsid = pImageCodecInfo[j].Clsid;
      free(pImageCodecInfo);
      return j;  // Success
    }    
  }

  free(pImageCodecInfo);
  return -1;
}