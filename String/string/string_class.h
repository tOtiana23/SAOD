#include <iostream>
#include <cassert>

using namespace std;

//Бусыгина Татьяна, ИВТ-22

/// <summary>
/// Класс строка
/// </summary>
class MyString {

private:
    char* str; //сама строка
    int len; //и её длина

    /// <summary>
    /// Копирование строки, передаваемой в качестве указателя на массив символов s
    /// </summary>
    /// <param name="s"></param>
    void copy(const char* s) {
        len = 0;
        while (s[len] != '\0') { //считаем длину
            len++;
        }
        str = new char[len + 1]; //выделяем память
        for (int i = 0; i < len; i++) { //копируем символы
            str[i] = s[i];
        }
        str[len] = '\0';
    }

public:
    /// <summary>
    /// Конструктор по умолчанию
    /// </summary>
    MyString() {
        str = new char[1];
        str[0] = '\0';
        len = 0;
    }

    /// <summary>
    /// Конструктор копирования
    /// </summary>
    /// <param name="s"> указатель на строку, которую копируем </param>
    MyString(const char* s) {
        copy(s);
    }

    /// <summary>
    /// Деструктор
    /// </summary>
    ~MyString() {
        delete[] str;
    }

    /// <summary>
    /// Длина строки
    /// </summary>
    /// <returns> длина </returns>
    int length() const {
        return len;
    }

    /// <summary>
    /// Доступ к символу по индексу
    /// </summary>
    /// <param name="index"> индекс </param>
    /// <returns> значение на этом индексе </returns>
    char& operator[](int index) {
        return str[index];
    }

    /// <summary>
    /// Константный доступ к символу
    /// </summary>
    /// <param name="index"> индекс </param>
    /// <returns> значение на этом индексе </returns>
    char operator[](int index) const {
        return str[index];
    }

    /// <summary>
    /// Присваивание строки
    /// </summary>
    /// <param name="other"> строка, которую присваиваем </param>
    /// <returns> ссылка на строку </returns>
    MyString& operator=(const MyString& other) {
        if (this != &other) {
            delete[] str;
            copy(other.str);
        }
        return *this;
    }

    /// <summary>
    /// Конкатенация строк
    /// </summary>
    /// <param name="other"> строка, с которой объеденяем </param>
    /// <returns></returns>
    MyString operator+(const MyString& other) const {
        MyString result;
        result.len = len + other.len; //считаем новую длину
        result.str = new char[result.len + 1]; //память для новой строки
        size_t i = 0;
        for (; i < len; i++) {
            result.str[i] = str[i];
        }
        for (int j = 0; j < other.len; j++, i++) { //копируем символы другой строки в конец новой строку
            result.str[i] = other.str[j];
        }
        result.str[result.len] = '\0';
        return result;
    }

    //Дружественная функция - это функция, которая имеет доступ к закрытым и защищенным членам класса, к которому она объявлена дружественной
    
    /// <summary>
    /// Вывод строки
    /// </summary>
    /// <param name="os">  представляет ссылку на объект потока вывода, в который мы хотим записать данные </param>
    /// <param name="s"> ссылку на объект класса, который мы хотим вывести </param>
    /// <returns> объект потока вывода (ostream&), который позволяет использовать цепочку операций вывода </returns>
    friend ostream& operator<<(ostream& os, const MyString& s) {
        for (int i = 0; i < s.len; i++) {
            os << s.str[i];
        }
        return os;
    }

    /// <summary>
    /// Вычисляет префиксную функцию для строки
    /// Префиксная функция для индекса i в строке - это длина наибольшего собственного суффикса подстроки, который одновременно является её префиксом
    /// </summary>
    /// <param name="prefix_function"></param>
    void compute_prefix_function(int* prefix_function) const {
        int m = length();           //получаем длину строки
        if (m == 1) {               //если длина строки равна 1
            prefix_function[0] = 0; //устанавливаем значение префиксной функции для первого элемента
            return; 
        }
        prefix_function[0] = 0;     //инициализируем значение префиксной функции для первого элемента
        int j = 0;
        for (int i = 1; i < m; i++) { //цикл по всем элементам строки, начиная с индекса 1
            while (j > 0 && str[i] != str[j]) { //пока j > 0 и символы не совпадают
                j = prefix_function[j - 1]; //обновляем значение j согласно префиксной функции
            }
            if (str[i] == str[j]) { //если символы совпадают
                j++; //увеличиваем значение j
            }
            prefix_function[i] = j; //записываем значение j в префиксную функцию
        }
    }

    /// <summary>
    /// Поиск подстроки pattern в строке, находится индекс первого вхождения, если длина шаблона 0, то возвращаем 0, если не найдено - 1
    /// </summary>
    /// <param name="pattern"> строка, которую ищем </param>
    /// <returns> индекс, с которого начинается искомая подстрока </returns>
    int kmp_search(const MyString& pattern) const {
        int m = pattern.length(); //получаем длину шаблона
        int n = length(); //получаем длину строки

        if (m == 0) { //если длина шаблона равна 0
            return 0; //возвращаем 0
        }

        int* prefix_function = new int[m]; //выделяем память под массив для префиксной функции шаблона
        pattern.compute_prefix_function(prefix_function); //вычисляем префиксную функцию для шаблона

        int i = 0, j = 0; //инициализируем переменные i и j
        while (i < n) { //цикл по всем элементам строки
            if (str[i] == pattern[j]) { //если символы совпадают
                i++; 
                j++;
                if (j == m) { //если весь шаблон найден
                    delete[] prefix_function; //освобождаем выделенную память
                    return i - j; //возвращаем индекс начала найденного шаблона в строке
                }
            }
            else {
                if (j != 0) { //если j не равно 0
                    j = prefix_function[j - 1]; //обновляем значение j согласно префиксной функции
                }
                else {
                    i++; //увеличиваем i
                }
            }
        }

        delete[] prefix_function; //освобождаем выделенную память
        return -1; //шаблон не найден, возвращаем -1
    }



