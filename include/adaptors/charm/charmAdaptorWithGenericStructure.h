#pragma once

#include "charmAdaptorDefault.h"
#ifdef RTS_IS_CHARM

#include <interfaces/adaptor/extensions/withGenericStructure.h>

/**
 * @brief This class is an extended adaptor for Charm++ that serves the purpose of implementing the WithGenericStructure interface.
 *
 * @details This class uses the same initialization code that the CharmAdaptorDefault.
 */
template<typename T>
class CharmAdaptorWithGenericStructure : public CharmAdaptorDefault, public WithGenericStructure<T> {
protected:

  /**
   * @variable ref A reference to the structure that this input adaptor encapsulates.
   */
  T ref;

public:

  CharmAdaptorWithGenericStructure(LDStats *stats) : CharmAdaptorDefault(stats) {}

  /**
   * @brief Initializes the reference to the structure that this adaptor provides to the strategy.
   *
   * @param structure_ref The reference to the structure.
   */
  void setStructure(T &structure_ref) {
    ref = structure_ref;
  }

  /**
   * @brief A method to obtain the additional input structure.
   */
  inline T &structure() {
    return ref;
  }
};

#endif