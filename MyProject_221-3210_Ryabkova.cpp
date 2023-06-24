// ����������� ����������� ���������
#include <iostream> // ��� ������ � ������ � �������
#include <map> // ��� ������������� �������������� �������
#include <string> // ��� ������ �� ��������
#include <ctime> // ��� ��������� ��������� �����
#include <Windows.h> 

using namespace std;

// ����������� ������ MetricRegister
class MetricRegister {
private:
    map<int, pair<int, int>> metrics; // ������������� ������ ��� �������� ������
    static MetricRegister* instance; // ����������� ��������� �� ������������ ��������� ������
    MetricRegister() {} // �������� ����������� �� ���������

public:

    static MetricRegister* getInstance() { // ����� ��� ��������� ��������� �� ������������ ��������� ������
        return instance ? instance : instance = new MetricRegister(); // �������� ���������� ��� �������������
    }

    bool add_metr(int resp_t, int wait_t) { // ����� ��� ���������� ����� �������
        int timestamp = metrics.size() + 1; // ������� ����� ������������ � �������� �����
        metrics[timestamp] = make_pair(resp_t, wait_t); // ���������� ������� � ������������� ������
        return true;
    }

    void show_metr() { // ����� ��� ������ ���� ������ �� �����
        cout << "�������: " << endl;
        for (const auto& metric : metrics) { // ������� ���� ������ � ������������� �������
            int timestamp = metric.first; // ��������� ����� - �������
            int responseTime = metric.second.first; // ��������� ������� �������
            int waitTime = metric.second.second; // ��������� ������� ��������
            cout << "����(������ �������) #" << timestamp << ", ����� �������: " << responseTime << ", ����� ��������: " << waitTime << endl; // ����� ���������� � ������� �� �����
        }
    }

    int count_cometr(int key) { // ����� ��� ���������� ��������������� ������� ��� ��������� �����
        if (metrics.find(key) != metrics.end()) { // �������� ������� ������� � �������� ������
            const auto& metric = metrics[key]; // ��������� ������� � �������� ������
            return metric.first + metric.second; // ���������� ��������������� �������
        }
        else
            return 0;
    }

    void test() { // ����� ��� ������������ ������
        for (int i = 0; i < 5; i++) { // ���������� 5 ������
            int x = rand(); // ��������� ��������� ����� ��� ������� ������� � ������� ��������
            int y = rand();
            add_metr(x, y); // ���������� ������� � ���������������� ����������
            if (metrics[metrics.size()] == std::pair<int, int>(x, y)) { // �������� ������������ ���������� �������
                cout << "���� #" << 2 * i + 1 << ": �������" << endl;
            }
            else {
                cout << "���� #" << 2 * i + 1 << ": �������" << endl;
            }
            if (count_cometr(metrics.size()) == x + y) { // �������� ������������ ���������� ��������������� �������
                cout << "���� #" << 2 * i + 2 << ": �������" << endl;
            }
            else {
                cout << "���� #" << 2 * i + 2 << ": �� �������" << endl;
            }
        }
        metrics.clear(); // ������� �������������� ������� ����� ���������� ������
    }
};

MetricRegister* MetricRegister::instance = nullptr; // ������������� ������������ ��������� �� ������������ ��������� ������

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL)); // ������������� ���������� ��������� �����
    MetricRegister::getInstance()->test(); // ������������ ������
    string input; // ���������� ��� �������� ��������� �������
    cout << "��� ����� ����� ������� ������� ������� add_metr '����� �������' '����� ��������'" <<
        endl << "��� ��������� ���� ������ ������� ������� show_metr" << endl << "��� ���������� ��������������� ������� ������� ������� count_cometr '����� ����� (������� �������)'" << endl;
    while (std::getline(std::cin, input)) // ������ ������ �� ������������ �����
    {
        if (input.find("add_metr") != string::npos) { // ���� ������� ���������� �� ������ "add_metr"
            input = input.substr(input.find("add_metr") + 9); // ���������� �������� ������� ������� � ������� ��������
            int spaceIndex = input.find(' ');
            int resp_t = stoi(input.substr(0, spaceIndex));
            input = input.substr(spaceIndex);
            int wait_t = stoi(input);
            MetricRegister::getInstance()->add_metr(resp_t, wait_t); // ���������� ����� �������
        }
        else if (input.find("show_metr") != string::npos) { // ���� ������� ���������� �� ������ "show_metr"
            MetricRegister::getInstance()->show_metr(); // ����� ���� ������ �� �����
        }
        else if (input.find("count_cometr") != string::npos) { // ���� ������� ���������� �� ������ "count_cometr"
            input = input.substr(input.find("count_cometr") + 13); // ���������� �������� �����
            int key = stoi(input);
            if (MetricRegister::getInstance()->count_cometr(key) != 0)
                cout << "��������������� ������� (����� ������� ������� � ��������): " << MetricRegister::getInstance()->count_cometr(key) << endl; // ���������� ��������������� ������� � ����� �� �������� �� �����
            else
                cout << "������ ����� ���" << endl; //����������� �� ���������� ���������� �����
        }
        else {
            cout << "������������ �������" << endl; // ���� ������� �� ������������� �� ����� �� ���� ��������� ������, ��������� ��������� �� ������
        }
    }

    system("PAUSE");
    return 0;
}




