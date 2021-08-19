/*
| License: Unlicense
| Created by: Lambdarevolution(at)gmail.com / 2020-04-01
| Description: Simple log class
*/
#ifndef LOG_LOG_H_
#define LOG_LOG_H_


#define LOG_WARNING(msg) Log::getInstance()->log(Log::Warning, msg);

#include "..\inc\types.h"

#include <string>
#include <fstream>
#include <chrono>
// Class: Log
// A very simple logging class. This is a singleton class
class Log {
private:
  static Log* instance;
  // Function: Log
    // Log constructor, clears the log file.
  Log() {
    std::ofstream file;
    file.open("MapEditor/log.txt", std::ios_base::trunc);
    file.clear();
    file.close();
  }

  ~Log() { }

public:
  enum eLogLevel {
    Note,
    Warning,
    Error
  };

  const std::string _LogLevelNames[3]{
  "Note","Warning","Error"
  };
  // Function: getInstance
    // Returns the instance of the log.
  static Log* getInstance() {
    if (instance == 0) {
      instance = new Log();
    }
    return instance;
  }
  // Function: log
    // Puts the input into the logfile with correct formatting and a newline
  inline void log(eLogLevel t_type, const char* t_msg, const char* t_smsg) {
    std::ofstream outfile;
    outfile.open("MapEditor/log.txt", std::ios::out | std::ios_base::app);
    outfile << "[" << _LogLevelNames[t_type] << "] " << t_msg << t_smsg << "\n";
    outfile.close();
  }

  inline void log(eLogLevel t_type, const char* t_msg) {
    std::ofstream outfile;
    outfile.open("MapEditor/log.txt", std::ios::out | std::ios_base::app);
    outfile << "[" << _LogLevelNames[t_type] << "] " << t_msg << "\n";
    outfile.close();
  }

  inline void log(eLogLevel t_type, long long* t_msg) {
    std::ofstream outfile;
    outfile.open("MapEditor/log.txt", std::ios::out | std::ios_base::app);
    outfile << "[" << _LogLevelNames[t_type] << "] " << t_msg << "\n";
    outfile.close();
  }

  inline void log(eLogLevel t_type, DWORD_PTR* t_msg) {
    std::ofstream outfile;
    outfile.open("MapEditor/log.txt", std::ios::out | std::ios_base::app);
    outfile << "[" << _LogLevelNames[t_type] << "] " << t_msg << "\n";
    outfile.close();
  }

  inline void log(eLogLevel t_type, const std::string* t_msg) {
    std::ofstream outfile;
    outfile.open("MapEditor/log.txt", std::ios::out | std::ios_base::app);
    outfile << "[" << _LogLevelNames[t_type] << "] " << t_msg << "\n";
    outfile.close();
  }

  inline void log(eLogLevel t_type, const char* t_msg, const int p0) {
    std::ofstream outfile;
    outfile.open("MapEditor/log.txt", std::ios::out | std::ios_base::app);
    outfile << "[" << _LogLevelNames[t_type] << "] " << t_msg << p0 << "\n";
    outfile.close();
  }

  inline void log(eLogLevel t_type, const char* t_msg, const float p0) {
    std::ofstream outfile;
    outfile.open("MapEditor/log.txt", std::ios::out | std::ios_base::app);
    outfile << "[" << _LogLevelNames[t_type] << "] " << t_msg << p0 << "\n";
    outfile.close();
  }

  inline void log(eLogLevel t_type, const char* t_msg, const Hash p0) {
    std::ofstream outfile;
    outfile.open("MapEditor/log.txt", std::ios::out | std::ios_base::app);
    outfile << "[" << _LogLevelNames[t_type] << "] " << t_msg << p0 << "\n";
    outfile.close();
  }

  inline void log(eLogLevel t_type, const char* t_msg, const DWORD64 p0) {
    std::ofstream outfile;
    outfile.open("MapEditor/log.txt", std::ios::out | std::ios_base::app);
    outfile << "[" << _LogLevelNames[t_type] << "] " << t_msg << p0 << "\n";
    outfile.close();
  }

  inline void log(eLogLevel t_type, const char* t_msg, const long long p0) {
    std::ofstream outfile;
    outfile.open("MapEditor/log.txt", std::ios::out | std::ios_base::app);
    outfile << "[" << _LogLevelNames[t_type] << "] " << t_msg << p0 << "\n";
    outfile.close();
  }

  inline void log(eLogLevel t_type, const char* t_msg, std::chrono::microseconds p0) {
    std::ofstream outfile;
    outfile.open("MapEditor/log.txt", std::ios::out | std::ios_base::app);
    outfile << "[" << _LogLevelNames[t_type] << "] " << t_msg << p0.count() << "\n";
    outfile.close();
  }



};
#endif
