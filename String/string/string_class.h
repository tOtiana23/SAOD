#include <iostream>
#include <cassert>

using namespace std;

//�������� �������, ���-22

/// <summary>
/// ����� ������
/// </summary>
class MyString {

private:
    char* str; //���� ������
    int len; //� � �����

    /// <summary>
    /// ����������� ������, ������������ � �������� ��������� �� ������ �������� s
    /// </summary>
    /// <param name="s"></param>
    void copy(const char* s) {
        len = 0;
        while (s[len] != '\0') { //������� �����
            len++;
        }
        str = new char[len + 1]; //�������� ������
        for (int i = 0; i < len; i++) { //�������� �������
            str[i] = s[i];
        }
        str[len] = '\0';
    }

public:
    /// <summary>
    /// ����������� �� ���������
    /// </summary>
    MyString() {
        str = new char[1];
        str[0] = '\0';
        len = 0;
    }

    /// <summary>
    /// ����������� �����������
    /// </summary>
    /// <param name="s"> ��������� �� ������, ������� �������� </param>
    MyString(const char* s) {
        copy(s);
    }

    /// <summary>
    /// ����������
    /// </summary>
    ~MyString() {
        delete[] str;
    }

    /// <summary>
    /// ����� ������
    /// </summary>
    /// <returns> ����� </returns>
    int length() const {
        return len;
    }

    /// <summary>
    /// ������ � ������� �� �������
    /// </summary>
    /// <param name="index"> ������ </param>
    /// <returns> �������� �� ���� ������� </returns>
    char& operator[](int index) {
        return str[index];
    }

    /// <summary>
    /// ����������� ������ � �������
    /// </summary>
    /// <param name="index"> ������ </param>
    /// <returns> �������� �� ���� ������� </returns>
    char operator[](int index) const {
        return str[index];
    }

    /// <summary>
    /// ������������ ������
    /// </summary>
    /// <param name="other"> ������, ������� ����������� </param>
    /// <returns> ������ �� ������ </returns>
    MyString& operator=(const MyString& other) {
        if (this != &other) {
            delete[] str;
            copy(other.str);
        }
        return *this;
    }

    /// <summary>
    /// ������������ �����
    /// </summary>
    /// <param name="other"> ������, � ������� ���������� </param>
    /// <returns></returns>
    MyString operator+(const MyString& other) const {
        MyString result;
        result.len = len + other.len; //������� ����� �����
        result.str = new char[result.len + 1]; //������ ��� ����� ������
        size_t i = 0;
        for (; i < len; i++) {
            result.str[i] = str[i];
        }
        for (int j = 0; j < other.len; j++, i++) { //�������� ������� ������ ������ � ����� ����� ������
            result.str[i] = other.str[j];
        }
        result.str[result.len] = '\0';
        return result;
    }

    //������������� ������� - ��� �������, ������� ����� ������ � �������� � ���������� ������ ������, � �������� ��� ��������� �������������
    
    /// <summary>
    /// ����� ������
    /// </summary>
    /// <param name="os">  ������������ ������ �� ������ ������ ������, � ������� �� ����� �������� ������ </param>
    /// <param name="s"> ������ �� ������ ������, ������� �� ����� ������� </param>
    /// <returns> ������ ������ ������ (ostream&), ������� ��������� ������������ ������� �������� ������ </returns>
    friend ostream& operator<<(ostream& os, const MyString& s) {
        for (int i = 0; i < s.len; i++) {
            os << s.str[i];
        }
        return os;
    }

    /// <summary>
    /// ��������� ���������� ������� ��� ������
    /// ���������� ������� ��� ������� i � ������ - ��� ����� ����������� ������������ �������� ���������, ������� ������������ �������� � ���������
    /// </summary>
    /// <param name="prefix_function"></param>
    void compute_prefix_function(int* prefix_function) const {
        int m = length();           //�������� ����� ������
        if (m == 1) {               //���� ����� ������ ����� 1
            prefix_function[0] = 0; //������������� �������� ���������� ������� ��� ������� ��������
            return; 
        }
        prefix_function[0] = 0;     //�������������� �������� ���������� ������� ��� ������� ��������
        int j = 0;
        for (int i = 1; i < m; i++) { //���� �� ���� ��������� ������, ������� � ������� 1
            while (j > 0 && str[i] != str[j]) { //���� j > 0 � ������� �� ���������
                j = prefix_function[j - 1]; //��������� �������� j �������� ���������� �������
            }
            if (str[i] == str[j]) { //���� ������� ���������
                j++; //����������� �������� j
            }
            prefix_function[i] = j; //���������� �������� j � ���������� �������
        }
    }

