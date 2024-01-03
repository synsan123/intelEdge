#include <iostream>
#include <vector>
using namespace std;

class Shape {
protected:
    virtual void draw() = 0;
public:
    void paint() { draw(); }
};

class Circle : public Shape {
protected:
    virtual void draw() { cout << "Circle" << endl; }
};

class Rect : public Shape {
protected:
    virtual void draw() { cout << "Rectangle" << endl; }
};

class Line : public Shape {
protected:
    virtual void draw() { cout << "Line" << endl; }
};

class UI {
public:
    static int seleteMenu() {
        int n;
        cout << "����:1, ����:2, ��κ���:3, ����:4 >> ";
        cin >> n;
        return n;
    }
    static int seleteShape() {
        int n;
        cout << "��:1, ��:2, �簢��:3 >> ";
        cin >> n;
        return n;
    }
    static int seleteDelIndex() {
        int n;
        cout << "�����ϰ��� �ϴ� ������ �ε��� >> ";
        cin >> n;
        return n;
    }
    static void showAll(vector<Shape*>& v, vector<Shape*>::iterator& it) {
        int i = 0;
        for (it = v.begin(); it != v.end(); it++, i++) { // vector v�� ù ���Һ��� �� ���ұ��� Ž�� �� ���
            cout << i << ": ";
            v.at(i)->paint();
        }
    }
};

class GraphicEditor {
    vector<Shape*> v;
    vector<Shape*>::iterator it;
public:
    GraphicEditor() {
        cout << "�׷��� �������Դϴ�.\n";
        start();
    }
    void start() {
        while (true) {
            int n;
            n = UI::seleteMenu();
            switch (n) {
            case 1: //������ ������ ���
                n = UI::seleteShape();
                switch (n) {
                case 1: //���� ������ ���
                    v.push_back(new Line());
                    break;
                case 2: //���� ������ ���
                    v.push_back(new Circle());
                    break;
                case 3: //�簢���� ������ ���
                    v.push_back(new Rect());
                    break;
                default:
                    cout << "�߸� �����ϼ̽��ϴ�.\n";
                    break;
                }
                break;
            case 2: { //������ ������ ���
                n = UI::seleteDelIndex();
                if (n >= v.size() || n < 0) { // ���� �ε����� ���� ����ó��  
                    cout << "���� �ε��� �Դϴ�.\n";
                    break;
                }
                it = v.begin();
                Shape* tmp = *(it + n); // vector���� ���Ұ� �����ǰ� �� �� ��ü delete�� ���� ����
                v.erase(it + n); // it+n ��ġ�� �ִ� ���� ����
                delete tmp; // vector���� ������ ��ü delete
                break;
            }
            case 3: //��� ���⸦ ������ ���
                UI::showAll(v, it); //�Ű������� vector v�� v�� iterator�� �ѱ�
                break;
            case 4: // ���Ḧ ������ ��� 
                return; //���α׷� ����
            default:
                cout << "�߸� �Է��ϼ̽��ϴ�.\n";
                break;
            }
        }
    }

};

int main() {
    new GraphicEditor();
}
