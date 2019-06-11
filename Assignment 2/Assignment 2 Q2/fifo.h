#include "systemc.h"
#include "fifo_if.h"

template <class T, unsigned N> class fifo : public sc_module, public fifo_out_if <T>, public fifo_in_if <T> {

...

  bool write(T data)
  {
    ...
  }

  bool read(T& data) 
  {
    ...
  }
   
...