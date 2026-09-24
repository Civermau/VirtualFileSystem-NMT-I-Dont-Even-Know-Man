#include <iostream>

#ifdef __linux__
    #include <unistd.h>
    #include <pwd.h>
    #include <sys/types.h>
    #include <sys/utsname.h>
    #include <sys/utsname.h>
    #include <fstream>
    #include <array>
    #include <algorithm>
#elif _WIN32
    #include <windows.h>
#endif

namespace sys {
    std::string getUsername();
    std::string getHostname();
    std::string getOS();
    std::string getHost();
    std::string getKernelVersion();
    std::string getUptime();
    std::string getShell();
    std::string getResolution();
    std::string getDE();
    std::string getWM();
    std::string getWMTheme();
    std::string getTheme();
    std::string getIcons();
    std::string getFonts();
    std::string getTerminal();
    std::string getCPU();
    std::string getGPU();
    std::string getMemory();

    std::string neofetch();
}
