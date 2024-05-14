#include "stack.h"
#include <sstream>
#include <iostream>

//Бусыгина Татьяна, ИВТ-22
template <typename T>
///Постфиксный стековый калькулятор, при делении на ноль возвращает 0, при неправильных данных возвращает -1
class PostfixCalculator : public Stack<T>
{
public:
    ///Вычисление значения постфиксного выражения,
    T evaluatePostfix(const std::string& postfixExpression)
    {
        std::istringstream iss(postfixExpression); // Создаем поток ввода из строки с постфиксным выражением
        std::string token; // Переменная для хранения текущего токена
        
        while (iss >> token) { // Цикл по каждому токену в строке
            if (isdigit(token[0])) { // Если токен является числом
                this->push(std::stoi(token)); // Помещаем число в стек
            } else { // Если токен является оператором
                if (this->sizes() < 2) { // Проверяем, достаточно ли операндов в стеке
                    throw std::invalid_argument("Invalid postfix expression"); // Бросаем исключение, если операндов недостаточно
                }
                
                T operand2 = this->get_node(0)->data; // Получаем второй операнд из стека
                this->pop(); // Удаляем второй операнд из стека
                
                T operand1 = this->get_node(0)->data; // Получаем первый операнд из стека
                this->pop(); // Удаляем первый операнд из стека
                
                T result; // Переменная для хранения результата вычисления
                
                switch (token[0]) { // Выполняем операцию в зависимости от оператора
                    case '+':
                        result = operand1 + operand2;
                        break;
                    case '-':
                        result = operand1 - operand2;
                        break;
                    case '*':
                        result = operand1 * operand2;
                        break;
                    case '/':
                        if (operand2 == 0) { // Проверяем деление на ноль
                            cout << "Division by zero is not possible"; // Выводим сообщение о невозможности деления на ноль
                            return 0; // Возвращаем 0
                        }
                        result = operand1 / operand2; // Выполняем деление
                        break;
                    default:
                        cout << "I don't know"; // Выводим сообщение о неизвестном операторе
                        return -1; // Возвращаем -1
                }
                
                this->push(result); // Помещаем результат вычисления обратно в стек
            }
        }
        
        if (this->sizes() != 1) { // Проверяем, что в стеке остался только один элемент (результат вычислений)
            throw std::invalid_argument("Invalid postfix expression"); // Бросаем исключение, если в стеке больше одного элемента
        }
        
        T finalResult = this->get_node(0)->data; // Получаем окончательный результат из стека
        this->clear(); // Очищаем стек
        
        return finalResult; // Возвращаем окончательный результат вычислений
    }

};

void assert_calc()
{
    PostfixCalculator<int> calculator;
    // Постфиксное выражение: 3 4 + 2 *
    // Ожидаемый результат: (3 + 4) * 2 = 14
    assert(calculator.evaluatePostfix("3 4 + 2 *") == 14);

    // Постфиксное выражение: 5 2 3 * +
    // Ожидаемый результат: 5 + (2 * 3) = 11
    assert(calculator.evaluatePostfix("5 2 3 * +") == 11);

    // Постфиксное выражение: 8 4 / 6 -
    // Ожидаемый результат: (8 / 4) - 6 = -4
    assert(calculator.evaluatePostfix("8 4 / 6 -") == -4);

    // Постфиксное выражение: 1 2 3 * + 4 -
    // Ожидаемый результат: 1 + (2 * 3) - 4 = 3
    assert(calculator.evaluatePostfix("1 2 3 * + 4 -") == 3);

    // Если исключение не было вызвано, что является ошибкой
    assert(calculator.evaluatePostfix("3 0 /") == 0);
}
