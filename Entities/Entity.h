/*
| License: The Unlicense
| Created by: Lambdarevolution(at)gmail.com / 2020-12-20
|
*/
#ifndef RDR2_MAPEDITOR_ENTITES_ENTITY_H_
#define RDR2_MAPEDITOR_ENTITES_ENTITY_H_

#include <string>
#include "..\inc\natives.h"
#include "..\inc\types.h"

// Class: entity
// A class that manages an entity
class entity {
public:
  enum Type {
    object,
    ped,
    light,
    vehicle,
    effect,
    pickup
  };

private:
  Vector3 position;
  Vector3 rotation;
  int  m_id;
  bool m_visible = true;
  bool m_collision = true;
  bool m_dynamic = true;
  bool m_gravity = true;
  bool m_freeze = false;
  bool m_invincible = false;
  int m_blip_id = 0;
  Hash m_blip_hash = 0;
  std::string m_tag = "";
  Type m_entitytype;

public:
  entity() : m_id(-1), m_visible(true), m_collision(true), m_gravity(true) { }
  ~entity() { }

  Vector3 GetPosition() { return this->position; }
  Vector3 GetRotation() { return this->rotation; }
  const bool Visible() { return this->m_visible; }
  const bool Collision() { return this->m_collision; }
  const bool Dynamic() { return this->m_dynamic; }
  const bool Gravity() { return this->m_gravity; }
  const bool Freeze() { return m_freeze;  }
  const bool IsScriptAttached() { return this->m_script_attached; }
  const bool IsInvincible() { return this->m_invincible; }
  const int GetId() { return this->m_id; }
  const std::string GetTag() { return this->m_tag; }
  const Type GetEntitytype() { return this->m_entitytype; }
  const int GetBlipHash() { return this->m_blip_hash; }

  // Setters
  void SetId(int id) { this->m_id = id; }
  void SetVisible(bool state) { this->m_visible = state; }
  void SetGravity(bool state) { this->m_gravity = state; }
  void SetEntityType(Type t_type) { this->m_entitytype = t_type; }
  void SetTag(std::string t_tag) { this->m_tag = t_tag; }

  virtual void Update() { }

  void SetFreeze(bool state) {
    this->m_freeze = state;
    if (ENTITY::IS_AN_ENTITY(this->m_id)) {
      ENTITY::FREEZE_ENTITY_POSITION(this->m_id, state);
    }
  }

  void SetDynamic(bool state) {
    this->m_dynamic = state;
    if (ENTITY::IS_AN_ENTITY(this->m_id)) {
      ENTITY::SET_ENTITY_DYNAMIC(this->m_id, state);
    }
  }

  void SetCollision(bool state) {
    this->m_collision = state;
    if (ENTITY::IS_AN_ENTITY(this->m_id)) {
      ENTITY::SET_ENTITY_COLLISION(this->m_id, state, true);
    }
  }

  void SetInvincible(bool state) {
    this->m_invincible = state;
    if (ENTITY::IS_AN_ENTITY(this->m_id)) {
      ENTITY::SET_ENTITY_INVINCIBLE(this->m_id, state);
    }
  }

  virtual void SetPosition(const Vector3 t_pos) {
    this->position = t_pos;
    if (ENTITY::IS_AN_ENTITY(this->m_id)) {
      ENTITY::SET_ENTITY_COORDS(this->m_id, t_pos.x, t_pos.y, t_pos.z, true, true, true, false);
    }
  }

  void SetHeading(const float heading) {
    if (ENTITY::IS_AN_ENTITY(this->m_id)) {
      ENTITY::SET_ENTITY_HEADING(this->m_id, ENTITY::GET_ENTITY_HEADING(this->m_id) + heading);  // Only used for placing.
    }
  }

  void SetRotation(const Vector3 t_rot) {
    this->rotation = t_rot;
    if (ENTITY::IS_AN_ENTITY(this->m_id)) {
      ENTITY::SET_ENTITY_ROTATION(this->m_id, t_rot.x, t_rot.y, t_rot.z, 0, true);
    }
  }
  
  void SetBlip(Hash t_value) {
    if (this->m_blip_id != NULL || this->m_blip_id != -1) {
      MAP::REMOVE_BLIP(&this->m_blip_id);
    }
    this->m_blip_hash = t_value;
    if (ENTITY::IS_AN_ENTITY(this->m_id)) {
      this->m_blip_id = MAP::_BLIP_ADD_FOR_ENTITY(t_value, this->GetId());
    } else {
      // This is not complete...
      this->m_blip_id = MAP::_BLIP_ADD_FOR_COORD(this->GetId(), this->position.x, this->position.y, this->position.z + 5.0f);
    }
  }
};
#endif  // RDR2_MAPEDITOR_ENTITES_ENTITY_H_
