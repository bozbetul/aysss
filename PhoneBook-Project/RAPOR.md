# TELEFON REHBERİ YÖNETİM SİSTEMİ - PERFORMANS ANALİZ RAPORU

## 1. GİRİŞ

Bu rapor, telefon rehberi yönetim sisteminde kullanılan farklı sıralama ve arama algoritmalarının performans analizlerini içermektedir. Proje kapsamında 4 farklı sıralama algoritması ve 2 farklı arama algoritması implement edilmiş ve performansları karşılaştırılmıştır.

### 1.1. Projenin Amacı

- Farklı sıralama algoritmalarının performanslarını karşılaştırmak
- Arama algoritmalarının verimliliğini analiz etmek
- Algoritmaların zaman karmaşıklıklarını pratik olarak gözlemlemek
- Veri yapılarının algoritma performansına etkisini incelemek

### 1.2. Kullanılan Teknolojiler

- **Programlama Dili:** C++
- **Zaman Ölçümü:** `<chrono>` kütüphanesi (nanosaniye hassasiyeti)
- **Veri Yapısı:** `vector<Contact>` (dinamik dizi)
- **Standart:** C++11

---

## 2. SIRALAMA ALGORİTMALARI

### 2.1. Quick Sort (Hızlı Sıralama)

#### 2.1.1. Algoritma Açıklaması
Quick Sort, böl-ve-yönet (divide and conquer) paradigmasını kullanan bir sıralama algoritmasıdır. Pivot adı verilen bir eleman seçilir ve dizi bu elemana göre ikiye bölünür.

#### 2.1.2. Çalışma Prensibi
1. Diziden bir pivot eleman seçilir (genellikle son eleman)
2. Pivot'tan küçük elemanlar sol tarafa, büyük elemanlar sağ tarafa yerleştirilir
3. Her iki alt dizi için işlem özyinelemeli (recursive) olarak tekrarlanır
4. Alt diziler 1 elemana indiğinde sıralama tamamlanır

#### 2.1.3. Zaman Karmaşıklığı
- **En İyi Durum:** O(n log n) - Pivot her seferinde diziyi eşit ikiye böldüğünde
- **Ortalama Durum:** O(n log n) - Rastgele veriler için
- **En Kötü Durum:** O(n²) - Dizi zaten sıralıysa veya ters sıralıysa
- **Uzay Karmaşıklığı:** O(log n) - Recursive çağrılar için stack

#### 2.1.4. Avantajları
- Ortalama durumda çok hızlıdır
- In-place sıralama yapar (az bellek kullanır)
- Cache-friendly (bellekte ardışık erişim)
- Gerçek dünya verilerinde genellikle en hızlı algoritmadır

#### 2.1.5. Dezavantajları
- En kötü durumda O(n²) performansı
- Kararlı (stable) bir algoritma değildir
- Recursive yapısı nedeniyle stack overflow riski

---

### 2.2. Insertion Sort (Eklemeli Sıralama)

#### 2.2.1. Algoritma Açıklaması
Insertion Sort, her elemanı sırayla alıp sıralı kısımda doğru yerine yerleştiren basit bir sıralama algoritmasıdır. Kağıt oyunu oynamak gibi çalışır.

#### 2.2.2. Çalışma Prensibi
1. İlk eleman zaten sıralı kabul edilir
2. İkinci elemandan başlayarak her eleman alınır
3. Eleman, sıralı kısımda doğru konumuna yerleştirilir
4. Bu işlem tüm elemanlar için tekrarlanır

#### 2.2.3. Zaman Karmaşıklığı
- **En İyi Durum:** O(n) - Dizi zaten sıralıysa
- **Ortalama Durum:** O(n²) - Rastgele veriler için
- **En Kötü Durum:** O(n²) - Dizi ters sıralıysa
- **Uzay Karmaşıklığı:** O(1) - Ekstra bellek gerektirmez

