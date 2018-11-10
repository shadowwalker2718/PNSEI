#pragma once

// Stream
#include <fstream>
#include <iostream>

// STL
#include <algorithm>
#include <array>
#include <bitset>
#include <deque>
#include <forward_list>
#include <functional>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Memory Management
#include <memory>

// Time
#include <chrono>

// Assert
#include <cassert>
#include <cmath>

// Exception
#include <exception>

// Multithread
#include <condition_variable>
#include <future>
#include <mutex>
#include <thread>

// Numerics
#include <climits>
#include <cmath>
#include <cstring> // strlen

#include <numeric> // accumulate, iota

#include <experimental/filesystem> // C++17
#include <iterator>                //ostream_iterator

using namespace std;
using namespace std::chrono;
namespace fs = experimental::filesystem;

// Boost
//#define BOOST_ALL_DYN_LINK
//#define BOOST_FILESYSTEM_DYN_LINK
//#include <boost/filesystem.hpp>
// using namespace boost::filesystem;

using VB = vector<bool>;
using VVB = vector<VB>;
using VS = vector<string>;
using VVS = vector<VS>;
using VI = vector<int>;
using VVI = vector<VI>;

using iMatrix=VVI;

struct Point {
  int x, y;
  Point(int _x, int _y): x(_x), y(_y){}
  Point(){x = y = 0;}
};