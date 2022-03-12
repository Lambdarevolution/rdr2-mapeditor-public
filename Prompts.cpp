#include "Prompts.h"

Prompts* Prompts::m_instance = 0;

Prompts * Prompts::getInstance() {
  if (m_instance == 0) {
    m_instance = new Prompts();
  }
  return m_instance;
}
std::vector<sPrompt*> Prompts::Promptlist;

void Prompts::CreatePrompt(char* t_input, char* t_text, EMode t_mode, bool t_enabled, bool t_visible, char* t_tag, int t_timer) {
  Hash input = MISC::GET_HASH_KEY(t_input);
  int promptid = HUD::_UI_PROMPT_REGISTER_BEGIN();
  HUD::_UI_PROMPT_SET_TYPE(promptid, 0);
  HUD::_UI_PROMPT_SET_TEXT(promptid, MISC::VAR_STRING(10, "LITERAL_STRING", t_text));
  HUD::_UI_PROMPT_CONTEXT_SET_SIZE(promptid, 30);
  HUD::_UI_PROMPT_SET_CONTROL_ACTION(promptid, input);

  switch (t_mode) {
  case EMode::indefinitely_mode:
    HUD::_UI_PROMPT_SET_HOLD_INDEFINITELY_MODE(promptid);
    break;

  case EMode::hold_mode:
    HUD::_UI_PROMPT_SET_HOLD_MODE(promptid, t_timer);
    break;

  case EMode::mash_mode_indefinitely_mode:
    HUD::_UI_PROMPT_SET_MASH_INDEFINITELY_MODE(promptid);
    break;

  case EMode::standard_mode:
    HUD::_UI_PROMPT_SET_STANDARD_MODE(promptid, 0);
    break;

  default:
    HUD::_UI_PROMPT_SET_HOLD_INDEFINITELY_MODE(promptid);
    break;
  }
  HUD::_UI_PROMPT_REGISTER_END(promptid);
  HUD::_0x53CE46C01A089DA1(promptid, 1);
  HUD::_UI_PROMPT_SET_ENABLED(promptid, t_enabled);
  HUD::_UI_PROMPT_SET_VISIBLE(promptid, t_visible);

  if (!HUD::_UI_PROMPT_IS_VALID(promptid)) {
    Log::getInstance()->log(Log::Error, "Could not create the prompt!");
    _ASSERT(!HUD::_UIPROMPT_IS_VALid(promptid));
  }
  sPrompt* _prompt = new sPrompt();
  _prompt->id = promptid;
  _prompt->tag = t_tag;
  Promptlist.push_back(_prompt);
}

void Prompts::DeletePrompt(char * t_tag) {
  for (int i = 0; i < Promptlist.size(); i++) {
    if (Promptlist[i]->tag == t_tag) {
      HUD::_UI_PROMPT_DELETE(Promptlist[i]->id);
      Promptlist.erase(Promptlist.begin() + i);
    }
  }
  Promptlist.shrink_to_fit();
}

void Prompts::HidePrompt(char * t_tag) {
  for (int i = 0; i < Promptlist.size(); i++) {
    if (Promptlist[i]->tag == t_tag) {
      HUD::_UI_PROMPT_SET_ENABLED(Promptlist[i]->id, false);
      HUD::_UI_PROMPT_SET_VISIBLE(Promptlist[i]->id, false);
    }
  }
}

void Prompts::ShowPrompt(char * t_tag) {
  for (int i = 0; i < Promptlist.size(); i++) {
    if (Promptlist[i]->tag == t_tag) {
      HUD::_UI_PROMPT_SET_ENABLED(Promptlist[i]->id, true);
      HUD::_UI_PROMPT_SET_VISIBLE(Promptlist[i]->id, true);
    }
  }
}

