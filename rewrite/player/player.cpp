#include "..\..\inc\natives.h"

#include "Player.h"

PlayerInfo::PlayerInfo() {
  if (PED::IS_PED_ON_MOUNT(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()))) {
    Hash lWeaponHash;
    this->m_on_mount = true;
    this->m_mount_ped = PED::GET_MOUNT(PLAYER::PLAYER_PED_ID());
    this->m_mount_position = ENTITY::GET_ENTITY_COORDS(this->m_mount_ped, false, true);
    this->m_player_position = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false, true);
    // Weapon.
    WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), &lWeaponHash, 0, 0, 0);
    this->m_weapon = lWeaponHash;

    // Remove ped from mount.
    // Not removing the ped can cause issues its safer to remount on exit.
    PED::_0x5337B721C51883A9(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), 1, 1);

  } else {
    Hash lWeaponHash;
    this->m_on_mount = false;
    this->m_player_position = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false, true);
    // Weapon.
    WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &lWeaponHash, 0, 0, 0);
    this->m_weapon = lWeaponHash;
  }
}

PlayerInfo::~PlayerInfo() {

}

void PlayerInfo::ResetPlayer() const {
  ENTITY::SET_ENTITY_COORDS(
   PLAYER::PLAYER_PED_ID(),
   m_player_position.x,
   m_player_position.y,
   (m_player_position.z + 0.05f) - (PED::_0x1D491CCF7211FB74(PLAYER::PLAYER_PED_ID()) / 2),
   0,
   0,
   1,
   false
  );

  WEAPON::SET_CURRENT_PED_WEAPON( 
   PLAYER::PLAYER_PED_ID(),
   m_weapon,
   1,
   0,
   0,
   0
  );

  if (m_on_mount) {
  ENTITY::SET_ENTITY_COORDS(
   m_mount_ped,
   m_mount_position.x,
   m_mount_position.y,
   m_mount_position.z,
   0,
   0,
   1,
   false
  );

   ENTITY::SET_ENTITY_COLLISION(m_mount_ped, true, true);
   ENTITY::SET_ENTITY_VISIBLE(m_mount_ped, true);
   PED::_0x028F76B6E78246EB(PLAYER::PLAYER_PED_ID(), m_mount_ped, -1, 0);
  }

  PLAYER::SET_EVERYONE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), false);
  ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true);
  ENTITY::SET_ENTITY_COLLISION(PLAYER::PLAYER_PED_ID(), true, true);
  PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), false);
}

