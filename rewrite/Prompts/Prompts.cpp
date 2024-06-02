#include "Prompts.h"
#include "Log.h"

Prompts* Prompts::m_instance = 0;

Prompts* Prompts::getInstance() {
  if (m_instance == 0) {
    m_instance = new Prompts();
  }
  return m_instance;
}
// We could overload this for the different modes but...., passing 0 on timer and mashes is fine for our purpose.
void Prompts::CreatePrompt(char* t_input, char* t_text, EMode t_mode, bool t_enabled, bool t_visible, char* t_tag, int t_timer, int t_mashes) {
  Hash input = GAMEPLAY::GET_HASH_KEY(t_input);
  const int promptid = UI::_0x04F97DE45A519419();
  UI::_0xF4A5C4509BF923B1(promptid, 0); 
  UI::_0x5DD02A8318420DD7(promptid, (char*)GAMEPLAY::VAR_STRING(10, "LITERAL_STRING", t_text)); // Note the cast.
  UI::_0x0C718001B77CA468(promptid, 30.0f);
  UI::_0xB5352B7494A08258(promptid, input);

  switch (t_mode) {
  case EMode::indefinitely_mode:
    UI::_0xEA5CCF4EEB2F82D1(promptid);
    break;

  case EMode::hold_mode:
    UI::_0x94073D5CA3F16B7B(promptid, t_timer);
    break;

  case EMode::mash_mode_indefinitely_mode:
    UI::_0x7B66E89312727274(promptid);
    break;

  case EMode::mash_mode:
    UI::_0xDF6423BF071C7F71(promptid, t_mashes);
    break;

  case EMode::standard_mode:
    UI::_0xCC6656799977741B(promptid, 0);
    break;

  case EMode::pressed_timed_mode:
    UI::_0x1473D3AF51D54276(promptid, t_timer);
    break;

  default:
    UI::_0xEA5CCF4EEB2F82D1(promptid);
    break;
  }

  UI::_0xF7AA2696A22AD8B9(promptid);
  UI::_0x53CE46C01A089DA1(promptid, 1);
  UI::_0x8A0FB4D03A630D21(promptid, t_enabled);
  UI::_0x71215ACCFDE075EE(promptid, t_visible);

  if (!UI::_0x347469FBDD1589A9(promptid)) {
    Log::GetInstance()->AddToLog(
      Log::logLevel::Error,
      "CreatePrompt() failed to generate an valid prompt with tag:%s",
      std::string(t_tag)
    );
    _ASSERT(!UI::_0x347469FBDD1589A9(promptid));
    return;
  }
  // Store this prompt.
  sPrompt* _prompt = new sPrompt();
  _prompt->id = promptid;
  _prompt->tag = t_tag;
  Promptlist.push_back(_prompt);  
}

void Prompts::DeletePrompt(char* t_tag) {
  for (int i = 0; i < Promptlist.size(); i++) {
    if (Promptlist[i]->tag == t_tag) {
      UI::_0x00EDE88D4D13CF59 (Promptlist[i]->id);
      Promptlist.erase(Promptlist.begin() + i);
    }
  }
  Promptlist.shrink_to_fit();
}

void Prompts::HidePrompt(char* t_tag) {
  for (int i = 0; i < Promptlist.size(); i++) {
    if (Promptlist[i]->tag == t_tag) {
      UI::_0x8A0FB4D03A630D21 (Promptlist[i]->id, false);
      UI::_0x71215ACCFDE075EE(Promptlist[i]->id, false);
      return;
    }
  }
  Log::GetInstance()->AddToLog(
    Log::logLevel::Warning,
    "HidePrompt() failed to find an prompt with the tag:%s",
    std::string(t_tag)
  );
}

void Prompts::ShowPrompt(char* t_tag) {
  for (int i = 0; i < Promptlist.size(); i++) {
    if (Promptlist[i]->tag == t_tag) {
      UI::_0x8A0FB4D03A630D21(Promptlist[i]->id, true);
      UI::_0x71215ACCFDE075EE(Promptlist[i]->id, true);
      return;
    }
  }
  Log::GetInstance()->AddToLog(
    Log::logLevel::Warning,
    "ShowPrompt() failed to find an prompt with the tag:%s",
    std::string(t_tag)
  );
}

void Prompts::DisablePrompt(char* t_tag) {
  for (int i = 0; i < Promptlist.size(); i++) {
    if (Promptlist[i]->tag == t_tag) {
      UI::_0x8A0FB4D03A630D21(Promptlist[i]->id, false);
      return;
    }
  }
  Log::GetInstance()->AddToLog(
    Log::logLevel::Warning,
    "DisablePrompt() failed to find an prompt with the tag:%s",
    std::string(t_tag)
  );
}

void Prompts::EnablePrompt(char* t_tag) {
  for (int i = 0; i < Promptlist.size(); i++) {
    if (Promptlist[i]->tag == t_tag) {
      UI::_0x8A0FB4D03A630D21(Promptlist[i]->id, true);
      return;
    }
  }
  Log::GetInstance()->AddToLog(
    Log::logLevel::Warning,
    "EnablePrompt() failed to find an prompt with the tag:%s",
    std::string(t_tag)
  );
}

bool Prompts::DoPromptExist(char* t_tag) {
  for (auto& prompt : Prompts::getInstance()->Promptlist) {
    if (prompt->tag == t_tag) {
      return true;
    }
  }
  return false;
}

