#include "../header_files/internal_commands.h" // String, Vector
#include "../header_files/util.h" // String, Vector, Unistd.h
#include <iostream>
#include <fstream>
#include <sstream>

// Example input >>>>> ("" are just for representation)     "source filename.sh [args...]"
// This is the same as though the user inputted this command: ". filename.sh [args...]"
// '.' and SOURCE are similar commands, if you need to research what 'source' does.

// This function is used to execute shell commands in the child process
bool executeShellCommand(const std::string& command) {
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Error executing command: " << command << std::endl;
        return false;
    }

// Buffer to store the outputs of each shell command
    char buffer[128];
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != nullptr)
            std::cout << buffer;
    }

// Therminate the child process
    pclose(pipe);
    return true;
}

bool internal_source(std::string args) {
    // Check if the command starts with "source"
    if (args.find("source ") == 0) {
        // Remove the "source " prefix
        args = args.substr(7);
    } else {
        std::cerr << "Error: Invalid source command. Please start with 'source filename.sh'" << std::endl;
        return false;
    }

    std::ifstream file(args);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << args << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines or lines starting with '#'
        if (line.empty() || line[0] == '#')
            continue;

        // Determine if it's a shell script
        bool isShellScript = line.find("#!") == 0;

        // Execute each line in bash
        if (!executeShellCommand(isShellScript ? line : "bash -c \"" + line + "\"")) {
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}

/* Testing the source command
int main() {
    std::string command = "source testing_script.sh"; 
    bool success = internal_source(command);
    if (!success) {
        std::cerr << "Failed to execute source command" << std::endl;
        return 1;
    }

    return 0;
}
*/
