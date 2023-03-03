/*!
 *   ________  ________  ________  ________  ________   ___  ___  _________
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_|
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * \file src/jvm_entry.cc
 * \brief The entry of the Coconut JVM.
 * \author SiriusNEO
 *
 * A toy JVM (Java Virtual Machine) written in C++. For learning purpose.
 *
 * About the project:
 *   This toy is created during my summer vacation. I began to be interested in
 *   JVM when I am working on JIT (Just-In-Time Compilation) and I am curious
 *   about its architecture and implementation.
 *
 * About the name:
 *   We all know that Java is named after "Java Coffee", which is also a small
 *   Indonesian island. As a tropical island, it produces not only coffee but
 *   also coconuts in abundance. And that is why I choose the name "coconut" for
 *   this JVM.
 *
 * References:
 *   - The Java® Virtual Machine Specification - Java SE 8 Edition
 *   - https://github.com/zxh0/jvm.go
 *
 * 3rd party:
 *   - C++ zip library: https://github.com/kuba--/zip
 *   - utf8-utf16 converter library:
 *     https://github.com/Davipb/utf8-utf16-converter
 */

#include "classloader/file_loader.h"
#include "utils/cmdline.h"
#include "utils/logging.h"
#include "vm/interpreter.h"

#define MAX_CLASSFILE_SIZE 1048576  // 1MB

// namespace
using namespace coconut;

// main entry
int main(int argc, char *argv[]) {
  utils::CommandOptions cmd(argc, argv);

  // test command options
  LOG(INFO) << "Main Class: " << cmd.mainClassName.c_str();
  LOG(INFO) << "Class Path: " << cmd.classPath.c_str();
  LOG(INFO) << "JRE Path: " << cmd.jrePath.c_str();

  // Load Classes
  classloader::FileLoader fileLoader(cmd.jrePath, cmd.classPath);
  utils::ByteReader classFileReader(MAX_CLASSFILE_SIZE);
  fileLoader.loadClassFile(cmd.mainClassName, classFileReader.bytePool);
  classloader::ClassInfo classInfo(classFileReader);

  // check the class info
  classInfo.display();
  LOG(INFO) << "ClassLoader end.";

  // interpret the program
  vm::Interpreter interpreter;
  interpreter.interpret(classInfo.methods[1]);

  return 0;
}
