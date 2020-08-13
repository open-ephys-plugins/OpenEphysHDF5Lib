# Open Ephys HDF5 Common Library
A common library for all formats that write HDF5 files

## Installation
### Installing the HDF5 library
The plugin requires a specific version of the HDF5 library (≥1.8.12 and <1.8.21)
For windows, linux, and mac the required files are already included for the plugin

### Building the plugins
Building the plugins requires [CMake](https://cmake.org/). Detailed instructions on how to build open ephys plugins with CMake can be found in [our wiki](https://open-ephys.atlassian.net/wiki/spaces/OEW/pages/1259110401/Plugin+CMake+Builds).

#### [MacOS only] Update rpaths
Update the rpaths of HDF5 libraries linked to `libOpenEphysHDF5.dylib` by running the following commands:
```
install_name_tool -change /usr/local/lib/libhdf5.10.dylib @loader_path/libhdf5.10.dylib path/to/libOpenEphysHDF5.dylib
```
```
install_name_tool -change /usr/local/lib/libhdf5_cpp.15.dylib @loader_path/libhdf5_cpp.15.dylib path/to/libOpenEphysHDF5.dylib
```