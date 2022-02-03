/*
| License: Unlicense
| Created by: Lambdarevolution(at)gmail.com / 2020-04-01
| Description: Linetrace for red dead redemption 2
*/
#ifndef LINETRACE_H
#define LINETRACE_H

#include "..\inc\natives.h"
#include "..\inc\types.h"

#include "VectorMath.h"
#include "Camera.h"

struct Hit {
  BOOL    Hit;
  Entity  Entity;
  Vector3 HitLocation;
  Vector3 SurfaceNormal;
};

/*
Function: LineTraceCamera

Shoots a linetrace from the center of the camera

Parameters:

length - The length of the linetrace

flags - The collision flag

cam - The camera to shoot the linetrace from
*/
static inline Hit LineTraceCamera(float length, int flags, Camera cam) {
  // The hit struct to return
  Hit result;

  // Get the position and rotation of the camera we are using
  Vector3 Cameraposition = CAM::GET_CAM_COORD(cam);

  // We get the forward vector
  Vector3 Camdirection = GetCameraForwardVector(cam);

  // We multiply the forward vector with the desired length of the line
  // and then add to the Cameraposition. Theese are custom functions.
  Vector3 lengthVector = multiply(&Camdirection, length);
  Vector3 EndLine = add(&Cameraposition, &lengthVector);

  // Fire the ray, get result and fill our Hit struct with the results.
  int Ray = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(Cameraposition.x, Cameraposition.y, Cameraposition.z, EndLine.x, EndLine.y, EndLine.z, flags, PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()), 1);
  SHAPETEST::GET_SHAPE_TEST_RESULT(Ray, &result.Hit, &result.HitLocation, &result.SurfaceNormal, &result.Entity);

  return result;
}

static inline Hit LineTraceCameraWithIgnore(float length, int flags, Camera cam, Entity ignoreactor) {
  // The hit struct to return
  Hit result;

  // Get the position and rotation of the camera we are using
  Vector3 Cameraposition = CAM::GET_CAM_COORD(cam);

  // We get the forward vector
  Vector3 Camdirection = GetCameraForwardVector(cam);

  // We multiply the forward vector with the desired length of the line
  // and then add to the Cameraposition. Theese are custom functions.
  Vector3 lengthVector = multiply(&Camdirection, length);
  Vector3 EndLine = add(&Cameraposition, &lengthVector);

  // Fire the ray, get result and fill our Hit struct with the results.
  int Ray = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(Cameraposition.x, Cameraposition.y, Cameraposition.z, EndLine.x, EndLine.y, EndLine.z, flags, ignoreactor, 1);
  SHAPETEST::GET_SHAPE_TEST_RESULT(Ray, &result.Hit, &result.HitLocation, &result.SurfaceNormal, &result.Entity);

  return result;
}

static inline Hit LineTraceWithIgnore(int flags, Vector3 StartPosition, Vector3 EndPosition, Entity ignoreactor) {
  // The hit struct to return
  Hit result;

  // Fire the ray, get result and fill our Hit struct with the results.
  int Ray = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(StartPosition.x, StartPosition.y, StartPosition.z, EndPosition.x, EndPosition.y, EndPosition.z, flags, ignoreactor, 1);
  SHAPETEST::GET_SHAPE_TEST_RESULT(Ray, &result.Hit, &result.HitLocation, &result.SurfaceNormal, &result.Entity);

  return result;
}