    /// <summary>
    /// ����� ��������� pattern � ������, ��������� ������ ������� ���������, ���� ����� ������� 0, �� ���������� 0, ���� �� ������� - 1
    /// </summary>
    /// <param name="pattern"> ������, ������� ���� </param>
    /// <returns> ������, � �������� ���������� ������� ��������� </returns>
    int kmp_search(const MyString& pattern) const {
        int m = pattern.length(); //�������� ����� �������
        int n = length(); //�������� ����� ������

        if (m == 0) { //���� ����� ������� ����� 0
            return 0; //���������� 0
        }

        int* prefix_function = new int[m]; //�������� ������ ��� ������ ��� ���������� ������� �������
        pattern.compute_prefix_function(prefix_function); //��������� ���������� ������� ��� �������

        int i = 0, j = 0; //�������������� ���������� i � j
        while (i < n) { //���� �� ���� ��������� ������
            if (str[i] == pattern[j]) { //���� ������� ���������
                i++; 
                j++;
                if (j == m) { //���� ���� ������ ������
                    delete[] prefix_function; //����������� ���������� ������
                    return i - j; //���������� ������ ������ ���������� ������� � ������
                }
            }
            else {
                if (j != 0) { //���� j �� ����� 0
                    j = prefix_function[j - 1]; //��������� �������� j �������� ���������� �������
                }
                else {
                    i++; //����������� i
                }
            }
        }

        delete[] prefix_function; //����������� ���������� ������
        return -1; //������ �� ������, ���������� -1
    }



    /// <summary>
    /// �������� �� ��������� �����
    /// </summary>
    /// <param name="other"> � ��� ���������� </param>
    /// <returns> ������ ��� ���� </returns>
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
    /// �������� �� ����������� �����
    /// </summary>
    /// <param name="other"> � ��� ���������� </param>
    /// <returns> ������ ��� ���� </returns>
    bool operator!=(const MyString& other) const {
        return !(*this == other);
    }

    /// <summary>
    /// ��������� (������)
    /// </summary>
    /// <param name="other"> � ��� ���������� </param>
    /// <returns> ������ ��� ���� </returns>
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
    /// ��������� (������)
    /// </summary>
    /// <param name="other"> � ��� ���������� </param>
    /// <returns> ������ ��� ���� </returns>
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
    /// ��������� (������ ��� �����)
    /// </summary>
    /// <param name="other"> � ��� ���������� </param>
    /// <returns> ������ ��� ���� </returns>
    bool operator>=(const MyString& other) const {
        return !(*this < other);
    }

    /// <summary>
    /// ��������� (������ ��� �����)
    /// </summary>
    /// <param name="other"> � ��� ���������� </param>
    /// <returns> ������ ��� ���� </returns>
    bool operator<=(const MyString& other) const {
        return !(*this > other);
    }
};

/// <summary>
/// ���� �������
/// </summary>
void testStringMethods() {

    // ���� ������ length()
    MyString str1 = "hello";
    assert(str1.length() == 5);

    // ���� ��������� []
    MyString str2 = "world";
    assert(str2[0] == 'w');
    assert(str2[4] == 'd');
    char& ref = str2[3];

    // ���� ��������� =
    MyString str3;
    str3 = str1;
    assert(str3 == "hello");
    str3 = str2;
    assert(str3 == "world");

    // ���� ��������� +
    MyString str4 = str1 + str2;
    assert(str4 == "helloworld");
}


/// <summary>
/// ����� ��� ������
/// </summary>
void testKMPSearch() {
    MyString text("This is a sample text");
    MyString pattern1("sample");
    MyString pattern2("hello");

    // �������� ��� ���������� �������
    int index1 = text.kmp_search(pattern1);
    assert(index1 == 10);  // ������ "sample" ������ �� ������� 10

    // �������� ��� ������������ �������
    int index2 = text.kmp_search(pattern2);
    assert(index2 == -1);  // ������ "hello" �� ������

    // �������� ��� ������� �������
    MyString emptyPattern("");
    int index3 = text.kmp_search(emptyPattern);
    assert(index3 == 0);  // ������ ������ ������ �� ������� 0

    // �������� ��� ������, ������� �������
    MyString pattern3("This is a sample text");
    int index4 = text.kmp_search(pattern3);
    assert(index4 == 0);  // ������ ����� ������, ������ �� ������� 0

    // �������� ��� ������� ������
    MyString emptyText("");
    int index5 = emptyText.kmp_search(pattern1);
    assert(index5 == -1);  // � ������ ������ ������ �� ������

    // �������� ��� ����� �������� ������ � �������
    MyString longText("This is a very long text to test the KMP search algorithm...");
    MyString longPattern("very long text to test");
    int index6 = longText.kmp_search(longPattern);
    assert(index6 == 10);  // ������� ������ ������ �� ������� 10
}



/// <summary>
/// ����� ���������
/// </summary>
void testStringComparison() {
    MyString str1 = "apple";
    MyString str2 = "banana";
    MyString str3 = "apple";
    MyString str4 = "Apple";
    MyString str5 = "";
    MyString str6 = "a";

    // �������� ��������� ==
    assert(str1 == str3);
    assert(!(str1 == str2));
    assert(!(str1 == str4));
    assert(str5 == "");

    // �������� ��������� !=
    assert(str1 != str2);
    assert(!(str1 != str3));
    assert(str1 != str4);
    assert(str5 != str6);

    // �������� ��������� >
    assert(str2 > str1);
    assert(!(str1 > str3));
    assert(str1 > str5);

    // �������� ��������� <
    assert(str1 < str2);
    assert(!(str1 < str3));
    assert(str5 < str1);

    // �������� ��������� >=
    assert(str2 >= str1);
    assert(str1 >= str3);
    assert(str1 >= str5);

    // �������� ��������� <=
    assert(str1 <= str2);
    assert(str1 <= str3);
    assert(str5 <= str1);
}