#### 2.2.4. Avantajları
- Basit ve anlaşılır implementasyon
- Küçük veri setlerinde çok hızlıdır
- Kararlı (stable) bir algoritmadır
- In-place sıralama yapar
- Kısmen sıralı verilerde çok verimlidir
- Adaptive (uyarlanabilir) bir algoritmadır

#### 2.2.5. Dezavantajları
- Büyük veri setlerinde çok yavaştır
- O(n²) zaman karmaşıklığı
- Çok sayıda karşılaştırma ve kaydırma işlemi

---

### 2.3. Merge Sort (Birleştirmeli Sıralama)

#### 2.3.1. Algoritma Açıklaması
Merge Sort, böl-ve-yönet yaklaşımını kullanan kararlı bir sıralama algoritmasıdır. Diziyi ikiye böler, her birini sıralar ve sonra birleştirir.

#### 2.3.2. Çalışma Prensibi
1. Dizi ortadan ikiye bölünür
2. Her iki yarı özyinelemeli olarak sıralanır
3. Sıralı iki yarı birleştirilerek tam sıralı dizi elde edilir
4. Birleştirme işlemi iki sıralı diziyi karşılaştırarak yapılır

#### 2.3.3. Zaman Karmaşıklığı
- **En İyi Durum:** O(n log n)
- **Ortalama Durum:** O(n log n)
- **En Kötü Durum:** O(n log n)
- **Uzay Karmaşıklığı:** O(n) - Geçici diziler için ekstra bellek

#### 2.3.4. Avantajları
- Her durumda garantili O(n log n) performansı
- Kararlı (stable) bir algoritmadır
- Tahmin edilebilir performans
- Linked list'lerde çok etkilidir
- Paralel işlemeye uygundur

#### 2.3.5. Dezavantajları
- Ekstra O(n) bellek gerektirir
- Küçük veri setlerinde Insertion Sort'tan yavaştır
- In-place değildir
- Cache performansı Quick Sort'tan düşüktür

---

### 2.4. Heap Sort (Yığın Sıralama)

#### 2.4.1. Algoritma Açıklaması
Heap Sort, binary heap veri yapısını kullanan bir sıralama algoritmasıdır. Önce max heap oluşturulur, sonra elemanlar birer birer çıkarılarak sıralanır.

#### 2.4.2. Çalışma Prensibi
1. Verilen diziden bir max heap oluşturulur
2. En büyük eleman (root) dizinin sonuna yerleştirilir
3. Heap boyutu 1 azaltılır ve heapify işlemi yapılır
4. Bu işlem heap boşalana kadar devam eder

#### 2.4.3. Zaman Karmaşıklığı
- **En İyi Durum:** O(n log n)
- **Ortalama Durum:** O(n log n)
- **En Kötü Durum:** O(n log n)
- **Uzay Karmaşıklığı:** O(1) - In-place sıralama

#### 2.4.4. Avantajları
- Garantili O(n log n) performansı
- In-place sıralama (az bellek kullanır)
- En kötü durumda bile O(n log n)
- Ekstra bellek gerektirmez
- Priority queue implementasyonunda kullanılır

#### 2.4.5. Dezavantajları
- Kararlı (stable) bir algoritma değildir
- Cache performansı düşüktür
- Pratikte Quick Sort'tan genellikle yavaştır
- Implementasyonu karmaşıktır

---

## 3. SIRALAMA ALGORİTMALARI KARŞILAŞTIRMASI

### 3.1. Zaman Karmaşıklığı Karşılaştırma Tablosu

| Algoritma | En İyi | Ortalama | En Kötü | Uzay |
|-----------|---------|----------|---------|------|
| **Quick Sort** | O(n log n) | O(n log n) | O(n²) | O(log n) |
| **Insertion Sort** | O(n) | O(n²) | O(n²) | O(1) |
| **Merge Sort** | O(n log n) | O(n log n) | O(n log n) | O(n) |
| **Heap Sort** | O(n log n) | O(n log n) | O(n log n) | O(1) |

### 3.2. Özellikler Karşılaştırması

