# Troubleshooting

While Devilution should produce a binary close to the original (compatible with Windows 95/NT), it may cause issues on newer systems. It has been reported to frequently crash on some setups, although for many it appears to be running flawless otherwise. Windows 7, Linux-WINE, and Windows 10 have all reported success.

Note that newer compilers may need to be tweaked to properly produce an executable. Currently this is being worked on to provide multiple Makefiles for a variety of systems. To ensure the best results, either MinGW or Visual Studio 2003/older should be used for the time being.

## Compilations with Different Toolchains
Compiling with different compilers (Visual C++, MinGW, Etc) will lead lead to different
results with how the executable interacts with the operating system, and may lead to either
weird crashes or different types of problems either during startup or runtime.

For example, for fearedbliss, on his Windows 10 x64 machine where he compiled Devilution
with MSYS2/MinGW32, he was getting the following messages:

![Screenshot 1: Windows 2000 Advisory](https://i.imgur.com/ScFLGu5.png)

![Screenshot 2: DirectDraw Error ](https://i.imgur.com/kiWkBuk.png)

In order for him to fix these issues, he simply used the DirectDraw patch (ddraw.dll)
and placed that .dll in his Diablo directory. That seems to have fixed it and he was
able to launch and run Diablo with no crashes (Quick smoke test - Cleared Level 1).