void Prompts::DisablePrompt(char * t_tag) {
  for (int i = 0; i < Promptlist.size(); i++) {
    if (Promptlist[i]->tag == t_tag) {
      HUD::_UI_PROMPT_SET_ENABLED(Promptlist[i]->id, false);
    }
  }
}

void Prompts::EnablePrompt(char * t_tag) {
  for (int i = 0; i < Promptlist.size(); i++) {
    if (Promptlist[i]->tag == t_tag) {
      HUD::_UI_PROMPT_SET_ENABLED(Promptlist[i]->id, true);
    }
  }
}

bool Prompts::DoPromptExist(char * t_tag) {
  for (auto &prompt : Prompts::getInstance()->Promptlist) {
    if (prompt->tag == t_tag) {
      return true;
    }
  }
  return false;
}

bool Prompts::IsPromptValid(char * t_tag) {
  for (int i = 0; i < Promptlist.size(); i++) {
    if (Promptlist[i]->tag == t_tag) {
      return HUD::_UI_PROMPT_IS_VALID(Promptlist[i]->id);
    }
  }
  return false;
}

// Just an ugly way of setting up the placing prompts...
void Prompts::SetPlacingPrompts() {
  this->HidePrompt("SelectObject");
  this->HidePrompt("DeleteObject");
  this->ShowPrompt("Rotate_left");
  this->ShowPrompt("Rotate_right");
  this->ShowPrompt("Place");
  this->ShowPrompt("Quick_Place");
}

bool Prompts::IsPromptBeingPressed(char* t_tag) {
  for (int i = 0; i < Promptlist.size(); i++) {
    if (Promptlist[i]->tag == t_tag) {
      return HUD::_UI_PROMPT_IS_PRESSED(Promptlist[i]->id);
    }
  }
  return false;
}

// Used to optimize and clean up editor update loop make sure we get the mode type this can be used as an async
bool Prompts::IsPromptCompleted(char* t_tag, EMode mode) {
  for (auto &prompt : Prompts::getInstance()->Promptlist) {
    switch (mode) {
    case Prompts::indefinitely_mode:
      HUD::_UI_PROMPT_IS_HOLD_MODE_RUNNING(prompt->id);
      break;
    case Prompts::hold_mode:
      if (prompt->tag == t_tag && HUD::_UI_PROMPT_HAS_HOLD_MODE_COMPLETED(prompt->id)) {
        return true;
      }
      break;
    case Prompts::hold_mode_running:
      if (prompt->tag == t_tag && HUD::_UI_PROMPT_IS_HOLD_MODE_RUNNING(prompt->id)) {
        return true;
      }
      break;
    case Prompts::mash_mode_indefinitely_mode:
      break;
    case Prompts::standard_mode:
   //   HUD::_UI_PROMPT_HAS_STANDARD_MODE_COMPLETED(prompt->id);
      break;
    default:
      break;
    }
  }
  return false;
}

// Used by scripting engine.
bool Prompts::ChaiIsPromptCompleted(std::string str, EMode mode) {
  char *t_tag = &str[0];
  for (auto &prompt : Prompts::getInstance()->Promptlist) {
    switch (mode) {
    case Prompts::indefinitely_mode:
      HUD::_UI_PROMPT_IS_HOLD_MODE_RUNNING(prompt->id);
      break;
    case Prompts::hold_mode:
      if (prompt->tag == t_tag && HUD::_UI_PROMPT_HAS_HOLD_MODE_COMPLETED(prompt->id)) {
        return true;
      }
      break;
    case Prompts::hold_mode_running:
      if (prompt->tag == t_tag && HUD::_UI_PROMPT_IS_HOLD_MODE_RUNNING(prompt->id)) {
        return true;
      }
      break;
    case Prompts::mash_mode_indefinitely_mode:
      break;
    case Prompts::standard_mode:
     // HUD::_UI_PROMPT_HAS_STANDARD_MODE_COMPLETED(prompt->id);
      break;
    default:
      break;
    }
  }
  return false;
}
