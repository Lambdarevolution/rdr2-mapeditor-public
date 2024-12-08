#include "Prompts.h"
#include "Log.h"

Prompts* Prompts::mInstance = 0;

Prompts* Prompts::getInstance() {
  if (mInstance == 0) {
    mInstance = new Prompts();
  }
  return mInstance;
}
// We could overload this for the different modes but...., passing 0 on timer and mashes is fine for our purpose.
void Prompts::CreatePrompt(char* p_input, char* text, EMode mode, bool enabled, bool visible, char* tag, int timer, int mashes) {
  Hash input = GAMEPLAY::GET_HASH_KEY(p_input);
  const int promptid = UI::_0x04F97DE45A519419();
  UI::_0xF4A5C4509BF923B1(promptid, 0);
  UI::_0x5DD02A8318420DD7(promptid, (char*)GAMEPLAY::VAR_STRING(10, "LITERAL_STRING", text)); // Note the cast.
  UI::_0x0C718001B77CA468(promptid, 30.0f);
  UI::_0xB5352B7494A08258(promptid, input);

  switch (mode) {
  case EMode::indefinitely_mode:
    UI::_0xEA5CCF4EEB2F82D1(promptid);
    break;

  case EMode::hold_mode:
    UI::_0x94073D5CA3F16B7B(promptid, timer);
    break;

  case EMode::mash_mode_indefinitely_mode:
    UI::_0x7B66E89312727274(promptid);
    break;

  case EMode::mash_mode:
    UI::_0xDF6423BF071C7F71(promptid, mashes);
    break;

  case EMode::standard_mode:
    UI::_0xCC6656799977741B(promptid, 0);
    break;

  case EMode::pressed_timed_mode:
    UI::_0x1473D3AF51D54276(promptid, timer);
    break;

  default:
    UI::_0xEA5CCF4EEB2F82D1(promptid);
    break;
  }

  UI::_0xF7AA2696A22AD8B9(promptid);
  UI::_0x53CE46C01A089DA1(promptid, 1);
  UI::_0x8A0FB4D03A630D21(promptid, enabled);
  UI::_0x71215ACCFDE075EE(promptid, visible);

  if (!UI::_0x347469FBDD1589A9(promptid)) {
    Log::GetInstance()->AddToLog(
      Log::logLevel::Error,
      "CreatePrompt() failed to generate an valid prompt with tag:%s",
      std::string(tag)
    );
    _ASSERT(!UI::_0x347469FBDD1589A9(promptid));
    return;
  }
  // Store this prompt.
  PromptInstance* _prompt = new PromptInstance();
  _prompt->mId = promptid;
  _prompt->mTag = tag;
  _prompt->mMode = mode;
  mPromptList.push_back(_prompt);
}

void Prompts::DeletePrompt(char* tag) {
  for (int i = 0; i < mPromptList.size(); i++) {
    if (mPromptList[i]->mTag == tag) {
      UI::_0x00EDE88D4D13CF59(mPromptList[i]->mId);
      delete mPromptList[i];
      mPromptList.erase(mPromptList.begin() + i);
    }
  }
  mPromptList.shrink_to_fit();
}

void Prompts::HidePrompt(char* tag) {
  for (int i = 0; i < mPromptList.size(); i++) {
    if (mPromptList[i]->mTag == tag) {
      UI::_0x8A0FB4D03A630D21(mPromptList[i]->mId, false);
      UI::_0x71215ACCFDE075EE(mPromptList[i]->mId, false);
      return;
    }
  }
  Log::GetInstance()->AddToLog(
    Log::logLevel::Warning,
    "HidePrompt() failed to find an prompt with the tag:%s",
    std::string(tag)
  );
}

void Prompts::ShowPrompt(char* tag) {
  for (int i = 0; i < mPromptList.size(); i++) {
    if (mPromptList[i]->mTag == tag) {
      UI::_0x8A0FB4D03A630D21(mPromptList[i]->mId, true);
      UI::_0x71215ACCFDE075EE(mPromptList[i]->mId, true);
      return;
    }
  }
  Log::GetInstance()->AddToLog(
    Log::logLevel::Warning,
    "ShowPrompt() failed to find an prompt with the tag:%s",
    std::string(tag)
  );
}

void Prompts::DisablePrompt(char* tag) {
  for (int i = 0; i < mPromptList.size(); i++) {
    if (mPromptList[i]->mTag == tag) {
      UI::_0x8A0FB4D03A630D21(mPromptList[i]->mId, false);
      return;
    }
  }
  Log::GetInstance()->AddToLog(
    Log::logLevel::Warning,
    "DisablePrompt() failed to find an prompt with the tag:%s",
    std::string(tag)
  );
}

void Prompts::EnablePrompt(char* tag) {
  for (int i = 0; i < mPromptList.size(); i++) {
    if (mPromptList[i]->mTag == tag) {
      UI::_0x8A0FB4D03A630D21(mPromptList[i]->mId, true);
      return;
    }
  }
  Log::GetInstance()->AddToLog(
    Log::logLevel::Warning,
    "EnablePrompt() failed to find an prompt with the tag:%s",
    std::string(tag)
  );
}

bool Prompts::DoPromptExist(char* tag) {
  for (auto& prompt : Prompts::getInstance()->mPromptList) {
    if (prompt->mTag == tag) {
      return true;
    }
  }
  return false;
}