bool Prompts::IsPromptValid(char* t_tag) {
  for (int i = 0; i < Promptlist.size(); i++) {
    if (Promptlist[i]->tag == t_tag) {
      return UI::_0x347469FBDD1589A9(Promptlist[i]->id);
    }
  }
  Log::GetInstance()->AddToLog(
    Log::logLevel::Warning,
    "IsPromptValid() failed to find an prompt with the tag:%s",
    std::string(t_tag)
  );
  return false;
}

void Prompts::SetPromptAttribute(char* t_tag, int t_attribute, bool t_enable) {
  for (int i = 0; i < Promptlist.size(); i++) {
    if (Promptlist[i]->tag == t_tag) {
      UI::_0x560E76D5E2E1803F(Promptlist[i]->id, t_attribute, t_enable);
      return;
    }
  }
  Log::GetInstance()->AddToLog(
    Log::logLevel::Warning,
    "SetPromptAttribute() failed to find an prompt with the tag:%s",
    std::string(t_tag)
  );
}

void Prompts::SetPromptText(char* t_tag, const char* t_txt) {
  for (int i = 0; i < Promptlist.size(); i++) {
    if (Promptlist[i]->tag == t_tag) {
      UI::_0x5DD02A8318420DD7(Promptlist[i]->id, (char*)GAMEPLAY::VAR_STRING(10, "LITERAL_STRING", t_txt));
      return;
    }
  }
  Log::GetInstance()->AddToLog(
    Log::logLevel::Warning,
    "SetPromptText() failed to find an prompt with the tag:%s",
    std::string(t_tag)
  );
}

void Prompts::SetPriority(char* t_tag, int t_priority) {
  for (int i = 0; i < Promptlist.size(); i++) {
    if (Promptlist[i]->tag == t_tag) {
      UI::_0xCA24F528D0D16289(Promptlist[i]->id, t_priority);
    }
  }
}

float Prompts::GetPromptProgress(char* t_tag) {
  for (int i = 0; i < Promptlist.size(); i++) {
    if (Promptlist[i]->tag == t_tag) {
      return (float)UI::_0x81801291806DBC50(Promptlist[i]->id);
    }
  }
  Log::GetInstance()->AddToLog(
    Log::logLevel::Warning,
    "GetPromptProgress() failed to find an prompt with the tag:%s",
    std::string(t_tag)
  );
  return 0.0f;
}  

void Prompts::SetHorizontalOrientation() {
  this->m_horizontalid = UI::_0xD9459157EB22C895();
}

void Prompts::ResetHorizontalOrientation() {
  UI::_0x6095358C4142932A(this->m_horizontalid);
}

bool Prompts::IsPromptBeingPressed(char* t_tag) {
  for (int i = 0; i < Promptlist.size(); i++) {
    if (Promptlist[i]->tag == t_tag) {
      return UI::_0x21E60E230086697F(Promptlist[i]->id);
    }
  }
  Log::GetInstance()->AddToLog(
    Log::logLevel::Warning,
    "IsPromptBeingPressed() failed to find an prompt with the tag:%s",
    std::string(t_tag)
  );
  return false;
}

bool Prompts::IsPromptJustReleased(char* t_tag) {
  for (int i = 0; i < Promptlist.size(); i++) {
    if (Promptlist[i]->tag == t_tag) {
      return UI::_0x635CC82FA297A827(Promptlist[i]->id);
    }
  }
  Log::GetInstance()->AddToLog(
    Log::logLevel::Warning,
    "IsPromptJustReleased() failed to find an prompt with the tag:%s",
    std::string(t_tag)
  );
  return false;
}


bool Prompts::IsPromptEnabled(char* t_tag) {
  for (int i = 0; i < Promptlist.size(); i++) {
    if (Promptlist[i]->tag == t_tag) {
      return UI::_0x0D00EDDFB58B7F28(Promptlist[i]->id);
    }
  }
  Log::GetInstance()->AddToLog(
    Log::logLevel::Warning, 
    "IsPromptEnabled() failed to find an prompt with the tag:%s", 
    std::string(t_tag)
  );
  return false;
}

bool Prompts::IsPromptCompleted(char* t_tag, EMode mode) {
  for (auto& prompt : Prompts::getInstance()->Promptlist) {
    if (prompt->tag == t_tag) {
      switch (mode) {
      case Prompts::indefinitely_mode:
        return UI::_0xC7D70EAEF92EFF48(prompt->id);
        break;
      case Prompts::hold_mode:
        return UI::_0xE0F65F0640EF0617(prompt->id);
        break;
      case Prompts::hold_mode_running:
        return UI::_0xC7D70EAEF92EFF48(prompt->id);
        break;
      case Prompts::mash_mode:
        return UI::_0x845CE958416DC473(prompt->id);
        break;
      case Prompts::mash_mode_indefinitely_mode:
        return false;
        break;
      case Prompts::pressed_timed_mode:
        return UI::_0x3CE854D250A88DAF(prompt->id);
        break;
      case Prompts::standard_mode:
        return UI::_0xC92AC953F0A982AE(prompt->id, 0);
        break;
      default:
        return UI::_0xC92AC953F0A982AE(prompt->id, 0);
        break;
      }
    }
    Log::GetInstance()->AddToLog(
      Log::logLevel::Warning,
      "IsPromptCompleted() failed to find an prompt with the tag:%s",
      std::string(t_tag)
    );
  }
  return false;
}

void Prompts::DeleteAllEditorPrompts() {
  for (int i = 0; i < this->Promptlist.size(); i++) {
    UI::_0x00EDE88D4D13CF59(this->Promptlist[i]->id);
    delete this->Promptlist[i];
  }
  this->Promptlist.clear();
}
