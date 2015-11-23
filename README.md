iidx-enabler
============
Easily Hex Edit your beatmaniaIIDX 22 PENDUAL DLL to enable certain hacks and features.

Usage
============
1. Make backup of your bm2dx.dll, I tell you once again, MAKE BACKUP OF YOUR BM2DX.DLL
2. Make bm2dx.dll writable (don't set it as read-only, uncheck read only, etc)
3. If you're going to patch omnimix, make sure to rename the dll first, and then rename it back again to bm2dx_xxxx.dll, where xxxx is omni or orig.
4. Put Pendual Enabler exe in the same directory as bm2dx.dll, the program will exit if bm2dx.dll not found, or bm2dx.dll is set as read-only.
5. Select the patch you want to use
6. Have an enjoying.

Compiling
==
On Linux:

To compile the main program run

`make`

To compile the unittest run the following

`make fakedll`
`make unittest`

On Windows:

This is still untested.