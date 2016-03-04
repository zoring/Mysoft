#include <boost/signal.hpp>
#include <iostream>
using namespace std;
struct Hello 
{
  void operator()() const
  {
    std::cout << "Hello";
  }
};
struct World
{
  void operator()() const
  {
    std::cout << ", World!" << std::endl;
  }
};
int  main(){
boost::signal<void ()> sig;

sig.connect(Hello());
sig.connect(World());

sig();
return 1;
}
