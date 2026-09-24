#pragma once

#include <unordered_map>
#include <functional>
#include <string>
#include <memory>
#include "Folder.h"

class CommandHandler {
public:
    CommandHandler();
    ~CommandHandler() = default;

    // Initialize with root folder
    void initialize(std::shared_ptr<Folder> rootFolder);
    
    // Process command and return whether the program should continue running
    bool executeCommand(const std::string& input);
    
    // Get current folder path for display
    std::string getCurrentPath() const;

private:
    std::unordered_map<std::string, std::function<void(const std::string&)>> commands;
    std::shared_ptr<Folder> root;
    std::shared_ptr<Folder> ALIVE;
    bool running;

    // Initialize all available commands
    void registerCommands();
    
    // Parse command input
    std::pair<std::string, std::string> parseCommand(const std::string& input);
}; 