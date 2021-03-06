#pragma once

#include <type_definitions.h>

#include <load_generator.h>

#include <model/policies/dependencies/workload_aware.h>
#include <abstractions/structures/input/workload_aware.h>

using Deps = MOGSLib::Dependency::WorkloadAware<Id, Load>;
using Schedule = typename Deps::Schedule;

/**
 *  @class WorkloadAwarePolicyTests
 *  @brief A base class to test workload aware policies.
 */
class WorkloadAwarePolicyTests : public ::testing::Test {
public:
  /// @brief Set the LoadGenerator type to the default load generator.
  using LoadGenerator = UnitTest::LoadGenerator<>;

  /// @brief Set the Input to the default implementation of the workload_aware input type.
  using Input = MOGSLib::Input::WorkloadAware<Id, Load>;
  
  Schedule map;
  Input input;

  /**
   *  @brief Set the data about pu amount and task amount.
   *  @param p The amount of pus in the system.
   *  @param t The amount of tasks in the system.
   */
  void set_pus_and_tasks(const Id &p, const Id &t) {
    input.pus.resize(p);
    input.tasks.resize(t);
    map = Schedule(t);
  }

  /**
   *  @brief Set the workload of the tasks.
   *  @param gen A function to generate the load of a task given its index.
   */
  void set_task_loads(Load (*gen)(const Id &)) {
    Id i = 0;
    std::transform(input.tasks.begin(), input.tasks.end(), input.tasks.begin(), [&i, &gen](Load) { return gen(i++); });
  }

  /// @brief Set up all the necessary data for the tests.
  void SetUp() {
    input = Input();
    map.clear();
  }
};