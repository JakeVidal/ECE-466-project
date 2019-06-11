...

template <class T> class consumer : public sc_module 
{
public:
  sc_port < fifo_in_if<T> > in;
  ...
  
  void do_reads()
  {
    T data;
    while (true) 
    {
      ...
      
      if (in->read(data)) 
        cout << "R " << data << " at " << sc_time_stamp() << endl;
	
      ...
    }
  } 
  
...