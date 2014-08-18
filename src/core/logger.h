#ifndef CORE_LOGGER_H
#define CORE_LOGGER_H

#include <string>
#include <vector>
#include <functional>
#include <fstream>
#include <mutex>

namespace Glib {
class Exception;
}

namespace GstreamerStudio {
namespace Core {

enum class LogLevel
{
  ERROR,
  WARN,
  DEBUG,
  INFO,
    
};

class Logger
{
 private:
  static Logger* instance;
  
  LogLevel level = LogLevel::ERROR;
  std::vector<std::reference_wrapper<std::ostream>> outputs;
  std::ofstream out_file;

  std::mutex stream_mutex;

 protected:
  Logger ();
  virtual ~Logger ();

 private:
  Logger (const Logger&) = delete;
  Logger& operator= (const Logger&) = delete;

  static std::string get_current_time ();

 public:
  void set_debug_level (LogLevel level);
  void log (const std::string& message, LogLevel level);
  void log (const std::exception& ex, LogLevel level);
  void log (const Glib::Exception& ex, LogLevel level);

  static Logger* get_instance ();

  static std::string level_to_string (LogLevel level);
};

}
}

#endif
