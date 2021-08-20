# Time related functions.

 Functions related to ingame time.
 
## Scope: Global

  ###### SetTime
    ```void SetTime(int hour, int minute, int second);```
    
    Instantly sets the ingame time.


  // GetTimeHour
  int GetTimeHour();
  returns the current hour in game time.

  // GetTimeMinute
  int GetTimeMinute();
  returns the current minute in game time.

  // GetTimeSecond
  int GetTimeSecond();
  returns the current second in game time.

  // GetTimeYear
  int GetTimeYear();
  returns the current year in game time.

  // SetDate
  void SetDate(int year, int month, int day);
  instantly sets the date.

  // PauseClock
  void PauseClock(bool state);
  Pauses the ingame clock, NOTE: it does not pause the game!

  // SetTimeScale
  void SetTimeScale(float scale);
  Sets the ingame timescale.

  // AdvanceTimeTo
  void AdvanceTimeTo(int hour, int minute, int second);
  Not tested.

  // AddTimeToClock
  void AddTimeToClock(int hours, int minutes, int second);
  Not tested.

  // SetMillisecondsPerGameMinute
  void SetMillisecondsPerGameMinute(int milliseconds);
  Not tested but name says it all..
