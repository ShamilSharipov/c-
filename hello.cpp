#include <iostream>
#include <string>
using namespace std;

/*class MyClass {
public:
    int *data;
    MyClass(int size) {
        this->Size = size;
        this->data = new int[size];
        for (int i = 0;i < size;i++) {
            data[i] = i;
        }
        cout <<"вызвался конструктор" << this << endl;
    }

    MyClass(const MyClass &other) {
        this->Size = other.Size;
        this->data = new int[other.Size];
        for (int i = 0;i < other.Size; i++) {
            this->data[i] = other.data[i];
        }
        cout <<"вызвался конструктор copy" << this << endl;
    }

    MyClass & operator = (const MyClass &other) {
        cout <<"вызвался оператор присваивания" << this << endl;
        this->Size = other.Size;
        if (this->data != nullptr) {
        delete[] this->data;
        }
        this->data = new int[other.Size];
        for (int i = 0;i < other.Size;i++) {
            this->data[i] = other.data[i];
        }
        return *this;
    }
    ~MyClass() {
        cout <<"вызвался деструктор" << this << endl;
        delete[] data;
    }
private:
    int Size;
    
};

void Foo(MyClass value) {
        cout <<"вызвалась функция Foo"<< endl;
    }

MyClass Foo2() {
    MyClass temp(2);
    return temp;
} */
class Point {
private:
    int x;
    int y;
public:
Point() {
    x = 0;
    y = 0;
}
Point(int valueX, int valueY) {
    x = valueX;
    y = valueY;
}

bool operator ==(const Point & other) {
    return this->x == other.x && this->y == other.y;
}
    void Print() {
        cout << "x = "<< x << "\ny = "<< y <<endl; 
    }
    int GetX() {
        return x;
    }
    int GetY() {
        return y;
    }
    void SetX(int valueX) {
        x = valueX;
    }
    void SetY(int valueY) {
        y = valueY;
    }

};

int main() {
    //MyClass a(10);
    
    //MyClass b(2);
    //a.operator=(b);
    //Foo(a);
    Point a(5, 1);
    Point b(5, 1);

    bool result = a == b;
    //a.Print();
    return 0;

}