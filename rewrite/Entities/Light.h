/*
| License: Unlicense
| Created by: Lambdarevolution(at)gmail.com
| Rewritten 2025. 
*/
#ifndef RDR2_MAPEDITOR_ENTITES_LIGHT_H
#define RDR2_MAPEDITOR_ENTITES_LIGHT_H

#include "Entity.h"

class Light : public EditorEntity {
private:
  int m_Red{ 255 };
  int m_Green{ 255 };
  int m_Blue{ 255 };
  float m_Range{ 10.0f };
  float m_Intensity{ 100.0f };

public:
  Light() {
  m_Red = 255;
  m_Green = 255;
  m_Blue = 255;
  m_Range = 10.0f;
  m_Intensity = 100.0f;
  SetId(std::rand() % 25000);
  SetPosition(Vector3(0.0f, 0.0f, 0.0f));
  SetCollision(false);
  SetGravity(false);
  SetIsDynamic(false);
  SetEntityType(EditorEntity::Type::light);
  SetRotation(Vector3(0.0f, 0.0f, 0.0f));
  }

  void Update() override {
    GRAPHICS::DRAW_LIGHT_WITH_RANGE(GetPosition().x, GetPosition().y, GetPosition().z, m_Red, m_Green, m_Blue, m_Range, m_Intensity);
  }

  void SetColor(const int t_red, const int t_green, const int t_blue) {
    m_Red = t_red, m_Green = t_green, m_Blue = t_blue;
  }

  void SetIntensity(const float t_intensity) {
    m_Intensity = t_intensity;
  }

  void SetRange(const float t_range) {
    m_Range = t_range;
  }

  float GetRange() const {
    return m_Range;
  }

  float GetIntensity() const {
    return m_Intensity;
  }

  int GetRedColor() const {
    return m_Red;
  }

  int GetGreenColor() const {
    return m_Green;
  }

  int GetBlueColor() const {
    return m_Blue;
  }

  void Clone(const Light& t_other_light) {
    SetColor(t_other_light.GetRedColor(), t_other_light.GetGreenColor(), t_other_light.GetBlueColor());
    SetIntensity(t_other_light.GetIntensity());
    SetRange(t_other_light.GetRange());
  }
};
#endif  // RDR2_MAPEDITOR_ENTITES_LIGHT_H
