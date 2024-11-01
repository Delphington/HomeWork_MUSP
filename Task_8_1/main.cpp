#include <iostream>
#include <cmath>
#include <variant>
#include <optional>

using namespace std;

struct Roots {
    double root1;
    double root2;
};

using Result = variant<monostate, Roots, double>;

class Srv {

public:
    static optional<int> parseCMD(string arg2) {
        try {
            return stoi(arg2);
        }
        catch (const invalid_argument &ex) {
            return nullopt;
        }
    }

    static double getDiscriminant(double a, double b, double c) {
        return b * b - 4 * a * c;
    }

    static Result solveQuadratic(double a, double b, double c) {
        if (a == 0) {
            return monostate();
        }

        double discriminant = getDiscriminant(a, b, c);

        if (discriminant > 0) {
            // Два различных действительных корня
            double root1 = (-b + sqrt(discriminant)) / (2 * a);
            double root2 = (-b - sqrt(discriminant)) / (2 * a);
            return Roots{root1, root2};
        } else if (discriminant == 0) {
            double root = -b / (2 * a);
            return root;
        } else {
            return monostate();
        }
    }

    static void printResult(const Result &result) {
        //Про switch case спросить
        if (holds_alternative<monostate>(result)) {
            cout << "no solution";
        } else if (holds_alternative<Roots>(result)) {
            const Roots &roots = get<Roots>(result);
            cout << "x1 = " << roots.root1 << ", x2 = " << roots.root2;
        } else if (holds_alternative<double>(result)) {
            double root = get<double>(result);
            cout << "x = " << root;
        }
    }
};

//ax^2 + b *x + c = 0
int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cout << "error input" << endl;
        return 1;
    }
    const int CONST_DEFAULT = 0;
    double a = Srv::parseCMD(argv[1]).value_or(CONST_DEFAULT);
    double b = Srv::parseCMD(argv[2]).value_or(CONST_DEFAULT);
    double c = Srv::parseCMD(argv[3]).value_or(CONST_DEFAULT);

    cout<<"a,b,c: " << a <<" "<< b<< " "<<c<<endl;
    Result result = Srv::solveQuadratic(a, b, c);
    Srv::printResult(result);
    return 0;
}
//Для запуска:
/**
g++ -o main main.cpp
./main  '1', '4', '4'  - 1 решение
./main  '1', '-5', '9'  - нет решений
./main  '1', '3', '-4'  - 2 решения
 */