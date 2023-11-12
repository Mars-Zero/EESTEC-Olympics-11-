#include <Windows.h>
#include <iostream>
#include <cstdint>
#include "EO11.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <mutex>
#include <thread>
#include <fstream>
#include <cstring>
#include <cmath>

#define MONTEN 6

double detectEcryption(std::string filePath)
{
    long byteCount[256];
    long totalc = 0;
    long monte[MONTEN];
    int monteCounter = 0;
    double mcount, montex, montey, incircle, inmonte;
    inmonte = mcount = 0;
    incircle = pow(pow(256.0, (MONTEN / 2.0)) - 1, 2.0);

    for (int i = 0; i < 256; i++)
    {
        byteCount[i] = 0;
    }

    std::ifstream fin(filePath, std::ios::binary);
    if (fin.is_open())
    {
        while (true)
        {
            unsigned char oc;
            fin.read(reinterpret_cast<char *>(&oc), sizeof(oc));
            if (!fin)
            {
                break;
            }
            totalc += 1;
            byteCount[oc]++;

            monte[monteCounter++] = oc;
            if (monteCounter >= MONTEN)
            {
                int montej;

                monteCounter = 0;
                mcount++;
                montex = montey = 0;
                for (montej = 0; montej < MONTEN / 2; montej++)
                {
                    montex = (montex * 256.0) + monte[montej];
                    montey = (montey * 256.0) + monte[(MONTEN / 2) + montej];
                }
                if ((montex * montex + montey * montey) <= incircle)
                {
                    inmonte++;
                }
            }
        }
    }
    else
    {
        return 0;
    }

    double percent = 0;
    double montepi = 4.0 * (((double)inmonte) / mcount);
    double monteErrRate = 100.0 * (fabs(M_PI - montepi) / M_PI);
    if (monteErrRate < 0.01)
    {
        percent += 95;
    }
    double expecti = (double)totalc / 256.0;
    double t = 0;
    for (int i = 0; i < 256; i++)
    {
        double diff = byteCount[i] - expecti;
        t += (diff * diff) / expecti;
    }
    double chisq = t;
    if (chisq > 300 && monteErrRate < 0.03)
    {
        percent += 75;
    }
    if (chisq < 300 && monteErrRate > 0.03)
    {
        percent += 60;
    }
    if (chisq > 2000 && monteErrRate > 20)
    {
        percent = 0;
    }
    if (percent >= 100)
    {
        percent = 99;
    }
    return percent;
}

