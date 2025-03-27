#include <iostream>
#include<vector>
#include<chrono>
#include <iostream>
#include <string> 
#include <random>
#include <unistd.h>
#include <algorithm> // Include for shuffle
#include <thread>    // For std::this_thread::sleep_for
#include <chrono>    // For std::chrono::seconds
#include <fstream>
#include <sstream>




#if defined(_WIN32) || defined(_WIN64)  // For Windows
    #include <curses.h>
#elif defined(__APPLE__) || defined(__MACH__)  // For macOS
    #include <ncurses.h>
#elif defined(__linux__)  // For Linux
    #include <ncurses.h>
#else
    #error "Unknown platform, unable to include curses/ncurses"
#endif

using namespace std;
