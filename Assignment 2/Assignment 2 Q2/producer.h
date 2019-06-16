#include "systemc.h"
#include "fifo.h"

template <class T> class producer : public sc_module 
{
public:
  sc_port < fifo_out_if<T> > out;
  ...

  void do_writes()
  {
    T data = 0;
    while (true) 
    {
      ...
      
      if (out->write(data)) 
        cout << "W " << data << " at " << sc_time_stamp() << endl;
	
      ...
    }
  }
  
...
