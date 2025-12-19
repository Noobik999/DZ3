#include <iostream>
#include "function_of_dz3.h"

int main() {
    std::string math_question;
    std::cout<<"Учтите, что десятичные дроби идут только через '.',а тригонометрия будет принимать только в градусах"<<std::endl;
    std::cout<<"Введите математическое выражение: ";
    std::getline(std::cin, math_question);
    std::vector<std::string> vyraj = obrat_polsk_not(math_question);
    for (int i = 0 ; i < vyraj.size(); i++) {
        std::cout<<vyraj[i]<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"Решение вашего уравнения: "<<reshenie_obr_polsk_not(vyraj)<<std::endl;
   // std::cout<<"Результат: "<<solve;
return 0;}