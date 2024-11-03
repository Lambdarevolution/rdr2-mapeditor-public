/*
| License: Unlicense
| Created by: Lambdarevolution(at)gmail.com 
*/
#ifndef RDR2_MAPEDITOR_ENTITES_LIGHT_H
#define RDR2_MAPEDITOR_ENTITES_LIGHT_H

#include "Entity.h"

class Light : public EditorEntity {
private:
  int mRed = 255;
  int mGreen = 255;
  int mBlue = 255;
  float mRange = 10.0f;
  float mIntensity = 100.0f;

public:
  Light() {
    Vector3 lInitialPosition;
    lInitialPosition.x, lInitialPosition.y, lInitialPosition.z = 0.f;
    this->SetId(std::rand() % 25000); 
    this->mRed = 255;
    this->mGreen = 255;
    this->mBlue = 255;
    this->mRange = 10.f;
    this->mIntensity = 100.f;
    this->SetPosition(lInitialPosition);
    this->SetCollision(false);
    this->SetGravity(false);
    this->SetDynamic(false);
    this->SetEntityType(EditorEntity::Type::light);
    this->SetRotation(lInitialPosition); 
  }

  void SetColor(const int red, const int green, const int blue) { 
    this->mRed = red, this->mGreen = green, this->mBlue = blue; 
  }

  void SetIntensity(const float intensity) {
    this->mIntensity = intensity; 
  }

  void SetRange(const float value) { 
    this->mRange = value; 
  }

  float GetRange() const {
    return this->mRange; 
  }

  float GetIntensity() const {
    return this->mIntensity; 
  }

  int GetRedColor() const { 
    return this->mRed; 
  }

  int GetGreenColor() const {
    return this->mGreen; 
  }

  int GetBlueColor() const { 
    return this->mBlue;
  }

  void Clone(Light& other) {
    this->SetColor(other.GetRedColor(), other.GetGreenColor(), other.GetBlueColor());
    this->SetIntensity(other.GetIntensity());
    this->SetRange(other.GetRange());
  }
};
#endif  // RDR2_MAPEDITOR_ENTITES_LIGHT_H
