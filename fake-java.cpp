#include <iostream>

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
        std::cout << "[ARM64 OPENJDK PATCH] Detected HytaleServer.jar, falling to non-native (x86-64) JRE." << std::endl;
        size_t pos = command.find("jre-native");
        if (pos != std::string::npos) {
            command.replace(pos, std::string("jre-native").length(), "jre-non-native");
        }
    } else {
        std::cout << "[ARM64 OPENJDK PATCH] Launching with native (ARM64) JDK instead." << std::endl;
    }
    std::cout << "[ARM64 OPENJDK PATCH] Executing command: " << command << std::endl;
    std::cout << "[ARM64 OPENJDK PATCH] If you're wondering what this is, check out https://github.com/softblueish/Hytale-ARM-patch" << std::endl;

    
    system(command.c_str());
    return 0;
}