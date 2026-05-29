#include "first.hpp"

int main()
{
    matrix_ mp={
        {1,5,3,5},
        {4,3,2,5},
        {321,4.2,23,55}
    };
    
    matrix_ sb(mp);
  

    mp.visit();
      sb.visit();
    return 0;

}