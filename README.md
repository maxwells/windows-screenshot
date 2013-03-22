# Multi Screen Capture

screenshot.exe is a small (Windows) tool that leverages Gdiplus to take an screenshot of all the users active displays (with the proper orientation in virtual desktop space). It wraps screenshot.dll (source included), which provides functionality to save png, jpeg, tiff, gif, or bmp screenshots to file. screenshot.dll is provided under the same license.

## Building

The provided makefile relies on g++. I've only compiled through Cygwin, but I can't imagine using Visual Studio would cause any problems.

## Usage

> ./screenshot.exe my_excellent_screenshot.png

### MIT License