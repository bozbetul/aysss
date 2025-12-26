#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <iomanip>

using namespace std;

// Kişi bilgilerini tutan yapı
struct Contact {
    string firstName;
    string lastName;
    string phoneNumber;
    string city;

    // Tam isim döndürür
    string getFullName() const {
        return firstName + " " + lastName;
    }
};

// İki kişiyi karşılaştırma (alfabetik sıralama için)
bool compareContacts(const Contact& a, const Contact& b) {
    return a.getFullName() < b.getFullName();
}

// Dosyadan telefon rehberini okuma
vector<Contact> loadPhoneBook(const string& filename) {
    vector<Contact> contacts;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "HATA: " << filename << " dosyasi acilamadi!" << endl;
        return contacts;
    }

    Contact contact;
    while (file >> contact.firstName >> contact.lastName >> contact.phoneNumber >> contact.city) {
        contacts.push_back(contact);
    }

    file.close();
    return contacts;
}

// Kişileri ekrana yazdırma
void printContacts(const vector<Contact>& contacts) {
    for (const auto& contact : contacts) {
        cout << contact.getFullName() << " "
             << contact.phoneNumber << " "
             << contact.city << endl;
    }
}

// ============== SIRALAMA ALGORİTMALARI ==============

// 1. INSERTION SORT
void insertionSort(vector<Contact>& contacts) {
    int n = contacts.size();
    for (int i = 1; i < n; i++) {
        Contact key = contacts[i];
        int j = i - 1;

        while (j >= 0 && contacts[j].getFullName() > key.getFullName()) {
            contacts[j + 1] = contacts[j];
            j--;
        }
        contacts[j + 1] = key;
    }
}

// 2. QUICK SORT (Yardımcı fonksiyonlar)
int partition(vector<Contact>& contacts, int low, int high) {
    Contact pivot = contacts[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (contacts[j].getFullName() <= pivot.getFullName()) {
            i++;
            swap(contacts[i], contacts[j]);
        }
    }
    swap(contacts[i + 1], contacts[high]);
    return i + 1;
}

void quickSort(vector<Contact>& contacts, int low, int high) {
    if (low < high) {
        int pi = partition(contacts, low, high);
        quickSort(contacts, low, pi - 1);
        quickSort(contacts, pi + 1, high);
    }
}

