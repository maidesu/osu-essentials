#pragma once

#include <thread>

#include "Feature.hpp"

namespace osuessentials {

class PriorityFeature : public Feature
{
public:
    PriorityFeature() {}
    ~PriorityFeature() {
        if (enabled) { TurnOff(); }
    }

    bool TurnOn() override;
    bool TurnOff() override;

private:
    std::thread thread;
    std::atomic<bool> stop { false };

    bool SetHighPriority();
};

} // namespace osuessentials
