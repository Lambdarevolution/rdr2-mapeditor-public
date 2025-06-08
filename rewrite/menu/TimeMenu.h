/*
| License: Unlicense
| Created by: Lambdarevolution(at)gmail.com
*/

#ifndef RDR2_MAPEDITOR_TIME_MENU_H
#define RDR2_MAPEDITOR_TIME_MENU_H

class IntMenuItem;
class MenuButton;
class MenuCheckBox;

namespace TimeMenu {
  void HandleHourForward(MenuButton* t_item);
  void HandleHourBackwards(MenuButton* t_item);
  void HandleClockPaused(MenuCheckBox* t_item);
  void HandleYearRight(IntMenuItem* t_item);
  void HandleYearLeft(IntMenuItem* t_item);
  void HandleMonthRight(IntMenuItem* t_item);
  void HandleMonthLeft(IntMenuItem* t_item);
  void HandleDayRight(IntMenuItem* t_item);
  void HandleDayLeft(IntMenuItem* t_item);
  void CreateTimeMenu(MenuButton* t_item);
}
#endif
