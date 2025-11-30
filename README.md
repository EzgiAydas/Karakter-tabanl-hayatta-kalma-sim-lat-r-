C Karakter Tabanlı Hayatta Kalma Simülatörü

Bu proje, C dilinde geliştirilmiş karakter tabanlı bir hayatta kalma simülasyonudur. Oyuncu; sağlık, enerji, yemek ve sığınak gibi kaynakları yöneterek zorlu doğa koşullarında hayatta kalmaya çalışır. Kod, C programlama becerilerini geliştirmek amacıyla hazırlanmış olup; koşullar, döngüler, rastgelelik, switch-case, fonksiyonlar gibi temel yapıların hepsini içeren öğretici bir yapıya sahiptir.

🎯 Amaç

Bu projenin amacı:

C dilindeki temel ve orta seviye yapıları kullanarak tamamen çalışabilir bir oyun mantığı kurmak,

Öğrencilerin ve geliştiricilerin C’de durum yönetimi, fonksiyonel oyun tasarımı ve girdi işleme gibi kavramları anlamasını sağlamak,

Eğlenceli bir metin tabanlı oyun ile programlamaya olan ilgiyi artırmak.

🧠 Oyun Mantığı

Oyuncu şu değerlerle başlar:

Sağlık: 100

Enerji: 100

Yemek: 5

Sığınak: Yok

Her turda oyuncu bir komut girer ve dünya bu komuta göre değişir.

🕹 Komutlar
Komut	Açıklama
A	Avlan → Yemek bulabilir veya yaralanabilirsin, enerji azalır.
S	Sığınak Ara → Enerji harcar, belirli ihtimallerle sığınak bulursun.
E	Envanter görüntüle → Yemek sayısını gösterir.
R	Dinlen → Enerji yenilenir, yemek varsa sağlık da artar.
F	Tehlike Serisi → 5 dalgalı tehlike döngüsünden geçersin.
P	Şifreli İlerleme → Doğru şifre girene kadar enerji kaybedersin.
X	Oyundan çıkış.
🛠 Kullanılan C Özellikleri

Bu proje C dilinde öğrenilebilecek pek çok yapıyı bilerek ve özellikle içerecek şekilde tasarlanmıştır:

✔ Fonksiyon Kullanımı

Mantıksal görevler modüler fonksiyonlara bölünmüştür:
avlan(), siginakAra(), dinlen(), tehlikeSerisi(), sifreliIlerleme(), durumuGoruntule()…

✔ Rastgelelik

rand() ve srand(time(0)) ile rastgele olaylar üretilir.

✔ Koşullu Yapılar

if-else, mantıksal operatörler, sağlık ve enerji kontrolleri.

✔ Döngüler

FOR → Tehlike dalgası simülasyonu

DO-WHILE → Şifreli geçiş + ana oyun döngüsü

WHILE → Oyun devam mekanizması

✔ Switch-Case Komut Sistemi

Kullanıcı girdisi ile oyun akışı tamamen switch-case üzerinden yönetilir.


✔ Karakter Girdisi

scanf(" %c") ile boşluk karakteri temizlenerek doğru giriş kontrolü yapılır.



Özet

Proje, karakter tabanlı bir hayatta kalma simülasyonu olarak kullanıcı etkileşimi sağlar ve C dilinde fonksiyon, döngü, koşul ve rastgelelik gibi temel programlama kavramlarını uygulamalı olarak öğretir. Oyun mantığı basit ama modülerdir, geliştirilmeye açıktır.


