/*!
 *    ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/utils/logging.h
 * \brief Logging related utils for coconut JVM.
 * \author SiriusNEO
 */

#ifndef SRC_UTILS_LOGGING_H_
#define SRC_UTILS_LOGGING_H_

#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace coconut {

namespace utils {

constexpr const char* kJVM_IERROR_MSG =
    "\n"
    "---------------------------------------------------------------\n"
    "Interal error happens when running Coconut JVM. \n"
    "Please check the source code for detailed reason. \n"
    "---------------------------------------------------------------\n";

class JVMLogException : public std::exception {
 public:
  JVMLogException(const std::string& file, int lineno,
                  const std::string& message)
      : message_(kJVM_IERROR_MSG + file + ": " + std::to_string(lineno) + ": " +
                 message) {}

  virtual const char* what() const noexcept { return message_.c_str(); }

 private:
  std::string message_;
};

auto LOG_LEVEL_LIST = {"INFO", "DEBUG", "WARNING", "ERROR", "FATAL"};

#define kJVM_LOG_INFO "INFO"
#define kJVM_LOG_DEBUG "DEBUG"
#define kJVM_LOG_WARNING "WARNING"
#define kJVM_LOG_ERROR "ERROR"
#define kJVM_LOG_FATAL "FATAL"

/*!
 * \brief Class to accumulate an log message.
 * Ref:
 * https://github.com/apache/tvm/blob/HEAD/include/tvm/runtime/logging.h#L323-L339
 */
class LogMessage {
 public:
  LogMessage(const std::string& file, int lineno, const std::string& level)
      : file_(file), lineno_(lineno) {
    for (const auto& valid_level : LOG_LEVEL_LIST) {
      if (valid_level == level) {
        level_ = valid_level;
        break;
      }
    }
    if (level_.empty()) {
      throw JVMLogException(file, lineno, "Invalid Log Level: " + level);
    }
  }

  ~LogMessage() throw(JVMLogException) {
    std::time_t time = std::time(nullptr);
    std::ostringstream info;
    info << "[" << std::put_time(std::localtime(&time), "%H:%M:%S") << "] "
         << file_ << ":" << lineno_ << ": " << stream_.str() << std::endl;
    if (level_ == kJVM_LOG_FATAL) {
      std::cerr << info.str();
      throw JVMLogException(file_, lineno_, stream_.str());
    } else {
      std::cout << info.str() << std::endl;
    }
  }

  std::ostringstream& stream() { return stream_; }

 private:
  std::string file_;
  int lineno_;
  std::string level_;
  std::ostringstream stream_;
};

#define LOG(level) LOG_##level
#define LOG_DEBUG utils::LogMessage(__FILE__, __LINE__, kJVM_LOG_DEBUG).stream()
#define LOG_INFO utils::LogMessage(__FILE__, __LINE__, kJVM_LOG_INFO).stream()
#define LOG_ERROR utils::LogMessage(__FILE__, __LINE__, kJVM_LOG_ERROR).stream()
#define LOG_WARNING \
  utils::LogMessage(__FILE__, __LINE__, kJVM_LOG_WARNING).stream()
#define LOG_FATAL utils::LogMessage(__FILE__, __LINE__, kJVM_LOG_FATAL).stream()

#define CHECK(x)                                                 \
  if (!(x))                                                      \
  utils::LogMessage(__FILE__, __LINE__, kJVM_LOG_FATAL).stream() \
      << "Check failed: (" #x << ") is false: "

}  // namespace utils

}  // namespace coconut

#endif  // SRC_UTILS_LOGGING_H_
