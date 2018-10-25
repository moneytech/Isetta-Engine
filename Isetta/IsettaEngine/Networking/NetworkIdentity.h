/*
 * Copyright (c) 2018 Isetta
 */

#pragma once
#include "Core/IsettaAlias.h"
#include "Scene/Component.h"

namespace Isetta {
CREATE_COMPONENT_BEGIN(NetworkIdentity, Component, true)
public:
NetworkIdentity();
NetworkIdentity(U32 id);

U32 id = 0;
U8 clientAuthority = -1;
int updateInterval = 5;

friend class NetworkManager;
CREATE_COMPONENT_END(NetworkIdentity, Component)
}  // namespace Isetta