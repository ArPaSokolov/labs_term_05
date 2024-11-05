#include <iostream>
#include <vector>

class Observer {
public:
    virtual void update(std::string message) = 0;
};

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
    // Создаем наблюдателей
    ConcreteObserver me("Арсений");
    ConcreteObserver yulia("Юля");
    ConcreteObserver oleg("Олег");

    // Создаем наблюдаемые объекты
    ConcreteObservable person1("Демид");
    ConcreteObservable person2("Олег");

    // Делаемся друзьями
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

    return 0;
}