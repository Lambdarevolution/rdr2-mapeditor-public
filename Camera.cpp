/*
| License: The Unlicense
| Created by: Lambdarevolution(at)gmail.com / 2020-04-01
| Description: Create and manage a camera in red dead redemption 2
*/

#include "Camera.h"

MapEditorCamera::MapEditorCamera() {
  m_camera = NULL;
  m_boostvalue = 1.0f;
  m_cameraspeed = 1.0f;
  m_fov = 50.0f;
}

MapEditorCamera::~MapEditorCamera() {
  if (CAM::DOES_CAM_EXIST(m_camera)) {
    CAM::DESTROY_CAM(m_camera, false);
  }
}

void MapEditorCamera::CreateCamera() {
  m_camera = CAM::CREATE_CAMERA(26379945, true);
  CAM::SET_CAM_ACTIVE(m_camera, true);
  CAM::RENDER_SCRIPT_CAMS(1, 0, 3000, 1, 0, 1);
  CAM::SET_CAM_COORD(m_camera, CAM::GET_GAMEPLAY_CAM_COORD().x, CAM::GET_GAMEPLAY_CAM_COORD().y, CAM::GET_GAMEPLAY_CAM_COORD().z);
  CAM::SET_CAM_ROT(m_camera, CAM::GET_GAMEPLAY_CAM_ROT(0).x, CAM::GET_GAMEPLAY_CAM_ROT(0).y, CAM::GET_GAMEPLAY_CAM_ROT(0).z, 0);
}

