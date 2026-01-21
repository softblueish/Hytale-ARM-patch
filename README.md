# Running Hytale on Windows ARM Devices such as Snapdragon X Elite laptops
## You can download [a patch installer here](https://github.com/softblueish/Hytale-ARM-patch/releases/download/1.0/Installer-Windows-ARM64.zip)
## How it works
This is a program that pretends to be ``java.exe`` and switches dynamically between native [ARM64 Windows Microsoft Build of OpenJDK 25.0.1-8](https://learn.microsoft.com/en-us/java/openjdk/) and non-native built-in JRE that ships with Hytale for highest in-game performance while still letting the game run without crashing.
<img width="1382" height="389" alt="image" src="https://github.com/user-attachments/assets/9a588920-fbc3-476d-89ce-8eeaea0ec181" />

## Why is it necessary to dynamically switch between the two Java builds?
``HytaleClient.exe`` runs perfectly on ARM Windows OpenJDK builds while ``HytaleServer.exe`` doesn't and crashes immediately, meaning that you need to be able to detect which is needed when and run the appropriate Java build.

## Example of the modified filetree
```
C:\Users\USERNAME\AppData\Roaming\Hytale\install\release\package
├───game
│   └───latest
│       ├───Client
│       │   ├───Data
  [Game Files]
│ 
├───jre
│   └───latest
│       └───bin
│           └───java.exe (injector)
├───jre-native
│   └───latest
│       └─── (Microsoft Windows ARM build of OpenJDK 25.0.1-8)
├───jre-non-native
│   └───latest
│       └─── (OpenJRE 25.0.1-8 that ships with the game itself)
└───sig
    └───build-4
````
## How to install and use
Please use the installer in the release page, otherwise you will have to compile everything yourself and set the folder structure up to mimic what's in the filetree

## How to build
```
g++ fake-java.cpp -o fake-java.exe
```
```
g++ installer.cpp -o installer.exe
```
You can get the [exact build of OpenJDK 25.0.1-8 here](https://learn.microsoft.com/en-us/java/openjdk/download#:~:text=OpenJDK%2025%2E0%2E1%20LTS)

## Credits
This is only possible thanks to the [ARM64 Windows Build of OpenJDK 25.0.1-8 by Microsoft](https://learn.microsoft.com/en-us/java/openjdk/)
