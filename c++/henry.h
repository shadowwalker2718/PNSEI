#pragma once


// Stream
#include <iostream>
#include <fstream>

// STL
#include <vector>
#include <string>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <forward_list>
#include <algorithm>
#include <functional>
#include <tuple>
#include <deque>
#include <array>
#include <stack>
#include <queue>
#include <bitset>
#include <iterator>


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
#include <thread>
#include <mutex>
#include <future>
#include <condition_variable>

// Numerics
#include <cmath>
#include <climits>
#include <cstring> // strlen

#include <iterator> //ostream_iterator
#include <experimental/filesystem> // C++17


using namespace std;
using namespace std::chrono;
namespace fs = experimental::filesystem;

// Boost
//#define BOOST_ALL_DYN_LINK
//#define BOOST_FILESYSTEM_DYN_LINK
//#include <boost/filesystem.hpp>
//using namespace boost::filesystem;


using VB = vector<bool>;
using VVB = vector<VB>;
using VS = vector<string>;
using VVS = vector<VS>;
