#include <iostream>
#include <vector>

// Observer interface
class Observer {
public:
    virtual void update(std::string message) = 0;
};

// Observable interface
class Observable {
protected:
    std::vector<Observer*> observers;

public:
    void registerObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void notifyObservers(std::string message) {
        for (Observer* observer : observers) {
            observer->update(message);
        }
    }
};

// ConcreteObservable (Friend) class
class ConcreteObservable : public Observable {
private:
    std::string friendName;

public:
    ConcreteObservable(std::string name) : friendName(name) {}

    void subscribe() {
        notifyObservers(friendName + " подписался на Хабр.");
    }

    void unsubscribe() {
        notifyObservers(friendName + " отписался от Хабр.");
    }
};

// ConcreteObserver class
class ConcreteObserver : public Observer {
private:
    std::string observerName;

public:
    ConcreteObserver(std::string name) : observerName(name) {}

    void update(std::string message) override {
        std::cout << "Уведомление для " << observerName << ": " << message << std::endl;
    }
};

int main() {

    std::cout << std::endl;
    // Создаем наблюдателей
    ConcreteObserver me("Арсений");
    ConcreteObserver yulia("Юля");
    ConcreteObserver oleg("Олег");

    // Создаем объекты-субъекты
    ConcreteObservable person1("Демид");
    ConcreteObservable person2("Олег");

    // Регистрируем наблюдателей
    person1.registerObserver(&me);
    person2.registerObserver(&me);
    person2.registerObserver(&yulia);
    person1.registerObserver(&oleg);

    // Подписываем и отписываем друзей
    person1.subscribe();
    std::cout << std::endl;
    person2.subscribe();
    std::cout << std::endl;
    person2.unsubscribe();

    std::cout << std::endl;

    return 0;
}