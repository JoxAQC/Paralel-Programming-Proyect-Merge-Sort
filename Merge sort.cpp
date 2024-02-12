#include <iostream>
#include <vector>

void merge(std::vector<int>& arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Crear arreglos temporales
    std::vector<int> leftArray(n1);
    std::vector<int> rightArray(n2);

    // Copiar datos a los arreglos temporales leftArray[] y rightArray[]
    for (int i = 0; i < n1; i++)
        leftArray[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArray[j] = arr[middle + 1 + j];

    // Mezclar los arreglos temporales de nuevo en arr[left..right]
    int i = 0; // Índice inicial del primer subarreglo
    int j = 0; // Índice inicial del segundo subarreglo
    int k = left; // Índice inicial del arreglo mezclado

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

    // Copiar los elementos restantes de leftArray[], si los hay
    while (i < n1) {
        arr[k] = leftArray[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de rightArray[], si los hay
    while (j < n2) {
        arr[k] = rightArray[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        // Encuentra el punto medio del arreglo
        int middle = left + (right - left) / 2;

        // Ordena la primera y la segunda mitad
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        // Mezcla las mitades ordenadas
        merge(arr, left, middle, right);
    }
}

int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};

    std::cout << "Arreglo original: ";
    for (int num : arr) {
        std::cout << num << " ";
    }

    mergeSort(arr, 0, arr.size() - 1);

    std::cout << "\nArreglo ordenado: ";
    for (int num : arr) {
        std::cout << num << " ";
    }

    return 0;
}
