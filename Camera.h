/*
| License: The Unlicense
| Created by: Lambdarevolution(at)gmail.com / 2020-04-01
| Description: Create and manage a camera in red dead redemption 2
*/
#ifndef RDR2_MAPEDITOR_CAMERA_H_
#define RDR2_MAPEDITOR_CAMERA_H_

#include "..\inc\natives.h"
#include "..\inc\types.h"

#include "VectorMath.h"
#include "Math.h"
// Class: MapEditorCamera
// The camera class used by the editor.
class MapEditorCamera {
 public:
  // Function: MapEditorCamera
  // Default constructor, initalizes the object, m_camera is set to null.
  MapEditorCamera();
  // Function: ~MapEditorCamera
  // Destructor, destroy the scriptcamera and activate gamecamera again.
  ~MapEditorCamera();
  // Function: GetCamera
  // Returns the camera object
  inline Camera GetCamera() { return m_camera; }
  // Function: SetCameraSpeed
  // Set the camera speed
  inline void SetCameraSpeed(float speed) { m_cameraspeed = speed; }
  // Function: SetCameraFov
  // Set the camera field of view
  inline void SetCameraFov(float t_fov) { m_fov = t_fov; }
  // Function: GetCameraSpeed
  // Returns:
  // The Camera speed
  inline const float GetCameraSpeed() { return this->m_cameraspeed; }
  // Function: GetCameraFov
  // Returns:
  // The Camera Fov
  inline const float GetCameraFov() { return this->m_fov; }
  // Function: CreateCamera
  // Creates and activates the camera
  void CreateCamera();
  /*
  Function: UpdateCamera

   Updates the camera, controls are proccessed in here.

  Parameters:

  blockinput - If true the control inputs are ignored.
  */
  void UpdateCamera(bool blockinput);

 private:
  // Variable: m_camera
  // The camera object itself
  Camera m_camera;
  // Variable: m_boostvalue
  // Used to speed up the camera with left shift
  float m_boostvalue;
  // Variable: m_cameraspeed
  // The base speed of the camera
  float m_cameraspeed;
  // Variable: m_fov
  // The field of view for the editor camera
  float m_fov;
};
#endif  // RDR2_MAPEDITOR_CAMERA_H_
