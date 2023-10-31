#include <iostream>
#include <fstream>
#include <string>
#include <vector>

unsigned short logBase2(unsigned short value)
{
    unsigned short result = 0;

    while (value >>= 1) // Shift right 1 bit until 1 bit remaining
    {
        result++;
    }
    return result;
}

unsigned short getDataByPagination(unsigned int targetIndex)
{
    const std::string filename = "data_memory.txt";

    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file 'data_memory.txt'." << std::endl;
        return 1;
    }

    std::string line;
    int currentIndex = 0;

    while (std::getline(file, line))
    {
        if (currentIndex == targetIndex)
            break;

        currentIndex++;
    }

    file.close();
    return (unsigned short)std::stoi(line);
}

// 32 bits - two level
void calculate(unsigned int virtualAddressDecimal)
{
    const unsigned short pageOffsetBytes = 4096;    // 2 ^ 12 = 4096
    const unsigned short pageLevelSizeBytes = 1024; // 2 ^ 10 = 1024

    std::cout << "O endereço " << virtualAddressDecimal << " contém:" << std::endl;

    unsigned short outerPageNumber = (virtualAddressDecimal >> (logBase2(pageOffsetBytes) + logBase2(pageLevelSizeBytes))); // Right-shift (remove offset + inner page level).
    std::cout << "\t* número da página de fora = " << outerPageNumber << std::endl;

    unsigned short innerPageNumber = ((virtualAddressDecimal >> logBase2(pageOffsetBytes)) & (pageLevelSizeBytes - 1)); // Right-shift (remove the offset) + Mask out outer page level.
    std::cout << "\t* número da página de dentro = " << innerPageNumber << std::endl;

    unsigned short offset = (virtualAddressDecimal & (pageOffsetBytes - 1)); // Mask out both outer and inner pages.
    std::cout << "\t* deslocamento = " << offset << std::endl;

    const int targetIndex = ((outerPageNumber * pageLevelSizeBytes) + (innerPageNumber * pageOffsetBytes) + offset);
    unsigned short dataAtAddress = getDataByPagination(targetIndex);
    std::cout << "\t* Valor lido: " << dataAtAddress << std::endl;
}

// 32 bits
void calculate(unsigned int virtualAddressDecimal, unsigned short pageOffsetBytes)
{
    std::cout << "O endereço " << virtualAddressDecimal << " contém:" << std::endl;

    unsigned int pageNumber = (virtualAddressDecimal >> logBase2(pageOffsetBytes)); // Right-shift (remove the offset).
    std::cout << "\t* número da página = " << pageNumber << std::endl;

    unsigned short offset = (virtualAddressDecimal & (pageOffsetBytes - 1)); // Mask out the page bits.
    std::cout << "\t* deslocamento = " << offset << std::endl;

    const unsigned int targetIndex = ((pageNumber * pageOffsetBytes) + offset);
    unsigned short dataAtAddress = getDataByPagination(targetIndex);
    std::cout << "\t* Valor lido: " << dataAtAddress << std::endl;
}

// 16 bits
void calculate(unsigned short virtualAddressDecimal, unsigned short pageOffsetBytes)
{
    std::cout << "O endereço " << virtualAddressDecimal << " contém:" << std::endl;

    unsigned short pageNumber = (virtualAddressDecimal >> logBase2(pageOffsetBytes)); // Right-shift (remove the offset, least significative bits).
    std::cout << "\t* número da página = " << pageNumber << std::endl;

    unsigned short offset = (virtualAddressDecimal & (pageOffsetBytes - 1)); // Extract the offset, least significative bits, by masking.
    std::cout << "\t* deslocamento = " << offset << std::endl;

    const unsigned int targetIndex = ((pageNumber * pageOffsetBytes) + offset);
    unsigned short dataAtAddress = getDataByPagination(targetIndex);
    std::cout << "\t* Valor lido: " << dataAtAddress << std::endl;
}

int main(int argc, char *argv[])
{
    const unsigned short pageOffsetBytes = 4096;
    bool isTwoLevelPagination = true;
    std::string input;

    std::vector<unsigned int> virtualAddresses;

    if (argc <= 1)
    {
        std::cerr << "No arguments specified. Reading from 'addresses.txt'..." << std::endl;

        std::ifstream addressFile("addresses.txt");
        if (!addressFile)
        {
            std::cerr << "Failed to open addresses.txt.\nExiting the program..." << std::endl;
            return 1;
        }

        unsigned int address;
        while (addressFile >> address)
        {
            virtualAddresses.push_back(address);
        }
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            unsigned int virtualAddressDecimal = std::stoi(argv[i]);
            virtualAddresses.push_back(virtualAddressDecimal);
        }
    }

    std::cout << "Do you wish to perform two-level pagination for 32-bit addresses? (Y/N): ";
    std::cin >> input;

    if (input == "N" || input == "n")
        isTwoLevelPagination = false;

    for (unsigned int virtualAddressDecimal : virtualAddresses)
    {
        std::cout << "- - - - - - - - - - - - - - - -" << std::endl;

        if (virtualAddressDecimal <= std::numeric_limits<unsigned short>::max())
        {
            std::cout << "** 16 bits **" << std::endl;
            calculate((unsigned short)virtualAddressDecimal, pageOffsetBytes);
        }
        else
        {
            if (isTwoLevelPagination)
            {
                std::cout << "** 32 bits - two level **" << std::endl;
                calculate(virtualAddressDecimal);
            }
            else
            {
                std::cout << "** 32 bits **" << std::endl;
                calculate(virtualAddressDecimal, pageOffsetBytes);
            }
        }
    }

    return 0;
}
