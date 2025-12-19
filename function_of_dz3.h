#ifndef DZ3_FUNCTION_OF_DZ3_H
#define DZ3_FUNCTION_OF_DZ3_H
#include <iostream>
#include <cmath>
#include <string>
#include <cctype>
#include <list>
#include <vector>
#include <algorithm>
#include <stack>
#include <numbers>
#include <map>

//Данный код был скопирован из 8 лабы, но модернизирован под требования 3 дз
std::list<char> operators = {'+', '-', '*', '/'};
const char func_sin = 's';
const char func_cos = 'c';
const char func_tan = 't';
const char func_ctg = 'C';
const char func_exp = 'E';
bool x_exists = false;
int prioritety(const char& oper) {
    if (oper == '+' or oper == '-') {
        return 1;
    }
    if (oper == '*' or oper == '/') {
        return 2;
    }
    if (oper == func_sin or oper == func_cos or oper == func_tan or oper == func_ctg or oper == func_exp) {
        return 3;
    }
    return 0;
}

void perenos_operatorov(std::stack<char>& stek, std::vector<std::string>& itog) {
    if (!stek.empty()) {
        if (stek.top() == func_sin) {
            itog.push_back("sin");
        }
        else if (stek.top() == func_cos) {
            itog.push_back("cos");
        }
        else if (stek.top() == func_tan) {
            itog.push_back("tan");
        }
        else if (stek.top() == func_ctg) {
            itog.push_back("ctg");
        }
        else if (stek.top() == func_exp) {
            itog.push_back("exp");
        }
        else {
            if (stek.top() != '(') {
                std::string stek_oper_dlya_peremesheniya = std::string(1, stek.top());
                itog.push_back(stek_oper_dlya_peremesheniya);
            }
        }
        stek.pop();
    }
}

float perevod_gradus (float a, const std::string& func) {
    if (func == "sin") {
        return std::sin(a*M_PI / 180.0f);
    }
    if (func == "cos") {
        return std::cos(a*M_PI / 180.0f);
    }
    if (func == "tan") {
        if (std::fabs(std::cos(a*M_PI/180.0f)) < 1e-10) {
            std::cout<<"Тангенс не существует в заданном значении a: "<<a<<std::endl;
            return NAN;
        }
        else {
            return std::tan(a*M_PI / 180.0f);
        }

    }
    if (func == "ctg") {
        if (std::fabs(std::sin(a*M_PI/180.0f)) < 1e-10) {
            std::cout<<"Котангенс не существует в заданном значении a: "<<a<<std::endl;
            return NAN;
        }
        else {
            return std::cos(a*M_PI / 180.0f) / std::sin(a*M_PI / 180.0f);
        }
    }
    if (func == "exp") {
        return std::exp(a);
    }
    return a;
}

