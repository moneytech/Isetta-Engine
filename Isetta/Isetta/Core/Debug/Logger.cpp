/*
 * Copyright (c) 2018 Isetta
 */
#include "Core/Debug/Logger.h"

#include <Windows.h>
#include <sstream>

namespace Isetta {

uint8_t Logger::gVerbosityMask = Debug::Verbosity::All;
uint32_t Logger::gChannelMask = ~0u;
bool Logger::gAlwaysFlush = false;

std::ofstream* Logger::engineStream = nullptr;
std::ofstream* Logger::channelStream = nullptr;

Debug::Verbosity::Enum Logger::defaultVerbosity = Debug::Verbosity::Info;
Debug::Channel::Enum Logger::defaultChannel = Debug::Channel::General;

void Logger::SetLoggerFiles(std::ofstream* inEngineStream,
                            std::ofstream* inChannelStream) {
  Logger::engineStream = inEngineStream;
  if (inChannelStream) {
    Logger::channelStream = inChannelStream;
  }
}
void Logger::SetLoggerChannelFile(std::ofstream* inChannelStream) {
  if (!Logger::engineStream) {
    throw std::logic_error(
        "Logger::SetLoggerChannel must have engine log file before changing "
        "channel file");
  }
  if (Logger::channelStream) {
    Logger::channelStream->close();
  }
  Logger::channelStream = inChannelStream;
}

int Logger::VDebugPrintF(const Debug::Channel::Enum channel,
                         const Debug::Verbosity::Enum verbosity,
                         const std::string inFormat, va_list argList) {
  const uint32_t MAX_CHARS = 1023;
  static char sBuffer[MAX_CHARS + 1];
  // TODO add actual time
  std::ostringstream stream;
  stream << "[" << 12 << ":" << 12 << ":" << 12 << "][" << ToString(verbosity)
         << "][" << ToString(channel) << "] " << inFormat << '\n';
  int charsWritten =
      vsnprintf(sBuffer, MAX_CHARS, stream.str().c_str(), argList);
  sBuffer[MAX_CHARS] = '\0';

  if (CheckChannelMask(channel)) {
    if (CheckVerbosity(verbosity)) {
      OutputDebugString(sBuffer);
    }
    if (Logger::channelStream) {
      *Logger::channelStream << sBuffer;
    }
  }
  if (Logger::engineStream) {
    *Logger::engineStream << sBuffer;
  }

  if (gAlwaysFlush) {
    Logger::engineStream->flush();
  }

  return charsWritten;
}

int Logger::PrintF(const std::string inFormat, ...) {
  va_list argList;
  va_start(argList, &inFormat);

  int charsWritten =
      VDebugPrintF(defaultChannel, defaultVerbosity, inFormat, argList);

  va_end(argList);
  return charsWritten;
}

int Logger::PrintF(const Debug::Channel::Enum channel,
                   const Debug::Verbosity::Enum verbosity,
                   const std::string inFormat, ...) {
  va_list argList;
  va_start(argList, &inFormat);

  int charsWritten = VDebugPrintF(channel, verbosity, inFormat, argList);

  va_end(argList);

  return charsWritten;
}

int Logger::_PrintFMacro(const std::string file, const int line,
                         const Debug::Channel::Enum channel,
                         const Debug::Verbosity::Enum verbosity,
                         const std::string inFormat, va_list argList) {
  std::ostringstream stream;
  stream << file << "(" << line << ") " << inFormat << '\n';

  int charsWritten = VDebugPrintF(channel, verbosity, stream.str(), argList);

  return charsWritten;
}

void Logger::Log(const Debug::Channel::Enum channel, const std::string inFormat,
                 ...) {
  va_list argList;
  va_start(argList, &inFormat);

  VDebugPrintF(channel, Debug::Verbosity::Info, inFormat, argList);

  va_end(argList);
}

void Logger::LogWarning(const Debug::Channel::Enum channel,
                        const std::string inFormat, ...) {
  va_list argList;
  va_start(argList, &inFormat);

  VDebugPrintF(channel, Debug::Verbosity::Warning, inFormat, argList);

  va_end(argList);
}

void Logger::LogDevelop(const Debug::Channel::Enum channel,
                        const std::string inFormat, ...) {
  va_list argList;
  va_start(argList, &inFormat);

  VDebugPrintF(channel, Debug::Verbosity::Development, inFormat, argList);

  va_end(argList);
}

void Logger::LogError(const Debug::Channel::Enum channel,
                      const std::string inFormat, ...) {
  va_list argList;
  va_start(argList, &inFormat);

  VDebugPrintF(channel, Debug::Verbosity::Error, inFormat, argList);

  va_end(argList);
}

bool Logger::CheckChannelMask(const Debug::Channel::Enum channel) {
  return (gChannelMask & channel) == static_cast<uint32_t>(channel);
}

bool Logger::CheckVerbosity(const Debug::Verbosity::Enum verbosity) {
  return (gVerbosityMask & verbosity) == static_cast<uint8_t>(verbosity);
}
}  // namespace Isetta
