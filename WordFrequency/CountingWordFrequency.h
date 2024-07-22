#ifndef COUNTINGWORDFREQUENCY_H
#define COUNTINGWORDFREQUENCY_H

#include <string>
#include <unordered_map>

class CountingWordFrequency
{
public:
    CountingWordFrequency(std::string fileNameIn, std::string fileNameOut)
        : fileNameIn(std::move(fileNameIn)), fileNameOut(std::move(fileNameOut)) {}

    void readFile(const std::string &filename);
    void saveFile(const std::string &filename);
    void run();

private:

    // Компаратор, сравнивающий сначала по количеству, а потом по алфавиту
    static bool compareWordsByNumberAndAlphabet(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b);

    void readLines();                                       // Функция чтения данных из очереди данных, считанныз из файла
    void addWordsToTheDictionary(const std::string &line);  // Функция распила строки на слова и записи их в словарь
    void writeTheDictionaryToTheBuffer();                   // Функция перевода словаря в буффер, для дальнейшей записи в файл

private:

    std::string fileNameIn;     // Имя файла для чтения
    std::string fileNameOut;    // Имя файла для записи

    std::unordered_map <std::string, int> dictionary;   // Словарь в котором будут учитыватсья слова
    std::string buffer;                                 // Вспомогательный буффер для записи в файл


};

#endif // COUNTINGWORDFREQUENCY_H
