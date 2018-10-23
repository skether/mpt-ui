#ifndef GLOBALDEFINE_H
#define GLOBALDEFINE_H

#define __DEBUG__

#ifdef __DEBUG__

#include <string>
#include <vector>
#include <fstream>
#include <ctime>

inline void _debugErase() {std::ofstream file; file.open("debugLog.txt", std::ofstream::trunc); file.close();}

inline void _debugLog(std::string str) {std::ofstream file; file.open("debugLog.txt", std::ofstream::app); file << time(NULL) << ": " << str << "\r\n"; file.close();}

inline void _debugLogIntVector(std::vector<int> v) { std::ofstream file; file.open("debugLog.txt", std::ofstream::app); for (std::vector<int>::iterator i = v.begin(); i != v.end(); ++i) { file << *i << ' '; } file << "\r\n"; file.close(); }

inline void _debugLogInt(int num) { std::ofstream file; file.open("debugLog.txt", std::ofstream::app); file << num << " "; file.close(); }

#endif

#endif