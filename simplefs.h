
#ifndef FS_simplefs_h
#define FS_simplefs_h


// basic filesystem

void readBlock(const char * diskName,unsigned int blockNumber,void * buffer);
void writeBlock(const char * diskName,unsigned int blockNumber,void * buffer);

//FS Structs ------------------

struct DirectoryEntry
{
	char  name[27];
	char  entryType;
	unsigned int blockLocation;
};

struct Directory
{
	DirectoryEntry entries[128];
};

//-------------------------------

// utilities

void createDiskInMB(const char * diskName,unsigned int diskSize);

void formatDisk(const char * diskName);
unsigned int getTotalBlocksOnDisk(const char * diskName);

//Directory utilities
  Directory setUpEmptyDirectory();
  


//--------------------------------

//FS API
void createDirectory(const char * diskName,const char * path);
void listDirectory(const char * diskName,const char * path);


//-------------------------------


#endif