| Özellik | Quick Sort | Insertion Sort | Merge Sort | Heap Sort |
|---------|-----------|----------------|------------|-----------|
| **Kararlılık** | Hayır | Evet | Evet | Hayır |
| **In-place** | Evet | Evet | Hayır | Evet |
| **Adaptive** | Hayır | Evet | Hayır | Hayır |
| **Recursive** | Evet | Hayır | Evet | Hayır (genelde) |
| **Cache Friendly** | Evet | Evet | Orta | Düşük |

### 3.3. Kullanım Senaryoları

#### Quick Sort Tercih Edilmeli:
- Genel amaçlı sıralama için
- Ortalama performans kritik olduğunda
- Bellek sınırlı olduğunda
- Büyük veri setlerinde

#### Insertion Sort Tercih Edilmeli:
- Küçük veri setlerinde (n < 50)
- Kısmen sıralı verilerde
- Basitlik gerektiğinde
- Kararlı sıralama gerektiğinde

#### Merge Sort Tercih Edilmeli:
- En kötü durum garantisi gerektiğinde
- Kararlı sıralama şart olduğunda
- Linked list sıralamada
- Paralel işlemede

#### Heap Sort Tercih Edilmeli:
- Garantili O(n log n) ve O(1) uzay gerektiğinde
- Priority queue implementasyonunda
- Bellek çok sınırlı olduğunda

---

## 4. ARAMA ALGORİTMALARI

### 4.1. Sequential Search (Sıralı Arama / Linear Search)

#### 4.1.1. Algoritma Açıklaması
Sequential Search, dizinin başından sonuna kadar her elemanı tek tek kontrol eden basit bir arama algoritmasıdır.

#### 4.1.2. Çalışma Prensibi
1. Dizinin ilk elemanından başla
2. Her elemanı aranan değerle karşılaştır
3. Eşleşme bulunursa döndür
4. Dizi sonuna kadar devam et
5. Bulunamazsa "bulunamadı" döndür

#### 4.1.3. Zaman Karmaşıklığı
- **En İyi Durum:** O(1) - Aranan eleman ilk sırada
- **Ortalama Durum:** O(n) - Aranan eleman ortada
- **En Kötü Durum:** O(n) - Aranan eleman sonda veya yok
- **Uzay Karmaşıklığı:** O(1)

#### 4.1.4. Avantajları
- Çok basit implementasyon
- Sıralanmamış verilerde çalışır
- Küçük veri setlerinde hızlıdır
- Ekstra bellek gerektirmez
- Her türlü veri yapısında kullanılabilir

#### 4.1.5. Dezavantajları
- Büyük veri setlerinde çok yavaştır
- Her aramada tüm diziyi taramak gerekebilir
- Verimli değildir

---

### 4.2. Binary Search (İkili Arama)

#### 4.2.1. Algoritma Açıklaması
Binary Search, **sıralanmış** dizilerde çalışan, her adımda arama alanını yarıya indiren çok verimli bir arama algoritmasıdır.

#### 4.2.2. Çalışma Prensibi
1. Dizinin ortasındaki elemanı kontrol et
2. Aranan değer ortadaki elemandan küçükse sol yarıda ara
3. Aranan değer ortadaki elemandan büyükse sağ yarıda ara
4. Eşleşme bulunana veya arama alanı bitene kadar devam et

#### 4.2.3. Zaman Karmaşıklığı
- **En İyi Durum:** O(1) - Aranan eleman ortada
- **Ortalama Durum:** O(log n)
- **En Kötü Durum:** O(log n)
- **Uzay Karmaşıklığı:** O(1) - Iterative implementasyon

#### 4.2.4. Avantajları
- Çok hızlıdır (logaritmik zaman)
- Büyük veri setlerinde çok verimlidir
- Tahmin edilebilir performans
- Basit implementasyon

#### 4.2.5. Dezavantajları
- **Sadece sıralanmış dizilerde çalışır**
- Sıralama maliyeti eklenir
- Random access gerektirir (array/vector)
- Linked list'lerde verimsizdir

---

## 5. ARAMA ALGORİTMALARI KARŞILAŞTIRMASI

