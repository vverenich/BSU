#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

std::atomic<bool> applicationExited{false};

std::mutex              mtxWaterLevelSensor;
std::condition_variable cvWaterLevelSensor;

std::mutex              mtxWaterGateLock;
std::condition_variable cvWaterGateLock;

std::condition_variable cvWaterTemperatureSensor;
std::mutex              mtxWaterTemperatureSensor;

// Sensors
class WaterPressureSensor {
  public:
    int getPressure() const {
        return m_Pressure;
    }

  public:
    int m_Pressure{100};
};

class WaterTemperatureSensor {
public:
    double getTemperature() const {
        return m_Temperature.load();
    }

    void setTemperature(const double value) {
        m_Temperature.store(value);
        cvWaterTemperatureSensor.notify_all();
    }

public:
    std::atomic<double> m_Temperature{20};
};


class WaterLevelSensor {
  public:
    bool getState() const {
        return m_State.load();
    }

    void setState(const bool state) {
        m_State.store(state);
        cvWaterLevelSensor.notify_all();
    }

  public:
    std::atomic<bool> m_State{false};
};

// Managed devices
class WaterGateLock {
  public:
    void openGate() {
        m_State.store(true);
        cvWaterGateLock.notify_all();
    }

    void closeGate() {
        m_State.store(false);
        cvWaterGateLock.notify_all();
    }

    bool getState() const {
        return m_State.load();
    }

  public:
    std::atomic<bool> m_State{false};
};

class WaterHeater {
public:
    void setTemperatureToHeat(const double temperature) {
        m_TemperatureToHeat.store(temperature);
        cvWaterTemperatureSensor.notify_all();
    }

    double getTemperatureToHeat() const {
        return m_TemperatureToHeat.load();
    }

    void work()
    {

    }

public:
    std::atomic<double> m_TemperatureToHeat{20};
};

class WaterPump {
public:

    void work()
    {

    }
};




class MonitoringSystem {    
  public:
    explicit MonitoringSystem(WaterPressureSensor* waterPressureSensor,
                              WaterTemperatureSensor* waterTemperatureSensor,
                              WaterLevelSensor* waterLevelSensor,
                              WaterGateLock* waterGateLock,
                              WaterHeater* waterHeater,
                              WaterPump* waterPump) :
        m_WaterPressureSensor{waterPressureSensor},
        m_WaterTemperatureSensor{waterTemperatureSensor},
        m_WaterLevelSensor{waterLevelSensor},
        m_WaterGateLock{waterGateLock},
        m_WaterHeater{waterHeater},
        m_WaterPump{waterPump}
    {

    }


    WaterPressureSensor*    m_WaterPressureSensor{nullptr};
    WaterTemperatureSensor* m_WaterTemperatureSensor{nullptr};
    WaterLevelSensor*       m_WaterLevelSensor{nullptr};
    WaterGateLock*          m_WaterGateLock{nullptr};
    WaterHeater*            m_WaterHeater{nullptr};
    WaterPump*              m_WaterPump{nullptr};
};

std::ostream& operator<< (std::ostream& out, MonitoringSystem& monitoringSystem) {
    out << "\n\n";
    out << "Water pressure: " << monitoringSystem.m_WaterPressureSensor->getPressure() << "\n";
    out << "Water temperature: " << monitoringSystem.m_WaterTemperatureSensor->getTemperature() << "\n";
    out << "Water level sensor state: " << monitoringSystem.m_WaterLevelSensor->getState() << "\n";
    out << "Water gate lock state: " << monitoringSystem.m_WaterGateLock->getState() << "\n";
    out << "\n\n";

    return out;
}

class Menu {
  public:
    explicit Menu(MonitoringSystem* monitoringSystem) :
        m_MonitoringSystem{monitoringSystem}
    {

    }

