

# How to run test on Windows
1. Download `curl` source code and deps you need (`openssl`, `libssh2` is required)  from https://curl.haxx.se/windows/
2. Extract `curl` to some place , e.g. `D:\Projects\curl`, so all `curl` source code should be in `D:\Projects\curl\curl-7.65.3` or something like that.
3. Create folder `D:\Projects\curl\deps`, and extract deps of your choice into it. This folder should contains `bin` `include` and `lib` folders. beware `openssl` might have its `DLLs` in its root folder while others have them in `bin` folder, you'd better copy those `DLLs` to `bin` as well.
4. Open `Developer Command Prompt for VS` and go to `D:\Projects\curl\curl-7.65.3\winbuild` to build. For test I suggest follwing command: `nmake /f Makefile.vc mode=dll WITH_SSH2=dll WITH_ZLIB=static MACHINE=x86`
5. Some folder like `D:\Projects\curl\curl-7.65.3\builds\libcurl-vc-x86-release-dll-zlib-static-ssh2-dll-ipv6-sspi-winssl` should be created. Now, copy `bin` `include` `lib` to `D:\Projects\curl\deps`. So it becomes the `deps` folder we need for our `tests`
6. Copy `deps` folder to `libqcurl` root folder, along side with `libqcurl` and `tests` folder
7. Build and run `libqcurl`
