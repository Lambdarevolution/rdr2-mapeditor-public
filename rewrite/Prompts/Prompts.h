/*
| License: Unlicense
| Created by: Lambdarevolution(at)gmail.com / 2020-03-28 / rewrite 2024-06-01
| Purpose: Create and manages rdr2 prompts easily using a singleton class.
*/
#ifndef RDR2_MAPEDITOR_PROMPTS_H
#define RDR2_MAPEDITOR_PROMPTS_H

#include <string>
#include <vector>

#include "..\..\inc\natives.h"
#include "..\..\inc\types.h"

// This is a hold struct for prompts, we do this since we cant get tags on the prompt at the moment we need our own solution.
struct PromptInstance {
  int mId = -1;
  char* mTag;
  uint mMode;
};

class Prompts {
 private:
  int mHorizontalId = -1;
  static Prompts* mInstance;
  std::vector<PromptInstance*> mPromptList;

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
  void CreatePrompt(char* p_input, char* text, EMode mode, bool enabled, bool visible, char* tag, int timer, int mashes);
  void DeletePrompt(char* tag);
  void HidePrompt(char* tag);
  void ShowPrompt(char* tag);
  void DisablePrompt(char* tag);
  void EnablePrompt(char* tag);
  void SetPromptAttribute(char* tag, int attribute, bool enable); 
  void SetPromptText(char* tag, const char* txt);
  void SetPriority(char* tag, int priority);
  float GetPromptProgress(char* tag);  
  bool DoPromptExist(char* tag);
  bool IsPromptValid(char* tag);
  bool IsPromptBeingPressed(char* tag);
  bool IsPromptJustReleased(char* tag);
  bool IsPromptEnabled(char* tag);
  bool IsPromptCompleted(char* tag);
  void SetHorizontalOrientation();
  void ResetHorizontalOrientation() const;
  void DeleteAllEditorPrompts();;
};
#endif  // RDR2_MAPEDITOR_PROMPTS_H_
