#include <iostream>
#include <stdint.h>
using namespace std;

class Animal {
    public:
    virtual void run() {
        cout << "dont know how run." << endl;
    }
    virtual void call() {
        cout << "dont konw how call." << endl;
    }
};

class Dog : public Animal {
    public:
        Dog():name_("dog"){}
        virtual void run() override {
            cout << name_ << " run slowly." << endl;
        }
        virtual void call() override {
            cout << name_ << ": wangwang." << endl;
        }
    private:
        string name_;
};

class Cat : public Animal {
    public:
        Cat():name_("cat"){}
        virtual void run() override {
            cout << name_ << " run quickly." << endl;
        }
        virtual void call() override {
            cout << name_ << ": miaomiao." << endl;
        }
    private:
        string name_;
};

class Worker {

};

class Owner {
    public:
        Owner():name_("owner"), mask(0xFFFFFFFFFFFFFFFFLL) {}
    private:
        string name_;
        Dog dog_;
        Cat cat_;
        uint64_t mask;
};

int main() {
    Animal a;
    a.run();
    a.call();

    Dog d;

    Animal& a2 = d;
    a2.run();
    a2.call();

    Cat c;// = new Cat();
    Animal *a3 = &c;
    a3->run();
    a3->call();

    Owner o;

    string s = "hello";
    return 0;
}
