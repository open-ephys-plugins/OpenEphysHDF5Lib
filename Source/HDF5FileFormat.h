/*
 ------------------------------------------------------------------

 This file is part of the Open Ephys GUI
 Copyright (C) 2014 Open Ephys

 ------------------------------------------------------------------

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 */

#ifndef HDF5FILEFORMAT_H_INCLUDED
#define HDF5FILEFORMAT_H_INCLUDED

#include <CommonLibHeader.h>

#define PROCESS_ERROR std::cerr << error.getCDetailMsg() << std::endl; return -1
#define CHECK_ERROR(x) if (x) std::cerr << "Error at " << __FILE__ " " << __LINE__ << std::endl;

#ifndef CHUNK_XSIZE
#define CHUNK_XSIZE 2048
#endif

#define DEFAULT_STR_SIZE 256

namespace H5
{
class DataSet;
class H5File;
class DataType;
}

namespace OpenEphysHDF5
{

class HDF5RecordingData;

/** 

	Base class for all HDF5 files

*/
class COMMON_LIB HDF5FileBase
{
public:

	/** Constructor */
    HDF5FileBase();

	/** Destructor -- closes the file if it's open  */
    virtual ~HDF5FileBase();

	/** Returns the full path to the HDF5 file */
	virtual String getFileName() = 0;

	/** Opens the file for writing */
    int open();

	/** Opens the file and sets the optimal chunk size for a particular number of channels */
	int open(int nChans);

	/** Closes the file (called automatically in destructor) */
    void close();
    
	/** Returns true if the file is open */
    bool isOpen() const;

	/** Returns true if the file is able to be opened */
	bool isReadyToOpen() const;


	class COMMON_LIB BaseDataType {
	public:
		enum Type { T_U8, T_U16, T_U32, T_U64, T_I8, T_I16, T_I32, T_I64, T_F32, T_F64, T_STR };
		BaseDataType();
		BaseDataType(Type, size_t);
		Type type;
		size_t typeSize;

		//handy accessors
		static const BaseDataType U8;
		static const BaseDataType U16;
		static const BaseDataType U32;
		static const BaseDataType U64;
		static const BaseDataType I8;
		static const BaseDataType I16;
		static const BaseDataType I32;
		static const BaseDataType I64;
		static const BaseDataType F32;
		static const BaseDataType F64;
		static const BaseDataType DSTR;
		static BaseDataType STR(size_t size);
	};

	static H5::DataType getNativeType(BaseDataType type);
	static H5::DataType getH5Type(BaseDataType type);

protected:

	/** Creates the basic file structure upon opening */
    virtual int createFileStructure() = 0;

	/** Sets an attribute (of any data type) at a given location in the file */
	int setAttribute(BaseDataType type, const void* data, String path, String name);

	/** Sets a string attribute at a given location in the file */
    int setAttributeStr(const String& value, String path, String name);

	/** Sets an array attribute (of any data type) at a given location in the file */
	int setAttributeArray(BaseDataType type, const void* data, int size, String path, String name);

	/** Sets a string array attribute at a given location in the file */
	int setAttributeStrArray(const StringArray& data, String path, String name);

	/** Creates a new group (throws an exception if it exists) */
    int createGroup(String path);

	/** Creates a new group (ignores if it exists) */
	int createGroupIfDoesNotExist(String path);

	/** Returns a pointer to a dataset at a given path*/
    HDF5RecordingData* getDataSet(String path);

	/** Creates a non-modifiable dataset with a string value */
	void createStringDataSet(String path, String value);
    
    /** Creates a dataset that holds an array of references to groups within the file */
    void createReferenceDataSet(String path, StringArray references);

    /** aliases for createDataSet */
	HDF5RecordingData* createDataSet(BaseDataType type, int sizeX, int chunkX, String path);
	HDF5RecordingData* createDataSet(BaseDataType type, int sizeX, int sizeY, int chunkX, String path);
	HDF5RecordingData* createDataSet(BaseDataType type, int sizeX, int sizeY, int sizeZ, int chunkX, String path);
	HDF5RecordingData* createDataSet(BaseDataType type, int sizeX, int sizeY, int sizeZ, int chunkX, int chunkY, String path);

    bool readyToOpen;

private:
	int setAttributeStrArray(Array<const char*>& data, int maxSize, String path, String name);

    /** Create an extendable dataset */
	HDF5RecordingData* createDataSet(BaseDataType type, int dimension, int* size, int* chunking, String path);

	/** Actually opens the file */
    int open(bool newfile, int nChans);

    ScopedPointer<H5::H5File> file;
    bool opened;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HDF5FileBase);
};

/** 

	Represents an HDF5 Dataset that can be extended indefinitely
	in blocks.

*/
class COMMON_LIB HDF5RecordingData
{
public:

	/** Constructor */
    HDF5RecordingData(H5::DataSet* data);

	/** Destructor */
    ~HDF5RecordingData();

	/** Writes a 1D block of data (samples) */
	int writeDataBlock(int xDataSize, HDF5FileBase::BaseDataType type, const void* data);

	/** Writes a 2D block of data (samples x channels) */
	int writeDataBlock(int xDataSize, int yDataSize, HDF5FileBase::BaseDataType type, const void* data);

	/** Writes a row of data in a 2D block (samples x channels) */
	int writeDataRow(int yPos, int xDataSize, HDF5FileBase::BaseDataType type, const void* data);

	/** Returns the number of samples written for each row (channel) */
    void getRowXPositions(Array<uint32>& rows);

private:
    int xPos;
    int xChunkSize;
    int size[3];
    int dimension;
    Array<uint32> rowXPos;
    ScopedPointer<H5::DataSet> dSet;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HDF5RecordingData);
};

}


#endif  // HDF5FILEFORMAT_H_INCLUDED
