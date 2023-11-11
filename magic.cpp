#include <iostream>
#include <fstream>
#include <vector>
#include <string>

const unsigned char magicref[1003][4] = {
    {0xFF, 0xD8, 0xFF, 0xE0}, // jpg
    {0XFF, 0XD8, 0XFF, 0XDB}, // jpg
    {0XFF, 0XD8, 0XFF, 0XEE}, // jpg
    {0XFF, 0XD8, 0XFF, 0XE1}, // jpg
    {0XFF, 0XD8, 0XFF, 0XE0}, // jpg
    {0X53, 0X51, 0X4C, 0X69}, // sql
    {0X53, 0X50, 0X30, 0X31}, // bin
    {0X69, 0X63, 0X6e, 0X73}, // icns
    {0X00, 0X00, 0X01, 0X00}, // icn
    {0X1F, 0X9D},             // tar
    {0X2D, 0X68, 0X6C, 0X30}, // lzh
    {0X2D, 0X68, 0X6C, 0X35}, // lzh
    {0X42, 0X41, 0X43, 0X4B}, // bac
    {0X42, 0X5A, 0X68},       // bz2
    {0X47, 0X49, 0X46, 0X38}, // gif
    {0X49, 0X49, 0X2A, 0X00}, // cr2
    {0X80, 0X2A, 0X5F, 0XD7}, // cin
    {0X42, 0X50, 0X47, 0XFB}, // bpg
    {0X42, 0X50, 0X47, 0XFB}, // bpg
    {0X00, 0X00, 0X00, 0X0C}, // jpeg 2000
    {0XFF, 0X4F, 0XFF, 0X51}, // jpeg 2000
    {0X4D, 0X5A},             // exe
    {0X5A, 0X4D},             // exe
    {0X50, 0X4B, 0X03},       // zip
    {0X52, 0X61, 0X72, 0X21}, // rar
    {0X89, 0X50, 0X4E, 0X47}, // png
    {0XCA, 0XFE, 0XBA, 0XBE}, // class
    {0XEF, 0XBB, 0XBF},       // txt utf 8
    {0XFF, 0XFE},             // txt utf 16
    {0XFF, 0XFF},             // txt utf 16
    {0X52, 0X49, 0X46, 0X46}, // wav
    {0X52, 0X49, 0X46, 0X46}, // avi
    {0XFF},                   // mp3
    {0X49, 0X44, 0X33},       // mp32
    {0X43, 0X44, 0X30, 0X30}, //

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
    bool result = false;
    printf("%d\n", sizeof(magicref) / sizeof(magicref[0]));
    for (int i = 0; i < sizeof(magicref) / sizeof(magicref[0]); i++)
    {

        if (memcmp(magic, magicref[i], sizeof(magicref[i])) == 0)
        {
            return true;
        }
    }

    return false;
}

int main()
{
    // Get the filename from the user
    std::string filename = "test.txt";

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