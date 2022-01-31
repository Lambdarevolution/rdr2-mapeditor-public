/*
| License: Unlicense
| Created by: Lambdarevolution(at)gmail.com / 2020-03-28
| Purpose: Creating and manage rdr2 prompts.
*/
#ifndef RDR2_MAPEDITOR_PROMPTS_H_
#define RDR2_MAPEDITOR_PROMPTS_H_

#include <vector>
#include <string>

#include "..\inc\natives.h"
#include "..\inc\types.h"
#include "Log/Log.h"

struct sPrompt {
  int id;
  std::string tag;
  bool visible;
};
// Class: Prompts
// A Class that handles all prompts in the editor
class Prompts {
public:
  enum EMode {    
    indefinitely_mode,
    hold_mode,
    hold_mode_running,
    mash_mode_indefinitely_mode,
    standard_mode
  };
  // Variable: HorizontalId
  // The id to reset prompts orientation.
  int HorizontalId;
  static std::vector<sPrompt*> Promptlist;
  static Prompts* getInstance();
  /*
  Function: CreatePrompt
  Creates a prompt input and stores in the promptlist.

  Parameters:
  t_input - The input key (action).
  t_text - The text to display along the prompt.
  t_mode - The mode the prompt should use.
  t_enabled - Should the prompt be enabled?.
  t_visible - Should the prompt be visible?.
  t_tag - The tag used to reference this prompt.
  t_timer - How long you should hold the prompt down for it to complete, this is used by some modes like hold mode.
  */
  void CreatePrompt(char* t_input, char* t_text, EMode t_mode, bool t_enabled, bool t_visible, char* t_tag, int t_timer);
  /*
  Function: DeletePrompt

  Parameters:
  t_tag - Deletes the prompt with this tag
  */
  void DeletePrompt(char* t_tag);
  /*
  Function: HidePrompt

  Parameters:
  t_tag - Hides the prompt with this tag.
  */
  void HidePrompt(char* t_tag);
  /*
  Function: ShowPrompt

  Parameters:
  t_tag - Shows the prompt with this tag.
  */
  void ShowPrompt(char* t_tag);
  /*
  Function: DisablePrompt

  Parameters:
  t_tag - Disables the prompt with this tag.
  */
  void DisablePrompt(char* t_tag);
  /*
 Function: EnablePrompt

 Parameters:
 t_tag - Enables the prompt with this tag.
 */
  void EnablePrompt(char* t_tag);
  /*
  Function: DoPromptExist
  Checks if a prompt with supplied tag exist.

  Parameters:
  t_tag - The tag to check.

  Return:
  Returns true if the prompt exists.
  */
  bool DoPromptExist(char* t_tag);
  bool IsPromptValid(char* t_tag);
  bool IsPromptBeingPressed(char* t_tag);
  bool IsPromptCompleted(char* t_tag, EMode mode);
  bool ChaiIsPromptCompleted(std::string, EMode mode);
  void SetPlacingPrompts();

private:
  static Prompts* m_instance;
};
#endif  // RDR2_MAPEDITOR_PROMPTS_H_
