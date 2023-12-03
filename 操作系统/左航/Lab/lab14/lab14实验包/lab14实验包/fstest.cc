#include "fstest.h"


void PerformanceTest(char *FileName)
{
    printf("Starting file system performance test:\n");
    FileWrite(FileName);
    FileRead(FileName);
    if (!kernel->fileSystem->Remove((char *)FileName)) {
      printf("Perf test: unable to remove %s\n", FileName);
      return;
    }
}


static void FileWrite(char *FileName)
{
    OpenFile *openFile;
    int i, numBytes;
    
    char contents[] = "1234567890";
    int contentsize = strlen(contents);
    int filesize = contentsize*10;//write the string 10 times.


    
    if (!kernel->fileSystem->Create((char*)FileName, filesize)) {
		printf("Perf test: can't create %s\n", FileName);
		return;
    }
    openFile = kernel->fileSystem->Open((char *)FileName);
    if (openFile == NULL) {
		printf("Perf test: unable to open %s\n", FileName);
		return;
    }
    for (i = 0; i < filesize; i += contentsize) {
		numBytes = openFile->Write((char *)contents, contentsize);
		if (numBytes < 10) {
			printf("Perf test: unable to write %s\n", FileName);
			delete openFile;
			return;
		}
        else{
            //printf("Sequential write of %d byte file, in %d byte chunks\n",filesize, contentsize);
            printf("Sequential write of %d:  %d byte chunks\n",i, numBytes);
        }
    }
    delete openFile;	// close file
}

static void FileRead(char *FileName)
{
	OpenFile *openFile;
	
    if ((openFile = kernel->fileSystem->Open((char *)FileName)) == NULL) {
		printf("Perf test: unable to open file %s\n", FileName);
		return;
    }

    int filesize = openFile->Length();
    int chunksize = 5;
    char *buffer = new(std::nothrow) char[filesize];
	int i, numBytes;

	
    for (i = 0; i < filesize; i += chunksize) {
		numBytes = openFile->Read(buffer, chunksize);
    printf("Sequential read %d: %d byte chunks\n",i, numBytes);
		//if ((numBytes < 10) || strncmp(buffer, Contents, chunksize)) {
        if(numBytes < chunksize){
			printf("Perf test: unable to read %s\n", FileName);
			delete openFile;
			delete [] buffer;
			return;
		}
    }
    delete [] buffer;
    delete openFile;	// close file
}
