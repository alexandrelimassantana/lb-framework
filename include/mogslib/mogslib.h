#pragma once

#include <tuple>
#include <string>

#include <abstractions/traits/charm_fast.h>

namespace MOGSLib {  using Traits = CharmFast;  }

#include <abstractions/contexts/charm.h>

#include <model/schedulers/greedy.h>

#include "macros.h"

namespace MOGSLib {

struct API {
  using Contexts = std::tuple<Ctx(Charm)>;
  using Schedulers = std::tuple<Sched(Greedy, 0)>;

  static Contexts contexts;
  static Schedulers schedulers;

  template<unsigned i>
  inline static void do_work(){
    std::get<i>(schedulers).work(std::get<i>(contexts));
  }

  inline static bool test_scheduler(const std::string &schedname, const std::string &name){
    return schedname.compare(name) == 0;
  }

  inline static void work(const std::string &name) {
    if(test_scheduler("greedy", name))
			do_work<0>();
    else {
      throw std::string("[MOGSLib] Invalid scheduler name.");
    }
  }
};

}