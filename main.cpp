#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <map>

using namespace std;


// ДВУСВЯЗНЫЙ СПИСОК
template<typename T>
class DoublyLinkedList {
private:
    // Узел списка - содержит данные и указатели на соседние узлы
    struct Node {
        T data;
        Node* prev;  // указатель на предыдущий узел
        Node* next;  // указатель на следующий узел
        
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };
    
    Node* head;     // указатель на первый узел списка
    Node* tail;     // указатель на последний узел списка
    size_t list_size; // текущее количество элементов в списке

public:
    // Конструктор - инициализирует пустой список
    DoublyLinkedList() : head(nullptr), tail(nullptr), list_size(0) {}
    
    // Деструктор - освобождает всю память, занимаемую списком
    ~DoublyLinkedList() {
        clear();
    }
    
    // Добавляет элемент в конец списка
    // Сложность: O(1)
    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            // Если список пуст, новый узел становится единственным
            head = tail = newNode;
        } else {
            // Добавляем новый узел после текущего tail
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        list_size++;
    }
    
    // Добавляет элемент в начало списка
    // Сложность: O(1)
    void push_front(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            // Добавляем новый узел перед текущим head
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        list_size++;
    }
    
    // Вставляет элемент на указанную позицию
    // Сложность: O(n) в худшем случае
    void insert(size_t index, const T& value) {
        if (index > list_size) {
            throw out_of_range("Индекс вне диапазона");
        }
        
        // Оптимизация для краевых случаев
        if (index == 0) {
            push_front(value);
            return;
        }
        
        if (index == list_size) {
            push_back(value);
            return;
        }
        
        // Находим узел, перед которым нужно вставить новый
        Node* current = head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
        
        // Создаем новый узел и вставляем его перед current
        Node* newNode = new Node(value);
        newNode->prev = current->prev;
        newNode->next = current;
        current->prev->next = newNode;
        current->prev = newNode;
        list_size++;
    }
    
    // Удаляет последний элемент списка
    // Сложность: O(1)
    void pop_back() {
        if (!tail) return; // список пуст
        
        Node* temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr; // список стал пустым
        }
        delete temp;
        list_size--;
    }
    
    // Удаляет первый элемент списка
    // Сложность: O(1)
    void pop_front() {
        if (!head) return;
        
        Node* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr; // список стал пустым
        }
        delete temp;
        list_size--;
    }
    
    // Удаляет элемент по указанному индексу
    // Сложность: O(n) в худшем случае
    void remove(size_t index) {
        if (index >= list_size) {
            throw out_of_range("Индекс вне диапазона");
        }
        
        if (index == 0) {
            pop_front();
            return;
        }
        
        if (index == list_size - 1) {
            pop_back();
            return;
        }
        
        // Находим узел для удаления
        Node* current = head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
        
        // Переключаем ссылки соседних узлов друг на друга
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        list_size--;
    }
    
    // Оператор доступа к элементу по индексу
    // Сложность: O(n) в худшем случае
    T& operator[](size_t index) {
        if (index >= list_size) {
            throw out_of_range("Индекс вне диапазона");
        }
        
        Node* current = head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }
    
    // Возвращает количество элементов в списке
    size_t size() const {
        return list_size;
    }
    
    // Очищает список, удаляя все элементы
    void clear() {
        while (head) {
            pop_front();
        }
    }
};


// ДИНАМИЧЕСКИЙ МАССИВ
template<typename T>
class DynamicArray {
private:
    T* data;        // указатель на массив в динамической памяти
    size_t capacity; // текуная вместимость массива
    size_t arr_size; // текущее количество элементов

    // Увеличивает вместимость массива при необходимости
    void resize() {
        capacity = capacity == 0 ? 1 : capacity * 2;
        T* newData = new T[capacity];
        
        // Копируем существующие элементы в новый массив
        for (size_t i = 0; i < arr_size; i++) {
            newData[i] = data[i];
        }
        
        delete[] data; // освобождаем старый массив
        data = newData;
    }

public:
    // Конструктор - создает пустой массив
    DynamicArray() : data(nullptr), capacity(0), arr_size(0) {}
    
    // Деструктор - освобождает память
    ~DynamicArray() {
        delete[] data;
    }
    
    // Добавляет элемент в конец массива
    // Амортизированная сложность: O(1)
    void push_back(const T& value) {
        if (arr_size >= capacity) {
            resize(); // увеличиваем capacity при необходимости
        }
        data[arr_size++] = value;
    }
    
    // Вставляет элемент на указанную позицию
    // Сложность: O(n) из-за сдвига элементов
    void insert(size_t index, const T& value) {
        if (index > arr_size) {
            throw out_of_range("Индекс вне диапазона");
        }
        
        if (arr_size >= capacity) {
            resize();
        }
        
        // Сдвигаем элементы вправо чтобы освободить место
        for (size_t i = arr_size; i > index; i--) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        arr_size++;
    }
    
    // Удаляет последний элемент массива
    // Сложность: O(1)
    void pop_back() {
        if (arr_size > 0) {
            arr_size--;
        }
    }
    
