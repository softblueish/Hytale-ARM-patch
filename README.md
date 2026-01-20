# Running Hypixel on Windows ARM Devices such as Snapdragon X Elite laptops
## How it works
This is a program that pretends to be ``java.exe`` and switches dynamically between native [ARM64 Windows Microsoft Build of OpenJDK 25.0.1-8](https://learn.microsoft.com/en-us/java/openjdk/) and non-native built-in JRE that ships with Hytale for highest in-game performance while still letting the game run without crashing.
<img width="1382" height="389" alt="image" src="https://github.com/user-attachments/assets/9a588920-fbc3-476d-89ce-8eeaea0ec181" />
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
Script and instructions for installation coming soon
## How to build
```
g++ fakejava.cpp -o java.exe
```
## Credits
This is only possible thanks to the [ARM64 Windows Build of OpenJDK 25.0.1-8 by Microsoft](https://learn.microsoft.com/en-us/java/openjdk/)
