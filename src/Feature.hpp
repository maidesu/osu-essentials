#pragma once

namespace osuessentials {

class Feature
{
public:
    virtual bool TurnOn() = 0;
    virtual bool TurnOff() = 0;

    virtual bool Toggle() {
        if (enabled)
        {
            TurnOff();
        }
        else
        {
            TurnOn();
        }
        enabled = !enabled;
        return enabled;
    }

    virtual bool isEnabled() const { return enabled; }

protected:
    bool enabled = false;
};

} // namespace osuessentials
