/*
 * Copyright (c) 2018 Isetta
 */
#include "Custom/EventTestLevel/EventSenderComponent.h"
#include "Core/Time/Time.h"
#include "Events/EventObject.h"
#include "Events/Events.h"
#include "Input/Input.h"

void EventSenderComponent::Start() {
  handleA = Isetta::Input::RegisterKeyPressCallback(Isetta::KeyCode::A, [&]() {
    Isetta::EventParam param{std::string{"RaiseEvent In Queue"}};
    Isetta::EventObject eventObject{"RaiseEvent",
                                    Isetta::Time::GetTimeFrame(),
                                    Isetta::EventPriority::MEDIUM,
                                    {param}};
    Isetta::Events::Instance().RaiseQueuedEvent(eventObject);
    Isetta::Input::UnregisterKeyPressCallback(Isetta::KeyCode::A, handleA);
  });
  handleB = Isetta::Input::RegisterKeyPressCallback(Isetta::KeyCode::S, [&]() {
    Isetta::EventParam param{std::string{"RaiseEvent Immediately"}};
    Isetta::EventObject eventObject{"RaiseEvent",
                                    Isetta::Time::GetTimeFrame(),
                                    Isetta::EventPriority::MEDIUM,
                                    {param}};
    Isetta::Events::Instance().RaiseImmediateEvent(eventObject);
    Isetta::Input::UnregisterKeyPressCallback(Isetta::KeyCode::S, handleB);
  });
  handleC = Isetta::Input::RegisterKeyPressCallback(Isetta::KeyCode::D, [&]() {
    Isetta::EventParam param1{std::string{"RaiseEvent High"}};
    Isetta::EventParam param2{std::string{"RaiseEvent Low"}};
    Isetta::EventParam param3{std::string{"RaiseEvent Late"}};

    Isetta::EventObject eventObject1{"RaiseEvent",
                                     Isetta::Time::GetTimeFrame(),
                                     Isetta::EventPriority::HIGH,
                                     {param1}};
    Isetta::EventObject eventObject2{"RaiseEvent",
                                     Isetta::Time::GetTimeFrame(),
                                     Isetta::EventPriority::LOW,
                                     {param2}};
    Isetta::EventObject eventObject3{"RaiseEvent",
                                     Isetta::Time::GetTimeFrame() + 5,
                                     Isetta::EventPriority::HIGH,
                                     {param3}};

    Isetta::Events::Instance().RaiseQueuedEvent(eventObject1);
    Isetta::Events::Instance().RaiseQueuedEvent(eventObject2);
    Isetta::Events::Instance().RaiseQueuedEvent(eventObject3);
    Isetta::Input::UnregisterKeyPressCallback(Isetta::KeyCode::D, handleC);
  });
}
