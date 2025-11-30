C Karakter Tabanlı Hayatta Kalma Simülatörü

Bu proje, C dilinde geliştirilmiş karakter tabanlı bir hayatta kalma simülasyonudur. Oyuncu; sağlık, enerji, yemek ve sığınak gibi kaynakları yöneterek zorlu doğa koşullarında hayatta kalmaya çalışır. Kod, C programlama becerilerini geliştirmek amacıyla hazırlanmış olup; koşullar, döngüler, rastgelelik, switch-case, fonksiyonlar gibi temel yapıların hepsini içeren öğretici bir yapıya sahiptir.



Bu projenin amacı:

 C dilindeki temel ve orta seviye yapıları kullanarak tamamen çalışabilir bir oyun mantığı kurmak,
 
 Öğrencilerin ve geliştiricilerin C’de durum yönetimi, fonksiyonel oyun tasarımı ve girdi işleme gibi kavramları anlamasını sağlamak,

 Eğlenceli bir metin tabanlı oyun ile programlamaya olan ilgiyi artırmak.


Oyuncu şu değerlerle başlar:

Sağlık: 100

Enerji: 100

Yemek: 5

Sığınak: Yok

Her turda oyuncu bir komut girer ve dünya bu komuta göre değişir.


Komutlar:



A	Avlan → Yemek bulabilir veya yaralanabilirsin, enerji azalır.

S	Sığınak Ara → Enerji harcar, belirli ihtimallerle sığınak bulursun.

E	Envanter görüntüle → Yemek sayısını gösterir.

R	Dinlen → Enerji yenilenir, yemek varsa sağlık da artar.

F	Tehlike Serisi → 5 dalgalı tehlike döngüsünden geçersin.

P	Şifreli İlerleme → Doğru şifre girene kadar enerji kaybedersin.

X	→ Oyundan çıkış.



1. Temel Akış Yönetimi (DO-WHILE):
   
Uygulamanın ana akışı, main() fonksiyonu içerisindeki DO-WHILE döngüsü tarafından yönetilir. Bu yapı, kullanıcının komut girmesi ve durumun görüntülenmesi sürecinin en az bir kez çalışmasını garanti eder. Döngü, oyuncu çıkış komutu olan X'i girmediği sürece (while (command != 'X')) sürekli devam eder.

2. Komut Yönlendirmesi (SWITCH-CASE):
 
Karakterin her eylemi, handle_command() fonksiyonu içindeki SWITCH-CASE yapısı ile dağıtılır. Girilen komut karakteri, switch ifadesi tarafından alınır ve ilgili case bloğuna yönlendirilerek (örneğin 'A' Avlanma, 'R' Dinlenme) kodun karmaşıklığı azaltılır ve eylem mantıkları birbirinden ayrılır.

3. Tekrarlı Eylem (FOR Döngüsü)

Bölgedeki tehlike simülasyonu, simulate_threat() fonksiyonu içerisinde bir FOR döngüsü kullanılarak uygulanmıştır. Bu döngü, rastgele belirlenen bir adım sayısı kadar tekrarlanır (for (i = 1; i <= danger_level; i++)). Bu tekrar mekanizması, tek bir F komutuna karşılık gelen bir seri olayın simüle edilmesini sağlar. Her adımda sığınak durumu kontrol edilerek hasar miktarı koşullu olarak belirlenir.

4. Doğrulama Akışı (DO-WHILE)

Şifreli engeli aşma mekaniği, try_to_escape() fonksiyonunda ikinci bir DO-WHILE döngüsü ile çalışır. Bu döngü, bir doğrulama akışı oluşturur; oyuncu doğru şifreyi girene VEYA deneme hakkı bitene kadar tekrarlanır. Döngü koşulu, mantıksal && operatörü kullanılarak kurulmuştur: while (entered_code != correct_code && attempts < max_attempts). Bu, her iki koşul da doğru olduğu sürece (yani hem şifre yanlış hem de hak var) döngünün devam etmesini sağlar.

5. Koşullu Kararlar (IF-ELSE)

Tüm eylem mantıkları, sonuçları ve karakter durumunu yönetmek için IF-ELSE yapılarına dayanır. Avlanma başarısı, sığınak bulma sonucu ve dinlenme sırasında iyileşme miktarı (sığınak olup olmamasına bağlı olarak) gibi kritik kararlar bu yapılarla koşullu olarak uygulanır. Özellikle, karakterin ölüm koşulu (if (health <= 0 || energy <= 0 || food_count < 0)) ana döngünün hemen başında kontrol edilerek simülasyonun kritik durumlarda sonlanması sağlanır.


6. Değişken Yönetimi
 
-Global Değişkenler: health, energy, food_count, shelter ve command global olarak tanımlanmıştır. Bu, tüm fonksiyonların karakter durumunu doğrudan okuyup değiştirebilmesini sağlar.

-Sabitler (#define): MAX_HEALTH, MIN_VALUE, SHELTER_EXISTS gibi sabitler, kod içindeki sayısal değerlerin amacını netleştirmek ve kolayca yönetilebilmek için kullanılmıştır.



7. Rastgelelik Mekanizması
   
-srand(time(NULL)): Programın her çalıştırılışında farklı sonuçlar üretilmesi için rastgele sayı üreteci, sistem saati ile başlatılır (seedleme).

-rand(): Olasılığa dayalı olaylarda (Avlanma Başarısı, Tehlike Seviyesi) dinamik sonuçlar üretmek için kullanılır.