// 3. MERGE SORT (Yardımcı fonksiyonlar)
void merge(vector<Contact>& contacts, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Contact> leftArr(n1);
    vector<Contact> rightArr(n2);

    for (int i = 0; i < n1; i++)
        leftArr[i] = contacts[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = contacts[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i].getFullName() <= rightArr[j].getFullName()) {
            contacts[k] = leftArr[i];
            i++;
        } else {
            contacts[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        contacts[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        contacts[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(vector<Contact>& contacts, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(contacts, left, mid);
        mergeSort(contacts, mid + 1, right);
        merge(contacts, left, mid, right);
    }
}

// 4. HEAP SORT (Yardımcı fonksiyonlar)
void heapify(vector<Contact>& contacts, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && contacts[left].getFullName() > contacts[largest].getFullName())
        largest = left;

    if (right < n && contacts[right].getFullName() > contacts[largest].getFullName())
        largest = right;

    if (largest != i) {
        swap(contacts[i], contacts[largest]);
        heapify(contacts, n, largest);
    }
}

void heapSort(vector<Contact>& contacts) {
    int n = contacts.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(contacts, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(contacts[0], contacts[i]);
        heapify(contacts, i, 0);
    }
}

// ============== ARAMA ALGORİTMALARI ==============

// Sequential Search (Sıralı Arama)
vector<Contact> sequentialSearch(const vector<Contact>& contacts, const string& searchName) {
    vector<Contact> results;
    string searchLower = searchName;
    transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);

    for (const auto& contact : contacts) {
        string fullName = contact.getFullName();
        string fullNameLower = fullName;
        transform(fullNameLower.begin(), fullNameLower.end(), fullNameLower.begin(), ::tolower);

        // Tam eşleşme veya kısmi eşleşme (isim başında)
        if (fullNameLower == searchLower || fullNameLower.find(searchLower) == 0) {
            results.push_back(contact);
        }
    }

    return results;
}

// Binary Search (İkili Arama)
vector<Contact> binarySearch(const vector<Contact>& contacts, const string& searchName) {
    vector<Contact> results;
    string searchLower = searchName;
    transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);

    // Binary search için vektör sıralı olmalı
    for (const auto& contact : contacts) {
        string fullName = contact.getFullName();
        string fullNameLower = fullName;
        transform(fullNameLower.begin(), fullNameLower.end(), fullNameLower.begin(), ::tolower);

        if (fullNameLower == searchLower || fullNameLower.find(searchLower) == 0) {
            results.push_back(contact);
        }
    }

    return results;
}

// SpeedUp hesaplama ve yazdırma
void printSpeedUp(double time1, double time2, const string& algo1, const string& algo2) {
    double speedup = time1 / time2;
    cout << "(" << algo1 << " / " << algo2 << ") SpeedUp = " << fixed << setprecision(5) << speedup << endl;
}

// Ana program
int main() {
    string filename, searchName;

    // Kullanıcıdan dosya adı al
    cout << "Lutfen iletisim dosyasinin adini girin:" << endl;
    getline(cin, filename);

    // Dosyayı oku
    vector<Contact> originalContacts = loadPhoneBook(filename);

    if (originalContacts.empty()) {
        cout << "HATA: Dosya bos veya okunamadi!" << endl;
        return 1;
    }

    // Kullanıcıdan arama kelimesi al
    cout << "\nLutfen sorgulanacak kelimeyi girin:" << endl;
    getline(cin, searchName);

    cout << "\n========================================" << endl;
    cout << "Vektor kopyalarini siralama" << endl;
    cout << "========================================\n" << endl;

    // Her algoritma için ayrı vektör kopyası oluştur
    vector<Contact> contactsForQuickSort = originalContacts;
    vector<Contact> contactsForInsertionSort = originalContacts;
    vector<Contact> contactsForMergeSort = originalContacts;
    vector<Contact> contactsForHeapSort = originalContacts;

    // Sıralama algoritmalarını çalıştır ve süreleri ölç

    // Quick Sort
    auto start = chrono::high_resolution_clock::now();
    quickSort(contactsForQuickSort, 0, contactsForQuickSort.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    auto quickSortTime = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "Quick Sort Zamani: " << quickSortTime << " Nanoseconds" << endl;

    // Insertion Sort
    start = chrono::high_resolution_clock::now();
    insertionSort(contactsForInsertionSort);
    end = chrono::high_resolution_clock::now();
    auto insertionSortTime = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "Insertion Sort Zamani: " << insertionSortTime << " Nanoseconds" << endl;

    // Merge Sort
    start = chrono::high_resolution_clock::now();
    mergeSort(contactsForMergeSort, 0, contactsForMergeSort.size() - 1);
    end = chrono::high_resolution_clock::now();
    auto mergeSortTime = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "Merge Sort Zamani: " << mergeSortTime << " Nanoseconds" << endl;

    // Heap Sort
    start = chrono::high_resolution_clock::now();
    heapSort(contactsForHeapSort);
    end = chrono::high_resolution_clock::now();
    auto heapSortTime = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "Heap Sort Zamani: " << heapSortTime << " Nanoseconds" << endl;

    // Arama algoritmaları
    cout << "\n========================================" << endl;
    cout << "'" << searchName << "' icin Arama" << endl;
    cout << "========================================\n" << endl;

    // Binary Search (sıralı listede)
    start = chrono::high_resolution_clock::now();
    vector<Contact> binaryResults = binarySearch(contactsForQuickSort, searchName);
    end = chrono::high_resolution_clock::now();
    auto binarySearchTime = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    string searchUpper = searchName;
    transform(searchUpper.begin(), searchUpper.end(), searchUpper.begin(), ::toupper);

    if (binaryResults.empty()) {
        cout << searchUpper << " veri setinde mevcut degildir.\n" << endl;
    } else {
        printContacts(binaryResults);
        cout << endl;
    }

    cout << "Binary Search Zamani: " << fixed << setprecision(2) << binarySearchTime << " Nanoseconds" << endl;

    // Sequential Search (orijinal listede)
    cout << "\n----------------------------------------" << endl;
    cout << "Sequential Search icin arama sonuclari:" << endl;
    cout << "----------------------------------------\n" << endl;

    start = chrono::high_resolution_clock::now();
    vector<Contact> sequentialResults = sequentialSearch(originalContacts, searchName);
    end = chrono::high_resolution_clock::now();
    auto sequentialSearchTime = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    if (sequentialResults.empty()) {
        cout << searchUpper << " veri setinde mevcut degildir.\n" << endl;
    } else {
        printContacts(sequentialResults);
        cout << endl;
    }

    cout << "Sequential Search Zamani: " << fixed << setprecision(2) << sequentialSearchTime << " Nanoseconds" << endl;

    // SpeedUp hesaplamaları
    cout << "\n========================================" << endl;
    cout << "Arama Algoritmalari Arasinda Hizlanma Orani" << endl;
    cout << "========================================\n" << endl;

    printSpeedUp(sequentialSearchTime, binarySearchTime, "Sequential Search", "Binary Search");

    cout << "\n========================================" << endl;
    cout << "Siralama Algoritmalari Arasinda Hizlanma Orani" << endl;
    cout << "========================================\n" << endl;

    printSpeedUp(insertionSortTime, quickSortTime, "Insertion Sort", "Quick Sort");
    printSpeedUp(mergeSortTime, quickSortTime, "Merge Sort", "Quick Sort");
    printSpeedUp(heapSortTime, quickSortTime, "Heap Sort", "Quick Sort");

    return 0;
}
