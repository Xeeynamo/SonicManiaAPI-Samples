# Sonic Mania mod samples

This repository aims to give a bootstrap to advanced modding techniques with Sonic Mania, using the power of [Mania Mod Loader](https://github.com/sonicretro/mania-mod-loader) and the revolutionary [ManiaAPI](https://github.com/thesupersonic16/ManiaAPI). This is especially focused on scripting functionality, allowing to override the game's logic by creating or expanding existing game objects.

## Samples

### Sample empty

This barebone mod is empty and it does not do anything. This contains the very minimal information required. It is a good place to start as you can use it as a playground or as a base to create your new mod.

## Set-up

The expectations by following this guide is to configure a development environment that will allow you to write the game scripts and test them with just a single click, allowing real-time debugging and breakpoint placement in the code.

### Repository and environment variables

Please be sure to clone the submodules when cloning this repository. A `git submodule update --init` would do the trick. Also be sure to add the environment variable `SONICMANIA_PATH` with the value of your Sonic Mania game directory.

### Remove Steam DRM

Strip the DRM from the game's executable, allowing to attach a debugger. Download [Steamless](https://github.com/atom0s/Steamless/releases), select the `SonicMania.exe` from your Steam copy and press _Unpack file_. Remember that the **executable name needs to be** `SonicMania.exe` as if you rename it as `SonicMania_unpack.exe`, for instance, Steam will force to load the original file name anyway.

### Disallow to reboot through Steam

By default when you open the game executable of a game it will be closed and re-executed through Steam internal launcher. We do not want to allow that as it would prevent to keep the debugger attached when launching the game. In the Sonic Mania game's folder create a new file called `steam_appid.txt` and paste in it the text `584400`.

### Disable ASLR

Windows applications are often compiled with ASLR enable, that instructs Windows to re-locate the application memory locations in-memory. This is bad when you do not want to lose the static address of variables and functions by keeping the base address the same at every execution. If you open `SonicMania.exe` with an hex editor, at the offset `0x176` you should notice the byte sequence `40 81 00 00`. That `40` there is the flag that enables the ASLR. Replace it to `00` so you have `00 81 00 00` and save your changes.

### Run your mod

An important step is to install [Mania Mod Manager](https://gamebanana.com/tools/6273). When you will run the "play" button on Visual Studio, the mod will be installed but not enabled by default. Ensure to do that from Mania Mod Manager at least for the first time. To run your mod and attach a debugger, just run it pressing F5 from Visual Studio.

## Special thanks

And _special_ is not due a formality. The community of Retro Engine Modding Server is an amazing source of talents and knowledge, while the modders & developers [thesupersonic16](https://github.com/thesupersonic16) and [Rubberduckycooly](https://github.com/Rubberduckycooly) gave me the initial bootstrap and all the framework that helped me to understand how Sonic Mania works internally. Without them, this would not be possible. Special thanks to all of them.
