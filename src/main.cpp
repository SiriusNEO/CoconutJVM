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
 * coconut is a toy Java Veritual Machine by SiriusNEO for learning purposes.
 * chaosfunc@gmail.com.                   2022 8.24
 */

#include "cmdline.hpp"

int main(int argc, char *argv[]) {
    CommandOptions cmd(argc, argv);

    // test command options
    printf("Main Class: %s\n", cmd.mainClassName.c_str());
    printf("Class Path: %s\n", cmd.classPath.c_str());
    printf("JRE Path: %s\n", cmd.classPath.c_str());
    printf("Main Class Arguments: ");
    for (int i = 0; i < cmd.args.size(); ++i) {
        if (i > 0) printf(", ");
        printf("%s", cmd.args[i].c_str());
    }
    printf("\n");

    return 0;
}