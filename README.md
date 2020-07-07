# Open Ephys HDF5 Common Library
A common library for all formats that write HDF5 files

## Installation
### Installing the HDF5 library
The plugin requires a specific version of the HDF5 library (≥1.8.12 and <1.8.21)
For windows and linux, the required files are already included for the plugin
We have detailed instructions on our wiki on how to install the required HDF5 version for [macOS](https://open-ephys.atlassian.net/wiki/spaces/OEW/pages/491555/macOS).

### Building the plugins
Building the plugins requires [CMake](https://cmake.org/). Detailed instructions on how to build open ephys plugins with CMake can be found in [our wiki](https://open-ephys.atlassian.net/wiki/spaces/OEW/pages/1259110401/Plugin+CMake+Builds).
We highly recommend building all three projects simultaneously using the configuration provided in the top-level Build folder, instead of the individual plugins. Building the plugins individually will need manual tweaking for them to find the OpenEphysHDF5 common library.
 