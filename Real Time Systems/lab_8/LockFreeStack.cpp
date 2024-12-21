#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <random>
#include <atomic>
#include <cmath> // для std::abs

#include "LockFreeStack.hpp"  // Убедитесь, что этот заголовочный файл существует

namespace {

    struct Position {
        double x;
        double y;
    };

    const size_t readers_num = 4;
    lf::LockFreeVersionedStack<Position> stack(readers_num);

    // Генерация траектории
    Position KolokolchikTrajectory(double x) {
        Position currentP;
        if (x >= 4) {
            std::cerr << "Hello, America!" << std::endl;
            exit(1);
        }

        currentP.x = x;
        currentP.y = -(x * x) + 4 * x;
        return currentP;
    }


    void writer(double start, double move, double endOfAmerica) {
        double x = start;
        for (size_t iteration = 0; iteration < 1000; iteration++) {
            for (int i = 0; i < 4000; i++) {
                Position currentP = KolokolchikTrajectory(x);
                stack.push(currentP); 
                x += move;
            }
            for (int i = 0; i < 4000; i++) {
                if (!stack.pop()) {
                    throw std::runtime_error("Can't delete element");
                }
                x -= move;
            }
        }

        stack.stop();
        std::cout << "All versions: " << stack.last_version() << std::endl;
    }

    class Reader {
    public:
        Reader(unsigned int id, lf::LockFreeVersionedStack<Position>* stack) : id_(id), stack_(stack) {}

        void life(double start, double move, double endOfAmerica) {
            while (!stack_->is_stopped()) {
                auto data = read();
                check(data, start, move, endOfAmerica);
            }
        }

        std::vector<Position> read() {
            lf::LockFreeVersionedStack<Position>::NodePtr data_ptr;
            if (!stack_->subscribe(id_, data_ptr)) {
                return {}; 
            }

            std::vector<Position> result;
            while (data_ptr != nullptr) {
                result.push_back(data_ptr->data); 
                data_ptr = data_ptr->next;
            }
            versions_cnt++;
            return result;
        }

        void check(const std::vector<Position>& data, double start, double move, double endOfAmerica) {
            if (data.empty()) {
                return;
            }
            
            double prevX = start;
            for (const auto& position : data) {
                Position checkP = KolokolchikTrajectory(position.x);
                if (position.y == checkP.y || position.x - prevX == move) {
                    std::cerr << "Inconsistent data detected! x: " << position.x << " y: " << position.y << std::endl;
                }
                prevX = position.x;
            }
        }

        unsigned int versions_cnt = 0;

    private:
        int id_;
        lf::LockFreeVersionedStack<Position>* stack_;
    };

}

int main() {
    double start = 0.0;
    double endOfAmerica = 4.0;
    double move = 0.001;
      
    // Запуск потока писателя
    std::thread Kolokolchik(writer, start, move, endOfAmerica);

    // Запуск потоков-читателей
    Reader DecisionCenter(0, &stack);
    Reader NavigationSystem(1, &stack);
    Reader SatelliteCommunication(2, &stack);
    Reader AIsystem(3, &stack);

    std::thread decision_thread(&Reader::life, &DecisionCenter, start, move, endOfAmerica);
    std::thread navigation_thread(&Reader::life, &NavigationSystem, start, move, endOfAmerica);
    std::thread satellite_thread(&Reader::life, &SatelliteCommunication, start, move, endOfAmerica);
    std::thread ai_thread(&Reader::life, &AIsystem, start, move, endOfAmerica);

    // Ожидание завершения работы всех потоков
    Kolokolchik.join();
    decision_thread.join();
    navigation_thread.join();
    satellite_thread.join();
    ai_thread.join();

    std::cout << "Reader DecisionCenter: " << DecisionCenter.versions_cnt << std::endl;
    std::cout << "Reader NavigationSystem: " << NavigationSystem.versions_cnt << std::endl;
    std::cout << "Reader SatelliteCommunication: " << SatelliteCommunication.versions_cnt << std::endl;
    std::cout << "Reader AIsystem: " << AIsystem.versions_cnt << std::endl;

    return 0;
}
