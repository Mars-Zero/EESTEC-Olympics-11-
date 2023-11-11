#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>

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
    {0X00, 0X00, 0X01, 0X00, 4},       // icn
    {0X1F, 0X9D, 0, 0, 2},       // tar
    {0X1F, 0XA0, 0, 0, 2},       // tar
    {0X1F, 0X8B,0 ,0, 2}, // tar gz
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
    {0X50, 0X4B, 0X03, 3},       // zip
    {0X50, 0X4B, 0X05, 3},       // zip
    {0X50, 0X4B, 0X07, 3},       // zip
    {0X4C, 0X5A, 0X49, 0X50, 4}, // lz
    {0X30, 0X37, 0X30, 0X37, 4}, //cpio
    {0X52, 0X61, 0X72, 0X21, 4}, // rar
    {0X89, 0X50, 0X4E, 0X47, 4}, // png
    {0XCA, 0XFE, 0XBA, 0XBE, 4}, // class
    {0XEF, 0XBB, 0XBF, 0, 3},    // txt utf 8
    {0XFF, 0XFE, 0, 0, 2},       // txt utf 16
    {0XFE, 0XFF, 0, 0, 2},       // txt utf 16
    {0XFE, 0XFE, 0, 0, 2},       // txt utf 16
    {0X0, 0X00, 0XFE, 0XFF, 2},       // txt utf 16
    {0X25, 0X50, 0X44, 0X46, 4}, // pdf
    {0X38, 0X42, 0X50, 0X53, 4}, // pdf
    {0X52, 0X49, 0X46, 0X46, 4}, // wav
    {0X52, 0X49, 0X46, 0X46, 4}, // avi
    {0XFF, 0, 0, 0, 1},          // mp3
    {0X49, 0X44, 0X32, 0, 1},          // mp3
    {0XC9, 0, 0, 0, 1},          // com
    {0X49, 0X44, 0X33, 0, 3},    // mp32
    {0X43, 0X44, 0X30, 0X30, 4}, //

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
        for (int j = 0; j < magicref[i][4]; j++)
        {
            if (magic[j] != magicref[i][j])
            {
                isSame = false;
                break;
            }
        }

        if (isSame)
        {
            return true;
        }
    }

    return false;
}

int main()
{
    // Get the filename from the user
    std::string filename = "Ransim//Scenarios//Archiver-TestFiles//MOCK_DATA1.csv.gz";

    // Check the magic number of the file
    bool validMagicNumber = checkMagicNumber(filename);

    // Print the result
    if (validMagicNumber)
    {
        std::cout << "The file has the correct magic number."
                  << "\n";
    }
    else
    {
        std::cout << "The file does not have the correct magic number."
                  << "\n";
    }

    /* std::ifstream file("example.jpg", std::ios::binary);
     if (file)
     {
         std::vector<char> buffer(4);
         file.read(buffer.data(), 4);
         std::vector<char> jpegMagicNumber = {0xFF, 0xD8, 0xFF, 0xE0};
         if (hasMagicNumber(buffer, jpegMagicNumber))
         {
             std::cout << "JPEG image" << std::endl;
         }
         else
         {
             std::cout << "Unknown file type" << std::endl;
         }
         file.close();
     }
     else
     {
         std::cout << "Failed to open the file" << std::endl;
     }*/
    return 0;
}
