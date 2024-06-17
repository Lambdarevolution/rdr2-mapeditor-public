/*
| License: Unlicense.
| Description: Used to save player information so we can restore the player state when exiting the editor.
| This used to be defined in the editor but is now in it's own struct.
| Created by Lambdarevolution(at)gmail.com 2024
*/
#ifndef PLAYER_H
#define PLAYER_H

#include "..\..\inc\types.h"

struct PlayerInfo {
  PlayerInfo();
  ~PlayerInfo();

  void ResetPlayer() const;

  Vector3 m_player_position;
  Vector3 m_mount_position;
  Entity m_mount_ped;
  bool m_on_mount;
  Hash m_weapon;
};

#endif  // PLAYER_H