    // Удаляет элемент по указанному индексу
    // Сложность: O(n) из-за сдвига элементов
    void remove(size_t index) {
        if (index >= arr_size) {
            throw out_of_range("Индекс вне диапазона");
        }
        
        // Сдвигаем элементы влево чтобы заполнить пустое место
        for (size_t i = index; i < arr_size - 1; i++) {
            data[i] = data[i + 1];
        }
        arr_size--;
    }
    
    // Оператор доступа к элементу по индексу
    // Сложность: O(1)
    T& operator[](size_t index) {
        if (index >= arr_size) {
            throw out_of_range("Индекс вне диапазона");
        }
        return data[index];
    }
    
    // Возвращает количество элементов в массиве
    size_t size() const {
        return arr_size;
    }
};

// СТЕК (реализация на основе двусвязного списка)
template<typename T>
class Stack {
private:
    DoublyLinkedList<T> list; // используем список для хранения элементов

public:
    // Добавляет элемент на вершину стека
    void push(const T& value) {
        list.push_back(value);
    }
    
    // Удаляет и возвращает элемент с вершины стека
    T pop() {
        if (isEmpty()) {
            throw runtime_error("Стек пуст");
        }
        T value = list[list.size() - 1];
        list.pop_back();
        return value;
    }
    
    // Возвращает элемент на вершине стека без удаления
    T& top() {
        if (isEmpty()) {
            throw runtime_error("Стек пуст");
        }
        return list[list.size() - 1];
    }
    
    // Проверяет, пуст ли стек
    bool isEmpty() const {
        return list.size() == 0;
    }
    
    // Возвращает количество элементов в стеке
    size_t size() const {
        return list.size();
    }
};


// КЛАСС ДЛЯ ОБРАБОТКИ МАТЕМАТИЧЕСКИХ ВЫРАЖЕНИЙ
class ExpressionParser {
private:
    // Проверяет, является ли токен оператором
    static bool isOperator(const string& token) {
        return token == "+" || token == "-" || token == "*" || token == "/" || token == "^";
    }
    
    // Проверяет, является ли токен функцией
    static bool isFunction(const string& token) {
        return token == "sin" || token == "cos";
    }
    
    // Возвращает приоритет оператора для определения порядка вычислений
    static int getPrecedence(const string& op) {
        if (op == "+" || op == "-") return 1;    // низший приоритет
        if (op == "*" || op == "/") return 2;    // средний приоритет
        if (op == "^") return 3;                 // высший приоритет
        if (isFunction(op)) return 4;            // функции - наивысший приоритет
        return 0;
    }
    
    // Проверяет, является ли токен числом (состоит только из цифр)
    static bool isNumber(const string& token) {
        for (char c : token) {
            if (!isdigit(c)) return false;
        }
        return true;
    }

public:
    // Разбивает строку выражения на отдельные токены по пробелам
    static vector<string> tokenize(const string& expression) {
        vector<string> tokens;
        stringstream ss(expression);
        string token;
        
        while (ss >> token) {
            tokens.push_back(token);
        }
        return tokens;
    }
    
    // Проверяет корректность математического выражения
    // Возвращает true если выражение корректно, false в противном случае
    static bool validateExpression(const vector<string>& tokens) {
        int bracketBalance = 0; // счетчик для проверки баланса скобок
        
        for (size_t i = 0; i < tokens.size(); i++) {
            const string& token = tokens[i];
            
            // Проверка на недопустимые токены
            if (!isNumber(token) && !isOperator(token) && !isFunction(token) &&
                token != "(" && token != ")") {
                cout << "Ошибка: Неизвестный токен '" << token << "'" << endl;
                return false;
            }
            
            // Подсчет баланса скобок
            if (token == "(") bracketBalance++;
            else if (token == ")") bracketBalance--;
            
            // Проверка корректности положения операторов
            if (isOperator(token)) {
                // Оператор не может быть первым или последним токеном
                if (i == 0 || i == tokens.size() - 1) {
                    cout << "Ошибка: Оператор '" << token << "' в недопустимом положении" << endl;
                    return false;
                }
                
                // После оператора не может идти другой оператор или закрывающая скобка
                const string& next = tokens[i + 1];
                if (isOperator(next) || next == ")") {
                    cout << "Ошибка: Оператор '" << token << "' за которым следует недопустимый токен '" << next << "'" << endl;
                    return false;
                }
            }
            
            // Проверка корректности использования функций
            if (isFunction(token)) {
                // После функции должна идти открывающая скобка
                if (i == tokens.size() - 1 || tokens[i + 1] != "(") {
                    cout << "Ошибка: Функция '" << token << "' за этим должны следовать '('" << endl;
                    return false;
                }
            }
        }
        
        // Проверка баланса скобок
        if (bracketBalance != 0) {
            cout << "Ошибка: Несбалансированные скобки" << endl;
            return false;
        }
        
        return true;
    }
    
