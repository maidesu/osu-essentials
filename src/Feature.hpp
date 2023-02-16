#pragma once

namespace osuessentials {

class Feature
{
public:
    virtual bool TurnOn() = 0;
    virtual bool TurnOff() = 0;

    virtual bool Toggle() {
        enabled = !enabled;
        if (enabled)
        {
            return TurnOn();
        }
        else
        {
            return TurnOff();
        }
    }

protected:
    bool enabled = false;
};

} // namespace osuessentials
