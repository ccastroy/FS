
#include <stdio.h>
#include <stdlib.h>
#include "simplefs.h"


#define BlockSize 4096
#define MegInBytes 1048576

void readBlock(const char * diskName,unsigned int blockNumber,void * buffer)
{
    FILE * diskFile = fopen(diskName,"rb");
    fseek(diskFile,BlockSize*blockNumber,SEEK_SET);
    fread(buffer,1,BlockSize,diskFile);
    fclose(diskFile);
}
void writeBlock(const char * diskName,unsigned int blockNumber,void * buffer)
{
    FILE * diskFile = fopen(diskName,"rb+");
    fseek(diskFile,BlockSize*blockNumber,SEEK_SET);
    fwrite(buffer,1,BlockSize,diskFile);
    fclose(diskFile);
}

void createDiskInMB(const char * diskName,unsigned int diskSize)
{
    FILE *  diskFile = fopen(diskName,"wb");
    
    unsigned int sizeInBytes = diskSize*MegInBytes ;
    
    fseek(diskFile,sizeInBytes-1,SEEK_SET);
    
    char zero = 0;
    fwrite(&zero,1,1,diskFile);
    
    fclose(diskFile);
}

unsigned int getTotalBlocksOnDisk(const char * diskName)
{
    FILE * diskFile = fopen(diskName,"rb");
    fseek(diskFile,0,SEEK_END);
    unsigned int diskSize = ftell(diskFile);
    fclose(diskFile);
    return diskSize/BlockSize;
}



Directory setUpEmptyDirectory()
{
	  Directory emptyDir;
	  for(int i=0;i<128;i++)
		  emptyDir.entries[i].blockLocation=0;
	  return emptyDir;
}


void formatDisk(const char * diskName)
{
    unsigned int diskTotalBlocks = getTotalBlocksOnDisk(diskName);
    //Bloque en heap
    char * superBlock = (char *)malloc(BlockSize);
    superBlock[0]='f';
    superBlock[1]='s';
    *((int *)(superBlock+2))=3;
    *((int *)(superBlock+6))=diskTotalBlocks-1;
    *((int *)(superBlock+10))=diskTotalBlocks;
    *((int *)(superBlock+14))=diskTotalBlocks-3;
    
    //Bloque en stack
    char freeBlock[BlockSize];
    char * freeBlockPtr = freeBlock;
    
    unsigned int secondToLastBlock =diskTotalBlocks-2;
    
    for(unsigned int i=3;i<=secondToLastBlock;i++)
    {
        *((int *)freeBlockPtr)=i+1;
        writeBlock(diskName,i, freeBlockPtr);
    }
    *((int *)freeBlockPtr)=0;
    writeBlock(diskName,diskTotalBlocks-1, freeBlockPtr);
    
	Directory rootDir = setUpEmptyDirectory();

	writeBlock(diskName,2, &rootDir);
	writeBlock(diskName,1, superBlock);
    
    //La memoria en heap siempre se limpia!!!
    free(superBlock);
}



void createDirectory(const char * diskName,const char * path)
{
	Directory newDir = setUpEmptyDirectory();

	//int TargetBlock = findPathTargetBlock(diskName,path);

}

