#ifndef RDR2_MAPEDITOR_TIME_MENU_H
#define RDR2_MAPEDITOR_TIME_MENU_H

class IntMenuItem;
class MenuButton;
class MenuCheckBox;
class MenuStringItem;

namespace TimeMenu {
  void HandleHourForward(MenuButton* button);
  void HandleHourBackwards(MenuButton* button);
  void HandleClockPaused(MenuCheckBox* item);
  void HandleYearRight(IntMenuItem* item);
  void HandleYearLeft(IntMenuItem* item);
  void HandleMonthRight(IntMenuItem* item);
  void HandleMonthLeft(IntMenuItem* item);
  void HandleDayRight(IntMenuItem* item);
  void HandleDayLeft(IntMenuItem* item);
  void CreateTimeListMenu(MenuButton* button);
}
#endif
