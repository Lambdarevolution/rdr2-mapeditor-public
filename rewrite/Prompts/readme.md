Prompt class rewritten. 

Changes:
- Switched to the scripthook sdk native.h (This is why so many natives are unnamed)
- Removed unused and redundant code. 
- Added mash mode.
- sPrompt struct now holds the mode.
- Added log messages when failing to find tag.

