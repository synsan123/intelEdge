#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v;
    double sum = 0;
    while (true) {
        int tmp;
        cout << "������ �Է��ϼ���(0�� �Է��ϸ� ����)>>";
        cin >> tmp;
        if (!tmp) break; //�Է��� ������ 0�̸� ���� 
        v.push_back(tmp); // �Է��� ������ 0�� �ƴϸ� v�� ���� 
        for (int i = 0; i < v.size(); i++) // vector v�� ��� ���� ��� 
            cout << v.at(i) << ' ';
        cout << endl;
        sum += tmp;
        cout << "��� = " << sum / v.size() << endl;
    }
}
