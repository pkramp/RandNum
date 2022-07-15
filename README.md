# RandNum
A simple header only library to generate random numbers efficiently.
Template method wrapper allow quick and easy generation of random numbers, both integral and floating point, through a common interface.
Allows for seeding and setting precision to which decimal place values will be randomized. Note that floating point numbers in general are not precise, so the effect here is diminishing with every decimal place.

Random numbers generated via Squirrel3 hash function and pseudo-random number generator developed by Squirrel Eiserloh and presented [here](https://www.youtube.com/watch?v=LWFzPP8ZbdU)

Limitations:
Doubles are limited to INT_MAX.

How to use:
Copy the header file into your includes/your project, include it via #include "RandNum/RandNum.h"


Example of usage:
```cpp
int main() {
  // set seed
  RandNum::seed() = 5;
  // get random number without range
  std::cout << RandNum::getRandom<int>() << std::endl; // prints 957954048
  std::cout << RandNum::getRandom<long long>() << std::endl; // prints -6181941694011907415
  std::cout << RandNum::getRandom<unsigned long long>() << std::endl; // prints 9375394229408857579
  std::cout << RandNum::getRandom<unsigned char>() << std::endl; // prints Í
  std::cout << RandNum::getRandom<unsigned int>() << std::endl; // prints 1655133459
  std::cout << RandNum::getRandom<int64_t>() << std::endl; // prints 7874188498171578602
  // get random number with max value
  std::cout << RandNum::getRandom(100) << std::endl; // prints 40
  // get random number with min and max value
  std::cout << RandNum::getRandom(5, 100) << std::endl; // prints 15
  // negative numbers also supported -100 to 100
  std::cout << RandNum::getRandom(-100, 100) << std::endl; // prints 5
  // generate doubles 
  std::cout << RandNum::getRandom(0.2) << std::endl; // prints 0.0666802
  std::cout << RandNum::getRandom(0.2, 0.4) << std::endl; // prints 0.374331
  // set floating point precision
  RandNum::precision() = 5;
  // get float between -5 and 5
  std::cout << std::setprecision(RandNum::precision())
            << RandNum::getRandom(-5.0f, 5.0f) << std::endl; // prints 3.443
  RandNum::precision() = 8;
  // get double between -500 and 500
  std::cout << RandNum::getRandom(-500.0, 500.0) << std::endl; // prints 281.91
  std::cout << RandNum::getRandom(-500.0, 500.0) << std::endl; // prints 446.12
  RandNum::precision() = 15;
  std::cout << std::setprecision(RandNum::precision())
            << RandNum::getRandom(-500.0, 500.0) << std::endl; // prints 348.660011656501
  std::cout << std::setprecision(RandNum::precision())
            << RandNum::getRandom(-500.0, 500.0) << std::endl; // prints 273.495506969286
  std::cout << std::setprecision(RandNum::precision())
            << RandNum::getRandom<double>() << std::endl; // prints 901534792.937718
  std::cout << std::setprecision(RandNum::precision())
            << RandNum::getRandom<long double>() << std::endl; // prints 1018400218.18301
}


