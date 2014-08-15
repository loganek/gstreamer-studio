#include "logger.h"

#include <ctime>
#include <iostream>

using namespace GstreamerStudio::Core;

Logger* Logger::instance = nullptr;

Logger* Logger::get_instance ()
{
  if (instance == nullptr)
  {
    instance = new Logger ();
  }

  return instance;
}

Logger::Logger ()
{
  out_file.open ("filename.log"); // todo: improved logger filename
  
  outputs.push_back (out_file);
  outputs.push_back (std::cout);
}

Logger::~Logger ()
{
  out_file.close ();
}

void Logger::set_debug_level (LogLevel level)
{
  this->level = level;
}

void Logger::log (const std::string& message, LogLevel level)
{
  if (this->level < level)
  {
    return;
  }
  
  for (std::ostream& out : outputs)
  {
    stream_mutex.lock ();
    out << "[" << level_to_string (level) << ": " << get_current_time () << "] " << message << std::endl;
    stream_mutex.unlock ();
  }
}

std::string Logger::get_current_time ()
{
  time_t current = time (nullptr);
  tm *local_time = localtime (&current);

  return std::to_string (local_time->tm_hour) + ":" + std::to_string (local_time->tm_min) + ":" + std::to_string (local_time->tm_sec);
}

std::string Logger::level_to_string (LogLevel level)
{
  switch (level)
  {
  case LogLevel::ERROR: 
    return "Error";
  case LogLevel::WARN:
    return "Warn";
  case LogLevel::DEBUG:
    return "Debug";
  case LogLevel::INFO:
    return "Info";
  default:
    return "Unknown log level";
  }
}
