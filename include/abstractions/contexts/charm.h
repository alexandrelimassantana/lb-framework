#pragma once

#include <abstractions/structures/input/workload_aware.h>
#include <model/policies/dependencies/base.h>

#include <abstractions/rts/charm/charm.h>

namespace MOGSLib { namespace Context {

struct Charm {
  using Id = typename Traits::Id;
  using Load = typename Traits::Load;
  using Schedule = typename MOGSLib::Dependency::Base<Id>::Schedule;

  MOGSLib::Input::WorkloadAware<Id, Load> _input;

  Schedule _schedule;

protected:
  inline void update_tasks() {
    MOGSLib::RTS::Charm::LBDB::Chare::count();
    MOGSLib::RTS::Charm::LBDB::Chare::load_prediction(_input.tasks);
  }

  inline void update_pus() {
    MOGSLib::RTS::Charm::LBDB::PU::count();
    MOGSLib::RTS::Charm::LBDB::PU::load_prediction(_input.pus);
  }

public:

  /** Gets the schedule as a C pointer **/
  inline Id* scheduleRaw() {
    return _schedule.data();
  }

  /** Gets the schedule as a C++ std::vector **/
  inline Schedule& schedule() {
    _schedule.resize(_input.ntasks());
    return _schedule;
  }

  /** Gets the workload-aware scheduler policy input **/
  inline auto& input() {
    update_tasks();
    update_pus();
    return _input;
  }

  inline auto nchunks() {
    return _input.npus()*4;
  }

};

}}