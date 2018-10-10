#pragma once

#include <system/static.h>

BEGIN_NAMESPACE(Dependency)

/**
 * @brief the minimal dependency of a Scheduler.
 * @details A scheduler needs to at least know the amount of elements to schedule, hence the task_data variable.
 */
template<typename TaskData>
struct BasicDependencies {
  TaskData *task_data;

  template<typename ... Concepts>
  BasicDependencies(std::tuple<Concepts...> concepts) : task_data(std::get<0>(concepts)) {}
};

END_NAMESPACE