void MapEditorCamera::UpdateCamera(bool blockinput) {
  if (blockinput) { return; }
  m_boostvalue = 1.0f;

  float Mouse_x = PAD::GET_CONTROL_NORMAL(0, MISC::GET_HASH_KEY("INPUT_LOOK_LR"));
  float Mouse_y = PAD::GET_CONTROL_NORMAL(0, MISC::GET_HASH_KEY("INPUT_LOOK_UD"));

  CAM::SET_CAM_PARAMS(m_camera, CAM::GET_CAM_COORD(m_camera).x, CAM::GET_CAM_COORD(m_camera).y, CAM::GET_CAM_COORD(m_camera).z, Clamp(CAM::GET_CAM_ROT(m_camera, 0).x - (Mouse_y * 6), -70, 70), 0, CAM::GET_CAM_ROT(m_camera, 0).z - (Mouse_x * 6), this->m_fov, 0, 1, 1, 2, 0, 0);


  if (PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("INPUT_MOVE_UP_ONLY"))) {
    if (PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("INPUT_SPRINT"))) {
      m_boostvalue = 1.5f;
    }

    Vector3 Right = GetCameraRightVector(this->m_camera);
    Vector3 pos = CAM::GET_CAM_COORD(this->m_camera);
    Vector3 Forward = GetCameraForwardVector(this->m_camera);

    if (PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("INPUT_MOVE_LEFT_ONLY"))) {
      pos.x += ((Forward.x + Right.x / 2.0f * m_boostvalue) / 2.2f) * m_cameraspeed;
      pos.y += ((Forward.y + Right.y / 2.0f * m_boostvalue) / 2.2f) * m_cameraspeed;
      pos.z += ((Forward.z + Right.z / 2.0f * m_boostvalue) / 2.2f) * m_cameraspeed;
      CAM::SET_CAM_PARAMS(m_camera, pos.x, pos.y, pos.z, Clamp(CAM::GET_CAM_ROT(m_camera, 0).x - (Mouse_y * 6), -70, 70), 0, CAM::GET_CAM_ROT(m_camera, 0).z - (Mouse_x * 6), this->m_fov, 0, 1, 1, 2, 0, 0);
      return;
    }

    if (PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("INPUT_MOVE_RIGHT_ONLY"))) {
      pos.x += ((Forward.x - Right.x / 2.0f * m_boostvalue) / 2.2f) * m_cameraspeed;
      pos.y += ((Forward.y - Right.y / 2.0f * m_boostvalue) / 2.2f) * m_cameraspeed;
      pos.z += ((Forward.z - Right.z / 2.0f * m_boostvalue) / 2.2f) * m_cameraspeed;
      CAM::SET_CAM_PARAMS(m_camera, pos.x, pos.y, pos.z, Clamp(CAM::GET_CAM_ROT(m_camera, 0).x - (Mouse_y * 6), -70, 70), 0, CAM::GET_CAM_ROT(m_camera, 0).z - (Mouse_x * 6), this->m_fov, 0, 1, 1, 2, 0, 0);
      return;
    }

    pos.x += (Forward.x / 2 * m_boostvalue) * m_cameraspeed;
    pos.y += (Forward.y / 2 * m_boostvalue) * m_cameraspeed;
    pos.z += (Forward.z / 2 * m_boostvalue) * m_cameraspeed;
    CAM::SET_CAM_PARAMS(m_camera, pos.x, pos.y, pos.z, Clamp(CAM::GET_CAM_ROT(m_camera, 0).x - (Mouse_y * 6), -70, 70), 0, CAM::GET_CAM_ROT(m_camera, 0).z - (Mouse_x * 6), this->m_fov, 0, 1, 1, 2, 0, 0);
  }

  if (PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("INPUT_MOVE_DOWN_ONLY"))) {
    if (PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("INPUT_SPRINT"))) {
      m_boostvalue = 1.5f;
    }

    Vector3 pos = CAM::GET_CAM_COORD(this->m_camera);
    Vector3 Forward = GetCameraForwardVector(this->m_camera);
    Vector3 Right = GetCameraRightVector(this->m_camera);

    if (PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("INPUT_MOVE_LEFT_ONLY"))) {
      pos.x -= ((Forward.x - Right.x / 2.0f * m_boostvalue) / 2.2f) * m_cameraspeed;
      pos.y -= ((Forward.y - Right.y / 2.0f * m_boostvalue) / 2.2f) * m_cameraspeed;
      pos.z -= ((Forward.z - Right.z / 2.0f * m_boostvalue) / 2.2f) * m_cameraspeed;
      CAM::SET_CAM_PARAMS(m_camera, pos.x, pos.y, pos.z, Clamp(CAM::GET_CAM_ROT(m_camera, 0).x - (Mouse_y * 6), -70, 70), 0, CAM::GET_CAM_ROT(m_camera, 0).z - (Mouse_x * 6), this->m_fov, 0, 1, 1, 2, 0, 0);
      return;
    }

    if (PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("INPUT_MOVE_RIGHT_ONLY"))) {
      pos.x -= ((Forward.x + Right.x / 2.0f * m_boostvalue) / 2.2f) * m_cameraspeed;
      pos.y -= ((Forward.y + Right.y / 2.0f * m_boostvalue) / 2.2f) * m_cameraspeed;
      pos.z -= ((Forward.z + Right.z / 2.0f * m_boostvalue) / 2.2f) * m_cameraspeed;
      CAM::SET_CAM_PARAMS(m_camera, pos.x, pos.y, pos.z, Clamp(CAM::GET_CAM_ROT(m_camera, 0).x - (Mouse_y * 6), -70, 70), 0, CAM::GET_CAM_ROT(m_camera, 0).z - (Mouse_x * 6), this->m_fov, 0, 1, 1, 2, 0, 0);
      return;
    }

    pos.x -= (Forward.x / 2 * m_boostvalue) * m_cameraspeed;
    pos.y -= (Forward.y / 2 * m_boostvalue) * m_cameraspeed;
    pos.z -= (Forward.z / 2 * m_boostvalue) * m_cameraspeed;
    CAM::SET_CAM_PARAMS(m_camera, pos.x, pos.y, pos.z, Clamp(CAM::GET_CAM_ROT(m_camera, 0).x - (Mouse_y * 6), -70, 70), 0, CAM::GET_CAM_ROT(m_camera, 0).z - (Mouse_x * 6), this->m_fov, 0, 1, 1, 2, 0, 0);
  }

  if (PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("INPUT_MOVE_RIGHT_ONLY"))) {
    if (PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("INPUT_SPRINT"))) {
      m_boostvalue = 1.5f;
    }

    Vector3 pos = CAM::GET_CAM_COORD(this->m_camera);
    Vector3 Right = GetCameraRightVector(this->m_camera);

    pos.x -= (Right.x / 2 * m_boostvalue) * m_cameraspeed;
    pos.y -= (Right.y / 2 * m_boostvalue) * m_cameraspeed;
    CAM::SET_CAM_PARAMS(m_camera, pos.x, pos.y, pos.z, Clamp(CAM::GET_CAM_ROT(m_camera, 0).x - (Mouse_y * 6), -70, 70), 0, CAM::GET_CAM_ROT(m_camera, 0).z - (Mouse_x * 6), this->m_fov, 0, 1, 1, 2, 0, 0);
  }

  if (PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("INPUT_MOVE_LEFT_ONLY"))) {
    if (PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("INPUT_SPRINT"))) {
      m_boostvalue = 1.5f;
    }

    Vector3 pos = CAM::GET_CAM_COORD(this->m_camera);
    Vector3 Right = GetCameraRightVector(this->m_camera);

    pos.x += (Right.x / 2 * m_boostvalue) * m_cameraspeed;
    pos.y += (Right.y / 2 * m_boostvalue) * m_cameraspeed;
    CAM::SET_CAM_PARAMS(m_camera, pos.x, pos.y, pos.z, Clamp(CAM::GET_CAM_ROT(m_camera, 0).x - (Mouse_y * 6), -70, 70), 0, CAM::GET_CAM_ROT(m_camera, 0).z - (Mouse_x * 6), this->m_fov, 0, 1, 1, 2, 0, 0);
  }
}
