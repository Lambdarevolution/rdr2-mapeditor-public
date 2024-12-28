/*
| License: The Unlicense
| Created by: Lambdarevolution(at)gmail.com / 2020-04-01 - rewritten 2024-11-10
*/
#ifndef RDR2_MAPEDITOR_CAMERA_H
#define RDR2_MAPEDITOR_CAMERA_H

#include "..\..\..\inc\types.h"

class MapEditorCamera {
 public:
  MapEditorCamera();
  ~MapEditorCamera();
  Camera GetCamera() const;
  void SetCameraSpeed(const float speed);
  void SetCameraFov(const float fov);
  void SetCameraRaiseButton(char* input);
  void SetCameraLowerButton(char* input);
  float GetCameraSpeed() const;
  float GetCameraFov() const;
  void CreateCamera();
  void UpdateCamera(const bool blockinput);
  void ActivateCamera() const;
  void DeactivateCamera() const;
  void SetLetterBox(const bool state);
  bool HasLetterBoxEffect() const;
  Vector3 GetCameraRightVector() const;
  Vector3 GetCameraForwardVector() const;
  inline float Clamp(float value, const float min, const float max);

 private:
  bool mLetterBox;
  Camera mCamera;
  char* mRaiseCameraInput;
  char* mLowerCameraInput;
  float mBoostValue;
  float mCameraSpeed;
  float mFov;
};
#endif  // RDR2_MAPEDITOR_CAMERA_H