const unsigned char magicref[1003][5] = {
    {0xFF, 0xD8, 0xFF, 0xE0, 4}, // jpg
    {0XFF, 0XD8, 0XFF, 0XDB, 4}, // jpg
    {0XFF, 0XD8, 0XFF, 0XEE, 4}, // jpg
    {0XFF, 0XD8, 0XFF, 0XE1, 4}, // jpg
    {0XFF, 0XD8, 0XFF, 0XE0, 4}, // jpg
    {0X53, 0X51, 0X4C, 0X69, 4}, // sql
    {0X53, 0X50, 0X30, 0X31, 4}, // bin
    {0X69, 0X63, 0X6e, 0X73, 4}, // icns
    {0X00, 0X00, 0, 0, 2},       // icn
    {0X00, 0X00, 0X01, 0X00, 4}, // icn
    {0X1F, 0X9D, 0, 0, 2},       // tar
    {0X1F, 0XA0, 0, 0, 2},       // tar
    {0X1F, 0X8B, 0, 0, 2},       // tar gz
    {0X2D, 0X68, 0X6C, 0X30, 4}, // lzh
    {0X2D, 0X68, 0X6C, 0X35, 4}, // lzh
    {0X42, 0X41, 0X43, 0X4B, 4}, // bac
    {0X42, 0X5A, 0X68, 0, 3},    // bz2
    {0X47, 0X49, 0X46, 0X38, 4}, // gif
    {0X49, 0X49, 0X2A, 0X00, 4}, // cr2
    {0X52, 0X4E, 0X43, 0X01, 4}, // compression
    {0X52, 0X4E, 0X43, 0X02, 4}, // compression
    {0X80, 0X2A, 0X5F, 0XD7, 4}, // cin
    {0X42, 0X50, 0X47, 0XFB, 4}, // bpg
    {0X42, 0X50, 0X47, 0XFB, 4}, // bpg
    {0X00, 0X00, 0X00, 0X0C, 4}, // jpeg 2000
    {0XFF, 0X4F, 0XFF, 0X51, 4}, // jpeg 2000
    {0X4D, 0X5A, 0, 0, 2},       // exe
    {0X5A, 0X4D, 0, 0, 2},       // exe
    {0X50, 0X4B, 0X03, 0, 3},    // zip
    {0X50, 0X4B, 0X05, 0, 3},    // zip
    {0X50, 0X4B, 0X07, 0, 3},    // zip
    {0X4C, 0X5A, 0X49, 0X50, 4}, // lz
    {0X30, 0X37, 0X30, 0X37, 4}, // cpio
    {0X52, 0X61, 0X72, 0X21, 4}, // rar
    {0X89, 0X50, 0X4E, 0X47, 4}, // png
    {0XCA, 0XFE, 0XBA, 0XBE, 4}, // class
    {0XEF, 0XBB, 0XBF, 0, 3},    // txt utf 8
    {0XFF, 0XFE, 0, 0, 2},       // txt utf 16
    {0XFE, 0XFF, 0, 0, 2},       // txt utf 16
    {0XFE, 0XFE, 0, 0, 2},       // txt utf 16
    {0X0, 0X00, 0XFE, 0XFF, 4},  // txt utf 16
    {0X25, 0X50, 0X44, 0X46, 4}, // pdf
    {0X38, 0X42, 0X50, 0X53, 4}, // pdf
    {0X52, 0X49, 0X46, 0X46, 4}, // wav
    {0X52, 0X49, 0X46, 0X46, 4}, // avi
    {0XFF, 0, 0, 0, 1},          // mp3
    {0X49, 0X44, 0X32, 0, 3},    // mp3
    {0XC9, 0, 0, 0, 1},          // com
    {0X49, 0X44, 0X33, 0, 3},    // mp32
    {0X43, 0X44, 0X30, 0X30, 4}, // iso
    {0X00, 0XCF, 0X11, 0XE0, 4}, // docx/ppt
    {0X50, 0X4D, 0X4F, 0X43, 4}, // docx/ppt
    {0X75, 0X73, 0X74, 0X61, 4}, // tar
    {0X4F, 0X41, 0X52, 0, 3},    // wav
    {0X37, 0X7A, 0XBC, 0XAF, 4}, // 7z
    {0XFD, 0X37, 0X7A, 0X58, 4}, // tart
    {0X2D, 0X2D, 0X2D, 0X2D, 4}, // tart
    {0X3C, 0X3F, 0X78, 0X6D, 4}, // tart
    {0X3C, 0X00, 0X3F, 0X00, 4}, // tart
    {0X00, 0X3C, 0X00, 0X3F, 4}, // tart
    {0X3C, 0X00, 0X00, 0X00, 4}, // tart
    {0X00, 0X00, 0X00, 0X3C, 4}, // tart
    {0X7B, 0X5C, 0X72, 0X74, 4}, // tart
    {0X66, 0X74, 0X79, 0X70, 4}, // tart
    {0X78, 0X01, 0X78, 0X5E, 4}, // tart
    {0X78, 0XDA, 0, 0, 2},       // tart
    {0X78, 0X7D, 0, 0, 2},       // tart
    {0X78, 0XBB, 0, 0, 2},       // tart
    {0X78, 0XF9, 0, 0, 2},       // tart
    {0X46, 0X4C, 0X56, 0, 3},    // tart
    {0X72, 0X65, 0X67, 0X66, 4}, // tart

};

bool checkMagicNumber(const std::string &filename)
{
    // Open the file
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        return false;
    }

    // Read the magic number from the file
    unsigned char magic[sizeof(magicref[0])];
    file.read(reinterpret_cast<char *>(magic), sizeof(magic));

    // Close the file
    file.close();

    // Compare the magic number to the reference magic number
    for (int i = 0; i < sizeof(magicref) / sizeof(magicref[0]); i++)
    {
        bool isSame = true;

        int value = magicref[i][4];
        if (memcmp(magic, magicref[i], 2) == 0)
        {
            return true;
        }
    }

    return false;
}

