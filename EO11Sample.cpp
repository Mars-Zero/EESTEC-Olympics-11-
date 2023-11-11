#include <Windows.h>
#include <iostream>
#include "EO11.h"
#include <unordered_map>
#include <vector>
#include <string>

std::unordered_map<uint32_t, std::vector<Notification *>> myMap;

void addNotification(uint32_t processID, Notification *notification)
{
    myMap[processID].push_back(notification);
}

void print_notif(Notification *notification)
{
    switch (notification->type)
    {
    case NotificationType::TEST_START:
        std::wcout << L"--------TEST_START--------" << std::endl;
        break;
    case NotificationType::TEST_END:
        std::wcout << L"--------TEST_END--------" << std::endl;
        break;
    case NotificationType::CLOSE_FILE:
    {
        const CloseFileNotification &notif = notification->closeFile;

        std::wcout << L"--------CLOSE_FILE--------" << std::endl;
        std::wcout << L"PID:         " << notif.processID << std::endl;
        std::wcout << L"TID:         " << notif.threadID << std::endl;
        std::wcout << L"FilePath:    " << notif.filePath << std::endl;
        std::wcout << L"FileId:      " << notif.fileId << std::endl;
        std::wcout << L"FileSize:    " << notif.fileSize << std::endl;
        std::wcout << L"FileContent: " << notif.fileContent << std::endl;
    }
    break;
    case NotificationType::CREATE_FILE_POST:
    {
        const CreateFilePostNotification &notif = notification->createFilePost;

        std::wcout << L"--------CREATE_FILE_POST--------" << std::endl;
        std::wcout << L"PID:               " << notif.processID << std::endl;
        std::wcout << L"TID:               " << notif.threadID << std::endl;
        std::wcout << L"FilePath:          " << notif.filePath << std::endl;
        std::wcout << L"FileId:            " << notif.fileId << std::endl;

        std::wcout << L"CreateDisposition: " << notif.createDisposition << std::endl;
        std::wcout << L"CreateOptions:     " << notif.createOptions << std::endl;
        std::wcout << L"DesiredAccess:     " << notif.desiredAccess << std::endl;
        std::wcout << L"FileAttributes:    " << notif.fileAttributes << std::endl;
        std::wcout << L"ShareAccess:       " << notif.shareAccess << std::endl;

        std::wcout << L"HasDeleteAccess:   " << notif.hasDeleteAccess << std::endl;
        std::wcout << L"HasReadAccess:     " << notif.hasReadAccess << std::endl;
        std::wcout << L"HasWriteAccess     " << notif.hasWriteAccess << std::endl;

        std::wcout << L"FileSize:          " << notif.fileSize << std::endl;
        std::wcout << L"FileContent:       " << notif.fileContent << std::endl;
    }
    break;
    case NotificationType::CREATE_FILE_PRE:
    {
        const CreateFilePreNotification &notif = notification->createFilePre;

        std::wcout << L"--------CREATE_FILE_PRE--------" << std::endl;
        std::wcout << L"PID:               " << notif.processID << std::endl;
        std::wcout << L"TID:               " << notif.threadID << std::endl;
        std::wcout << L"FilePath:          " << notif.filePath << std::endl;

        std::wcout << L"CreateDisposition: " << notif.createDisposition << std::endl;
        std::wcout << L"CreateOptions:     " << notif.createOptions << std::endl;
        std::wcout << L"DesiredAccess:     " << notif.desiredAccess << std::endl;
        std::wcout << L"FileAttributes:    " << notif.fileAttributes << std::endl;
        std::wcout << L"ShareAccess:       " << notif.shareAccess << std::endl;

        std::wcout << L"HasDeleteAccess:   " << notif.hasDeleteAccess << std::endl;
        std::wcout << L"HasReadAccess:     " << notif.hasReadAccess << std::endl;
        std::wcout << L"HasWriteAccess     " << notif.hasWriteAccess << std::endl;
    }
    break;
    case NotificationType::PROCESS_START:
    {
        const ProcessStartNotification &notif = notification->processStart;

        std::wcout << L"--------PROCESS_START--------" << std::endl;
        std::wcout << L"PID:        " << notif.processID << std::endl;
        std::wcout << L"PPID:       " << notif.parentProcessID << std::endl;
        std::wcout << L"Path:       " << notif.processPath << std::endl;
        std::wcout << L"ParentPath: " << notif.parentProcessPath << std::endl;
    }
    break;
    case NotificationType::PROCESS_STOP:
    {
        const ProcessStopNotification &notif = notification->processStop;

        std::wcout << L"--------PROCESS_STOP--------" << std::endl;
        std::wcout << L"PID:        " << notif.processID << std::endl;
        std::wcout << L"PPID:       " << notif.parentProcessID << std::endl;
    }
    break;
    case NotificationType::SET_FILE_INFO:
    {
        const SetFileInfoNotification &notif = notification->setFileInfo;

        std::wcout << L"--------SET_FILE_INFO--------" << std::endl;
        std::wcout << L"PID:      " << notif.processID << std::endl;
        std::wcout << L"TID:      " << notif.threadID << std::endl;
        std::wcout << L"FileId:   " << notif.fileId << std::endl;
        std::wcout << L"NewPath:  " << notif.newFilePath << std::endl;
        std::wcout << L"OldPath:  " << notif.oldFilePath << std::endl;
    }
    break;
    default:
        std::wcout << L"Error, invalid" << std::endl;
    }

    std::wcout << std::endl;
}

