#ifndef TEXTPROCESSOR_H
#define TEXTPROCESSOR_H

#include <string>
#include <stdexcept>

// ============================================================
//  Исключение: не удалось открыть файл
// ============================================================
class FileOpenException : public std::runtime_error {
public:
    explicit FileOpenException(const std::string& m) : std::runtime_error(m) {}
};

// ============================================================
//  TextProcessor — обработка текста из файла
//  Задание: вывести предложения с максимальным числом
//           знаков пунктуации
// ============================================================
class TextProcessor {
public:
    // Главная функция: читает файл и выводит результат
    static void processFile(const std::string& filename);

private:
    // Является ли символ знаком пунктуации
    static bool isPunctuation(char c);

    // Сколько знаков пунктуации в строке
    static int countPunctuation(const std::string& s);
};

#endif // TEXTPROCESSOR_H