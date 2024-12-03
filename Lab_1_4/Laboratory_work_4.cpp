#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <sstream>

/*
**************************************************************
*          Nizhniy Novgorod Technical University             *
*          Study work number 4. Task number 21                *
*          Performed student Larin Vladislav, 23-VMz.        *
**************************************************************
*/

// Функция умножения матрицы на скаляр
std::vector<std::vector<int>> matrixScalarMultiply(const std::vector<std::vector<int>>& matrix, int scalar) {
    std::vector<std::vector<int>> result(matrix.size(), std::vector<int>(matrix[0].size()));
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[0].size(); ++j) {
            result[i][j] = matrix[i][j] * scalar;
        }
    }
    return result;
}

//Функция нахождения минимального значения элемента матрицы
int findMatrixMin(const std::vector<std::vector<int>>& matrix) {
	int minVal = std::numeric_limits<int>::max();
    	for (const auto& rows : matrix){
   		for (const auto& element : rows){
   		if (element < minVal){
   			minVal = element;
   			}
   		} 
   	} 
 return minVal;
}
   	
   	

// Функция для чтения матрицы из файла
std::vector<std::vector<int>> readMatrixFromFile(const std::string& filename) {
    std::vector<std::vector<int>> matrix;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
       exit(1);
    }
    
    std::string line;
    while (std::getline (file, line)){
    	std::stringstream ss(line);
    	std::vector<int> row;
    	int value;
    	
    	while(ss >> value){
    		row.push_back(value);
    	}
    	matrix.push_back(row);
    } 
    file.close();
    return matrix;
}

int main() {
    // Считываем матрицы из файлов
        char hello_text[]=
            "***************************************************************************\n"
            "* Nizhniy Novgorod Technical University    *\n"
            "* Study work number 4. Variant 21   *\n"
            "* Performed student Larin Vladislav, 23-VMz.   *\n"
            "***************************************************************************\n";
    std::cout << hello_text << std::endl;
    std::vector<std::vector<int>> A = readMatrixFromFile("matrix_A.txt");
    std::cout << "Matrix A: " << std::endl;
    for (const auto& row : A) {
    	for (int val : row) {
 	       std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    std::vector<std::vector<int>> B = readMatrixFromFile("matrix_B.txt");
        std::cout << "Matrix B: " << std::endl;
    for (const auto& row : B) {
    	for (int val : row) {
 	       std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    std::vector<std::vector<int>> C = readMatrixFromFile("matrix_C.txt");
    std::cout << "Matrix C: " << std::endl;
    for (const auto& row : C) {
    	for (int val : row) {
 	       std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    // Находим Amin и Bmin
    int Amin = findMatrixMin(A);
    int Bmin = findMatrixMin(B);

    // Создаем матрицу R
    int difference = abs(Amin - Bmin);
    std::vector<std::vector<int>> R = matrixScalarMultiply(C, difference);

    // Выводим результаты
    std::cout << "Amin: " << Amin << std::endl;
    std::cout << "Bmin: " << Bmin << std::endl;
    std::cout << "Матрица R:" << std::endl;
    for (const auto& row : R) {
      for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
