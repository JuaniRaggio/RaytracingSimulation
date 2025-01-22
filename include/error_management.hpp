#pragma once

#include <iostream>

#define SUCCESS 0
#define CHECKERROR(expr, msg)\
  do { \
    if ((expr)) { \
      std::cerr << msg; \
    } \
  } while(0)
