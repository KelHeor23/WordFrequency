#include "CountingWordFrequency.h"

#include "../FileIO/FileIO.h"
#include "../FileIO/FileIOError.h"

#include <algorithm>
#include <iostream>
#include <regex>
#include <sstream>
#include <thread>

void CountingWordFrequency::readFile(const std::string &filename)
{
    std::thread readFileThread(FileIO::readFile, filename); // Чтение из файла запускаю в другом потоке
    readLines();                                            // В основном, обрабатываю строки

    readFileThread.join();                                  // Жду завершения потока чтения файла
}

void CountingWordFrequency::saveFile(const std::string &filename)
{
    FileIO::saveFile(filename, buffer);
}

void CountingWordFrequency::run()
{
    try {
        readFile(fileNameIn);               // Считываю файл в словарь
        writeTheDictionaryToTheBuffer();    // Перевожу словарь в буффер
        saveFile(fileNameOut);              // Сохраняю в файл
    }
    catch (const FileIO::FileIOError& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Something wrong" << std::endl;
    }
}

void CountingWordFrequency::addWordsToTheDictionary(const std::string &line)
{
    std::regex wordRegex("[a-zA-Z]+"); // Регулярное выражение для слов, содержащих только латинские буквы

    std::sregex_iterator wordIt(line.begin(), line.end(), wordRegex);
    std::sregex_iterator wordEnd;

    for (; wordIt != wordEnd; ++wordIt) {
        std::string word = wordIt->str();

        std::transform(word.begin(), word.end(), word.begin(), ::tolower); // Привожу слово к нижнему регистру
        dictionary[word]++;
    }
}

void CountingWordFrequency::writeTheDictionaryToTheBuffer()
{
    std::vector<std::pair<std::string, size_t>> temp; // Временный вектор для сортировки

    for (const auto &it : dictionary)
        temp.push_back(it);

    std::sort(temp.begin(), temp.end(), compareWordsByNumberAndAlphabet);

    std::stringstream ss; // Используется для оптимизации конкатенации
    ss.str().reserve(temp.size() * (sizeof(size_t) + 10)); // Для оптимизации, предполагаю что медианый размер слова не будет превышать 10 символов

    for (auto &it : temp)
        ss << it.second << " " << it.first << "\n";

    buffer = ss.str();
}

bool CountingWordFrequency::compareWordsByNumberAndAlphabet(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
    if (a.second == b.second) {
        return a.first < b.first;
    }
    return a.second > b.second;
}

void CountingWordFrequency::readLines()
{
    while (true) {
        std::unique_lock<std::mutex> lock(FileIO::mutexQueue);
        FileIO::cvData.wait(lock, [this]{
            return (!FileIO::queueData.empty() || FileIO::isFullFile) && FileIO::dataReady;
        });

        if (!FileIO::queueData.empty()) {
            std::string line = FileIO::queueData.front();
            FileIO::queueData.pop();
            addWordsToTheDictionary(line);  // Разбираем стркоу на слова и вносим в словарь
            lock.unlock();
        } else if (FileIO::isFullFile) {
            break;
        }
    }
}


