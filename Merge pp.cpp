#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib> // Para rand()
#include <ctime>   // Para time()

void merge(std::vector<int>& arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<int> leftArray(n1);
    std::vector<int> rightArray(n2);

    for (int i = 0; i < n1; i++)
        leftArray[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArray[j] = arr[middle + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (leftArray[i] <= rightArray[j]) {
            arr[k] = leftArray[i];
            i++;
        } else {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArray[j];
        j++;
        k++;
    }
}

void mergeSortSequential(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSortSequential(arr, left, middle);
        mergeSortSequential(arr, middle + 1, right);

        merge(arr, left, middle, right);
    }
}

void mergeSortParallel(std::vector<int>& arr, int left, int right, int numThreads) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        if (numThreads > 1) {
            std::thread leftThread(mergeSortParallel, std::ref(arr), left, middle, numThreads / 2);
            std::thread rightThread(mergeSortParallel, std::ref(arr), middle + 1, right, numThreads / 2);

            leftThread.join();
            rightThread.join();
        } else {
            mergeSortParallel(arr, left, middle, numThreads);
            mergeSortParallel(arr, middle + 1, right, numThreads);
        }

        merge(arr, left, middle, right);
    }
}

int main() {
    // Ingreso del número de elementos del arreglo
    int n;
    std::cout << "Ingrese el numero de elementos del arreglo: ";
    std::cin >> n;

    // Generar arreglo con números aleatorios
    std::vector<int> arr(n);
    srand(time(0));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 5000; // Números aleatorios entre 0 y 99
    }
    
    // Crear una copia del arreglo original
    std::vector<int> arr2(arr);

    /* std::cout << "Arreglo original: ";
    for (int num : arr) {
        std::cout << num << " ";
    } */

    // Medir tiempo para Merge Sort secuencial
    auto startTimeSequential = std::chrono::high_resolution_clock::now();
    mergeSortSequential(arr, 0, arr.size() - 1);
    auto endTimeSequential = std::chrono::high_resolution_clock::now();

	/* 
    std::cout << "\nArreglo ordenado secuencialmente: ";
    for (int num : arr) {
        std::cout << num << " ";
    } */

    auto durationSequential = std::chrono::duration_cast<std::chrono::microseconds>(endTimeSequential - startTimeSequential);
    std::cout << "\nTiempo secuencial: " << durationSequential.count() << " microsegundos\n";

	// Restaurar el arreglo original
    arr = arr2;

    // Medir tiempo para Merge Sort paralelo
    int numThreads = 4; // Puedes ajustar el número de hilos según tus necesidades
    auto startTimeParallel = std::chrono::high_resolution_clock::now();
    mergeSortParallel(arr2, 0, arr2.size() - 1, numThreads);
    auto endTimeParallel = std::chrono::high_resolution_clock::now();

	/*
    std::cout << "\nArreglo ordenado en paralelo: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    */

    auto durationParallel = std::chrono::duration_cast<std::chrono::microseconds>(endTimeParallel - startTimeParallel);
    std::cout << "\nTiempo paralelo: " << durationParallel.count() << " microsegundos\n";

    return 0;
}
