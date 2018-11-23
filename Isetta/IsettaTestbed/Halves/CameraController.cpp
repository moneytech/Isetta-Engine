/*
 * Copyright (c) 2018 Isetta
 */
#include "CameraController.h"
#include "Core/IsettaCore.h"
#include "PlayerController.h"

namespace Isetta {

void CameraController::Update() {
  auto player = PlayerController::Instance();
  if (player != nullptr) {
    transform->SetWorldPos(player->transform->GetWorldPos() + Math::Vector3{0, y, z});
    Math::Vector3 dir = transform->GetWorldPos() - player->transform->GetWorldPos();
    transform->LookAt(transform->GetWorldPos() + dir);
  }
}

void CameraController::GuiUpdate() {
  float base = 150;
  float padding = 20;
  GUI::SliderFloat(RectTransform{Math::Rect{-200, base, 300, 100},
                                 GUI::Pivot::TopRight, GUI::Pivot::TopRight},
                   "Camera Height", &y, 0, 30.f);
  GUI::SliderFloat(RectTransform{Math::Rect{-200, base + padding, 300, 100},
                                 GUI::Pivot::TopRight, GUI::Pivot::TopRight},
                   "Camera HoriDis", &z, 0, 30.f);
}
}  // namespace Isetta
