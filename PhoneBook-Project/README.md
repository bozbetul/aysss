# Telefon Rehberi Yönetim Sistemi

## Proje Hakkında

Bu proje, bir telefon rehberi uygulamasıdır ve farklı sıralama ve arama algoritmalarının performanslarını karşılaştırmak için geliştirilmiştir. Program, telefon rehberi verilerini okur, çeşitli algoritmalara uygular ve bu algoritmaların çalışma sürelerini ölçerek performans analizleri yapar.

## Özellikler

### Sıralama Algoritmaları
Program 4 farklı sıralama algoritması kullanır:
1. **Quick Sort** (Hızlı Sıralama)
2. **Insertion Sort** (Eklemeli Sıralama)
3. **Merge Sort** (Birleştirmeli Sıralama)
4. **Heap Sort** (Yığın Sıralama)

### Arama Algoritmaları
Program 2 farklı arama algoritması kullanır:
1. **Sequential Search** (Sıralı Arama) - Sıralanmamış veri setinde çalışır
2. **Binary Search** (İkili Arama) - Sıralanmış veri setinde çalışır

### Performans Ölçümü
- Tüm algoritmaların çalışma süreleri **nanosaniye** cinsinden ölçülür
- Algoritmalar arası **SpeedUp** (hızlanma) oranları hesaplanır
- Karşılaştırmalı performans analizi yapılır

## Gereksinimler

- **C++ Derleyici** (g++, clang++ veya benzeri)
- **C++11 veya üstü** standart desteği

## Kurulum

### 1. Projeyi İndirin
```bash
git clone <repository-url>
cd PhoneBook-Project
```

### 2. Programı Derleyin
```bash
g++ -std=c++11 main.cpp -o phoneBook
```

veya

```bash
clang++ -std=c++11 main.cpp -o phoneBook
```

## Kullanım

### Program Çalıştırma

```bash
./phoneBook
```

### Adım Adım Kullanım

1. **Dosya Adı Girin:**
   ```
   Lutfen iletisim dosyasinin adini girin:
   PhoneBook.txt
   ```

2. **Aranacak İsmi Girin:**
   ```
   Lutfen sorgulanacak kelimeyi girin:
   Ahmet
   ```

3. **Sonuçları İnceleyin:**
   Program otomatik olarak:
   - Tüm sıralama algoritmalarını çalıştırır
   - Arama algoritmalarını uygular
   - Performans karşılaştırmaları yapar
   - Sonuçları ekrana yazdırır

## Dosya Formatı

`PhoneBook.txt` dosyası aşağıdaki formatta olmalıdır:

```
Isim Soyisim TelefonNumarasi Sehir
```

**Örnek:**
```
Ahmet Yilmaz 5551234567 Istanbul
Mehmet Demir 5559876543 Ankara
Zeynep Kaya 5556789012 Izmir
```

**Önemli Notlar:**
- Her satır bir kişiyi temsil eder
- Veriler boşluk ile ayrılmalıdır
- Her satırda 4 bilgi olmalıdır (isim, soyisim, telefon, şehir)

## Arama Türleri

Program iki tip arama destekler:

### 1. Tam İsim Arama (Full Contact Name Search)
Kullanıcının girdiği ismin tam olarak eşleştiği kayıtları bulur.

**Örnek:**
```
Arama: Ahmet Yilmaz
Sonuç: Sadece "Ahmet Yilmaz" kaydını bulur
```

### 2. Kısmi İsim Arama (Partial Contact Name Search)
Kullanıcının girdiği kelimeyle başlayan tüm kayıtları bulur.

**Örnek:**
```
Arama: Ahmet
Sonuç: "Ahmet Yilmaz", "Ahmet Kaya", "Ahmet Demir" vb. tüm Ahmet'leri bulur
```

## Örnek Çıktı

```
========================================
Vektor kopyalarini siralama
========================================

Quick Sort Zamani: 5644 Nanoseconds
Insertion Sort Zamani: 5663 Nanoseconds
Merge Sort Zamani: 8592 Nanoseconds
Heap Sort Zamani: 7514 Nanoseconds

========================================
'Ahmet' icin Arama
========================================

Ahmet Yilmaz 5551234567 Istanbul
Ahmet Yildiz 5551239876 Kayseri

Binary Search Zamani: 2094.18 Nanoseconds

----------------------------------------
Sequential Search icin arama sonuclari:
----------------------------------------

Ahmet Yilmaz 5551234567 Istanbul
Ahmet Yildiz 5551239876 Kayseri

Sequential Search Zamani: 5784.73 Nanoseconds

========================================
Arama Algoritmalari Arasinda Hizlanma Orani
========================================

(Sequential Search / Binary Search) SpeedUp = 2.76229

========================================
Siralama Algoritmalari Arasinda Hizlanma Orani
========================================

(Insertion Sort / Quick Sort) SpeedUp = 1.12271
(Merge Sort / Quick Sort) SpeedUp = 1.70325
(Heap Sort / Quick Sort) SpeedUp = 1.48968
```

## SpeedUp Değerlerinin Anlamı

SpeedUp değeri, bir algoritmanın diğerine göre ne kadar hızlı olduğunu gösterir:

- **SpeedUp > 1**: İlk algoritma daha yavaş (ikinci algoritma daha hızlı)
- **SpeedUp = 1**: Her iki algoritma aynı hızda
- **SpeedUp < 1**: İlk algoritma daha hızlı

**Örnek:**
```
(Sequential Search / Binary Search) SpeedUp = 2.76
```
Bu sonuç, Binary Search'ün Sequential Search'ten **2.76 kat daha hızlı** olduğunu gösterir.

## Proje Yapısı

```
PhoneBook-Project/
├── main.cpp           # Ana program kodu
├── PhoneBook.txt      # Örnek telefon rehberi verisi
├── README.md          # Bu dosya (kullanım kılavuzu)
└── RAPOR.md          # Detaylı algoritma analizi ve performans raporu
```

## Hata Giderme

### Dosya Bulunamadı Hatası
```
HATA: PhoneBook.txt dosyasi acilamadi!
```
**Çözüm:** Dosyanın programla aynı klasörde olduğundan emin olun.

### Derleme Hatası
```
error: 'chrono' is not a member of 'std'
```
**Çözüm:** C++11 standardını kullanarak derleyin:
```bash
g++ -std=c++11 main.cpp -o phoneBook
```

### Boş Sonuç
```
MARIO veri setinde mevcut degildir.
```
**Çözüm:** Aradığınız ismin dosyada bulunduğundan emin olun. Büyük/küçük harf duyarlılığı yoktur.

## Performans Notları

- **Küçük veri setleri** (< 1000 kayıt): Tüm algoritmalar benzer performans gösterir
- **Orta veri setleri** (1000-10000 kayıt): Quick Sort ve Merge Sort öne çıkar
- **Büyük veri setleri** (> 10000 kayıt): Quick Sort genellikle en hızlıdır
- **Arama**: Binary Search her zaman Sequential Search'ten hızlıdır (sıralı veri setinde)

## Katkıda Bulunma

Bu proje eğitim amaçlı geliştirilmiştir. Algoritmaları geliştirmek veya yeni özellikler eklemek için pull request gönderebilirsiniz.

## Lisans

Bu proje eğitim amaçlı geliştirilmiştir ve serbestçe kullanılabilir.

## İletişim

Sorularınız veya önerileriniz için issue açabilirsiniz.
