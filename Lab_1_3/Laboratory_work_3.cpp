#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <iomanip>

/*
**************************************************************
*          Nizhniy Novgorod Technical University             *
*          Study work number 3. Task number 21                *
*          Performed student Larin Vladislav, 23-VMz.        *
**************************************************************
*/

constexpr double a = -1,  b = 3, delta = 0.1;
double x_value = a;
const int strings_arr = static_cast<int>((b - a) / delta + 1);
static double matrix_arr[2][strings_arr];
double* max_value;
double* min_value;

double F(double) {
    return pow(x_value,2) - 2*x_value + 2/(x_value-1);
}

int main() {
    char hello_text[]=
            "***************************************************************************\n"
            "* Nizhniy Novgorod Technical University    *\n"
            "* Study work number 3. Task number 21   *\n"
            "* Performed student Larin Vladislav, 23-VMz.   *\n"
            "***************************************************************************\n";

    std::cout << hello_text;
    std::ofstream txt_file("arr_data.txt");
    std::cout << "i : X[i] : Y[i] : &X[i] : &Y[i]\n";
    std::cout << "-----------------------------------------------"<< std::endl;
    txt_file << "i : X[i] : Y[i] : &X[i] : &Y[i]\n"
         << "-----------------------------------------------"<< std::endl;


    for (int i = 0; i < strings_arr; i++, x_value += delta) {
        matrix_arr[0][i] = x_value;
        matrix_arr[1][i] = F(x_value);
        std::cout << i << "\t" << matrix_arr[0][i] << "\t" << matrix_arr[1][i] << "\t" << &matrix_arr[0][i] << "\t" << &matrix_arr[1][i] << std::endl;
        txt_file << std::setw(2) << std::left << i << "\t"
                 << std::setw(5) << std::setprecision(2) << std::fixed << std::left << matrix_arr[0][i]
                 << "\t" << std::setw(10) << std::setprecision(8) << std::fixed << std::left << matrix_arr[1][i]
                 << "\t" << &matrix_arr[0][i] << "\t" << &matrix_arr[1][i] << std::endl;
    }

    max_value = std::max_element(matrix_arr[1], matrix_arr[1] + strings_arr);
    min_value = std::min_element(matrix_arr[1], matrix_arr[1] + strings_arr);

    std::cout << "\nSize of matrix: " << sizeof(matrix_arr) << " byte\n" << "Max element: " << max_value << "\nMin F(x_value): " << min_value;
    txt_file << "\nSize of matrix: " << sizeof(matrix_arr) << " byte\n" << "Max F(x_value): " << max_value <<"\nMin F(x_value): " <<  min_value;
    txt_file.close();
    return 0;
}
