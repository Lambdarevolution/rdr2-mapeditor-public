/*
| License: Unlicense
| Created by: Lambdarevolution(at)gmail.com
| Description: Saving
*/
#ifndef SAVEMAP_H
#define SAVEMAP_H

#include "../../inc/natives.h"
#include "../../inc/types.h"
#include "Editor.h"

namespace SaveManager {

  bool SaveAsXml(char* savename);
  bool ExportFinal(char* savename);
  bool ExportYmap(char* savename);

};
#endif
