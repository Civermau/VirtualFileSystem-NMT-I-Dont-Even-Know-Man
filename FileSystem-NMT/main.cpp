#include "Folder.h"
#include "Display.h"
#include "CommandHandler.h"

int main()
{
	// Create root folder
	std::shared_ptr<Folder> root = std::make_shared<Folder>("~");
	
	// Initialize command handler
	CommandHandler commandHandler;
	commandHandler.initialize(root);

	// Main command processing loop
	bool running = true;
	while (running)
	{
		// Get command input from user
		dsp::StandarDisplay(commandHandler.getCurrentPath() + "$ ");
		std::string input = dsp::GetInput();

		// Process the command and check if we should continue running
		running = commandHandler.executeCommand(input);
	}
	
	return 0;
}