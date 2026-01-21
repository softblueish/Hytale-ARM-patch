#include <iostream>
#include <filesystem>

void CopyRecursive(const std::filesystem::path& src, const std::filesystem::path& target) noexcept
{
    try
    {
        std::filesystem::copy(src, target, std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive);
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
    }
}

int main(int argc, char* argv[]) {
    std::string exePath = argv[0];
    std::string folderPath = exePath.substr(0, exePath.find_last_of("\\/"));
    std::string armJavaPath = folderPath + "\\jdk-25.0.1+8\\";

    std::string username = getenv("USERNAME");
    std::string gamePath = "C:\\Users\\" + username + "\\AppData\\Roaming\\Hytale\\";
    std::string packagePath = gamePath + "install\\release\\package\\";
    std::string fakeJREPath = packagePath + "jre\\latest\\";
    std::string nativeJREPath = packagePath + "jre-native\\latest\\";
    std::string nonNativeJREPath = packagePath + "jre-non-native\\latest\\";

    if (!std::filesystem::exists(gamePath)) {
        std::cout << "Error: Game path does not exist: " << gamePath << std::endl;
        std::cout << "Please make sure Hytale is installed" << std::endl;
        return 1;
    }

    std::cout << "Game installation found at: \"" << gamePath << "\"" <<std::endl;
    std::cout << std::endl;

    if(std::filesystem::exists(nativeJREPath) && std::filesystem::exists(nonNativeJREPath) && std::filesystem::exists(fakeJREPath)) {
        std::cout << "This patch has already been installed" << std::endl;
        std::cout << "To uninstall, please reinstall Hytale or validate the gamefiles through the launcher" << std::endl;
        system("pause");
        return 0;
    }

    std::cout << "Confirm installation of the ARM64 OpenJDK patch?" << std::endl;
    std::cout << "This will copy necessary files to the Hytale installation directory." << std::endl;
    std::cout << "Type 'yes' to confirm, or anything else to cancel: ";
    std::string userInput;
    std::cin >> userInput;
    if(userInput != "yes") {
        std::cout << "Installation cancelled." << std::endl;
        return 0;
    }
    
    std::cout << std::endl;
    std::cout << "[1/6] Started patch installation." << std::endl;
    std::filesystem::rename(packagePath + "jre", packagePath + "jre-non-native");
    std::cout << "[2/6] Original Java installation renamed to the non-native Java installation." << std::endl;
    std::filesystem::create_directories(fakeJREPath + "bin");
    std::cout << "[3/6] Created path for the impostor Java installation." << std::endl;
    std::filesystem::copy_file(folderPath + "\\fake-java.exe", fakeJREPath + "bin\\java.exe");
    std::cout << "[4/6] Copied impostor Java executable to the java installation." << std::endl;
    std::filesystem::create_directories(nativeJREPath);
    std::cout << "[5/6] Created path for the native Java installation." << std::endl;
    CopyRecursive(armJavaPath, nativeJREPath);
    std::cout << "[6/6] Copied Microsoft ARM OpenJDK 25.0.1+8 to the native Java installation." << std::endl;
    std::cout << std::endl;
    std::cout << "Installation complete. You can now launch Hytale with ARM64 Java support." << std::endl;
    system("pause");

    return 0;
}