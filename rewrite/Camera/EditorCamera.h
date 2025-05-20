/*
| License: The Unlicense
| Created by: Lambdarevolution(at)gmail.com 
| Rewritten: 2025
*/
#ifndef RDR2_MAPEDITOR_CAMERA_H
#define RDR2_MAPEDITOR_CAMERA_H

#include "..\..\..\inc\types.h"

class MapEditorCamera {
 public:
  MapEditorCamera();
  ~MapEditorCamera();
  Camera GetCamera() const;
  void SetCameraSpeed(const float t_speed);
  void SetCameraFov(const float t_fov);
  void SetCameraRaiseButton(char* t_input);
  void SetCameraLowerButton(char* t_input);
  float GetCameraSpeed() const;
  float GetCameraFov() const;
  void CreateCamera();
  void UpdateCamera(const bool t_blockinput);
  void ActivateCamera() const;
  void DeactivateCamera() const;
  void SetLetterBox(const bool t_state);
  bool HasLetterBoxEffect() const;
  Vector3 GetCameraRightVector() const;
  Vector3 GetCameraForwardVector() const;
  inline float Clamp(float t_value, const float t_min, const float t_max);

 private:
   bool m_LetterBox{ false };
   Camera m_Camera{ NULL };
   char* m_RaiseCameraInput{ nullptr };
   char* m_LowerCameraInput{ nullptr };
   float m_BoostValue{ 1.5f };
   float m_CameraSpeed{ 1.0f };
   float m_Fov{ 50.0f };
};
#endif  // RDR2_MAPEDITOR_CAMERA_H
