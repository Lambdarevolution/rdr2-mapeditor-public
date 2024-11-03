#include "..\..\inc\natives.h"

#include "Player.h"

PlayerInfo::PlayerInfo() {
  if (PED::IS_PED_ON_MOUNT(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()))) {
    Hash lWeaponHash;
    this->mOnMount = true;
    this->mMountPed = PED::GET_MOUNT(PLAYER::PLAYER_PED_ID());
    this->mMountPosition = ENTITY::GET_ENTITY_COORDS(this->mMountPed, false, true);
    this->mPlayerPosition = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false, true);
    // Weapon.
    WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), &lWeaponHash, 0, 0, 0);
    this->mWeapon = lWeaponHash;

    // Remove ped from mount.
    // Not removing the ped can cause issues its safer to remount on exit.
    PED::_0x5337B721C51883A9(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), 1, 1);

  }
  else {
    Hash lWeaponHash;
    this->mOnMount = false;
    this->mPlayerPosition = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false, true);
    // Weapon.
    WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &lWeaponHash, 0, 0, 0);
    this->mWeapon = lWeaponHash;
  }
}

PlayerInfo::~PlayerInfo() {

}

void PlayerInfo::ResetPlayer() const {
  ENTITY::SET_ENTITY_COORDS(
   PLAYER::PLAYER_PED_ID(),
   mPlayerPosition.x,
    mPlayerPosition.y,
   (mPlayerPosition.z + 0.05f) - (PED::_0x1D491CCF7211FB74(PLAYER::PLAYER_PED_ID()) / 2),
   0,
   0,
   1,
   false
  );

  WEAPON::SET_CURRENT_PED_WEAPON( 
   PLAYER::PLAYER_PED_ID(),
   mWeapon,
   1,
   0,
   0,
   0
  );

  if (mOnMount) {
  ENTITY::SET_ENTITY_COORDS(
   mMountPed,
   mMountPosition.x,
   mMountPosition.y,
   mMountPosition.z,
   0,
   0,
   1,
   false
  );

   ENTITY::SET_ENTITY_COLLISION(mMountPed, true, true);
   ENTITY::SET_ENTITY_VISIBLE(mMountPed, true);
   PED::_0x028F76B6E78246EB(PLAYER::PLAYER_PED_ID(), mMountPed, -1, 0);
  }

  PLAYER::SET_EVERYONE_IGNORE_PLAYER(PLAYER::PLAYER_ID(), false);
  ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true);
  ENTITY::SET_ENTITY_COLLISION(PLAYER::PLAYER_PED_ID(), true, true);
  PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), false);
}

