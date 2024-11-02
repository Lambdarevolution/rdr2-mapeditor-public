/*
| License: Unlicense
| Created by: Lambdarevolution(at)gmail.com
| Description: Editor constraints.
*/
#ifndef EDITOR_CONSTRAINTS_H
#define EDITOR_CONSTRAINTS_H

#include <cstdint>

class  EditorConstraints {
  std::uint16_t mPeds;
  std::uint16_t mLights;
  std::uint16_t mVehicles;
  std::uint16_t mObjects;
  std::uint16_t mComposites;

public:
  EditorConstraints() {
    mPeds = 50;
    mLights = 5;
    mVehicles = 10;
    mObjects = 500;
    mComposites = 5;
  }

  EditorConstraints(const std::uint16_t peds, const std::uint16_t lights, const std::uint16_t vehicles, const std::uint16_t objects, const std::uint16_t composites) {
    mPeds = peds;
    mLights = lights;
    mVehicles = vehicles;
    mObjects = objects;
    mComposites = composites;
  }

  void SetMaxPedCount(const std::uint16_t amount) {
    mPeds = amount;
  }

  void SetMaxLightCount(const std::uint16_t amount) {
    mLights = amount;
  }

  void SetMaxVehiclesCount(const std::uint16_t amount) {
    mVehicles = amount;
  }

  void SetMaxObjectsCount(const std::uint16_t amount) {
    mObjects = amount;
  }

  void SetMaxCompositeCount(const std::uint16_t amount) {
    mComposites = amount;
  }

  std::uint16_t GetMaxPedCount() const {
    return mPeds;
  }

  std::uint16_t GetMaxLightCount() const {
    return mLights;
  }

  std::uint16_t GetMaxVehicleCount() const {
    return mVehicles;
  }

  std::uint16_t GetMaxObjectsCount() const {
    return mObjects;
  }

  std::uint16_t GetMaxCompositeCount() const {
    return mComposites;
  }
};

#endif
