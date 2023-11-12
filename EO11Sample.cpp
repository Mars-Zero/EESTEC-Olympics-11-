#include <Windows.h>
#include <iostream>
#include "EO11.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <mutex>
#include <thread>

std::unordered_map<uint32_t, std::pair<double, int>> myMap;
//pid -> {average, number of tests}

std::mutex mtx;
const double threshhold = 50;
const int threshgold_nr_files = 5;

bool verif_kill(int average, int nr) {
    return average >= threshhold && nr >= threshgold_nr_files;
}

void testFile(std::string path, uint32_t processId) {
    if (path.at(path.size() - 1) == '\\') {
        return;
    }
    //check if zip
    //resultOfPiVerif = call java pi
    //call alalalt signature

    mtx.lock();

    std::cout << "===============" << processId << "==============\n";
    std::cout << "PATH:::::::::::   " << path << "/n/n";
    std::cout << "===================================================\n";

    // if (myMap.find(processId) == myMap.end()) {
    //     myMap.insert(std::make_pair(processId, std::make_pair(0, 0)));
    // }

    // myMap[processId].first = (myMap[processId].first * myMap[processId].second /*+ resultOfPiVerif +*/) / myMap[processId].second == 0 ? 1 : 0;
    // myMap[processId].second++;
    // if (!verif_kill(myMap[processId].first, myMap[processId].second)) {
    //     EO11NotifyDetectionOnPID_t(processId);
    // }

    mtx.unlock();
}

void Callback(const struct Notification *notification, void *ctx)
{
    ctx;

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
    }
    break;
    case NotificationType::CREATE_FILE_POST:
    {
        const CreateFilePostNotification &notif = notification->createFilePost;
        Notification notif1 = *notification;
        std::wstring ws(notif1.createFilePost.filePath);
        std::string str(ws.begin(), ws.end());
        std::thread thr(testFile, str, notif1.createFilePost.processID);
        thr.detach();
    }
    break;
    case NotificationType::CREATE_FILE_PRE:
    {
        const CreateFilePreNotification &notif = notification->createFilePre;
        Notification notif1 = *notification;
    }
    break;
    case NotificationType::PROCESS_START:
    {
        const ProcessStartNotification &notif = notification->processStart;
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
        Notification notif1 = *notification;
        std::wstring ws(notif1.setFileInfo.newFilePath);
        std::string str(ws.begin(), ws.end());
        std::thread thr(testFile, str, notif1.createFilePost.processID);
        thr.detach();
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
