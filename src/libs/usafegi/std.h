#ifndef _STD_H_
#define _STD_H_

#ifdef _WIN32
#include <memory>
#include <random>
#else
#include <tr1/memory>
#include <tr1/random>
#endif

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>

using std::tr1::shared_ptr;
using std::tr1::weak_ptr;
using std::tr1::dynamic_pointer_cast;
using std::tr1::minstd_rand;
using std::tr1::uniform_real;
using std::string;
using std::min;
using std::max;
using std::stringstream;
using std::cout;
using std::endl;
using std::pair;

#endif
