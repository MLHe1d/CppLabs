#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <getopt.h>
#include <cstring>

struct Record {
    std::string bookTitle;
    std::string authorName;
    int catalogNumber;
    std::string publisher;
    double price;
};

void printHelp() {
    std::cout << "Program for managing an array of records.\n"
              << "Usage:\n"
              << "  --help, -h              : Display this help information\n"
              << "  -s [N] [file_name]      : Create a file with N records\n"
              << "  -r [N] [file_name]      : Read up to N records from a file\n\n"
              << "Description of record fields:\n"
              << "  1. Book title\n"
              << "  2. Author's full name\n"
              << "  3. Catalog number\n"
              << "  4. Publisher\n"
              << "  5. Book price\n\n"
              << "Developer: Your Name\n";
}

void createRecords(int n, const std::string &fileName) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open the file for writing.\n";
        return;
    }

    std::vector<Record> records;
    for (int i = 0; i < n; ++i) {
        Record record;
        std::cout << "Enter data for record #" << i + 1 << ":\n";
        std::cout << "Book title: ";
        std::getline(std::cin, record.bookTitle);
        std::cout << "Author's full name: ";
        std::getline(std::cin, record.authorName);
        std::cout << "Catalog number: ";
        std::cin >> record.catalogNumber;
        std::cin.ignore();  // Clear the input buffer
        std::cout << "Publisher: ";
        std::getline(std::cin, record.publisher);
        std::cout << "Book price: ";
        std::cin >> record.price;
        std::cin.ignore();  // Clear the input buffer
        records.push_back(record);
    }

    for (const auto &rec : records) {
        file << rec.bookTitle << ';'
             << rec.authorName << ';'
             << rec.catalogNumber << ';'
             << rec.publisher << ';'
             << rec.price << '\n';
    }

    std::cout << "Records have been successfully saved to the file: " << fileName << "\n";
    file.close();
}

void readRecords(int n, const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open the file for reading.\n";
        return;
    }

    std::vector<Record> records;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream stream(line);
        Record record;
        std::getline(stream, record.bookTitle, ';');
        std::getline(stream, record.authorName, ';');
        stream >> record.catalogNumber;
        stream.ignore();  // Skip the delimiter
        std::getline(stream, record.publisher, ';');
        stream >> record.price;
        records.push_back(record);
    }

    if (records.empty()) {
        std::cout << "The file is empty or contains no records.\n";
        return;
    }

    std::cout << std::setw(20) << "Book Title"
              << std::setw(20) << "Author"
              << std::setw(10) << "Catalog"
              << std::setw(20) << "Publisher"
              << std::setw(10) << "Price\n";

    for (size_t i = 0; i < records.size() && i < static_cast<size_t>(n); ++i) {
        const auto &rec = records[i];
        std::cout << std::setw(20) << rec.bookTitle
                  << std::setw(20) << rec.authorName
                  << std::setw(10) << rec.catalogNumber
                  << std::setw(20) << rec.publisher
                  << std::setw(10) << rec.price << "\n";
    }
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
