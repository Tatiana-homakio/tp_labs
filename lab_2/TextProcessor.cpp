#include "TextProcessor.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;   

// Возвращает true, если символ — знак пунктуации
bool TextProcessor::isPunctuation(char c) {
    return c == '.' || c == ',' || c == '!' || c == '?' ||
           c == ';' || c == ':' || c == '-' || c == '"' ||
           c == '\'' || c == '(' || c == ')';
}

// Считает знаки пунктуации в строке
int TextProcessor::countPunctuation(const string& s) {
    int c = 0;
    for (size_t i = 0; i < s.size(); ++i)
        if (isPunctuation(s[i])) ++c;              // символ пунктуации — увеличиваем счётчик
    return c;
}

// Читает файл, режет на предложения и печатает те, где больше всего пунктуации
void TextProcessor::processFile(const string& filename) {
    ifstream fin(filename);                        // открываем файл
    if (!fin.is_open())                            // не открылся — исключение
        throw FileOpenException("Cannot open file: " + filename);

    stringstream buffer;
    buffer << fin.rdbuf();                         // читаем весь файл в буфер
    string text = buffer.str();                    // получаем строку
    fin.close();

    const int MAX_SENT = 10000;                    // максимум предложений
    string* sentences = new string[MAX_SENT];      // свой массив строк
    int sentCount = 0;

    string current;
    for (size_t i = 0; i < text.size(); ++i) {
        char c = text[i];
        current += c;                              // накапливаем символы

        if (c == '.' || c == '!' || c == '?') {    // конец предложения
            size_t start = current.find_first_not_of(" \n\t\r"); // пропускаем пробелы
            if (start != string::npos) {
                size_t end = current.find_last_not_of(" \n\t\r");
                if (sentCount < MAX_SENT)
                    sentences[sentCount++] = current.substr(start, end - start + 1);
            }
            current.clear();                       // начинаем новое предложение
        }
    }
    // Остаток без завершающей точки
    size_t start = current.find_first_not_of(" \n\t\r");
    if (start != string::npos) {
        size_t end = current.find_last_not_of(" \n\t\r");
        if (sentCount < MAX_SENT)
            sentences[sentCount++] = current.substr(start, end - start + 1);
    }

    if (sentCount == 0) {                          // нет предложений — выходим
        cout << "File contains no sentences.\n";
        delete[] sentences;
        return;
    }

    int maxP = -1;                                 // ищем максимум пунктуации
    for (int i = 0; i < sentCount; ++i) {
        int p = countPunctuation(sentences[i]);
        if (p > maxP) maxP = p;
    }

    cout << "\n=== Sentences with maximum punctuation count ("
         << maxP << ") ===\n";

    for (int i = 0; i < sentCount; ++i) {          // печатаем все с максимумом
        if (countPunctuation(sentences[i]) == maxP)
            cout << ">> " << sentences[i] << "\n";
    }

    delete[] sentences;                            // освобождаем память
}