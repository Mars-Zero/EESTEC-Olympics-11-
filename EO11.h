#ifndef _EESTEC_OLYMPICS_H
#define _EESTEC_OLYMPICS_H
#include <cstdint>

struct ProcessStartNotification {
    uint32_t processID;       /*ID of the process*/
    uint32_t parentProcessID; /*ID of the parent process*/
    const wchar_t* processPath;
    const wchar_t* parentProcessPath;
};

struct ProcessStopNotification {
    uint32_t processID;       /*ID of the process, is always given*/
    uint32_t parentProcessID; /*ID of the parent process, is always given*/
};

struct CreateFilePreNotification {
    uint32_t processID;      /*Accessor process ID*/
    uint32_t threadID;       /*Thread ID of the accessor thread*/
    const wchar_t* filePath; /*Path of the file*/

    uint32_t desiredAccess;     /*Content of DesiredAccess from NtCreateFile*/
    uint16_t shareAccess;       /*Content of ShareAccess from NtCreateFile*/
    uint16_t fileAttributes;    /*Content of FileAttributes from NtCreateFile*/
    uint32_t createDisposition; /*Content of CreateDisposition from NtCreateFile*/
    uint32_t createOptions;     /*Content of CreateOptions from NtCreateFile*/

    uint8_t hasReadAccess;   /*Boolean value, 1 if read access has been requested, 0 if not*/
    uint8_t hasWriteAccess;  /*Boolean value, 1 if write access has been requested, 0 if not*/
    uint8_t hasDeleteAccess; /*Boolean value, 1 if delete access has been requested, 0 if not*/
};

struct CreateFilePostNotification {
    uint32_t processID;      /*Accessor process ID*/
    uint32_t threadID;       /*Thread ID of the accessor thread*/
    const wchar_t* filePath; /*Path of the file*/
    uint64_t fileId;         /*Ntfsid of the file*/
    uint32_t createStatus;   /*Content of IoStatusBlock from NtCreateFile*/

    uint32_t desiredAccess;     /*Content of DesiredAccess from NtCreateFile*/
    uint16_t shareAccess;       /*Content of ShareAccess from NtCreateFile*/
    uint16_t fileAttributes;    /*Content of FileAttributes from NtCreateFile*/
    uint32_t createDisposition; /*Content of CreateDisposition from NtCreateFile*/
    uint32_t createOptions;     /*Content of CreateOptions from NtCreateFile*/

    uint8_t hasReadAccess;   /*Boolean value, 1 if read access has been requested, 0 if not*/
    uint8_t hasWriteAccess;  /*Boolean value, 1 if write access has been requested, 0 if not*/
    uint8_t hasDeleteAccess; /*Boolean value, 1 if delete access has been requested, 0 if not*/

    uint64_t fileSize; /*Size of the file*/
    void* fileContent; /*Content of the file*/
};

struct CloseFileNotification {
    uint32_t processID;      /*ID of the process that closed the file*/
    uint32_t threadID;       /*Thread ID of the accessor thread*/
    const wchar_t* filePath; /*Path of the file*/
    uint64_t fileId;         /*Ntfsid of the file*/
    uint8_t newFile;         /*Boolean value, 1 if the file is newly created, 0 if the file existet before on disk*/

    uint8_t isCopied;
    uint8_t isWritten;

    uint64_t fileSize; /*Size of the file*/
    void* fileContent; /*Content of the file*/
};

struct SetFileInfoNotification {
    uint32_t processID;         /*ID of the process that called NtSetFileInfo*/
    uint32_t threadID;          /*Thread ID of the accessor thread*/
    const wchar_t* oldFilePath; /*Old path of the file*/
    const wchar_t* newFilePath; /*New path of the file*/
    uint64_t fileId;            /*Ntfsid of the file*/
};

enum NotificationType {
    INVALID          = 0,
    PROCESS_START    = 1,
    PROCESS_STOP     = 2,
    CREATE_FILE_PRE  = 3,
    CREATE_FILE_POST = 4,
    CLOSE_FILE       = 5,
    SET_FILE_INFO    = 6,
    TEST_START       = 7,
    TEST_END         = 8
};

struct Notification {
    NotificationType type;
    union {
        struct ProcessStartNotification processStart;
        struct ProcessStopNotification processStop;
        struct CreateFilePreNotification createFilePre;
        struct CreateFilePostNotification createFilePost;
        struct CloseFileNotification closeFile;
        struct SetFileInfoNotification setFileInfo;
    };
};

typedef void (*CallbackFunc)( struct Notification* notification, void* ctx);

typedef uint32_t(__stdcall* EO11Init_t)(CallbackFunc cbk, void* ctx);
typedef void(__stdcall* EO11Uninit_t)();
typedef uint32_t(__stdcall* EO11AddFolderWatch_t)(const wchar_t* folderPath);
typedef void(__stdcall* EO11NotifyDetectionOnPID_t)(uint32_t pid);

#endif
