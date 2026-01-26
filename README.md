# Running Hytale on Windows ARM Devices such as Snapdragon X Elite laptops
## You can download [a patch installer here](https://github.com/softblueish/Hytale-ARM-patch/releases/download/1.1/Installer-Windows-ARM64.zip)

> If you're struggling with installing the game itself, I can recommend [this guide](https://hytalehub.com/threads/a-quick-and-easy-guide-on-installing-and-optimizing-hytale-for-windows-on-arm-computers-snapdragon-x-elite-surface-ect.12875/). This patch only works if you've already managed to install the game

## Screenshot
<img width="2879" height="1619" alt="Screenshot 2026-01-26 124622" src="https://github.com/user-attachments/assets/41a1d2c7-dd45-48d3-8c1c-cc86b3983746" />

An image from one of my singleplayer tests using the [full control testing branch](https://github.com/softblueish/Hytale-ARM-patch/tree/main-full-control) of this patch (not for use outside development)
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

## Notice
To anyone who attempts to create a ``netty_quiche42_aarch_64.dll`` to try to make the game run 100% natively, first things first I commend you, but let me warn you: **I've spent several days straight now on this issue**, check the [losthope](github.com/softblueish/Hytale-ARM-patch/tree/losthope) branch to see some of my failed attempts. What I've found is that [Netty 4.2](https://github.com/netty/netty/tree/4.2) depends on libraries that are REALLY REALLY ancient (some made before Windows ARM really was a thing) and it's just plain awful to deal with.
