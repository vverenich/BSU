#include <iostream>
#include <vector>
#include <cmath>

struct Neuron {
    std::vector<double> weights;
    double bias;

    Neuron(int numInputs) {
        weights.resize(numInputs);
        for (int i = 0; i < numInputs; ++i) {
            weights[i] = getRandomWeight();
        }
        bias = getRandomWeight();
    }

    double getRandomWeight() {
        return ((double)rand() / RAND_MAX) * 2 - 1;
    }

    double activationFunction(double x) {
        return 1.0 / (1.0 + std::exp(-x)); // Сигмоида
    }

    double calculateOutput(const std::vector<double>& inputs) {
        double sum = bias;
        for (int i = 0; i < inputs.size(); ++i) {
            sum += inputs[i] * weights[i];
        }
        return activationFunction(sum);
    }
};

class Perceptron {
private:
    std::vector<Neuron> inputLayer;
    std::vector<Neuron> hiddenLayer;
    std::vector<Neuron> outputLayer;

public:
    Perceptron(int numInputs, int numHidden, int numOutputs) {
        inputLayer.resize(numInputs, Neuron(0));
        hiddenLayer.resize(numHidden, Neuron(numInputs));
        outputLayer.resize(numOutputs, Neuron(numHidden));
    }

    void train(const std::vector<std::vector<int>>& trainingData, const std::vector<int>& labels) {
        const double allowedError{0.005};
        for (int epoch = 0; epoch < 70; ++epoch) {
            double error = 0;
            double delta = 0;
            for (int i = 0; i < trainingData.size(); ++i) {
                const std::vector<int>& input = trainingData[i];
                int label = labels[i];

                std::vector<double> inputValues;
                for (int j = 0; j < input.size(); ++j) {
                    inputValues.push_back(static_cast<double>(input[j]));
                }

                std::vector<double> hiddenOutputs(hiddenLayer.size());
                for (int j = 0; j < hiddenLayer.size(); ++j) {
                    hiddenOutputs[j] = hiddenLayer[j].calculateOutput(inputValues);
                }

                std::vector<double> outputOutputs(outputLayer.size());
                for (int j = 0; j < outputLayer.size(); ++j) {
                    outputOutputs[j] = outputLayer[j].calculateOutput(hiddenOutputs);
                }

                for (int j = 0; j < outputLayer.size(); ++j) {
                    double error = label - outputOutputs[j];
                    double delta = error * outputOutputs[j] * (1 - outputOutputs[j]);
                    for (int k = 0; k < hiddenLayer.size(); ++k) {
                        outputLayer[j].weights[k] += delta * hiddenOutputs[k];
                    }
                    outputLayer[j].bias += delta;
                }

                for (int j = 0; j < hiddenLayer.size(); ++j) {
                    for (int k = 0; k < outputLayer.size(); ++k) {
                        error += outputLayer[k].weights[j] * outputOutputs[k] * (1 - outputOutputs[k]);
                    }
                    delta = error * hiddenOutputs[j] * (1 - hiddenOutputs[j]);
                    for (int k = 0; k < inputLayer.size(); ++k) {
                        hiddenLayer[j].weights[k] += delta * inputValues[k];
                    }
                    hiddenLayer[j].bias += delta;
                }
            }


            std::cout << "epoch: " << epoch << ", error: " << error << "\n";

            if (error < allowedError) {
                return;
            }

        }
    }

    int predict(const std::vector<int>& input) {
        std::vector<double> inputValues;
        for (int j = 0; j < input.size(); ++j) {
            inputValues.push_back(static_cast<double>(input[j]));
        }

        std::vector<double> hiddenOutputs(hiddenLayer.size());
        for (int j = 0; j < hiddenLayer.size(); ++j) {
            hiddenOutputs[j] = hiddenLayer[j].calculateOutput(inputValues);
        }

        std::vector<double> outputOutputs(outputLayer.size());
        for (int j = 0; j < outputLayer.size(); ++j) {
            outputOutputs[j] = outputLayer[j].calculateOutput(hiddenOutputs);
        }

        double maxOutput = outputOutputs[0];
        int maxIndex = 0;
        for (int i = 1; i < outputOutputs.size(); ++i) {
            if (outputOutputs[i] > maxOutput) {
                maxOutput = outputOutputs[i];
                maxIndex = i;
            }
        }

        return maxIndex;
    }
};
int main() {
    // Тренировочные данные и метки
    std::vector<std::vector<int>> trainingData = {
        {1, 0, 0, 0, 0, 1,
         0, 1, 0, 0, 1, 0,
         0, 0, 1, 1, 0, 0,
         0, 1, 0, 0, 1, 0,
         1, 0, 0, 0, 0, 1},  // Символ крестика
        {1, 0, 0, 0, 0, 1,
         1, 1, 1, 1, 1, 1,
         0, 0, 1, 1, 0, 0,
         0, 1, 1, 1, 1, 0,
         1, 1, 0, 0, 0, 1},  // Символ крестика
        {1, 0, 1, 1, 1, 1,
         0, 1, 1, 1, 1, 1,
         0, 0, 1, 1, 1, 1,
         0, 1, 1, 1, 1, 1,
         1, 0, 1, 1, 1, 1},  // не Символ крестика
    };
    std::vector<int> labels = {1, 1, 0};  // Метки: 1 - символ крестика, 0 - не символ крестика

    // Создание и обучение персептрона
    Perceptron perceptron(30, 5, 1);
    perceptron.train(trainingData, labels);

    // Тестирование на новых данных
    std::vector<int> testInput = {1, 0, 0, 0, 0, 1,
                                  0, 1, 0, 0, 1, 0,
                                  0, 0, 1, 1, 0, 0,
                                  0, 1, 0, 0, 1, 0,
                                  1, 0, 0, 0, 0, 1};  // Символ крестика
    int prediction = perceptron.predict(testInput);
    std::cout << "Prediction: " << prediction << std::endl;

    return 0;
}
