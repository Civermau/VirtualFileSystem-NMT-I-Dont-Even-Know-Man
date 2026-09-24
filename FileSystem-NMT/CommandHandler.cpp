#include "CommandHandler.h"
#include "Display.h"
#include "SystemUtils.h"

CommandHandler::CommandHandler() : running(true)
{
    // Maybe idea, should not be deleted
    // Yep, definetively should NOT be deleted BY ANY MEANS
    // <Coconut here>
    // Stop even trying man
}

void CommandHandler::initialize(std::shared_ptr<Folder> rootFolder)
{
    root = rootFolder;
    ALIVE = rootFolder;
    registerCommands();
}

void CommandHandler::registerCommands()
{
    // Register all commands
    commands["clear"] = [](const std::string &)
    {
        dsp::ClearConsole();
    };

    commands["ls"] = [this](const std::string &)
    {
        root->ShowContents(dsp::StandarDisplay);
    };

    commands["tree"] = [this](const std::string &)
    {
        root->ShowAll(dsp::StandarDisplay, 0);
    };

    commands["pwd"] = [this](const std::string &)
    {
        dsp::StandarDisplay(root->GetPath() + "\n");
    };


    commands["fastfetch"] = [this](const std::string &)    // TODO: ADD THE LOGO SOMEHOW
    {
        dsp::StandarDisplay(sys::getUsername() + "@" + sys::getHostname() + "\n");
        dsp::StandarDisplay("-----------------------------------\n");
        dsp::StandarDisplay("OS: " + sys::getOS() + "\n");
        dsp::StandarDisplay("Host: " + sys::getHost() + "\n");
        dsp::StandarDisplay("Kernel: " + sys::getKernelVersion() + "\n");
        dsp::StandarDisplay("Uptime: " + sys::getUptime() + "\n");
        dsp::StandarDisplay("Shell: " + sys::getShell() + "\n");
        dsp::StandarDisplay("Resolution: " + sys::getResolution() + "\n");
        dsp::StandarDisplay("DE: " + sys::getDE() + "\n");
        dsp::StandarDisplay("WM: " + sys::getWM() + "\n");
        dsp::StandarDisplay("WM Theme: " + sys::getWMTheme() + "\n");
        
    };

    commands["help"] = [this](const std::string &)
    {
        dsp::StandarDisplay("Welcome to this Virtual File System\n");
        dsp::StandarDisplay("A fake file system based in the Linux command line\n");
        dsp::StandarDisplay("Original project made by @Zellterics\n");
        dsp::StandarDisplay("Contributions by @Civermau\n");
        dsp::StandarDisplay("-----------------------------------\n");
        dsp::StandarDisplay("Commands:\n");
        dsp::StandarDisplay("Command                         Description\n");
        dsp::StandarDisplay("-------                         -----------\n");
        dsp::StandarDisplay("clear                           Clear the console\n");
        dsp::StandarDisplay("ls                              List the contents of the current directory\n"); 
        dsp::StandarDisplay("tree                            Display the directory tree\n");
        dsp::StandarDisplay("pwd                             Display the current directory\n");
        dsp::StandarDisplay("fastfetch                       Display the system information\n");
        dsp::StandarDisplay("help                            Display this help message\n");
        dsp::StandarDisplay("rm <file/folder>                Remove a file or directory\n");
        dsp::StandarDisplay("mv <file/folder> <new_name>     Move a file or directory and rename it\n");
        dsp::StandarDisplay("mkdir <folder>                  Create a new directory\n");
        dsp::StandarDisplay("touch <file>                    Create a new file\n");
        dsp::StandarDisplay("cd <folder>                     Change the current directory\n");
        dsp::StandarDisplay("exit                            Exit the program\n");
    };

    commands["rm"] = [this](const std::string &arg)
    {
        if (!root->DeleteContent(arg))
        {
            dsp::StandarDisplay("bash: rm: " + arg + ": Doesn't exists\n");
        }
    };

    // Since files actually don't have content, a cp command would be just like another touch command, I see no need to implement it
    // Actually mv is kind of pointless too, again, there is no content so it's just like doing an rm and a touch in the same command
    // (literally what I am doing), but meh, at least this one pretends to be more complex
    commands["mv"] = [this](const std::string &arg)
    {
        if (!root->DeleteContent(arg))
        {
            dsp::StandarDisplay("bash: cp: " + arg + ": Doesn't exists\n");
            return;
        }
        if (!root->CreateContent(arg, NodeType::NodeFile))
        {
            dsp::StandarDisplay("bash: cp: " + arg + ": File already exists with that name\n");
        }
    };

    commands["exit"] = [this](const std::string &)
    {
        running = false;
    };

    commands["cd"] = [this](const std::string &arg)
    {
        if (arg == "..")
        {
            root = root->GetParent();
            return;
        }
        if (arg == "~")
        {
            root = ALIVE;
            return;
        }
        if (root->GetSubFolder(arg).expired())
        {
            dsp::StandarDisplay("bash: cd: " + arg + ": No such file or directory\n");
            return;
        }
        root = root->GetSubFolder(arg).lock();
    };

    commands["mkdir"] = [this](const std::string &arg)
    {
        if (!root->CreateContent(arg, NodeType::NodeFolder))
        {
            dsp::StandarDisplay("bash: mkdir: " + arg + ": Directory already exists\n");
        }
    };

    commands["touch"] = [this](const std::string &arg)
    {
        if (!root->CreateContent(arg, NodeType::NodeFile))
        {
            dsp::StandarDisplay("bash: touch: " + arg + ": File already exists\n");
        }
    };
}

bool CommandHandler::executeCommand(const std::string &input)
{
    // Parse command and arguments
    std::string cmd, args;
    std::tie(cmd, args) = parseCommand(input);

    // Skip empty commands
    if (cmd.empty())
    {
        return true;
    }

    // Execute command if it exists
    auto cmdIt = commands.find(cmd);
    if (cmdIt != commands.end())
    {
        cmdIt->second(args);
    }
    else
    {
        dsp::StandarDisplay("Unknown command: " + cmd + "\n");
    }

    return running;
}

std::pair<std::string, std::string> CommandHandler::parseCommand(const std::string &input)
{
    std::string cmd, arg;
    size_t spacePos = input.find(' ');

    if (spacePos != std::string::npos)
    {
        cmd = input.substr(0, spacePos);
        arg = input.substr(spacePos + 1);
    }
    else
    {
        cmd = input;
        arg = "";
    }

    return {cmd, arg};
}

std::string CommandHandler::getCurrentPath() const
{
    return root->GetPath();
}