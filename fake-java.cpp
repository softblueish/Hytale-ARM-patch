#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    std::cout << "[ARM64 OPENJDK PATCH] Java runtime intercepted successfully." << std::endl;

    // Gets the path to the ARM OpenJDK installation made by the patch
    std::string username = getenv("USERNAME");
    std::string executable = "C:\\Users\\" + username + "\\AppData\\Roaming\\Hytale\\install\\release\\package\\jre-native\\latest\\bin\\java.exe";

    // Separates the arguments and puts them into a vector sorrounded by quotes
    std::vector<std::string> args;
    for (int i = 1; i < argc; ++i) {
        args.push_back("\"" + std::string(argv[i]) + "\"");
    }

    // Joins the arguments back into a single command that can be ran
    std::string arguments = "";
    for (const auto& arg : args) {
        arguments += " " + arg;
    }

    // Checks if HytaleServer.jar is being ran, and if so, launch WSL instead
    if(arguments.find("HytaleServer.jar") != std::string::npos) {
        std::cout << "[ARM64 OPENJDK PATCH] Detected HytaleServer.jar, launching WSL" << std::endl;
        executable = "wsl.exe --exec java";

        // Make the paths WSL compatible
        for (auto& arg : args) {
            if(arg.find("C:\\") != std::string::npos) {
                std::string wslPath = arg;
                size_t pos = wslPath.find("C:\\");
                if (pos != std::string::npos) {
                    wslPath.replace(pos, 3, "/mnt/c/");
                }
                for (size_t pos = 0; (pos = wslPath.find('\\', pos)) != std::string::npos; pos++) {
                    wslPath.replace(pos, 1, "/");
                }
                arg = wslPath;
            }
        }

        // Joins the arguments back into a single command that can be ran
        std::string arguments = "";
        for (const auto& arg : args) {
            arguments += " " + arg;
        }

        // Replace localhost with the loopback IP address which can be accessed from the Host
        size_t ipPos = arguments.find("localhost");
        if (ipPos != std::string::npos) {
            arguments.replace(ipPos, 9, "127.0.0.1");
        }

        std::cout << "[ARM64 OPENJDK PATCH] Executing command: " << executable << arguments << std::endl;
        std::cout << "[ARM64 OPENJDK PATCH] If you're wondering what this is, check out https://github.com/softblueish/Hytale-ARM-patch" << std::endl;

        // Execute the command through WSL
        system((executable + arguments).c_str());

    } else {
        std::cout << "[ARM64 OPENJDK PATCH] Launching with native (ARM64) JDK instead." << std::endl;
        std::cout << "[ARM64 OPENJDK PATCH] Executing command: " << executable << arguments << std::endl;
        std::cout << "[ARM64 OPENJDK PATCH] If you're wondering what this is, check out https://github.com/softblueish/Hytale-ARM-patch" << std::endl;
        
        // Execute the command with the ARM64 JDK through Host
        system((executable + arguments).c_str());
    }
    return 0;
}