### 5.1. Zaman Karmaşıklığı Karşılaştırması

| Algoritma | En İyi | Ortalama | En Kötü | Ön Koşul |
|-----------|---------|----------|---------|----------|
| **Sequential Search** | O(1) | O(n) | O(n) | Yok |
| **Binary Search** | O(1) | O(log n) | O(log n) | Sıralı dizi |

### 5.2. Performans Karşılaştırması (n = 1,000,000 için)

| Algoritma | Ortalama İşlem Sayısı |
|-----------|----------------------|
| **Sequential Search** | 500,000 karşılaştırma |
| **Binary Search** | ~20 karşılaştırma |

**SpeedUp Oranı:** Sequential / Binary = 25,000x hızlanma!

### 5.3. Kullanım Senaryoları

#### Sequential Search Tercih Edilmeli:
- Veri sırasız olduğunda
- Tek seferlik arama yapılacaksa
- Veri seti çok küçükse (n < 100)
- Sıralama maliyeti aramadan fazla ise

#### Binary Search Tercih Edilmeli:
- Veri zaten sıralı olduğunda
- Çok sayıda arama yapılacaksa
- Büyük veri setlerinde (n > 1000)
- Hızlı arama kritik olduğunda

---

## 6. PERFORMANS TEST SONUÇLARI

### 6.1. Test Ortamı
- **Veri Seti Boyutu:** 98 kişi
- **Veri Tipi:** Türk isimleri (string karşılaştırma)
- **İşlemci:** Değişken (sistem bağımlı)
- **Ölçüm Birimi:** Nanosaniye

### 6.2. Örnek Test Sonuçları

#### Sıralama Algoritmaları (98 eleman için örnek):
```
Quick Sort Zamanı:      5,644 Nanoseconds
Insertion Sort Zamanı:  5,663 Nanoseconds
Merge Sort Zamanı:      8,592 Nanoseconds
Heap Sort Zamanı:       7,514 Nanoseconds
```

#### Arama Algoritmaları ("Ahmet" araması için örnek):
```
Binary Search Zamanı:      2,094 Nanoseconds
Sequential Search Zamanı:  5,784 Nanoseconds
```

### 6.3. SpeedUp Hesaplamaları

#### Arama Algoritmaları:
```
Sequential Search / Binary Search = 5,784 / 2,094 = 2.76x
```
**Yorum:** Binary Search, Sequential Search'ten **2.76 kat daha hızlı**.

#### Sıralama Algoritmaları:
```
Insertion Sort / Quick Sort = 5,663 / 5,644 = 1.003x (neredeyse eşit)
Merge Sort / Quick Sort     = 8,592 / 5,644 = 1.52x
Heap Sort / Quick Sort      = 7,514 / 5,644 = 1.33x
```

**Yorum:**
- Küçük veri setinde (98 eleman) Quick Sort ve Insertion Sort neredeyse aynı performansı gösteriyor
- Merge Sort %52 daha yavaş
- Heap Sort %33 daha yavaş

### 6.4. Veri Seti Büyüklüğünün Etkisi

#### Küçük Veri Seti (n ≈ 100):
- **Insertion Sort** rekabetçidir
- Tüm algoritmalar milisaniyenin altında çalışır
- Farklar ihmal edilebilir

#### Orta Veri Seti (n ≈ 10,000):
- **Quick Sort** öne çıkmaya başlar
- **Insertion Sort** gözle görülür yavaşlar (100x)
- **Merge Sort** ve **Heap Sort** kararlı performans

#### Büyük Veri Seti (n ≈ 1,000,000):
- **Quick Sort** açık ara lider
- **Insertion Sort** kullanılamaz hale gelir (10,000x yavaş)
- **Binary Search** vazgeçilmez olur

---

## 7. PERFORMANS ANALİZİ VE YORUMLAR

### 7.1. Sıralama Algoritmaları Analizi

