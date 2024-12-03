#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <stdexcept>
#include <iomanip>

// Класс TCharArray
class TCharArray {
private:
    char* buf;
    size_t len;
public:
    TCharArray() : buf(nullptr), len(0) {}
    TCharArray(const char* str) : buf(nullptr), len(strlen(str)) {
        buf = new char[len + 1];
        strcpy(buf, str);
    }
    TCharArray(const TCharArray& other) : buf(nullptr), len(other.len) {
        buf = new char[len + 1];
        strcpy(buf, other.buf);
    }
    ~TCharArray() {
        delete[] buf;
    }

    void set(const char* str) {
        delete[] buf;
        len = strlen(str);
        buf = new char[len + 1];
        strcpy(buf, str);
    }

    const char* get() const {
        return buf;
    }

    char& operator[](int index) {
        if (index < 0 || index >= len)
            throw std::out_of_range("Index out of range");
        return buf[index];
    }

    char& at(int index) {
        return operator[](index);
    }
};

// Класс String
class String : public TCharArray {
public:
    using TCharArray::TCharArray;

    String operator+(const String& other) const {
        size_t newLen = strlen(get()) + strlen(other.get());
        char* newBuf = new char[newLen + 1];
        strcpy(newBuf, get());
        strcat(newBuf, other.get());
        String result(newBuf);
        delete[] newBuf;
        return result;
    }

    bool operator==(const String& other) const {
        return strcmp(get(), other.get()) == 0;
    }

    bool operator!=(const String& other) const {
        return !(*this == other);
    }

    bool operator>(const String& other) const {
        return strcmp(get(), other.get()) > 0;
    }

    bool operator<(const String& other) const {
        return strcmp(get(), other.get()) < 0;
    }
};

// Класс записи
struct BookRecord {
    String title;
    String author;
    int catalogNumber;
    String publisher;
    double price;

    void print() const {
        std::cout << std::setw(20) << title.get() << " | "
                  << std::setw(15) << author.get() << " | "
                  << std::setw(5) << catalogNumber << " | "
                  << std::setw(15) << publisher.get() << " | "
                  << std::fixed << std::setprecision(2) << price << std::endl;
    }

    void input() {
        std::string buffer;
        std::cout << "Enter title: ";
        std::cin >> buffer;
        title.set(buffer.c_str());

        std::cout << "Enter author: ";
        std::cin >> buffer;
        author.set(buffer.c_str());

        std::cout << "Enter catalog number: ";
        std::cin >> catalogNumber;

        std::cout << "Enter publisher: ";
        std::cin >> buffer;
        publisher.set(buffer.c_str());

        std::cout << "Enter price: ";
        std::cin >> price;
    }
};

// Функция вывода справки
void printHelp() {
    std::cout << "Usage: program [OPTIONS]\n"
              << "--help, -h        Show help information\n"
              << "-s [N] [file]     Create table with N records in file\n"
              << "-r [N] [file]     Read up to N records from file\n"
              << "-e [N] [file]     Edit the Nth record in file\n"
              << "-a [N] [file]     Append N records to file\n";
}

// Основная функция
int main(int argc, char* argv[]) {
    if (argc < 2) {
        printHelp();
        return 1;
    }

    std::string command = argv[1];

    if (command == "--help" || command == "-h") {
        printHelp();
        return 0;
    } else if (command == "-s" && argc == 4) {
        // Создание таблицы
        int n = std::stoi(argv[2]);
        std::ofstream file(argv[3], std::ios::binary | std::ios::trunc);
        if (!file) {
            std::cerr << "Error: Cannot open file for writing\n";
            return 1;
        }

        for (int i = 0; i < n; ++i) {
            BookRecord record;
            record.input();
            file.write(reinterpret_cast<const char*>(&record), sizeof(record));
        }

        file.close();
    } else if (command == "-r" && argc == 4) {
        // Чтение таблицы
        int n = std::stoi(argv[2]);
        std::ifstream file(argv[3], std::ios::binary);
        if (!file) {
            std::cerr << "Error: Cannot open file for reading\n";
            return 1;
        }

        BookRecord record;
        int count = 0;
        while (file.read(reinterpret_cast<char*>(&record), sizeof(record)) && count < n) {
            record.print();
            ++count;
        }

        file.close();
    } else if (command == "-e" && argc == 4) {
        // Редактирование записи
        int n = std::stoi(argv[2]);
        std::fstream file(argv[3], std::ios::binary | std::ios::in | std::ios::out);
        if (!file) {
            std::cerr << "Error: Cannot open file for editing\n";
            return 1;
        }

        file.seekg((n - 1) * sizeof(BookRecord), std::ios::beg);
        BookRecord record;
        if (!file.read(reinterpret_cast<char*>(&record), sizeof(record))) {
            std::cerr << "Error: Record not found\n";
            file.close();
            return 1;
        }

        std::cout << "Editing record:\n";
        record.print();
        std::cout << "Enter new data:\n";
        record.input();

        file.seekp((n - 1) * sizeof(BookRecord), std::ios::beg);
        file.write(reinterpret_cast<const char*>(&record), sizeof(record));

        file.close();
    } else if (command == "-a" && argc == 4) {
        // Добавление записей
        int n = std::stoi(argv[2]);
        std::ofstream file(argv[3], std::ios::binary | std::ios::app);
        if (!file) {
            std::cerr << "Error: Cannot open file for appending\n";
            return 1;
        }

        for (int i = 0; i < n; ++i) {
            BookRecord record;
            record.input();
            file.write(reinterpret_cast<const char*>(&record), sizeof(record));
        }

        file.close();
    } else {
        std::cerr << "Error: Unknown command\n";
        printHelp();
        return 1;
    }

    return 0;
}
