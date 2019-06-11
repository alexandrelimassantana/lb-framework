#pragma once

#include <abstractions/rts/charm/traits.h>

struct CharmFast {
  using Id = typename MOGSLib::SystemTraits<MOGSLib::System::charm>::Id;
  using Load = typename MOGSLib::SystemTraits<MOGSLib::System::charm>::Load;

  using UnavailablePUs = typename MOGSLib::CharmSemantics::UnavailablePUs<false>;
  using RigidJobs = typename MOGSLib::CharmSemantics::RigidJobs<false>;
};