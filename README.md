# Open Ephys HDF5 Common Library

A common library for any Open Ephys GUI plugins that need to write HDF5 files, based on version 1.21.1 of the HDF5 library. When building the GUI locally, plugins that depend on this library (such as [nwb-format](https://github.com/open-ephys-plugins/nwb-format)) must be compiled *after* this library.

## Building from source

First, follow the instructions on [this page](https://open-ephys.github.io/gui-docs/Developer-Guide/Compiling-the-GUI.html) to build the Open Ephys GUI.

**Important:** This library is intended for use with the latest version of the GUI, 0.6.X. The GUI should be compiled from the [`main`](https://github.com/open-ephys/plugin-gui/tree/main) branch, rather than the previous `master` branch.

Then, clone this repository into a directory at the same level as the `plugin-GUI`, e.g.:
 
```
Code
├── plugin-GUI
│   ├── Build
│   ├── Source
│   └── ...
├── OEPlugins
│   └── OpenEphysHDF5Lib
│       ├── Build
│       ├── Source
│       └── ...
```

### Windows

**Requirements:** [Visual Studio](https://visualstudio.microsoft.com/) and [CMake](https://cmake.org/install/)

From the `Build` directory, enter:

```bash
cmake -G "Visual Studio 17 2022" -A x64 ..
```

Next, launch Visual Studio and open the `OE_COMMONLIB_OpenEphysHDF5.sln` file that was just created. Select the appropriate configuration (Debug/Release) and build the solution.

Selecting the `INSTALL` project and manually building it will copy the library's `.dll` and any other required files into the GUI's `shared` directory.


### Linux

**Requirements:** [CMake](https://cmake.org/install/)

From the `Build` directory, enter:

```bash
cmake -G "Unix Makefiles" ..
cd Debug
make -j
make install
```

This will build the library and copy the `.so` file into the GUI's `plugins` directory.


### macOS

**Requirements:** [Xcode](https://developer.apple.com/xcode/) and [CMake](https://cmake.org/install/)

From the `Build` directory, enter:

```bash
cmake -G "Xcode" ..
```

Next, launch Xcode and open the `OE_COMMONLIB_OpenEphysHDF5.xcodeproj` file that now lives in the “Build” directory.

Running the `ALL_BUILD` scheme will compile the library; running the `INSTALL` scheme will install the `.dylib` file to `/Users/<username>/Library/Application Support/open-ephys/shared-api8`.
