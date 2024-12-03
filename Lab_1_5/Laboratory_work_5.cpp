#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
//#include <codecvt>
//#include <locale>


// Функция для чтения файла в строку
std::string readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(1);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}


// Функция для парсинга текста и извлечения слов
std::vector<std::string> parseText(const std::string& text) {
    std::vector<std::string> words;
    size_t pos = 0;
    while (pos < text.size()) {
        // Извлечение длины слова
        size_t lenStart = pos;
        while (isdigit(text[lenStart])) ++lenStart;

        int wordLength = stoi(text.substr(pos, lenStart - pos));
        pos = lenStart;

        // Извлечение слова
        if (pos + wordLength <= text.size()) {
            words.push_back(text.substr(pos, wordLength));
            pos += wordLength;
        } else {
            std::cerr << "Error: Incorrect word length specified in the text." << std::endl;
            exit(1);
        }

        // Пропуск пробелов, если они есть
        while (pos < text.size() && isspace(text[pos])) ++pos;
    }
    return words;
}

// Функция для вывода текста и N-го слова
void printTextAndNthWord(const std::vector<std::string>& words, int N) {
    for (const auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << std::endl;

    if (N > 0 && N <= words.size()) {
        std::cout << "The " << N << "-th word is: " << words[N - 1] << std::endl;
    } else {
        std::cout << "Error: N is out of range." << std::endl;
    }
}

int main() {
   
        char hello_text[]=
            "***************************************************************************\n"
            "* Nizhniy Novgorod Technical University    *\n"
            "* Study work number 5. Variant 21   *\n"
            "* Performed student Larin Vladislav, 23-VMz.   *\n"
            "***************************************************************************\n";
    std::cout << hello_text << std::endl;
    
    std::string filename;
    std::cout << "Enter the filename: ";
    std::cin >> filename;

    std::string text = readFile(filename);
    std::vector<std::string> words = parseText(text);

    std::cout << "Enter the value of N: ";
    int N;
    std::cin >> N;

    printTextAndNthWord(words, N);

    return 0;
}
