#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

//Encrypthor
std::string encrypthor(std::string text){
	std::vector<char> word(text.begin(), text.end());
	std::string alphabet = "abcdefghijklmnopqrstuvwxyz.!,_- ";

	for (int i = 0; i < (int)text.length(); i++){
		for (int j =0; j <(int)alphabet.length(); j++ ){
			if (word[i] == alphabet[j]){
				word[i] = alphabet[((j + 3))];
				break;
			}
		}
	}
	std::string str(word.begin(), word.end());
	return str;	 
} 

//Decrypthor
std::string decrypthor(std::string text, int n){
	std::vector<char> word(text.begin(), text.end());
	std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < (int)text.length(); i++){
		for (int j =0; j <(int)alphabet.length(); j++ ){
			if (word[i] == alphabet[j]){
				word[i] = alphabet[((j - n))];
				break;
			}
		}
	}
	std::string str(word.begin(), word.end());
	return str;	 
} 

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
/*
std::string printText(const std::string) {
    for (const auto& word : word) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
}
*/


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
    int key;

    std::string text = readFile(filename);
    std::string cryptotext = encrypthor(text);
    
    std::cout <<"Encoded message:\n"<< cryptotext << std::endl;
    
    std::cout << "Please, insert key: \n";
    std::cin >> key;
    
    
    std::string decryptotext = decrypthor(text, key);
//  std::cout << text << std::endl;
    std::cout << decryptotext << std::endl; 
  
//  printText(cryptotext);
//  printText(decryptotext);


    return 0;
}