bool Prompts::IsPromptValid(char* tag) {
  for (int i = 0; i < mPromptList.size(); i++) {
    if (mPromptList[i]->mTag == tag) {
      return UI::_0x347469FBDD1589A9(mPromptList[i]->mId);
    }
  }
  Log::GetInstance()->AddToLog(
    Log::logLevel::Warning,
    "IsPromptValid() failed to find an prompt with the tag:%s",
    std::string(tag)
  );
  return false;
}

void Prompts::SetPromptAttribute(char* tag, int attribute, bool enable) {
  for (int i = 0; i < mPromptList.size(); i++) {
    if (mPromptList[i]->mTag == tag) {
      UI::_0x560E76D5E2E1803F(mPromptList[i]->mId, attribute, enable);
      return;
    }
  }
  Log::GetInstance()->AddToLog(
    Log::logLevel::Warning,
    "SetPromptAttribute() failed to find an prompt with the tag:%s",
    std::string(tag)
  );
}

void Prompts::SetPromptText(char* tag, const char* txt) {
  for (int i = 0; i < mPromptList.size(); i++) {
    if (mPromptList[i]->mTag == tag) {
      UI::_0x5DD02A8318420DD7(mPromptList[i]->mId, (char*)GAMEPLAY::VAR_STRING(10, "LITERAL_STRING", txt));
      return;
    }
  }
  Log::GetInstance()->AddToLog(
    Log::logLevel::Warning,
    "SetPromptText() failed to find an prompt with the tag:%s",
    std::string(tag)
  );
}

void Prompts::SetPriority(char* tag, int priority) {
  for (int i = 0; i < mPromptList.size(); i++) {
    if (mPromptList[i]->mTag == tag) {
      UI::_0xCA24F528D0D16289(mPromptList[i]->mId, priority);
    }
  }
}

float Prompts::GetPromptProgress(char* tag) {
  for (int i = 0; i < mPromptList.size(); i++) {
    if (mPromptList[i]->mTag == tag) {
      return (float)UI::_0x81801291806DBC50(mPromptList[i]->mId);
    }
  }
  Log::GetInstance()->AddToLog(
    Log::logLevel::Warning,
    "GetPromptProgress() failed to find an prompt with the tag:%s",
    std::string(tag)
  );
  return 0.0f;
}

void Prompts::SetHorizontalOrientation() {
  mHorizontalId = UI::_0xD9459157EB22C895();
}

void Prompts::ResetHorizontalOrientation() const {
  UI::_0x6095358C4142932A(mHorizontalId);
}

bool Prompts::IsPromptBeingPressed(char* tag) {
  for (int i = 0; i < mPromptList.size(); i++) {
    if (mPromptList[i]->mTag == tag) {
      return UI::_0x21E60E230086697F(mPromptList[i]->mId);
    }
  }
  Log::GetInstance()->AddToLog(
    Log::logLevel::Warning,
    "IsPromptBeingPressed() failed to find an prompt with the tag:%s",
    std::string(tag)
  );
  return false;
}

bool Prompts::IsPromptJustReleased(char* tag) {
  for (int i = 0; i < mPromptList.size(); i++) {
    if (mPromptList[i]->mTag == tag) {
      return UI::_0x635CC82FA297A827(mPromptList[i]->mId);
    }
  }
  Log::GetInstance()->AddToLog(
    Log::logLevel::Warning,
    "IsPromptJustReleased() failed to find an prompt with the tag:%s",
    std::string(tag)
  );
  return false;
}


bool Prompts::IsPromptEnabled(char* tag) {
  for (int i = 0; i < mPromptList.size(); i++) {
    if (mPromptList[i]->mTag == tag) {
      return UI::_0x0D00EDDFB58B7F28(mPromptList[i]->mId);
    }
  }
  Log::GetInstance()->AddToLog(
    Log::logLevel::Warning,
    "IsPromptEnabled() failed to find an prompt with the tag:%s",
    std::string(tag)
  );
  return false;
}

bool Prompts::IsPromptCompleted(char* tag) {
  for (int i = 0; i < mPromptList.size(); i++) {
    if (mPromptList[i]->mTag == tag) {
      switch (mPromptList[i]->mMode) {
      case Prompts::indefinitely_mode:
        return UI::_0xC7D70EAEF92EFF48(mPromptList[i]->mId);
        break;
      case Prompts::hold_mode:
        return UI::_0xE0F65F0640EF0617(mPromptList[i]->mId);
        break;
      case Prompts::hold_mode_running:
        return UI::_0xC7D70EAEF92EFF48(mPromptList[i]->mId);
        break;
      case Prompts::mash_mode:
        return UI::_0x845CE958416DC473(mPromptList[i]->mId);
        break;
      case Prompts::mash_mode_indefinitely_mode:
        return false;
        break;
      case Prompts::pressed_timed_mode:
        return UI::_0x3CE854D250A88DAF(mPromptList[i]->mId);
        break;
      case Prompts::standard_mode:
        return UI::_0xC92AC953F0A982AE(mPromptList[i]->mId, 0);
        break;
      default:
        return UI::_0xC92AC953F0A982AE(mPromptList[i]->mId, 0);
        break;
      }
    }
  }

  Log::GetInstance()->AddToLog(
    Log::logLevel::Warning,
    "IsPromptCompleted() failed to find an prompt with the tag:%s",
    std::string(tag)
  );

  return false;
}

void Prompts::DeleteAllEditorPrompts() {
  for (int i = 0; i < mPromptList.size(); i++) {
    UI::_0x00EDE88D4D13CF59(mPromptList[i]->mId);
    delete mPromptList[i];
  }
  mPromptList.clear();
}


