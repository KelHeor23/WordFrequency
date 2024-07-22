#include "WordFrequency/CountingWordFrequency.h"
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "The first argument is the input file, the second is the output file" << std::endl;
        return 0;
    }

    std::string fileNameIn(argv[1]);
    std::string fileNameOut(argv[2]);

    CountingWordFrequency counting(fileNameIn, fileNameOut);
    counting.run();

    return 0;
}