const unsigned char zipref[1003][5] = {
    {0X1F, 0X9D, 0, 0, 2},       // tar
    {0X1F, 0XA0, 0, 0, 2},       // tar
    {0X1F, 0X8B, 0, 0, 2},       // tar gz
    {0X50, 0X4B, 0X03, 0, 3},    // zip
    {0X50, 0X4B, 0X05, 0, 3},    // zip
    {0X50, 0X4B, 0X07, 0, 3},    // zip
    {0X52, 0X61, 0X72, 0X21, 4}, // rar
};

bool checkZipNumber(const std::string &filename)
{
    // Open the file
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        return false;
    }

    // Read the magic number from the file
    unsigned char magic[sizeof(zipref[0])];
    file.read(reinterpret_cast<char *>(magic), sizeof(magic));

    // Close the file
    file.close();

    // Compare the magic number to the reference magic number
    for (int i = 0; i < sizeof(zipref) / sizeof(zipref[0]); i++)
    {
        bool isSame = true;

        int value = zipref[i][4];
        if (memcmp(magic, zipref[i], 2) == 0)
        {
            return true;
        }
    }

    return false;
}

std::unordered_map<uint32_t, std::pair<double, int>> myMap;
std::unordered_map<uint32_t, bool> pidAccesat;
std::unordered_map<uint64_t, double> files;
std::unordered_map<uint32_t, uint32_t> mapChildToParent;

std::mutex mtx;
const double threshhold = 50;
const int threshgold_nr_files = 5;

bool verif_kill(int average, int nr)
{
    return average >= threshhold && nr >= threshgold_nr_files;
}

void reset_values()
{
    myMap.clear();
    pidAccesat.clear();
    files.clear();
}

void testFile(std::string path, uint32_t processId, uint64_t fileId)
{
    if (path.at(path.size() - 1) == '\\')
    {
        return;
    }

    // std::cout << "===============" << processId << "==============\n";
    // std::cout << "PATH:::::::::::   " << path << "\n";
    // std::cout << "===================================================\n";

    double resultOfPiVerif = detectEcryption(path);
    mtx.lock();

    if (pidAccesat.find(processId) != pidAccesat.end())
    {
        mtx.unlock();
        return;
    }

    uint32_t ppid = mapChildToParent[processId];
    if (pidAccesat.find(ppid) != pidAccesat.end())
    {
        pidAccesat[processId] = true;
        std::cout << "RAPORTAT  " << processId << "\n";
        EO11NotifyDetectionOnPID_t(processId);
    }

    if (myMap.find(processId) == myMap.end())
    {
        myMap.insert(std::make_pair(processId, std::make_pair(0, 0)));
    }

    if (files.find(fileId) == files.end())
    {
        files.insert({fileId, resultOfPiVerif});
    }
    else if (resultOfPiVerif - files[fileId] < 5)
    {
        files[fileId] = resultOfPiVerif;
        resultOfPiVerif = 0;
    }
    else
    {
        myMap[processId].second++;
        myMap[processId].first = (1.0 * myMap[processId].first * (myMap[processId].second - 1.0) + resultOfPiVerif) / (myMap[processId].second * 1.0);
    }

    // std::cout << "PID: " << processId << " Average: " << myMap[processId].first << " number: " << myMap[processId].second << "\n";
    if (verif_kill(myMap[processId].first, myMap[processId].second))
    {
        pidAccesat[processId] = true;
        std::cout << "RAPORTAT  " << processId << "\n";
        EO11NotifyDetectionOnPID_t(processId);
    }

    mtx.unlock();
}

void Callback(const struct Notification *notification, void *ctx)
{
    ctx;

    switch (notification->type)
    {
    case NotificationType::TEST_START:
        reset_values();
        std::wcout << L"--------TEST_START--------" << std::endl;
        break;
    case NotificationType::TEST_END:
        reset_values();
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
        std::thread thr(testFile, str, notif1.createFilePost.processID, notif1.createFilePost.fileId);
        thr.detach();
        // std::wcout << "Proc that deletes:??  new path: " << notif.filePath << "   old path:" << notif.fileContent << "\n";
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
        mapChildToParent[notif.processID] = notif.parentProcessID;
        std::wcout << "Proc start: PID: " << notif.processID << " path: " << notif.processPath << " PPID: " << notif.parentProcessID << "\n";
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
        std::thread thr(testFile, str, notif1.setFileInfo.processID, notif1.setFileInfo.fileId);
        thr.detach();
        // std::wcout << "Proc that deletes:??  new path: " << notif.newFilePath << "   old path:" << notif.oldFilePath << "\n";
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
