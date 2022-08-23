/*
 *  The command line tool for @coconut.
 */


#pragma once

#include <cstring>
#include <string>
#include <vector>
#include <cstdio>

#define VERSION "coconut 0.1dev"

#define DEFAULT_CP "."
#define DEFAULT_MAINCN "Main.class"
#define DEFAULT_JREPATH "../../jre/"

void cmdlinePanic(const char* message) {
    printf("coconut: %s\n", message);
    exit(1);
}

class CommandOptions {
    public:
        int            argc;

        // jre path. not standard.
        std::string    jrePath;

        // cp
        std::string    classPath;
        // class
        std::string    mainClassName;
        // args
        std::vector<std::string>    args;

        CommandOptions(int _argc, char* _argv[]): 
        argc(_argc), 
        classPath(DEFAULT_CP), 
        mainClassName(DEFAULT_MAINCN), 
        args() {
            if (argc <= 1) {
                cmdlinePanic("error: no argument.");
            } 

            for (int i = 1; i < argc; ++i) {
                if (std::strcmp(_argv[i], "--help") == 0) {
                    printf("Usage: coconut [options] <mainclass> [args...] (to execute a class)\n\n");
                    printf("Arguments following the main class will be passed to main class.\n\n");
                    printf("Options:\n");
                    printf("\t--help\tshow the help documentation\n");
                    printf("\t--version\tshow the version information\n");
                    printf("\t--class-path\tclass search path\n");
                    printf("\t--jre-path\tjava runtime environment path\n");
                    exit(0);
                }
                else if (std::strcmp(_argv[i], "--version") == 0) {
                    printf("%s\n", VERSION);
                    exit(0);
                }
                else if (std::strcmp(_argv[i], "--class-path") == 0) {
                    ++i;
                    if (i == _argc) {
                        cmdlinePanic("error: --class-path requires class path specification");
                    }
                    classPath = std::string(_argv[i]);
                }
                else if (std::strcmp(_argv[i], "--jre-path") == 0) {
                    ++i;
                    if (i == _argc) {
                        cmdlinePanic("error: --jre-path requires jre path specification");
                    }
                    jrePath = std::string(_argv[i]);
                }
                else if (mainClassName == DEFAULT_MAINCN) {
                    // this must be the main class
                    mainClassName = std::string(_argv[i]);
                }
                else {
                    // args passed to main class
                    args.push_back(std::string(_argv[i]));
                }
            }
        }
};