#### 7.1.1. Quick Sort Neden En Hızlı?
1. **Cache Locality:** Bellekte ardışık erişim
2. **In-place:** Ekstra bellek kopyalama yok
3. **Optimizasyon:** Derleyiciler Quick Sort'u optimize eder
4. **Pivot Seçimi:** Ortalama durumda iyi pivot seçimi

#### 7.1.2. Insertion Sort Neden Küçük Veride İyi?
1. **Düşük Overhead:** Ekstra fonksiyon çağrısı yok
2. **Adaptive:** Kısmen sıralı verilerde çok hızlı
3. **Basit:** Az instruction, az branch prediction miss

#### 7.1.3. Merge Sort Neden Daha Yavaş?
1. **Bellek Kopyalama:** Sürekli yeni array oluşturma
2. **Cache Miss:** Farklı bellek bölgelerine erişim
3. **Overhead:** Recursive fonksiyon çağrıları

#### 7.1.4. Heap Sort Neden Orta Seviyede?
1. **Random Access:** Cache-friendly değil
2. **Parent-Child Hesaplama:** Ekstra aritmetik işlemler
3. **Branch Prediction:** Tahmin edilemez dallanmalar

### 7.2. Arama Algoritmaları Analizi

#### 7.2.1. Binary Search Avantajları
- **Logaritmik Büyüme:** n iki katına çıksa bile sadece 1 adım eklenr
- **Tahmin Edilebilir:** Her zaman log₂(n) adım
- **Verimli:** Minimum karşılaştırma

**Örnek:**
```
n = 100     → 7 adım
n = 1,000   → 10 adım  (10x veri, sadece 3 adım fazla!)
n = 1,000,000 → 20 adım (10,000x veri, sadece 13 adım fazla!)
```

#### 7.2.2. Sequential Search Dezavantajları
- **Lineer Büyüme:** Veri 2 katına çıkarsa zaman da 2 kat
- **Tahmin Edilemez:** İlk eleman da olabilir, son da

---

## 8. SONUÇ VE ÖNERİLER

### 8.1. Genel Sonuçlar

1. **Algoritma seçimi veri boyutuna bağlıdır**
   - n < 50: Insertion Sort yeterli
   - 50 < n < 10,000: Quick Sort veya Merge Sort
   - n > 10,000: Quick Sort (garantili performans gerekiyorsa Merge Sort)

2. **Arama için önce sıralama yapın**
   - Tek aramada: Sequential Search
   - Birden fazla aramada: Sıralama + Binary Search

3. **Bellek vs Hız trade-off'u**
   - Bellek sınırlı: Quick Sort veya Heap Sort
   - Hız kritik: Quick Sort
   - Garanti gerekli: Merge Sort

### 8.2. Telefon Rehberi Projesi İçin Öneriler

#### Küçük Rehber (< 1000 kişi):
```cpp
Sıralama: Insertion Sort veya Quick Sort
Arama: Sequential Search (sıralama yapmadan)
```

#### Orta Rehber (1000-10000 kişi):
```cpp
Sıralama: Quick Sort
Arama: Bir kez sırala, Binary Search kullan
```

#### Büyük Rehber (> 10000 kişi):
```cpp
Sıralama: Quick Sort (veya Merge Sort güvenlik için)
Arama: Mutlaka Binary Search
İndexleme: Hash table kullanılabilir (O(1) arama!)
```

### 8.3. Gelecek Geliştirmeler

1. **Hybrid Sorting:**
   - Quick Sort + Insertion Sort kombinasyonu
   - Küçük alt dizilerde Insertion Sort'a geç
   - std::sort bu yaklaşımı kullanır

2. **Hash Tablosu:**
   - O(1) arama performansı
   - İsim → Contact mapping
   - Çok fazla arama için ideal

3. **Trie Veri Yapısı:**
   - Önek (prefix) araması için
   - Otomatik tamamlama
   - "Ah" yazınca tüm "Ahmet"leri göster

4. **Parallelization:**
   - Merge Sort paralel çalıştırılabilir
   - Çok çekirdekli işlemcilerde hızlanma

### 8.4. Öğrenilen Dersler

