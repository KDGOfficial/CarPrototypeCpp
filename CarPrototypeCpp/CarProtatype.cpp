#include <iostream>
#include <memory>
#include <string>

using namespace std;

// ������� ��������� ��� ������������ ��������
class Prototype {
public:
    virtual ~Prototype() = default;
    virtual unique_ptr<Prototype> clone() const = 0;
};

// ����� ���������
class Engine : public Prototype {
    string type;
    int horsepower;
public:
    Engine(string type, int hp) : type(type), horsepower(hp) {}
    unique_ptr<Prototype> clone() const override {
        return make_unique<Engine>(*this);
    }
    void show() const { cout << "���������: " << type << ", " << horsepower << " �.�.\n"; }
};

// ����� ������� �������
class Transmission : public Prototype {
    string type;
    int gears;
public:
    Transmission(string type, int gears) : type(type), gears(gears) {}
    unique_ptr<Prototype> clone() const override {
        return make_unique<Transmission>(*this);
    }
    void show() const { cout << "������� �������: " << type << ", " << gears << " �������\n"; }
};

// ����� �������������
class Manufacturer : public Prototype {
    string name;
    string country;
public:
    Manufacturer(string name, string country) : name(name), country(country) {}
    unique_ptr<Prototype> clone() const override {
        return make_unique<Manufacturer>(*this);
    }
    void show() const { cout << "�������������: " << name << " (" << country << ")\n"; }
};

// ����� �����
class Chassis : public Prototype {
    string material;
public:
    Chassis(string material) : material(material) {}
    unique_ptr<Prototype> clone() const override {
        return make_unique<Chassis>(*this);
    }
    void show() const { cout << "�����: " << material << "\n"; }
};

// ����� �����������
class Electronics : public Prototype {
    string system;
public:
    Electronics(string system) : system(system) {}
    unique_ptr<Prototype> clone() const override {
        return make_unique<Electronics>(*this);
    }
    void show() const { cout << "�����������: " << system << "\n"; }
};

// ����� ����������
class Car : public Prototype {
    string model;
    unique_ptr<Engine> engine;
    unique_ptr<Transmission> transmission;
    unique_ptr<Manufacturer> manufacturer;
    unique_ptr<Chassis> chassis;
    unique_ptr<Electronics> electronics;
public:
    Car(string model, unique_ptr<Engine> eng, unique_ptr<Transmission> trans,
        unique_ptr<Manufacturer> manu, unique_ptr<Chassis> ch, unique_ptr<Electronics> elec)
        : model(model), engine(move(eng)), transmission(move(trans)), manufacturer(move(manu)), chassis(move(ch)), electronics(move(elec)) {
    }

    unique_ptr<Prototype> clone() const override {
        return make_unique<Car>(model,
            unique_ptr<Engine>(static_cast<Engine*>(engine->clone().release())),
            unique_ptr<Transmission>(static_cast<Transmission*>(transmission->clone().release())),
            unique_ptr<Manufacturer>(static_cast<Manufacturer*>(manufacturer->clone().release())),
            unique_ptr<Chassis>(static_cast<Chassis*>(chassis->clone().release())),
            unique_ptr<Electronics>(static_cast<Electronics*>(electronics->clone().release())));
    }

    void show() const {
        cout << "������ ����������: " << model << "\n";
        engine->show();
        transmission->show();
        manufacturer->show();
        chassis->show();
        electronics->show();
    }
};

// �������� ���������
int main() {
    unique_ptr<Car> originalCar = make_unique<Car>("Tesla Model S",
        make_unique<Engine>("�������������", 1020),
        make_unique<Transmission>("��������������", 1),
        make_unique<Manufacturer>("Tesla", "���"),
        make_unique<Chassis>("����������� �����"),
        make_unique<Electronics>("���������"));

    cout << "������������ ����������:\n";
    originalCar->show();

    unique_ptr<Car> clonedCar = unique_ptr<Car>(static_cast<Car*>(originalCar->clone().release()));

    cout << "\n���� ����������:\n";
    clonedCar->show();

    return 0;
}
