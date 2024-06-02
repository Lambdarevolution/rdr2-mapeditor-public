/*
| License: Unlicense
| Created by: Lambdarevolution(at)gmail.com / 2020-03-28 / rewrite 2024-06-01
| Purpose: Create and manages rdr2 prompts easily using a singleton class.
*/
#ifndef RDR2_MAPEDITOR_PROMPTS_H_
#define RDR2_MAPEDITOR_PROMPTS_H_

#include <string>
#include <vector>

#include "..\..\inc\natives.h"
#include "..\..\inc\types.h"

// This is just a holder.
struct sPrompt {
  int id = -1;
  std::string tag;
  uint mode;
};

class Prompts {
 private:
  int m_horizontalid = -1;
  static Prompts* m_instance;
  std::vector<sPrompt*> Promptlist;

 public:
  enum EMode {
    indefinitely_mode,
    hold_mode,
    hold_mode_running,
    mash_mode,
    mash_mode_indefinitely_mode,
    pressed_timed_mode,
    standard_mode
  };

  static Prompts* getInstance();
  void CreatePrompt(char* t_input, char* t_text, EMode t_mode, bool t_enabled, bool t_visible, char* t_tag, int t_timer, int t_mashes);
  void DeletePrompt(char* t_tag);
  void HidePrompt(char* t_tag);
  void ShowPrompt(char* t_tag);
  void DisablePrompt(char* t_tag);
  void EnablePrompt(char* t_tag);
  void SetPromptAttribute(char* t_tag, int t_attribute, bool t_enable); 
  void SetPromptText(char* t_tag, const char* t_txt);
  void SetPriority(char* t_tag, int t_priority);
  float GetPromptProgress(char* t_tag);  
  bool DoPromptExist(char* t_tag);
  bool IsPromptValid(char* t_tag);
  bool IsPromptBeingPressed(char* t_tag);
  bool IsPromptJustReleased(char* t_tag);
  bool IsPromptEnabled(char* t_tag);
  bool IsPromptCompleted(char* t_tag);
  void SetHorizontalOrientation();
  void ResetHorizontalOrientation();
  void DeleteAllEditorPrompts();
};
#endif  // RDR2_MAPEDITOR_PROMPTS_H_
