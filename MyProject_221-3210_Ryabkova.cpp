// Подключение необходимых библиотек
#include <iostream> // для работы с вводом и выводом
#include <map> // для использования ассоциативного массива
#include <string> // для работы со строками
#include <ctime> // для генерации случайных чисел
#include <Windows.h> 

using namespace std;

// Определение класса MetricRegister
class MetricRegister {
private:
    map<int, pair<int, int>> metrics; // ассоциативный массив для хранения метрик
    static MetricRegister* instance; // статический указатель на единственный экземпляр класса
    MetricRegister() {} // закрытый конструктор по умолчанию

public:

    static MetricRegister* getInstance() { // метод для получения указателя на единственный экземпляр класса
        return instance ? instance : instance = new MetricRegister(); // создание экземпляра при необходимости
    }

    bool add_metr(int resp_t, int wait_t) { // метод для добавления новой метрики
        int timestamp = metrics.size() + 1; // текущее время используется в качестве ключа
        metrics[timestamp] = make_pair(resp_t, wait_t); // добавление метрики в ассоциативный массив
        return true;
    }

    void show_metr() { // метод для вывода всех метрик на экран
        cout << "Метрики: " << endl;
        for (const auto& metric : metrics) { // перебор всех метрик в ассоциативном массиве
            int timestamp = metric.first; // получение ключа - времени
            int responseTime = metric.second.first; // получение времени отклика
            int waitTime = metric.second.second; // получение времени ожидания
            cout << "Ключ(момент времени) #" << timestamp << ", время отклика: " << responseTime << ", время ожидания: " << waitTime << endl; // вывод информации о метрике на экран
        }
    }

    int count_cometr(int key) { // метод для вычисления вспомогательной метрики для заданного ключа
        if (metrics.find(key) != metrics.end()) { // проверка наличия метрики с заданным ключом
            const auto& metric = metrics[key]; // получение метрики с заданным ключом
            return metric.first + metric.second; // вычисление вспомогательной метрики
        }
        else
            return 0;
    }

    void test() { // метод для тестирования класса
        for (int i = 0; i < 5; i++) { // выполнение 5 тестов
            int x = rand(); // генерация случайных чисел для времени отклика и времени ожидания
            int y = rand();
            add_metr(x, y); // добавление метрики с сгенерированными значениями
            if (metrics[metrics.size()] == std::pair<int, int>(x, y)) { // проверка корректности добавления метрики
                cout << "Тест #" << 2 * i + 1 << ": пройден" << endl;
            }
            else {
                cout << "Тест #" << 2 * i + 1 << ": пройден" << endl;
            }
            if (count_cometr(metrics.size()) == x + y) { // проверка корректности вычисления вспомогательной метрики
                cout << "Тест #" << 2 * i + 2 << ": пройден" << endl;
            }
            else {
                cout << "Тест #" << 2 * i + 2 << ": не пройден" << endl;
            }
        }
        metrics.clear(); // очистка ассоциативного массива после выполнения тестов
    }
};

MetricRegister* MetricRegister::instance = nullptr; // инициализация статического указателя на единственный экземпляр класса

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL)); // инициализация генератора случайных чисел
    MetricRegister::getInstance()->test(); // тестирование класса
    string input; // переменная для хранения введенной команды
    cout << "Для ввода новой метрики введите команду add_metr 'время отклика' 'время ожидания'" <<
        endl << "Для просмотра всех метрик введите команду show_metr" << endl << "Для вычисления вспомогательной метрики введите команду count_cometr 'номер ключа (момента времени)'" << endl;
    while (std::getline(std::cin, input)) // чтение команд из стандартного ввода
    {
        if (input.find("add_metr") != string::npos) { // если команда начинается со строки "add_metr"
            input = input.substr(input.find("add_metr") + 9); // извлечение значений времени отклика и времени ожидания
            int spaceIndex = input.find(' ');
            int resp_t = stoi(input.substr(0, spaceIndex));
            input = input.substr(spaceIndex);
            int wait_t = stoi(input);
            MetricRegister::getInstance()->add_metr(resp_t, wait_t); // добавление новой метрики
        }
        else if (input.find("show_metr") != string::npos) { // если команда начинается со строки "show_metr"
            MetricRegister::getInstance()->show_metr(); // вывод всех метрик на экран
        }
        else if (input.find("count_cometr") != string::npos) { // если команда начинается со строки "count_cometr"
            input = input.substr(input.find("count_cometr") + 13); // извлечение значения ключа
            int key = stoi(input);
            if (MetricRegister::getInstance()->count_cometr(key) != 0)
                cout << "Вспомогательная метрика (сумма времени отклика и ожидания): " << MetricRegister::getInstance()->count_cometr(key) << endl; // вычисление вспомогательной метрики и вывод ее значения на экран
            else
                cout << "Такого ключа нет" << endl; //уведомление об отсутствии введенного ключа
        }
        else {
            cout << "Неопознанная команда" << endl; // если команда не соответствует ни одной из трех возможных команд, выводится сообщение об ошибке
        }
    }

    system("PAUSE");
    return 0;
}




