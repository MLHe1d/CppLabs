#include <iostream>
#include <cmath>

/*
**************************************************************
*          Nizhniy Novgorod Technical University             *
*          Study work number 2. Task number 2                *
*          Performed student Larin Vladislav, 23-VMz.        *
**************************************************************
*/

double x_value = 0.05;
double AVG = 0;
double len_value = (1.55-0.05)/0.05;

double F(double){
    double y = 3* sqrt(x_value) + (4 / pow(x_value, 5)) + pow(pow(x_value, 2), 1.0 / 3.0) - 7 / x_value;
    return y;

}

double Max_value, Min_value = F(x_value);

int main() {
    char hello_text[] = "Nizhniy Novgorod Technical University\n"
                        "Study work number 2. Task number 2.\n"
                        "Performed student Larin Vladislav , 23-VMz.";
    std::cout<< hello_text << std::endl;
    std::cout<< "Task No. 21: " << std::endl;
    std::cout<< "x_value  |  y\n";


    for (int i{1}; x_value < 1.55; i++){
        x_value = 0.05 * i;
        if (Max_value < F(x_value)){
            Max_value = F(x_value);
        }
        if(Min_value > F(x_value)){
            Min_value = F(x_value);
        }
        AVG += F(x_value);
        std::cout << x_value << " | " << F(x_value) << "\n";
    }
    std::cout << "Max value: " << Max_value <<std::endl;
    std::cout << "Min value: " << Min_value <<std::endl;
    std::cout << "AVG: " << AVG/len_value <<std::endl;

    return 0;
}