std::vector<std::string> obrat_polsk_not(const std::string& mat_vyr) {
    std::vector<std::string> itogovoe;
    std::string podvyrajenie;
    std::stack<char> stek_oper;
    static std::string x;
    bool prev = false;
    bool sled = false;
    bool dot_exist = false;
    bool unar_minus = false;
    for (int i = 0; i < mat_vyr.length(); i++) {
        if (mat_vyr[i] == '-') {
            unar_minus = false;
        }
        if (mat_vyr[i] == ' ') { //Данным условием избавляемся от всех лишних пробелов, даже если их расставлена целая 1000
            continue;
        }
        if (i+1 < mat_vyr.length() and mat_vyr[i] == '-' and (i == 0 or i-1 >= 0 and (std::find(operators.begin(), operators.end(),mat_vyr[i-1] ) != operators.end() or mat_vyr[i-1] == '('))) {
            podvyrajenie.push_back(mat_vyr[i]);
            unar_minus = true;
            continue;
        }
        if (std::isdigit(mat_vyr[i]) or (mat_vyr[i] == '.' and dot_exist == false)) {
            podvyrajenie.push_back(mat_vyr[i]);
            if (mat_vyr[i] == '.') {
                dot_exist = true;
            }
            if (i + 1 >= mat_vyr.length() or (!std::isdigit(mat_vyr[i+1]) and mat_vyr[i+1] !='.')) {
                itogovoe.push_back(podvyrajenie);
                podvyrajenie.clear();
                dot_exist = false;
            }
        }
        else if (dot_exist == true and mat_vyr[i] == '.') {
            std::cout<<"Ошибка, вы ввели число с 2 точками";
            exit(0);
        }
        else if (mat_vyr[i] == 'e') {
            if (i + 2 < mat_vyr.length() and mat_vyr[i+1] == 'x' and mat_vyr[i+2] == 'p') {
                stek_oper.push('E');
                i+=2;
                continue;
            }
            if (i + 1 < mat_vyr.length() and (std::find(operators.begin(), operators.end(), mat_vyr[i+1]) != operators.end())) {
                itogovoe.push_back(std::to_string(std::numbers::e));
            }

        }
        if (i + 2 < mat_vyr.length() and mat_vyr[i] == 's' and mat_vyr[i+1] == 'i' and mat_vyr[i+2] == 'n') {
            stek_oper.push('s');
            i+=2;
        }
        else if (i + 2 < mat_vyr.length() and mat_vyr[i] == 'c' and mat_vyr[i+1] == 'o' and mat_vyr[i+2] == 's') {
            stek_oper.push('c');
            i+=2;
        }
        else if (i + 2 < mat_vyr.length() and mat_vyr[i] == 't' and mat_vyr[i+1] == 'a' and mat_vyr[i+2] == 'n') {
            stek_oper.push('t');
            i+=2;
        }
        else if (i + 2 < mat_vyr.length() and mat_vyr[i] == 'c' and mat_vyr[i+1] == 't' and mat_vyr[i+2] == 'g') {
            stek_oper.push('C');
            i+=2;
        }
        else if (mat_vyr[i] == 'x') {
            if (x_exists == true and i-1 != 'e') {
                itogovoe.push_back(x);
            }
            if (i+1 < mat_vyr.length() and mat_vyr[i+1] == 'p' and mat_vyr[i-1] == 'e') {
                continue;
            }
            if (x_exists == false and ((i+1 > mat_vyr.length() and mat_vyr[i+1] !='p') or i <= mat_vyr.length()-1)) {
                std::cout<<"В выражении присутствует переменная x, введите значение для неё: ";
                std::string input;
                std::getline(std::cin, input);
                itogovoe.push_back(input);
                x = input;
                x_exists = true;
            }
            else if (i+1 < mat_vyr.length() and std::find(operators.begin(), operators.end(), mat_vyr[i+1]) == operators.end() and mat_vyr[i+1] != 'p' and mat_vyr[i+1] != ' ') {
                std::cout<<"В выражении присутствует ошибка, после x не следует оператор";
                exit(0);
            }
            }
        else if (mat_vyr[i] == 'p') {
            if (i+1 < mat_vyr.length() and (mat_vyr[i+1] == 'i')) {
                if (i > 0) {
                    if (std::find(operators.begin(), operators.end(), mat_vyr[i-1]) != operators.end() or mat_vyr[i-1] == ' ' or mat_vyr[i-1] == '(') {
                        prev = true;
                    }
                    else {
                        std::cout<<"Недопустимая запись";
                        exit(0);
                        }
                }
                else {
                    prev = true;
                }
                if (i+2 < mat_vyr.length()) {
                    if (std::find(operators.begin(), operators.end(), mat_vyr[i+2]) != operators.end() or mat_vyr[i+2] == ')') {
                        sled = true;
                    }
                    else {
                        std::cout<<"Недопустимая запись";
                        exit(0);
                    }
                }
                else {
                    sled = true;
                }
                if (sled == true and prev == true) {
                    itogovoe.push_back((std::to_string(std::numbers::pi)));
                    sled = false;
                    prev = false;
                    i++;
                }
            }
            else if ((i+1 < mat_vyr.length() and mat_vyr[i+1] != '(') or i+1 == mat_vyr.length()) {
                std::cout<<"Ошибка - Недопустимый символ после p"<<std::endl;
                exit(0);
            }
        }
        else if (mat_vyr[i] == '(') {
            stek_oper.push(mat_vyr[i]);
        }
        else if (mat_vyr[i] == ')') {
            while (!stek_oper.empty() and stek_oper.top() != '(') {
                perenos_operatorov(stek_oper, itogovoe);
            }
            if (!stek_oper.empty()) {
                stek_oper.pop();
            }
        }
        else if (std::find(operators.begin(), operators.end(), mat_vyr[i]) != operators.end()) { //Проверяем пред нами + - * / через поиск в списке
            dot_exist = false;
                while (!stek_oper.empty() and stek_oper.top() != '(' and prioritety(stek_oper.top()) >= prioritety(mat_vyr[i])) {

                   perenos_operatorov(stek_oper, itogovoe);
                }
            stek_oper.push(mat_vyr[i]);
        }

    }
    if (!podvyrajenie.empty()) {
        itogovoe.push_back(podvyrajenie);
    }
    while (!stek_oper.empty()) {
        perenos_operatorov(stek_oper, itogovoe);
    }
    return itogovoe;
}

float operation(float& a, float& b, const std::string& oper) {
    if (oper == "+") {
        return a + b;
    }
    else if (oper == "-") {
        return  a - b;
    }
    else if (oper == "*") {
        return a * b;
    }
    else if (oper == "/") {
        if (b != 0) {
            return a / b;
        }
        else {
            std::cout<<"В выражении есть деление на ноль"<<std::endl;
            return NAN;
        }
    }
    return 0;
}

float reshenie_obr_polsk_not(std::vector<std::string>& vyrajenie) {
    std::stack<float> stack_of_numbers;
    for (size_t i = 0; i < vyrajenie.size(); i++) {
        const std::string& token = vyrajenie[i];
        if (!token.empty()) {
            if (std::isdigit(token[0])) {
                stack_of_numbers.push(std::stof(token));
            }
            else if (token == "sin" or token == "cos" or token == "tan" or token == "ctg" or token == "exp") {
            if (stack_of_numbers.empty()) {
                std::cout<<"Ошибка - недостаточно данных для функции: "<<token<<std::endl;
                return NAN;
            }
            float arg = stack_of_numbers.top();
            stack_of_numbers.pop();
            float result = perevod_gradus(arg, token);
            if (std::isnan(result)) {
                return NAN;
            }
            stack_of_numbers.push(result);
        }
        else if (token[0] == '-' and token.size() > 1 and std::isdigit(token[1])) {
            stack_of_numbers.push(std::stof(token));
            }
        else if (token == "-" or token == "+" or token == "*" or token == "/") {
                float second = stack_of_numbers.top();
                stack_of_numbers.pop();
                float first = stack_of_numbers.top();
                stack_of_numbers.pop();

                float result = operation(first, second, token);
                stack_of_numbers.push(result);
            }
        }
    }
    if (stack_of_numbers.empty()) {
        return NAN;
    }
    return stack_of_numbers.top();
}

#endif //DZ3_FUNCTION_OF_DZ3_H