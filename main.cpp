1234

#include <stdio.h>
#include "simplefs.h"

int main(int argc, const char * argv[])
{
    printf("Size %d %d\n",sizeof(DirectoryEntry),sizeof(Directory));
    createDiskInMB("DiskA", 10);
    printf("arrggh");
    formatDisk("DiskA");
    printf("NNII");

    return 0;
}

