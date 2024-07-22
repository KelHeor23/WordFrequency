#include "../FileIO/FileIO.h"

#include "../FileIO/FileIOError.h"
#include <fstream>

namespace FileIO {

std::queue<std::string> queueData;
std::mutex mutexQueue;
std::condition_variable cvData;
std::atomic<bool> isFullFile = false;

bool readFile(const std::string &filename)
{
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;
        // Построчно считываем файл.
        // В идеале, считывать как можно большими кусками, но в данном примере решил пока обойтись стркоами.
        while (std::getline(file, line)) {
            std::unique_lock<std::mutex> lock(mutexQueue);
            queueData.push(line);
            lock.unlock();
            cvData.notify_one();
        }
        file.close();
        isFullFile = true;  // Отмечаю, что файл полностью прочитан
        cvData.notify_one();
    } else {
        throw FileIOError("Unable to open file: " + filename + "\n");
    }

    return true;
}

bool saveFile(const std::string &filename, const std::string &buffer)
{
    std::ofstream outputFile(filename, std::ios::out | std::ios::trunc);

    if(outputFile.is_open()) {
        outputFile << buffer;
        outputFile.close();
    } else {
        throw FileIOError("Unable to open or create file: " + filename + "\n");
    }

    return true;
}

}


