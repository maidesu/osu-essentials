#include "SubmitFeature.hpp"

#include "util/BlockDomain.hpp"

namespace osuessentials {

    bool SubmitFeature::TurnOn()
    {
        return util::BlockDomainOut();
    }

    bool SubmitFeature::TurnOff()
    {
        return util::UnBlockDomainOut();
    }

} //namespace osuessentials