    // Преобразует инфиксную запись в постфиксную
    static vector<string> infixToPostfix(const vector<string>& tokens) {
        vector<string> output; // выходная очередь для постфиксной записи
        Stack<string> stack;   // стек для операторов и функций
        
        for (const string& token : tokens) {
            if (isNumber(token)) {
                // Числа сразу добавляем в выходную очередь
                output.push_back(token);
            }
            else if (isFunction(token)) {
                // Функции помещаем в стек
                stack.push(token);
            }
            else if (token == "(") {
                // Открывающую скобку помещаем в стек
                stack.push(token);
            }
            else if (token == ")") {
                // Для закрывающей скобки выталкиваем все операторы до открывающей скобки
                while (!stack.isEmpty() && stack.top() != "(") {
                    output.push_back(stack.pop());
                }
                stack.pop(); // удаляем открывающую скобку из стека
                
                // Если после скобки была функция, добавляем ее в выход
                if (!stack.isEmpty() && isFunction(stack.top())) {
                    output.push_back(stack.pop());
                }
            }
            else if (isOperator(token)) {
                // Выталкиваем из стека операторы с большим или равным приоритетом
                while (!stack.isEmpty() && isOperator(stack.top()) &&
                       getPrecedence(stack.top()) >= getPrecedence(token)) {
                    output.push_back(stack.pop());
                }
                stack.push(token); // помещаем текущий оператор в стек
            }
        }
        
        // Выталкиваем оставшиеся операторы из стека
        while (!stack.isEmpty()) {
            output.push_back(stack.pop());
        }
        
        return output;
    }
    
    // Вычисляет значение постфиксного выражения
    // Использует стек для хранения промежуточных результатов
    static double evaluatePostfix(const vector<string>& postfix) {
        Stack<double> stack;
        
        for (const string& token : postfix) {
            if (isNumber(token)) {
                // Число - преобразуем строку в double и помещаем в стек
                stack.push(stod(token));
            }
            else if (isOperator(token)) {
                // Оператору нужны два операнда
                if (stack.size() < 2) {
                    throw runtime_error("Недостаточно операндов для оператора " + token);
                }
                
                // Извлекаем операнды из стека (порядок важен!)
                double b = stack.pop();
                double a = stack.pop();
                double result;
                
                // Выполняем операцию в зависимости от токена
                if (token == "+") {
                    result = a + b;
                }
                else if (token == "-") {
                    result = a - b;
                }
                else if (token == "*") {
                    result = a * b;
                }
                else if (token == "/") {
                    if (b == 0) {
                        throw runtime_error("Деление на ноль");
                    }
                    result = a / b;
                }
                else if (token == "^") {
                    result = pow(a, b);
                }
                
                // Помещаем результат обратно в стек
                stack.push(result);
            }
            else if (isFunction(token)) {
                // Функции нужен один операнд
                if (stack.size() < 1) {
                    throw runtime_error("Недостаточно операндов для функции " + token);
                }
                
                double a = stack.pop();
                double result;
                
                if (token == "sin") {
                    result = sin(a);
                }
                else if (token == "cos") {
                    result = cos(a);
                }
                
                stack.push(result);
            }
        }
        
        // В стеке должен остаться ровно один элемент - результат вычисления
        if (stack.size() != 1) {
            throw runtime_error("Некорректное выражение");
        }
        
        return stack.pop();
    }
};

// ГЛАВНАЯ ФУНКЦИЯ
int main() {
    string input;
    
    cout << "Введите выражения для вычисления (введите 'exit', чтобы завершить работу):" << endl;
    cout << "Разрешенные символы: +, -, *, /, ^, sin, cos, (, ), цифры 0-9" << endl;
    cout << "Разделяйте каждый символ пробелом" << endl << endl;
    
    // Основной цикл программы
    while (true) {
        cout << "> ";
        getline(cin, input);
        
        if (input == "exit") {
            break; // выход из программы
        }
        
        if (input.empty()) {
            continue; // игнорируем пустой ввод
        }
        
        try {
            // 1. Разбиваем ввод на токены
            vector<string> tokens = ExpressionParser::tokenize(input);
            
            if (tokens.empty()) {
                cout << "Ошибка: Пустое выражение" << endl;
                continue;
            }
            
            // 2. Проверяем корректность выражения
            if (!ExpressionParser::validateExpression(tokens)) {
                continue; // если есть ошибки, переходим к следующей итерации
            }
            
            // 3. Преобразуем в постфиксную запись
            vector<string> postfix = ExpressionParser::infixToPostfix(tokens);
            
            // 4. Вычисляем результат
            double result = ExpressionParser::evaluatePostfix(postfix);
            
            // 5. Выводим результаты только если все этапы прошли успешно
            cout << "Постфиксная запись: ";
            for (const string& token : postfix) {
                cout << token << " ";
            }
            cout << endl;
            cout << "Результат: " << result << endl << endl;
            
        } catch (const exception& e) {
            // Обрабатываем исключения
            cout << "Ошибка: " << e.what() << endl;
        }
    }
    
    return 0;
}