    /// <summary>
    /// Проверка на равенство строк
    /// </summary>
    /// <param name="other"> с чем сравниваем </param>
    /// <returns> правда или ложь </returns>
    bool operator==(const MyString& other) const {
        if (len != other.len) {
            return false;
        }
        for (int i = 0; i < len; i++) {
            if (str[i] != other.str[i]) {
                return false;
            }
        }
        return true;
    }

    /// <summary>
    /// Проверка на неравенство строк
    /// </summary>
    /// <param name="other"> с чем сравниваем </param>
    /// <returns> правда или ложь </returns>
    bool operator!=(const MyString& other) const {
        return !(*this == other);
    }

    /// <summary>
    /// Сравнение (больше)
    /// </summary>
    /// <param name="other"> с чем сравниваем </param>
    /// <returns> правда или ложь </returns>
    bool operator>(const MyString& other) const {
        int minLen = std::min(len, other.len);
        for (int i = 0; i < minLen; i++) {
            if (str[i] > other.str[i]) {
                return true;
            }
            else if (str[i] < other.str[i]) {
                return false;
            }
        }
        return len > other.len;
    }

    /// <summary>
    /// Сравнение (меньше)
    /// </summary>
    /// <param name="other"> с чем сравниваем </param>
    /// <returns> правда или ложь </returns>
    bool operator<(const MyString& other) const {
        int minLen = std::min(len, other.len);
        for (int i = 0; i < minLen; i++) {
            if (str[i] < other.str[i]) {
                return true;
            }
            else if (str[i] > other.str[i]) {
                return false;
            }
        }
        return len < other.len;
    }

    /// <summary>
    /// Сравнение (больше или равно)
    /// </summary>
    /// <param name="other"> с чем сравниваем </param>
    /// <returns> правда или ложь </returns>
    bool operator>=(const MyString& other) const {
        return !(*this < other);
    }

    /// <summary>
    /// Сравнение (меньше или равно)
    /// </summary>
    /// <param name="other"> с чем сравниваем </param>
    /// <returns> правда или ложь </returns>
    bool operator<=(const MyString& other) const {
        return !(*this > other);
    }
};

/// <summary>
/// Тест методов
/// </summary>
void testStringMethods() {

    // Тест метода length()
    MyString str1 = "hello";
    assert(str1.length() == 5);

    // Тест оператора []
    MyString str2 = "world";
    assert(str2[0] == 'w');
    assert(str2[4] == 'd');
    char& ref = str2[3];

    // Тест оператора =
    MyString str3;
    str3 = str1;
    assert(str3 == "hello");
    str3 = str2;
    assert(str3 == "world");

    // Тест оператора +
    MyString str4 = str1 + str2;
    assert(str4 == "helloworld");
}


/// <summary>
/// Тесты КМП поиска
/// </summary>
void testKMPSearch() {
    MyString text("This is a sample text");
    MyString pattern1("sample");
    MyString pattern2("hello");

    // Проверка для найденного шаблона
    int index1 = text.kmp_search(pattern1);
    assert(index1 == 10);  // Шаблон "sample" найден на позиции 10

    // Проверка для ненайденного шаблона
    int index2 = text.kmp_search(pattern2);
    assert(index2 == -1);  // Шаблон "hello" не найден

    // Проверка для пустого шаблона
    MyString emptyPattern("");
    int index3 = text.kmp_search(emptyPattern);
    assert(index3 == 0);  // Пустой шаблон найден на позиции 0

    // Проверка для текста, равного шаблону
    MyString pattern3("This is a sample text");
    int index4 = text.kmp_search(pattern3);
    assert(index4 == 0);  // Шаблон равен тексту, найден на позиции 0

    // Проверка для пустого текста
    MyString emptyText("");
    int index5 = emptyText.kmp_search(pattern1);
    assert(index5 == -1);  // В пустом тексте шаблон не найден

    // Проверка для очень длинного текста и шаблона
    MyString longText("This is a very long text to test the KMP search algorithm...");
    MyString longPattern("very long text to test");
    int index6 = longText.kmp_search(longPattern);
    assert(index6 == 10);  // Длинный шаблон найден на позиции 10
}



/// <summary>
/// Тесты сравнений
/// </summary>
void testStringComparison() {
    MyString str1 = "apple";
    MyString str2 = "banana";
    MyString str3 = "apple";
    MyString str4 = "Apple";
    MyString str5 = "";
    MyString str6 = "a";

    // Проверка оператора ==
    assert(str1 == str3);
    assert(!(str1 == str2));
    assert(!(str1 == str4));
    assert(str5 == "");

    // Проверка оператора !=
    assert(str1 != str2);
    assert(!(str1 != str3));
    assert(str1 != str4);
    assert(str5 != str6);

    // Проверка оператора >
    assert(str2 > str1);
    assert(!(str1 > str3));
    assert(str1 > str5);

    // Проверка оператора <
    assert(str1 < str2);
    assert(!(str1 < str3));
    assert(str5 < str1);

    // Проверка оператора >=
    assert(str2 >= str1);
    assert(str1 >= str3);
    assert(str1 >= str5);

    // Проверка оператора <=
    assert(str1 <= str2);
    assert(str1 <= str3);
    assert(str5 <= str1);
}
