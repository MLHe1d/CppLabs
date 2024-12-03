/*
/*
**************************************************************************
* Нижегородский государственный технический университет *
* Лабораторная работа №4. Задание №2. *
* Выполнила студентка группы 23-ВМз Бутыкова Юлия Олеговна *
**************************************************************************
*/
#include <iostream>
#include <string>
int sum;
std::string toBinary(int n)
{
if (n == 0) {
return "";
}
sum=sum+(n%2);
return toBinary(n / 2) + std::to_string(n % 2);
}
std::string fourNumber(int n)
{
if (n == 0) {
return "";
}
sum=sum+(n%4);
return fourNumber(n / 4) + std::to_string(n % 4);
}
std::string fiveNumber(int n)
{
if (n == 0) {
return "";
}
sum=sum+(n%5);
return fiveNumber(n / 5) + std::to_string(n % 5);
}
int main()
{
char logo[]=
"***************************************************************************\n"
"* Нижегородский государственный технический университет *\n"
"* Лабораторная работа №4. Задание №1. *\n"
"* Выполнила студентка группы 23-ВМз Бутыкова Юлия Олеговна *\n"
"***************************************************************************\n";
std::cout <<logo;
int size;
int choice;
std::cout << "Выбор способа подготовки данных: " << std::endl;
std::cout << "1 - Ручной ввод" << std::endl;
std::cout << "2 - Автоматическая программная генерация" << std::endl;
std::cin >> choice;
int *arr = new int [size];
if (choice == 1) {
std::cout << "Введите натуральное число <=40 "<<std::endl;
std::cin >> size;
}
else if (choice == 2) {
int a = rand() % 40; // Генерация случайного числа до 40
size = a;
}
else {
std::cout << "Ошибка: выбран неверный вариант!" << std::endl;
return 0;
}
if (size == 41){
std::cout<<"Ошибка: введено недопустимое число!";
return 0;
}
else if (size>41){
std::cout<< "Ошибка: введено недопустимое число!";
return 0;
}
for (int i=0; i<size; i++) {
arr[i] = rand ()%100;
}
for (int i=0; i<size; i++) {
std::cout<<arr[i]<<std::endl;
}
std::cout<< "==========================================="<<std::endl;
for (int i=0; i<size; i++) {
std::cout << "Число " << arr[i] << " в двоичной системе счисления " << toBinary(arr[i]);
std::cout<< "\tСумма чисел "<<sum<<std::endl;
sum=0;
}
std::cout<< "=============================================="<<std::endl;
for (int i=0; i<size; i++) {
if(arr[i]%2==0){
fourNumber(arr[i]);
std::cout<<sum<<std::endl;
sum=0;
}
else {
fiveNumber(arr[i]);
std::cout<<sum<<std::endl;
sum=0;
}
}
delete [] arr;
return 0;
}