void print_notifications()
{
    for (auto m : myMap) {
        for (auto notif : myMap[m->first])
        {
            print_notif(notif);
        }
        
        std::wcout << std::endl;
    }
}

void Callback(struct Notification *notification, void *ctx)
{
    ctx;

    switch (notification->type)
    {
    case NotificationType::TEST_START:
        std::wcout << L"--------TEST_START--------" << std::endl;
        break;
    case NotificationType::TEST_END:
        std::wcout << L"--------TEST_END--------" << std::endl;
        print_notifications();
        break;
    case NotificationType::CLOSE_FILE:
    {
        const CloseFileNotification &notif = notification->closeFile;
        myMap[notif.processID].push_back(notification);
    }
    break;
    case NotificationType::CREATE_FILE_POST:
    {
        const CreateFilePostNotification &notif = notification->createFilePost;
        myMap[notif.processID].push_back(notification);
    }
    break;
    case NotificationType::CREATE_FILE_PRE:
    {
        const CreateFilePreNotification &notif = notification->createFilePre;
        myMap[notif.processID].push_back(notification);
    }
    break;
    case NotificationType::PROCESS_START:
    {
        const ProcessStartNotification &notif = notification->processStart;

        if (myMap.find(notif.processID) == myMap.end())
        {
            myMap.insert(std::make_pair(notif.processID, std::vector<Notification *>()));
        }
    }
    break;
    case NotificationType::PROCESS_STOP:
    {
        const ProcessStopNotification &notif = notification->processStop;
    }
    break;
    case NotificationType::SET_FILE_INFO:
    {
        const SetFileInfoNotification &notif = notification->setFileInfo;
        myMap[notif.processID].push_back(notification);
    }
    break;
    default:
        std::wcout << L"Error, invalid" << std::endl;
    }
}

HANDLE g_hStopEvent = nullptr;

BOOL WINAPI ConsoleHandler(DWORD signal)
{
    if (signal == CTRL_C_EVENT && g_hStopEvent)
        SetEvent(g_hStopEvent);

    return TRUE;
}

int main()
{
    g_hStopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!g_hStopEvent)
    {
        std::cout << "Error CreateEventW: " << GetLastError() << std::endl;
        return 1;
    }

    if (!SetConsoleCtrlHandler(ConsoleHandler, TRUE))
    {
        std::cout << "Error SetConsoleCtrlHandler: " << GetLastError() << std::endl;
        return 1;
    }

    HMODULE hModule = LoadLibraryW(L"EO11.dll");
    if (!hModule)
    {
        std::cout << "Error LoadLibraryW: " << GetLastError() << std::endl;
        return 1;
    }

    EO11Init_t pfnInit = (EO11Init_t)GetProcAddress(hModule, "EO11Init");
    if (!pfnInit)
    {
        std::cout << "Error, could not get EO11Init" << std::endl;
        return 1;
    }

    EO11Uninit_t pfnUninit = (EO11Uninit_t)GetProcAddress(hModule, "EO11Uninit");
    if (!pfnUninit)
    {
        std::cout << "Error, could not get EO11Uninit" << std::endl;
        return 1;
    }

    EO11AddFolderWatch_t pfnAddFolderWatch = (EO11AddFolderWatch_t)GetProcAddress(hModule, "EO11AddFolderWatch");
    if (!pfnAddFolderWatch)
    {
        std::cout << "Error, could not get EO11AddFolderWatch" << std::endl;
        return 1;
    }

    EO11NotifyDetectionOnPID_t pfnNotifyDetectionOnPID = (EO11NotifyDetectionOnPID_t)GetProcAddress(hModule, "EO11NotifyDetectionOnPID");
    if (!pfnNotifyDetectionOnPID)
    {
        std::cout << "Error, could not get EO11NotifyDetectionOnPID" << std::endl;
        return 1;
    }

    uint32_t result = pfnInit(&Callback, nullptr);
    if (result != ERROR_SUCCESS)
    {
        std::cout << "Error, could not initialize dll: " << result << std::endl;
        return 1;
    }

    WaitForSingleObject(g_hStopEvent, INFINITE);

    pfnUninit();

    return 0;
}
