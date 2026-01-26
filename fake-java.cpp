#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    std::cout << "[ARM64 OPENJDK PATCH] Java runtime intercepted successfully." << std::endl;

    std::string username = getenv("USERNAME");
    std::string command = "C:\\Users\\" + username + "\\AppData\\Roaming\\Hytale\\install\\release\\package\\jre-native\\latest\\bin\\java.exe";
    for (int i = 1; i < argc; ++i) {
        command += " ";

        if(command.substr(0, 2) == "C:") {
            command += "\"";
            command += argv[i];
            command += "\"";
        } else {
            command += argv[i];
        }
    }

    if(command.find("HytaleServer.jar") != std::string::npos) {
        std::cout << "[ARM64 OPENJDK PATCH] Detected HytaleServer.jar, falling to (custom) non-native (x86-64) JRE." << std::endl;

        command = "C:\\Users\\" + username + "\\AppData\\Roaming\\Hytale\\install\\release\\package\\jre-non-native\\latest\\bin\\java.exe";

        std::vector<std::string> bannedKeywords = {
        };
        for (int i = 1; i < argc; ++i) {
            bool bannedKeywordFound = false;
            for(const auto& keyword : bannedKeywords) {
                if(std::string(argv[i]).find(keyword) != std::string::npos) {
                    std::cout << "[ARM64 OPENJDK PATCH] Removing banned keyword argument: " << argv[i] << std::endl;
                    bannedKeywordFound = true;
                    break;
                }
            }
            if(bannedKeywordFound)
                continue;

            command += " ";
            if(command.substr(0, 2) == "C:") {
                command += "\"";
                command += argv[i];
                command += "\"";
            } else {
                command += argv[i];
            }
        }
        std::cout << "[ARM64 OPENJDK PATCH] Launching with native (ARM64) JDK instead." << std::endl;
        std::cout << "[ARM64 OPENJDK PATCH] Executing command: " << command << std::endl;
        std::cout << "[ARM64 OPENJDK PATCH] If you're wondering what this is, check out https://github.com/softblueish/Hytale-ARM-patch" << std::endl;

        system(("wt " + command).c_str());
        const int safetyTimer = 20000;
        for(int i = 1; i <= 100; i++) {
            std::cout << "-=|Setup|" << i << std::endl;
            Sleep(safetyTimer/100);
        }

        std::cout << ">> Singleplayer Ready <<" << std::endl;
        
    } else {
        std::cout << "[ARM64 OPENJDK PATCH] Launching with native (ARM64) JDK instead." << std::endl;
        std::cout << "[ARM64 OPENJDK PATCH] Executing command: " << command << std::endl;
        std::cout << "[ARM64 OPENJDK PATCH] If you're wondering what this is, check out https://github.com/softblueish/Hytale-ARM-patch" << std::endl;

        system(command.c_str());
    }

    return 0;
}