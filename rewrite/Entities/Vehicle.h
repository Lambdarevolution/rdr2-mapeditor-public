/*
| License: Unlicense
| Created by: Lambdarevolution(at)gmail.com / 2020-12-20 / Rewritten 2025. 
| NOTES:
| - Some functions are still missing.
| - Decorators are now part of EditorEntity.
| - Reset and clone isnt implemented yet.
*/
#ifndef RDR2_MAPEDITOR_ENTITES_VEHICLE_H
#define RDR2_MAPEDITOR_ENTITES_VEHICLE_H

#include "Entity.h"
#include <vector>

class GameVehicle : public EditorEntity {

  float m_Dirt{ 0.0f };
  float m_Mud{ 0.0f };
  float m_Snow{ 0.0f };
  float m_WetLevel{ 0.0f };
  bool  m_Unbreakable{ false };
  bool m_Driveable{ true };
  bool m_Anchor{ false };
  bool m_InHurry{ false };
  bool m_Strong{ false };
  bool m_ProvidesCover{ true };
  bool m_UnbreakableLights{ false };
  bool m_TargetableVehicle{ false };
  bool m_VehicleCanBeUsedByFleeingPeds{ true };
  int m_VehicleLivery{ 0 };
  int m_VehicleTint{ 0 };
  int m_LightState{ 0 };
  float m_VehicleHealth{ 1000.0f };

  std::vector<Hash> m_LanterPropSets;
  std::vector<Hash> m_PropSets;

public:
  GameVehicle(const Hash t_hash, const Vector3 t_position, const Vector3 t_rotation) {
    if (STREAMING::IS_MODEL_IN_CDIMAGE(t_hash) && STREAMING::IS_MODEL_VALID(t_hash)) {
      STREAMING::REQUEST_MODEL(t_hash, FALSE);
      while (!STREAMING::HAS_MODEL_LOADED(t_hash)) {
        WAIT(1);
      }
    }
    else {
      Log::GetInstance()->AddToLog(Log::Error, "Model with dec hash [%i] seems to be invalid.", t_hash);
      return;
    }

    // Base properties
    SetId(-1);
    SetCollision(true);
    SetGravity(true);
    SetIsDynamic(true);
    SetEntityType(EditorEntity::Type::vehicle);
    SetPosition(t_position); 
    SetRotation(t_rotation);

    SetId(VEHICLE::CREATE_VEHICLE(t_hash, t_position.x, t_position.y, t_position.z, 0.0f, false, false, false, false));
    WAIT(1);
    if (!ENTITY::IS_AN_ENTITY(GetId())) {
      Log::GetInstance()->AddToLog(Log::Error, "Vehicle with dec hash [%i] did not return an valid entity id.", t_hash);
      return;
    }

    // Intialized values are mostly guessed, so if possible we updated them with correct values after creation. 
    m_VehicleHealth = VEHICLE::GET_VEHICLE_BODY_HEALTH(GetId());
    m_Driveable = VEHICLE::IS_VEHICLE_DRIVEABLE(GetId(), false, false);
    m_VehicleLivery = VEHICLE::_0xBB765B8FD49A796C(GetId());
    m_VehicleTint = VEHICLE::_0xA44D65E6C624526F(GetId());
  }

  ~GameVehicle() {}

  void SetDirtLevel(const float t_value) {
    m_Dirt = t_value;
    VEHICLE::SET_VEHICLE_DIRT_LEVEL(GetId(), t_value);
  }

  void SetMudLevel(const float t_value) {
    m_Mud = t_value;
    VEHICLE::_0x4D15E49764CB328A(GetId(), t_value);
  }

  void SetSnowLevel(const float t_snow_level) {
    m_Snow = t_snow_level;
    VEHICLE::_0x6F73EFAB11651D7F(GetId(), t_snow_level);
  }

  void SetDriveAble(const bool t_driveable) {
    m_Driveable = t_driveable;
    VEHICLE::SET_VEHICLE_UNDRIVEABLE(GetId(), t_driveable);
  }

  void SetWetLevel(const float t_wet_level) {
    m_WetLevel = t_wet_level;
    VEHICLE::_0x5AABB09F6FBD1F87(GetId(), t_wet_level);
  }

  void SetVehicleCanBeUsedByFleeingPeds(bool t_state) {
    m_VehicleCanBeUsedByFleeingPeds = t_state;
    VEHICLE::SET_VEHICLE_CAN_BE_USED_BY_FLEEING_PEDS(GetId(), t_state);
  }

  void LockDoorsForPlayer(bool t_lock) {
    VEHICLE::SET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(GetId(), PLAYER::GET_PLAYER_INDEX(), t_lock);
  }

  void SetBoatAnchor(bool t_anchor) {
    if (t_anchor && !VEHICLE::_GET_BOAT_ANCHOR(GetId())) {
        return;
    }
    m_Anchor = t_anchor;
    VEHICLE::SET_BOAT_ANCHOR(GetId(), t_anchor);
  }

  void SetVehicleFixed() const {
    VEHICLE::SET_VEHICLE_FIXED(GetId());
  }

