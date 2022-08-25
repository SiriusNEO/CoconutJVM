/*
 *  The main entry of @coconut.
 *   
 *   ________  ________  ________  ________  ________   ___  ___  _________   
 *   |\   ____\|\   __  \|\   ____\|\   __  \|\   ___  \|\  \|\  \|\___   ___\ 
 *   \ \  \___|\ \  \|\  \ \  \___|\ \  \|\  \ \  \\ \  \ \  \\\  \|___ \  \_| 
 *    \ \  \    \ \  \\\  \ \  \    \ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \  
 *     \ \  \____\ \  \\\  \ \  \____\ \  \\\  \ \  \\ \  \ \  \\\  \   \ \  \ 
 *      \ \_______\ \_______\ \_______\ \_______\ \__\\ \__\ \_______\   \ \__\
 *       \|_______|\|_______|\|_______|\|_______|\|__| \|__|\|_______|    \|__|
 *
 * coconut is a toy JVM(Java Veritual Machine) by SiriusNEO for learning purposes.
 * chaosfunc@gmail.com.                   2022 8.24
 */

#include "cmdline.hpp"
#include "utils/log.hpp"
#include "classloader/FileLoader.hpp"
#include "classloader/ClassInfo.hpp"

using namespace coconut;
using namespace cocotools;

#define MAX_CLASSFILE_SIZE 1048576  // 1MB

int main(int argc, char *argv[]) {
    CommandOptions cmd(argc, argv);

    // test command options
    Log::info("Main Class: %s", cmd.mainClassName.c_str());
    Log::info("Class Path: %s", cmd.classPath.c_str());
    Log::info("JRE Path: %s", cmd.jrePath.c_str());

    // Load Classes
    FileLoader fileLoader(cmd.jrePath, cmd.classPath);
    ByteReader classFileReader(MAX_CLASSFILE_SIZE);
    fileLoader.loadClassFile(cmd.mainClassName, classFileReader.bytePool);
    ClassInfo classInfo(classFileReader);
    classInfo.display();

    return 0;
}