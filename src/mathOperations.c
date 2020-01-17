#include "globalIncludes.h"
#include "mathOperations.h"

intmax_t multiplicativeInverse(intmax_t a, intmax_t n)//x^(-1) * x = 1 mod n
{
  //Using euclidean algorithm
  intmax_t c = 0;
  intmax_t xa = 1;
  intmax_t xn = 0;

  while(a != 0 && n != 0)
  {
    if(a >= n){
      c = a/n;
      a %= n;
      xa -= xn * c;
    }
    else{
      c = n/a;
      n %= a;
      xn -= xa * c;
    }
  }

  if(a+n != 1)
    return 0;
  else if(a > 0)
    return xa;
  else
    return xn;
}
