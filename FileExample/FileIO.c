#include "FileIO.h"

static void FileIO_WriteData(struct IOBase *ioBase, char *data, size_t len)
{
    struct FileIO *fileIO = (struct FileIO*)ioBase;
    fwrite(data, sizeof(*data), len, fileIO->filePtr);
}

static void FileIO_ReadData(struct IOBase *ioBase, char *data, size_t len)
{
    struct FileIO *fileIO = (struct FileIO*)ioBase;
    size_t n = fread(data, sizeof(*data), len, fileIO->filePtr);
    if (n > 0)
    {
        data[n] = '\0';
    }
}

struct IOBase FileIOvtable =
{
    .WriteData = FileIO_WriteData,
    .ReadData = FileIO_ReadData
};

struct IOBase *CreateFileIO(char *pathname, char *mode)
{
    FILE *fptr = fopen(pathname, mode);

    if (fptr == NULL)
    {
        perror("File");
        return NULL;
    }

    struct FileIO *fileIO = (struct FileIO *)malloc(sizeof(struct FileIO));
    fileIO->vtable = FileIOvtable;
    fileIO->filePtr = fptr;

    return (struct IOBase *)fileIO;
}

void DestroyFileIO(struct IOBase *ioBase)
{
    struct FileIO *fileIO = (struct FileIO *)ioBase;
    fclose(fileIO->filePtr);

    free(fileIO);
}
