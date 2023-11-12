EO11.dll - dll-ul de interfatare cu framework-ul oferit. Un exemplu de integrare in limbajul C++ este oferit in fisierul EO11Sample.cpp
	     EO11Sample.exe fiind binarul rezultat in urma compilarii.
EO11.h   - header-ul cu definitiile necesare integrarii EO11.dll
EO11Sample.cpp - Un sample de integrare al EO11.dll scris in limbajul C++
EO11Sample.exe - Rezultatul compilarii EO11.exe
vsdk.dll - dll necesar functionarii EO11.dll, trebuie pus langa EO11.dll
EO11TesterFramework.exe - framework-ul care ruleaza sample-urile date si la final va rula jurizarea.
				  Usage .\EO11TesterFramework.exe [--default_ransomware=$ransomwareName]
Ransim - folder cu sample-urile si testbed-urile





// void print_notif(Notification notification)
// {
//     switch (notification.type)
//     {
//     case NotificationType::TEST_START:
//         std::wcout << L"--------TEST_START--------" << std::endl;
//         break;
//     case NotificationType::TEST_END:
//         std::wcout << L"--------TEST_END--------" << std::endl;
//         break;
//     case NotificationType::CLOSE_FILE:
//     {
//         const CloseFileNotification &notif = notification.closeFile;

//         std::wcout << L"--------CLOSE_FILE--------" << std::endl;
//         std::wcout << L"PID:         " << notif.processID << std::endl;
//         std::wcout << L"TID:         " << notif.threadID << std::endl;
//         //std::wcout << L"FilePath:    " << notif.filePath << std::endl;
//         std::wcout << L"FileId:      " << notif.fileId << std::endl;
//         std::wcout << L"FileSize:    " << notif.fileSize << std::endl;
//         std::wcout << L"FileContent: " << notif.fileContent << std::endl;
//     }
//     break;
//     case NotificationType::CREATE_FILE_POST:
//     {
//         const CreateFilePostNotification &notif = notification.createFilePost;

//         std::wcout << L"--------CREATE_FILE_POST--------" << std::endl;
//         std::wcout << L"PID:               " << notif.processID << std::endl;
//         std::wcout << L"TID:               " << notif.threadID << std::endl;
//         //std::wcout << L"FilePath:          " << notif.filePath << std::endl;
//         std::wcout << L"FileId:            " << notif.fileId << std::endl;

//         std::wcout << L"CreateDisposition: " << notif.createDisposition << std::endl;
//         std::wcout << L"CreateOptions:     " << notif.createOptions << std::endl;
//         std::wcout << L"DesiredAccess:     " << notif.desiredAccess << std::endl;
//         std::wcout << L"FileAttributes:    " << notif.fileAttributes << std::endl;
//         std::wcout << L"ShareAccess:       " << notif.shareAccess << std::endl;

//         std::wcout << L"HasDeleteAccess:   " << notif.hasDeleteAccess << std::endl;
//         std::wcout << L"HasReadAccess:     " << notif.hasReadAccess << std::endl;
//         std::wcout << L"HasWriteAccess     " << notif.hasWriteAccess << std::endl;

//         std::wcout << L"FileSize:          " << notif.fileSize << std::endl;
//         std::wcout << L"FileContent:       " << notif.fileContent << std::endl;
//     }
//     break;
//     case NotificationType::CREATE_FILE_PRE:
//     {
//         const CreateFilePreNotification &notif = notification.createFilePre;

//         std::wcout << L"--------CREATE_FILE_PRE--------" << std::endl;
//         std::wcout << L"PID:               " << notif.processID << std::endl;
//         std::wcout << L"TID:               " << notif.threadID << std::endl;
//         // std::wcout << L"FilePath:          " << notif.filePath << std::endl;

//         std::wcout << L"CreateDisposition: " << notif.createDisposition << std::endl;
//         std::wcout << L"CreateOptions:     " << notif.createOptions << std::endl;
//         std::wcout << L"DesiredAccess:     " << notif.desiredAccess << std::endl;
//         std::wcout << L"FileAttributes:    " << notif.fileAttributes << std::endl;
//         std::wcout << L"ShareAccess:       " << notif.shareAccess << std::endl;

//         std::wcout << L"HasDeleteAccess:   " << notif.hasDeleteAccess << std::endl;
//         std::wcout << L"HasReadAccess:     " << notif.hasReadAccess << std::endl;
//         std::wcout << L"HasWriteAccess     " << notif.hasWriteAccess << std::endl;
//     }
//     break;
//     case NotificationType::PROCESS_START:
//     {
//         const ProcessStartNotification &notif = notification.processStart;

//         std::wcout << L"--------PROCESS_START--------" << std::endl;
//         std::wcout << L"PID:        " << notif.processID << std::endl;
//         std::wcout << L"PPID:       " << notif.parentProcessID << std::endl;
//         std::wcout << L"Path:       " << notif.processPath << std::endl;
//         std::wcout << L"ParentPath: " << notif.parentProcessPath << std::endl;
//     }
//     break;
//     case NotificationType::PROCESS_STOP:
//     {
//         const ProcessStopNotification &notif = notification.processStop;

//         std::wcout << L"--------PROCESS_STOP--------" << std::endl;
//         std::wcout << L"PID:        " << notif.processID << std::endl;
//         std::wcout << L"PPID:       " << notif.parentProcessID << std::endl;
//     }
//     break;
//     case NotificationType::SET_FILE_INFO:
//     {
//         const SetFileInfoNotification &notif = notification.setFileInfo;

//         std::wcout << L"--------SET_FILE_INFO--------" << std::endl;
//         std::wcout << L"PID:      " << notif.processID << std::endl;
//         std::wcout << L"TID:      " << notif.threadID << std::endl;
//         std::wcout << L"FileId:   " << notif.fileId << std::endl;
//         std::wcout << L"NewPath:  " << notif.newFilePath << std::endl;
//         std::wcout << L"OldPath:  " << notif.oldFilePath << std::endl;
//     }
//     break;
//     default:
//         std::wcout << L"Error, invalid" << std::endl;
//     }

//     std::wcout << std::endl;
// }

// void print_notifications()
// {
//     for (auto m : myMap) {
//         std::wcout << "=======================" << m.first << "=======================" << std::endl;

//         for (auto notif : myMap[m.first])
//         {
//             std::cout << "Path:" << notif. << std::endl;
//         }
        
//         std::wcout << "==========================================================" << std::endl;
//     }
// }