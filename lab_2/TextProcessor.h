#ifndef TEXTPROCESSOR_H
#define TEXTPROCESSOR_H

#include <string>
#include <stdexcept>

// Исключение: не удалось открыть файл
class FileOpenException : public std::runtime_error {
public:
    explicit FileOpenException(const std::string& m) : std::runtime_error(m) {}
};

// Обработка текста: найти предложения с максимальным числом знаков пунктуации
class TextProcessor {
public:
    static void processFile(const std::string& filename);  // главная функция

private:
    static bool isPunctuation(char c);                     // символ — пунктуация?
    static int  countPunctuation(const std::string& s);    // сколько пунктуации в строке
};

#endif