    void run() {
        int count = 0;
        bool isRunning{true};
        while (isRunning)
        {
            std::cout << "\n\n";
            std::cout << "1) Print monitoring system state.\n";
            std::cout << "2) Set new water temperature to heat to.\n";
            std::cout << "3) Close water gate lock .\n";
            std::cout << "4) Open water gate lock .\n";
            std::cout << "5) Exit.\n";
            std::cout << "6) * Set current tempearture of water.\n";
            std::cout << "7) * Set state of water level sensor.\n";
            std::cout << "Enter your selection (1, 2, 3 or 4): ";

            int choice;
            std::cin >> choice;

            switch (choice)
            {
                case 1: {
                    std::cout << *m_MonitoringSystem;

                    break;
                }

                case 2: {
                    std::cout << "\nEnter new temperature to heat to: ";
                    double temperature;
                    std::cin >> temperature;

                    m_MonitoringSystem->m_WaterHeater->setTemperatureToHeat(temperature);

                    break;
                }

                case 3: {
                    m_MonitoringSystem->m_WaterGateLock->closeGate();

                    break;
                }

                case 4: {
                    m_MonitoringSystem->m_WaterGateLock->openGate();

                    break;
                }

                case 5: {
                    isRunning = false;
                    applicationExited.store(true);

                    break;
                }

                case 6: {
                    std::cout << "\nEnter current temperature: ";
                    double temperature;
                    std::cin >> temperature;

                    m_MonitoringSystem->m_WaterTemperatureSensor->setTemperature(temperature);

                    break;
                }

                case 7: {
                    std::cout << "\nEnter the state: ";
                    int state;
                    std::cin >> state;
                    m_MonitoringSystem->m_WaterLevelSensor->setState(state);

                    break;
                }

                default : {
                    std::cout << "\nYou have made the wrong choice. Try again.";

                    break;
                }
            }



            count ++;
            if (count == 100) {
                    break;
            }
        }

    }

  public:
    MonitoringSystem* m_MonitoringSystem{nullptr};
};

WaterPressureSensor waterPressureSensor{};
WaterTemperatureSensor waterTemperatureSensor{};
WaterLevelSensor waterLevelSensor{};
WaterGateLock waterGateLock{};
WaterHeater waterHeater{};
WaterPump waterPump{};

MonitoringSystem monitoringSystem = MonitoringSystem(&waterPressureSensor,
                                                     &waterTemperatureSensor,
                                                     &waterLevelSensor,
                                                     &waterGateLock,
                                                     &waterHeater,
                                                     &waterPump);

Menu menu = Menu(&monitoringSystem);

void pumpThreadFunction() {
    while (!applicationExited.load()) {
        // Проверка состояния датчика уровня воды
        std::unique_lock<std::mutex> lockWaterLevelSensor(mtxWaterLevelSensor);
        cvWaterLevelSensor.wait(lockWaterLevelSensor, [] { return waterLevelSensor.getState() == false; });

        // Проверка на блокировку пропуска воды
        std::unique_lock<std::mutex> lockWaterGateLock(mtxWaterGateLock);
        cvWaterGateLock.wait(lockWaterGateLock, [] { return  waterGateLock.getState() == true; });

        // Выполнение работы насоса
        std::cout << "\n * pump is working *";
        waterPump.work();

        cvWaterLevelSensor.notify_all();
        cvWaterGateLock.notify_all();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void heaterThreadFunction() {
    while (!applicationExited.load()) {
        // Проверка состояния датчика температуры
        std::unique_lock<std::mutex> lockWaterTemperatureSensor(mtxWaterTemperatureSensor);
        cvWaterTemperatureSensor.wait(lockWaterTemperatureSensor, [] {
            return waterTemperatureSensor.getTemperature() < waterHeater.getTemperatureToHeat(); });

        // Выполнение работы нагревателя
        std::cout << "\n* heater is working *";
        waterHeater.work();

        cvWaterTemperatureSensor.notify_all();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}




int main() {
    std::thread pumpThread(pumpThreadFunction);
    std::thread heaterTread(heaterThreadFunction);

    cvWaterGateLock.notify_all();
    cvWaterLevelSensor.notify_all();
    cvWaterTemperatureSensor.notify_all();

    menu.run();

    pumpThread.join();
    heaterTread.join();

    return 0;
}


