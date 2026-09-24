#include "SystemUtils.h"

namespace sys
{
#ifdef __linux__
    std::string getUsername()
    {
        struct passwd *pw = getpwuid(getuid());
        return pw ? pw->pw_name : "Unknown";
    }

    std::string getHostname()
    {
        char buffer[256];
        if (gethostname(buffer, sizeof(buffer)) == 0)
        {
            return std::string(buffer);
        }
        return "Unknown";
    }

    std::string getOS()
    {
        struct utsname u;
        uname(&u);
        return std::string(u.sysname);
    }

    std::string getHost()
    {
        struct utsname u;
        uname(&u);
        return std::string(u.machine);
    }

    std::string getKernelVersion()
    {
        struct utsname u;
        uname(&u);
        return std::string(u.sysname) + " " + u.release;
    }

    std::string getUptime()
    {
        double secs;
        std::ifstream("/proc/uptime") >> secs;
        int days = secs / 86400;
        int hours = (secs - days * 86400) / 3600;
        int minutes = (secs - days * 86400 - hours * 3600) / 60;
        int seconds = secs - days * 86400 - hours * 3600 - minutes * 60;
        return std::to_string(days) + " days, " + std::to_string(hours) + " hours, " + std::to_string(minutes) + " minutes, " + std::to_string(seconds) + " seconds";
    }

    std::string getShell()
    {
        return std::string(getenv("SHELL"));
    }

    std::string getResolution()
    {
        std::array<char, 128> buf;
        FILE *pipe = popen("xrandr --current | grep '*'", "r");
        fgets(buf.data(), buf.size(), pipe);
        pclose(pipe);
        int w, h;
        sscanf(buf.data(), "%dx%d", &w, &h);
        return std::to_string(w) + "x" + std::to_string(h);
    }

    std::string getDE()
    {
        std::string line, id;
        std::ifstream f("/etc/os-release");
        while (std::getline(f, line))
        {
            if (line.rfind("PRETTY_NAME=", 0) == 0)
            {
                size_t p = line.find('=');
                id = line.substr(p + 1);
                if (id.front() == '"' && id.back() == '"')
                    id = id.substr(1, id.size() - 2);
                break;
            }
        }
        return id;
    }

    std::string getWM()
    {
        char *wm = getenv("XDG_CURRENT_DESKTOP");
        return wm ? wm : "";
    }

    std::string getWMTheme()
    {
        std::array<char, 128> buf;
        FILE *p = popen("gsettings get org.gnome.desktop.interface gtk-theme", "r");
        fgets(buf.data(), buf.size(), p);
        pclose(p);
        std::string s(buf.data());
        s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
        return s;
    }

#elif _WIN32
    std::string getUsername()
    {
        return "Cant do on windows";
    }

    std::string getHostname()
    {
        return "Cant do on windows";
    }

    std::string getKernelVersion()
    {
        return "Cant do on windows";
    }
#endif
}