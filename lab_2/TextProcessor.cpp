#include "TextProcessor.h"
#include <fstream>
#include <iostream>
#include <sstream>

// ============================================================
//  Знак пунктуации?
// ============================================================
bool TextProcessor::isPunctuation(char c) {
    return c == '.' || c == ',' || c == '!' || c == '?' ||
           c == ';' || c == ':' || c == '-' || c == '"' ||
           c == '\'' || c == '(' || c == ')';
}

// ============================================================
//  Подсчёт знаков пунктуации в строке
// ============================================================
int TextProcessor::countPunctuation(const std::string& s) {
    int c = 0;
    for (size_t i = 0; i < s.size(); ++i)
        if (isPunctuation(s[i])) ++c;
    return c;
}

// ============================================================
//  Основная функция
// ============================================================
void TextProcessor::processFile(const std::string& filename) {
    // ---------- Открываем файл ----------
    std::ifstream fin(filename);
    if (!fin.is_open())
        throw FileOpenException("Cannot open file: " + filename);

    // ---------- Читаем весь файл в строку ----------
    std::stringstream buffer;
    buffer << fin.rdbuf();
    std::string text = buffer.str();
    fin.close();

    // ---------- Разбиваем на предложения ----------
    // Используем свой динамический массив строк (без std::vector)
    const int MAX_SENT = 10000;
    std::string* sentences = new std::string[MAX_SENT];
    int sentCount = 0;

    std::string current;
    for (size_t i = 0; i < text.size(); ++i) {
        char c = text[i];
        current += c;

        // Конец предложения
        if (c == '.' || c == '!' || c == '?') {
            size_t start = current.find_first_not_of(" \n\t\r");
            if (start != std::string::npos) {
                size_t end = current.find_last_not_of(" \n\t\r");
                if (sentCount < MAX_SENT)
                    sentences[sentCount++] = current.substr(start, end - start + 1);
            }
            current.clear();
        }
    }
    // Остаток без точки
    size_t start = current.find_first_not_of(" \n\t\r");
    if (start != std::string::npos) {
        size_t end = current.find_last_not_of(" \n\t\r");
        if (sentCount < MAX_SENT)
            sentences[sentCount++] = current.substr(start, end - start + 1);
    }

    // ---------- Проверка на пустоту ----------
    if (sentCount == 0) {
        std::cout << "File contains no sentences.\n";
        delete[] sentences;
        return;
    }

    // ---------- Ищем максимум пунктуации ----------
    int maxP = -1;
    for (int i = 0; i < sentCount; ++i) {
        int p = countPunctuation(sentences[i]);
        if (p > maxP) maxP = p;
    }

    // ---------- Выводим все предложения с максимумом ----------
    std::cout << "\n=== Sentences with maximum punctuation count ("
              << maxP << ") ===\n";

    bool found = false;
    for (int i = 0; i < sentCount; ++i) {
        if (countPunctuation(sentences[i]) == maxP) {
            std::cout << ">> " << sentences[i] << "\n";
            found = true;
        }
    }
    if (!found)
        std::cout << "No matching sentences found.\n";

    // ---------- Освобождаем память ----------
    delete[] sentences;
}