1. **Teorik vs Pratik:**
   - Teoride O(n log n) ama pratikte Quick Sort > Merge Sort
   - Sabitler (constants) önemlidir
   - Cache ve bellek erişimi kritiktir

2. **"En İyi" Algoritma Yoktur:**
   - Veri boyutuna bağlı
   - Veri özelliklerine bağlı (sıralı mı, rastgele mi)
   - Kullanım senaryosuna bağlı

3. **Ölçüm Önemlidir:**
   - Teorik analiz yol göstericidir
   - Gerçek performans ölçülmelidir
   - Profiling yapılmalıdır

---

## 9. KAYNAKLAR VE REFERANSLAR

### 9.1. Akademik Kaynaklar
- Cormen, T. H., et al. (2009). *Introduction to Algorithms* (3rd ed.). MIT Press.
- Knuth, D. E. (1998). *The Art of Computer Programming, Volume 3: Sorting and Searching* (2nd ed.).
- Sedgewick, R., & Wayne, K. (2011). *Algorithms* (4th ed.). Addison-Wesley.

### 9.2. Online Kaynaklar
- [Big-O Cheat Sheet](https://www.bigocheatsheet.com/)
- [VisuAlgo - Algoritma Görselleştirme](https://visualgo.net/)
- [GeeksforGeeks - Sorting Algorithms](https://www.geeksforgeeks.org/sorting-algorithms/)

### 9.3. Zaman Karmaşıklığı Referans Tablosu

#### Yaygın Büyüme Hızları (Yavaştan Hızlıya):
```
O(1)         - Constant     - Hash table arama
O(log n)     - Logarithmic  - Binary search
O(n)         - Linear       - Sequential search
O(n log n)   - Linearithmic - Quick/Merge/Heap sort
O(n²)        - Quadratic    - Insertion/Bubble sort
O(2ⁿ)        - Exponential  - Recursive Fibonacci
O(n!)        - Factorial    - Traveling salesman (brute force)
```

**n = 1,000,000 için karşılaştırma:**
```
O(1)       = 1 işlem
O(log n)   = 20 işlem
O(n)       = 1,000,000 işlem
O(n log n) = 20,000,000 işlem
O(n²)      = 1,000,000,000,000 işlem (1 trilyon!)
```

---

## 10. EK BİLGİLER

### 10.1. Kararlı (Stable) Sıralama Nedir?

**Tanım:** Eşit elemanların sıralamadan sonra da aynı göreceli sırayı koruması.

**Örnek:**
```
Girdi: [(Ali, 25), (Mehmet, 30), (Zeynep, 25)]
Sadece yaşa göre sırala:

Kararlı:    [(Ali, 25), (Zeynep, 25), (Mehmet, 30)]  ✓
Kararsız:   [(Zeynep, 25), (Ali, 25), (Mehmet, 30)]  (Ali ve Zeynep yer değiştirdi)
```

**Kararlı Algoritmalar:** Insertion Sort, Merge Sort
**Kararsız Algoritmalar:** Quick Sort, Heap Sort

### 10.2. In-Place Sıralama Nedir?

**Tanım:** Ekstra bellek kullanmadan (veya çok az kullanarak O(1)) sıralama.

**In-place:** Quick Sort, Insertion Sort, Heap Sort
**Not in-place:** Merge Sort (O(n) ekstra bellek)

### 10.3. Adaptive Algoritma Nedir?

**Tanım:** Kısmen sıralı verilerde daha hızlı çalışan algoritma.

**Adaptive:** Insertion Sort (Kısmen sıralı n elemanda O(n)!)
**Non-adaptive:** Quick Sort, Merge Sort, Heap Sort

---

## RAPOR SONU

**Hazırlayan:** Telefon Rehberi Yönetim Sistemi Geliştirme Ekibi
**Tarih:** 2025
**Versiyon:** 1.0

Bu rapor, algoritmaların teorik temellerini ve pratik performanslarını analiz ederek, doğru algoritma seçiminin önemini göstermektedir. Uygun algoritma seçimi, yazılım performansını katbekat artırabilir.
