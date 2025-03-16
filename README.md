# Hasta Kuyruk Sistemi

Bu proje, hastaların aciliyet durumuna göre sıraya alınmasını ve sırası gelen hastaya doktorun reçete yazmasını sağlayan basit bir C programıdır.

## Özellikler
- Hasta ekleme
- Aciliyet durumuna göre hasta sıralama (1: Kırmızı, 2: Sarı, 3: Yeşil)
- Doktorun sıradaki hastaya reçete yazması
- Hastaları sıralı listeleme
- Hastaları kuyruktan alma

### Menü Seçenekleri
Program çalıştırıldığında aşağıdaki menü görüntülenir:
1. **Hasta Ekle**: Kullanıcıdan TC kimlik numarası ve aciliyet durumu istenir ve hasta kuyruğa eklenir.
2. **Doktor Reçete Yaz**: Sıradaki hasta alınır ve doktor tarafından reçete yazılır.
3. **Hastaları Sırala**: Mevcut hastalar aciliyet sırasına göre sıralanır ve ekrana yazdırılır.
4. **Sıradaki Hasta**: Kuyruktaki ilk hasta görüntülenir ve sıradan çıkarılır.
5. **Çıkış**: Programdan çıkılır.

## Yapı
Program şu temel veri yapılarını kullanır:
- **Struct Hasta**: Hasta bilgilerini (TC, aciliyet, kayıt numarası) saklar.
- **Struct Node**: Hastaları bağlı liste olarak saklayan düğümdür.
- **Struct Kuyruk**: Hastaların eklenip çıkarıldığı kuyruk veri yapısıdır.
