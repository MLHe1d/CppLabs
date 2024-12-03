#include <iostream>
#include <cmath>

/*
**************************************************************
*          Nizhniy Novgorod Technical University             *
*          Study work number 2. Task number 1                *
*          Performed student Larin Vladislav, 23-VMz.        *
**************************************************************
*/

double n_value;
double iter_value;
double P_value = 0;


int main() {
   char hello_text[] = "Nizhniy Novgorod Technical University\n"
                        "Study work number 2. Task number 1.\n"
                        "Performed student Larin Vladislav , 23-VMz.";
    std::cout<< hello_text << std::endl;
    std::cout<< "Input n: " << std::endl;
    std::cin >> n_value;

    for(int i{0}; iter_value <= pow((2*n_value),2) ; i++){
        P_value += iter_value;
        iter_value = pow((n_value + i), 2);
    }
    std::cout << "Result: " << P_value << "." << std::endl;
    return 0;
}
