#include <iostream>
#include <math.h>
#include <vector>

namespace {
    const double PI = 3.141592653589793238463;
}
class Shape {
    double height;
public:
    virtual double area() const { return 0.0; }
    virtual double perimeter() const { return 0.0; }
    void initializeHeight() {
        std::cout << "inaltimea formei:\n";
        std::cin >> height;
    }
    double jam() const { return 2 * area() * height; }
    double cream() const { return perimeter() * height + area(); }
};

class Circle : public Shape {
    double radius;
public:
    Circle() {
        std::cout << "raza:\n";
        std::cin >> radius;
    }
    double area() const override { return PI * radius * radius; }
    double perimeter() const override { return 2 * PI * radius; }
};

class Rectangle : public Shape {
    double lenght;
    double width;
public:
    Rectangle() {
        std::cout << "lungimea si latimea:\n";
        std::cin >> lenght >> width;
    }
    double area() const override { return lenght * width; }
    double perimeter() const override { return 2 * (lenght + width); }
};

class Square : public Shape {
    double side;
public:
    Square() {
        std::cout << "latura:\n";
        std::cin >> side;
    }
    double area() const override { return pow(side, 2); }
    double perimeter() const override { return 4 * side; }
};

class Triangle : public Shape {
    double c1;
    double c2;
public:
    Triangle() {
        std::cout << "cele doua catete:\n";
        std::cin >> c1 >> c2;
    }
    double area() const override { return (c1 * c2) / 2; }
    double perimeter() const override {
        double hypotenuse = sqrt(pow(c1, 2) + pow(c2, 2));
        return c1 + c2 + hypotenuse;
    }
};

class ShapeCollection {
    std::vector<Shape*> myVector;
public:
    void add() {
        std::cout << "tipul bazei:\n";
        std::string s;
        std::cin >> s;
        Shape* currentShape = nullptr;
        if (s == "cerc") currentShape = new Circle;
        else if (s == "dreptunghi") currentShape = new Rectangle;
        else if (s == "patrat") currentShape = new Square;
        else if (s == "triunghi") currentShape = new Triangle;
        if (currentShape != nullptr) {
            myVector.push_back(currentShape);
            myVector.back()->initializeHeight();
            std::cout << "necesarul de gem: " << myVector.back()->jam() << " g\n";
            std::cout << "necesarul de frisca: " << myVector.back()->cream() << " g\n";
        }
        else {
            std::cout << "forma gresita\n";
            add();
        }
    }
    void total() {
        double jamSum = 0.0;
        double creamSum = 0.0;
        for (const auto& i : myVector)
        {
            jamSum += i->jam();
            creamSum += i->cream();
        }
        std::cout << "necesarul total de gem este: " << jamSum << " g\n";
        std::cout << "necesarul total de frisca este: " << creamSum << " g\n";
    }
    void remove() {
        while (true) {
            int index;
            std::cin >> index;
            index--;
            if (index >= myVector.size() || index < 0)
            {
                std::cout << "index gresit\n";
                continue;
            }
            delete myVector[index];
            myVector.erase(myVector.begin() + index);
            break;
        }
    }
};

void loop()
{
    ShapeCollection container;
    while (true) {
        std::cout << "comanda:\n";
        std::string s;
        std::cin >> s;
        if (s == "add")
            container.add();
        else if (s == "remove")
            container.remove();
        else if (s == "total")
            container.total();
        else if (s == "stop") break;
        else {
            std::cout << "input gresit\n\n";
            continue;
        }
        std::cout << "\n\n";
    }
}
int main()
{
    loop();
    return 0;
}