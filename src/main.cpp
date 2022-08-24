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

using namespace cocotools;

int main(int argc, char *argv[]) {
    CommandOptions cmd(argc, argv);

    // test command options
    Log::info("Main Class: %s", cmd.mainClassName.c_str());
    Log::info("Class Path: %s", cmd.classPath.c_str());
    Log::info("JRE Path: %s", cmd.jrePath.c_str());

    // Load Classes
    coconut::FileLoader fileLoader(cmd.jrePath, cmd.classPath);
    unsigned char* testPool = new unsigned char[2*1024*1024+10];
    int byteNum = fileLoader.readClassFile(cmd.mainClassName, testPool);
    if (byteNum > 0) {
        Log::info("Total bytes: %d", byteNum);
        for (int i = 0; i < byteNum; i++) {
            printf("%d ", testPool[i]);
        }
    }
    delete[] testPool;

    return 0;
}