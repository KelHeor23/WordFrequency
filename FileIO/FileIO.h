#ifndef FILEIO_H
#define FILEIO_H

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>

namespace FileIO {

extern std::queue<std::string> queueData;
extern std::mutex mutexQueue;
extern std::condition_variable cvData;
extern std::atomic<bool> isFullFile;   // Флаг завершения обработки файла
extern std::atomic<bool> dataReady;   // Флаг для защиты от spurious wakeup

bool readFile(const std::string& filename);
bool saveFile(const std::string& filename, const std::string &buffer);

}



#endif // FILEIO_H
