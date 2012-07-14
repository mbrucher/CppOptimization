/**
 * \file state.h
 */


#ifndef STATE_H_
#define STATE_H_

namespace Optimization
{
  namespace Local
  {
    /**
     * Optimization state for an optimizer
     */
    template<class DataType_, class Container_>
    struct State
    {
      typedef DataType_ DataType;
      typedef Container_ Container;

      Container best_parameters;
      DataType best_value;

      Container current_parameters;
      DataType current_value;

      Container former_parameters;
      DataType former_value;

      long iteration;
    };
  }
}


#endif /* STATE_H_ */
