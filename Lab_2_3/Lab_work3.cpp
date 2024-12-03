#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <getopt.h>
#include <cstring>

// Класс для представления записи
class Record {
public:
    std::string bookTitle;  // Наименование книги
    std::string authorName; // Ф.И.О. автора
    int catalogNumber;      // Номер по каталогу
    std::string publisher;  // Издательство
    double price;           // Стоимость книги

    // Сериализация записи в бинарный файл
    void writeToBinary(std::ofstream &out) const {
        size_t size;

        size = bookTitle.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        out.write(bookTitle.c_str(), size);

        size = authorName.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        out.write(authorName.c_str(), size);

        out.write(reinterpret_cast<const char*>(&catalogNumber), sizeof(catalogNumber));

        size = publisher.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        out.write(publisher.c_str(), size);

        out.write(reinterpret_cast<const char*>(&price), sizeof(price));
    }

    // Десериализация записи из бинарного файла
    void readFromBinary(std::ifstream &in) {
        size_t size;

        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        bookTitle.resize(size);
        in.read(&bookTitle[0], size);

        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        authorName.resize(size);
        in.read(&authorName[0], size);

        in.read(reinterpret_cast<char*>(&catalogNumber), sizeof(catalogNumber));

        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        publisher.resize(size);
        in.read(&publisher[0], size);

        in.read(reinterpret_cast<char*>(&price), sizeof(price));
    }

    // Вывод записи в консоль
    void print() const {
        std::cout << std::setw(20) << bookTitle
                  << std::setw(20) << authorName
                  << std::setw(10) << catalogNumber
                  << std::setw(20) << publisher
                  << std::setw(10) << price << '\n';
    }
};

// Дескриптор для хранения количества записей
struct Descriptor {
    size_t recordCount;

    void writeToBinary(std::ofstream &out) const {
        out.write(reinterpret_cast<const char*>(&recordCount), sizeof(recordCount));
    }

    void readFromBinary(std::ifstream &in) {
        in.read(reinterpret_cast<char*>(&recordCount), sizeof(recordCount));
    }
};

void printHelp() {
    std::cout << "Program for managing a binary table of book records.\n"
              << "Usage:\n"
              << "  --help, -h              : Show this help message\n"
              << "  -s [N] [file_name]      : Create a table with N records and save to file\n"
              << "  -r [N] [file_name]      : Read up to N records from the file and display\n\n"
              << "Fields of a record:\n"
              << "  1. Book Title\n"
              << "  2. Author's Full Name\n"
              << "  3. Catalog Number\n"
              << "  4. Publisher\n"
              << "  5. Book Price\n\n"
              << "Developer: Your Name\n";
}

void createRecords(int n, const std::string &fileName) {
    std::ofstream file(fileName, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file for writing.\n";
        return;
    }

    Descriptor descriptor;
    descriptor.recordCount = n;
    descriptor.writeToBinary(file);

    std::vector<Record> records(n);
    for (int i = 0; i < n; ++i) {
        std::cout << "Enter data for record #" << i + 1 << ":\n";
        std::cout << "Book Title: ";
        std::cin.ignore(); // Игнорировать символ новой строки
        std::getline(std::cin, records[i].bookTitle);
        std::cout << "Author's Full Name: ";
        std::getline(std::cin, records[i].authorName);
        std::cout << "Catalog Number: ";
        std::cin >> records[i].catalogNumber;
        std::cout << "Publisher: ";
        std::cin.ignore();
        std::getline(std::cin, records[i].publisher);
        std::cout << "Book Price: ";
        std::cin >> records[i].price;
    }

    for (const auto &record : records) {
        record.writeToBinary(file);
    }

    std::cout << "Records successfully saved to file: " << fileName << "\n";
    file.close();
}

void readRecords(int n, const std::string &fileName) {
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file for reading.\n";
        return;
    }

    Descriptor descriptor;
    descriptor.readFromBinary(file);

    if (descriptor.recordCount == 0) {
        std::cout << "The file is empty or contains no records.\n";
        return;
    }

    std::cout << std::setw(20) << "Book Title"
              << std::setw(20) << "Author"
              << std::setw(10) << "Catalog #"
              << std::setw(20) << "Publisher"
              << std::setw(10) << "Price\n";

    Record record;
    for (size_t i = 0; i < descriptor.recordCount && i < static_cast<size_t>(n); ++i) {
        record.readFromBinary(file);
        record.print();
    }

    file.close();
}

int main(int argc, char *argv[]) {
    const char *const short_opts = "hs:r:";
    const option long_opts[] = {
        {"help", no_argument, nullptr, 'h'},
        {nullptr, required_argument, nullptr, 's'},
        {nullptr, required_argument, nullptr, 'r'},
        {nullptr, 0, nullptr, 0}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, short_opts, long_opts, nullptr)) != -1) {
        switch (opt) {
            case 'h':
                printHelp();
                return 0;
            case 's': {
                int n = std::stoi(optarg);
                std::string fileName = argv[optind];
                createRecords(n, fileName);
                return 0;
            }
            case 'r': {
                int n = std::stoi(optarg);
                std::string fileName = argv[optind];
                readRecords(n, fileName);
                return 0;
            }
            default:
                std::cerr << "Invalid argument. Use --help for assistance.\n";
                return 1;
        }
    }

    std::cerr << "No arguments provided. Use --help for assistance.\n";
    return 1;
}
