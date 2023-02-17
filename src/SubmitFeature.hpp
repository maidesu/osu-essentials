#pragma once

#include "Feature.hpp"

namespace osuessentials {

class SubmitFeature : public Feature
{
public:
    SubmitFeature() {}
    ~SubmitFeature() {
        if (enabled) { TurnOff(); }
    }

    bool TurnOn() override;
    bool TurnOff() override;
};

} // namespace osuessentials
