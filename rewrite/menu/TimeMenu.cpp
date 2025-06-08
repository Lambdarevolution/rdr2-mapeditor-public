#include "TimeMenu.h"
#include "Widgets.h"
#include "Editor.h"

void TimeMenu::HandleHourForward(MenuButton* button) {
	TIME::ADD_TO_CLOCK_TIME(1, 0, 0);
}

void TimeMenu::HandleHourBackwards(MenuButton* button) {
	TIME::ADD_TO_CLOCK_TIME(-1, 0, 0);
}

void TimeMenu::HandleClockPaused(MenuCheckBox* item) {
	Editor::getInstance()->m_world.mClockPaused = !item->GetState();
	TIME::PAUSE_CLOCK(Editor::getInstance()->m_world.mClockPaused, 0);
	item->SetState(Editor::getInstance()->m_world.mClockPaused);
}

void TimeMenu::HandleYearRight(IntMenuItem* item) {
	TIME::SET_CLOCK_DATE(TIME::GET_CLOCK_DAY_OF_MONTH(), TIME::GET_CLOCK_MONTH(), (TIME::GET_CLOCK_YEAR() + 1));
	item->SetValue(TIME::GET_CLOCK_YEAR());
}

void TimeMenu::HandleYearLeft(IntMenuItem* item) {
	TIME::SET_CLOCK_DATE(TIME::GET_CLOCK_DAY_OF_MONTH(), TIME::GET_CLOCK_MONTH(), (TIME::GET_CLOCK_YEAR() - 1));
	item->SetValue(TIME::GET_CLOCK_YEAR());
}

void TimeMenu::HandleMonthRight(IntMenuItem* item) {
	TIME::SET_CLOCK_DATE(TIME::GET_CLOCK_DAY_OF_MONTH(), (TIME::GET_CLOCK_MONTH() + 1), TIME::GET_CLOCK_YEAR());
	item->SetValue(TIME::GET_CLOCK_MONTH());
}

void TimeMenu::HandleMonthLeft(IntMenuItem* item) {
	TIME::SET_CLOCK_DATE(TIME::GET_CLOCK_DAY_OF_MONTH(), (TIME::GET_CLOCK_MONTH() -1) , TIME::GET_CLOCK_YEAR());
	item->SetValue(TIME::GET_CLOCK_MONTH());
}

void TimeMenu::HandleDayRight(IntMenuItem* item) {
	TIME::SET_CLOCK_DATE((TIME::GET_CLOCK_DAY_OF_MONTH() + 1), TIME::GET_CLOCK_MONTH(), TIME::GET_CLOCK_YEAR());
	item->SetValue(TIME::GET_CLOCK_DAY_OF_MONTH());
}

void TimeMenu::HandleDayLeft(IntMenuItem* item) {
	TIME::SET_CLOCK_DATE((TIME::GET_CLOCK_DAY_OF_MONTH() - 1), TIME::GET_CLOCK_MONTH(), TIME::GET_CLOCK_YEAR());
	item->SetValue(TIME::GET_CLOCK_DAY_OF_MONTH());
}

void TimeMenu::CreateTimeMenu(MenuButton* button) {
	auto menu = std::make_shared<MenuBase>("Time");

	menu->AddMenuItem(std::make_shared<MenuButton>("Hour forward", HandleHourForward));
	menu->AddMenuItem(std::make_shared<MenuButton>("Hour backward", HandleHourBackwards));
	menu->AddMenuItem(std::make_shared<MenuCheckBox>("Pause Clock", &HandleClockPaused, Editor::getInstance()->m_world.mClockPaused));
	menu->AddMenuItem(std::make_shared<IntMenuItem>(
		"Year", 
		TIME::GET_CLOCK_YEAR(),
		&HandleYearLeft,
		&HandleYearRight
		));

	menu->AddMenuItem(std::make_shared<IntMenuItem>(
		"Month",
		TIME::GET_CLOCK_MONTH(),
		&HandleMonthLeft,
		&HandleMonthRight
		));

	menu->AddMenuItem(std::make_shared<IntMenuItem>(
		"Day",
		TIME::GET_CLOCK_DAY_OF_MONTH(),
		&HandleDayLeft,
		&HandleDayRight
		));

	GetMenuHandle()->mController->AddMenu(std::move(menu));
}