  void SetVehicleInHurry(const bool t_hurry) {
    m_InHurry = t_hurry;
    VEHICLE::_0xCE1531927AD6C9F8(GetId(), t_hurry);
  }

  void SetVehicleStrong(const bool t_strong) {
    m_Strong = t_strong;
    VEHICLE::SET_VEHICLE_STRONG(GetId(), t_strong);
  }

  void SetVehicleGivesCover(const bool t_cover) {
    m_ProvidesCover = t_cover;
    VEHICLE::SET_VEHICLE_PROVIDES_COVER(GetId(), t_cover);
  }

  void SetVehicleHasUnbreakableLights(const bool t_unbreakable) {
    m_UnbreakableLights = t_unbreakable;
    VEHICLE::_0xC903855E028A05F2(GetId(), t_unbreakable);
  }

  void SetVehicleCanBeTargeted(const bool t_targetable) {
    m_TargetableVehicle = t_targetable;
    VEHICLE::SET_VEHICLE_CAN_BE_TARGETTED(GetId(), t_targetable);
  }

  void SetVehicleLivery(const int t_livery) {
    m_VehicleLivery = t_livery;
    VEHICLE::_0xF89D82A0582E46ED(GetId(), t_livery);
  }

  void SetVehicleTint(const int t_tint) {
    m_VehicleTint = t_tint;
    VEHICLE::_0x8268B098F6FCA4E2(GetId(), t_tint);
  }

  void SetVehicleLightState(const int t_light_state) {
    m_LightState = t_light_state;
    VEHICLE::SET_VEHICLE_LIGHTS(GetId(), t_light_state);
  }

  void SetVehicleLanternPropset(const Hash t_lantern_propset) {
    m_LanterPropSets.push_back(t_lantern_propset);
    PROP::_0xC0F0417A90402742(GetId(), t_lantern_propset);
  }

  void RemoveAllVehicleLanternPropset() {
    m_LanterPropSets.clear();
    PROP::_0xE31C0CB1C3186D40(GetId());
  }

  void SetVehiclePropset(const Hash t_propset) {
    m_PropSets.push_back(t_propset);
    PROP::_0x75F90E4051CC084C(GetId(), t_propset);
  }

  void RemoveAllVehiclePropset() {
    m_PropSets.clear();
    PROP::_0x75F90E4051CC084C(GetId(), 0);
  }

  void SetVehicleHealth(const float t_health) {
    m_VehicleHealth = t_health;
    VEHICLE::SET_VEHICLE_BODY_HEALTH(GetId(), t_health);
  }

  float GetVehicleHealth() const {
    VEHICLE::GET_VEHICLE_BODY_HEALTH(GetId());
  }

  float GetVehicleInHurry() const {
    return m_InHurry;
  }

  void SetVehicleWheelsCanBreak(const bool t_breakable) const {
    VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(GetId(), t_breakable);
  }

  void SetVehicleDriveable(const bool t_undrivable) {
    VEHICLE::SET_VEHICLE_UNDRIVEABLE(GetId(), t_undrivable);
    VEHICLE::SET_VEHICLE_DOORS_LOCKED_FOR_ALL_PLAYERS(GetId(), t_undrivable);
  }

  void Explode(const bool t_sound, const bool t_visible, const int t_unknown1, const int t_unknown2) {
    VEHICLE::EXPLODE_VEHICLE(GetId(), t_sound, t_visible, t_unknown1);
  }

  int BreakOfWheel(const int t_wheel) {
    return VEHICLE::_0xD4F5EFB55769D272(GetId(), t_wheel);
  }

  bool GetBoatAnchorState() const {
    return m_Anchor;
  }

  const float GetWetLevel() const {
    return m_WetLevel;
  }

  bool GetIsDriveable() const {
    return m_Driveable;
  }

  float GetSnowLevel() const {
    return m_Snow;
  }

  float GetDirtLevel() const {
    return m_Dirt;
  }

  float GetMudLevel() const {
    return m_Mud;
  }

  bool IsUnbreakable() const {
    return m_Unbreakable;
  }

  bool IsDrivable() const {
    return m_Driveable;
  }

  bool IsStrong() const {
    return m_Strong;
  }

  bool GivesCover() const {
    return m_ProvidesCover;
  }

  bool HasUnbreakableLight() const {
    return m_UnbreakableLights;
  }

  bool VehicleIsTargetable() const {
    return m_TargetableVehicle;
  }

  bool VehicleCanBeUsedByFleeingPeds() const {
    return m_VehicleCanBeUsedByFleeingPeds;
  }

  int GetVehicleLivery() const {
    return m_VehicleLivery;
  }

  int GetVehicleTint() const {
    return m_VehicleTint;
  }

  std::vector<Hash> GetVehicleLanternPropsets() const {
    return m_LanterPropSets;
  }

  std::vector<Hash> GetVehiclePropsets() const {
    return m_PropSets;
  }

  /*
  void Clone(const GameVehicle& t_other_vehicle) override{

  }

  void Reset() override {

  }
  */
};
#endif  // RDR2_MAPEDITOR_ENTITES_VEHICLE_H
