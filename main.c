#include <stdio.h>  // Standart giriş/çıkış fonksiyonları için
#include <stdlib.h> // Rand() ve srand() fonksiyonları için
#include <time.h>   // Rand() fonksiyonu için zamanı seed olarak kullanmak için

// Sabitler (Değişkenlerin kolay okunması için)
#define MAX_HEALTH 100
#define MAX_ENERGY 100
#define MIN_VALUE  0
#define SHELTER_EXISTS 1
#define SHELTER_NONE 0

// --- Durum Değişkenleri ---
int health = 100;    // Sağlık (0-100)
int energy = 100;    // Enerji (0-100)
int food_count = 5;  // Yemek sayısı
int shelter = SHELTER_NONE; // Sığınak bulunup bulunmadığı (1/0)
char command;        // Kullanıcının gireceği komut

// --- Fonksiyon Tanımları ---
void display_stats();       // Durum sistemini gösteren fonksiyon
void handle_command(char cmd); // Komutları işleyen ana SWITCH-CASE fonksiyonu
void simulate_threat();     // FOR döngüsü ile tehlike simülasyonu
void try_to_escape();       // DO-WHILE döngüsü ile şifre/engel aşma

int main() {
	// Rastgele sayı üreticisini başlat
	srand(time(NULL));

	// Oyun karşılama mesajı
	printf(">> KARAKTER TABANLI HAYATTA KALMA SIMULATORU <<\n");
	printf("Hayatta Kalma Simulasyonuna Hos Geldiniz.\n");

	// Ana oyun döngüsü (Program çalıştığında simülasyonun devam etmesi için DO-WHILE)
	// Oyuncu 'X' (Çıkış) komutunu vermedikçe devam eder.
	do {
		// Mevcut durumu göster
		display_stats();

		// Kritik durum kontrolü ve ölüm
		if (health <= 0 || energy <= 0 || food_count < 0) {
			printf("\n!!! SIMULASYON SONA ERDI !!!\n");
			printf("Karakteriniz yasamini yitirdi. Hayatta kalma sureniz sona erdi.\n");
			break; // Ana döngüden çık
		}

		// Oyuncudan komut al
		printf("\nKomut Girin (A, S, R, E, F, P, X): ");
		scanf(" %c", &command); // Boşluk (' ') format belirteci, önceki boşlukları temizler

		// Girilen komutu büyük harfe çevir (SWITCH-CASE kolaylığı için)
		if (command >= 'a' && command <= 'z') {
			command = command - 'a' + 'A';
		}

		// Komutu işle
		handle_command(command);

	} while (command != 'X'); // DO-WHILE Döngüsü Koşulu

	printf("\nSimulasyondan cikiliyor. Gorusmek uzere!\n");
	return 0;
}

// --- Fonksiyon Uygulamaları ---

// Durum Değişkenlerini Ekrana Bastıran Fonksiyon (4. Durum Yönetimi)
void display_stats() {
	printf("\n--- Mevcut Durum ---\n");
	printf("Saglik: %d/%d | Enerji: %d/%d | Yemek Sayisi: %d\n", health, MAX_HEALTH, energy, MAX_ENERGY, food_count);

	// Sığınak kontrolü ve yazdırma
	if (shelter == SHELTER_EXISTS) {
		printf("Siginak Durumu: Bulundu (Korunuyorsunuz)\n");
	} else {
		printf("Siginak Durumu: Yok (Tehlikelere acik)\n");
	}
	printf("--------------------\n");
}

// Komut İşleme Fonksiyonu (1. SWITCH-CASE Zorunluluğu)
void handle_command(char cmd) {
	int success_chance; // Başarı ihtimalini tutacak değişken

	// SWITCH-CASE ile komutları ayırma
	switch (cmd) {
		case 'A': // Avlan (Enerji azalt, Yemek kazanma ihtimali)
			printf(">> Avlanma baslatiliyor...\n");

			// Aritmetik İşlem: Enerji Kaybı
			energy -= 20;
			if (energy < MIN_VALUE) energy = MIN_VALUE;

			// Mantıksal İşlem: Başarı ihtimali (&& veya || kullanıldı)
			// Enerji 50'den büyük VEYA Yemek 5'ten az ise şans %70, aksi halde %40.
			if (energy > 50 || food_count < 5) {
				success_chance = 70;
			} else {
				success_chance = 40;
			}

			// IF-ELSE Yapısı: Başarı kontrolü
			if (rand() % 100 < success_chance) {
				// Aritmetik İşlem: Yemek Kazanma
				food_count += 2;
				printf("Basarili av! 2 adet yemek kazandiniz. (Enerji: -20)\n");
			} else {
				printf("Avlanma basarisiz oldu. Bos dondunuz. (Enerji: -20)\n");
			}
			break;

		case 'S': // Sığınak Ara (Başarı ihtimali mantıksal operatörlerle)
			printf(">> Siginak araniyor...\n");

			// Aritmetik İşlem: Enerji Kaybı
			energy -= 10;
			if (energy < MIN_VALUE) energy = MIN_VALUE;

			// Mantıksal İşlem: Sığınak bulma koşulu (&& operatörü)
			// Enerji 30'dan büyük VE Sığınak henüz bulunmamışsa şans %60.
			if (energy > 30 && shelter == SHELTER_NONE) {
				success_chance = 60;
			} else {
				success_chance = 10; // Koşullar sağlanmazsa çok düşük şans
			}

			// IF-ELSE Yapısı: Sığınak bulma
			if (rand() % 100 < success_chance) {
				shelter = SHELTER_EXISTS; // Sığınak bulundu
				printf("Harika! Kendinizi koruyabileceginiz bir siginak buldunuz!\n");
			} else {
				printf("Siginak bulma girisimi basarisiz oldu. (Enerji: -10)\n");
			}
			break;

		case 'R': // Dinlen (Enerji ve Sağlık kontrolü, aritmetik işlemler)
			printf(">> Dinlenmeye basladiniz...\n");

			// Aritmetik İşlemler: Sağlık ve Enerji Artışı
			if (shelter == SHELTER_EXISTS) {
				// Sığınakta dinlenme (Daha fazla iyileşme)
				health += 25;
				energy += 30;
				printf("Siginagin guvenliginde dinleniyorsunuz. (Saglik: +25, Enerji: +30)\n");
			} else {
				// Açık alanda dinlenme (Daha az iyileşme)
				health += 10;
				energy += 15;
				printf("Aciik alanda dinleniyorsunuz. (Saglik: +10, Enerji: +15)\n");
			}

			// Üst limit kontrolü (Sağlık ve Enerji)
			if (health > MAX_HEALTH) health = MAX_HEALTH;
			if (energy > MAX_ENERGY) energy = MAX_ENERGY;
			break;

		case 'E': // Envanteri Görüntüle
			// display_stats() fonksiyonu bu bilgileri zaten gösteriyor,
			// ek olarak özel bir mesaj eklenebilir.
			printf(">> Envanter ve durum bilgileri gosteriliyor.\n");
			break;

		case 'F': // Bölgedeki tehlike simülasyonu (FOR Döngüsü Zorunluluğu)
			simulate_threat();
			break;

		case 'P': // Şifreli engel aşma (DO-WHILE Doğrulama Döngüsü Zorunluluğu)
			try_to_escape();
			break;

		case 'X': // Çıkış
			printf(">> Programdan cikis secildi.\n");
			break;

		default: // Geçersiz komut
			printf(">> Gecersiz komut. Lutfen A, S, R, E, F, P veya X girin.\n");
			break;
	}
}

// FOR Döngüsü: Bölgedeki tehlike serisini simüle et
void simulate_threat() {
	int danger_level = rand() % 5 + 1; // 1 ile 5 arasında rastgele tehlike seviyesi
	int i;
	printf(">> Bolgede %d adimlik 'Tehlike Dalgasi' simule ediliyor...\n", danger_level);

	// FOR Döngüsü: Her döngü oyuncunun durumuna bağlı bir olay gerçekleştirir.
	for (i = 1; i <= danger_level; i++) {
		printf("--- Tehlike Dalgasi Adim %d ---\n", i);

		// IF-ELSE Yapısı: Tehlikeye karşı korunma kontrolü
		// Sığınak varsa daha az kayıp, sığınak yoksa daha fazla kayıp.
		if (shelter == SHELTER_EXISTS) {
			// Sığınak varsa sadece küçük bir enerji kaybı riski
			if (rand() % 3 == 0) { // %33 ihtimalle
				energy -= 5;
				printf("Siginak sizi korudu, ancak kisa bir enerji kaybi yasandi. (Enerji: -5)\n");
			} else {
				printf("Siginagin guvenliginde tehlikeyi atlattiniz.\n");
			}
		} else {
			// Sığınak yoksa sağlık ve enerji kaybı riski
			int loss = rand() % 10 + 5; // 5 ile 14 arası kayıp
			health -= loss;
			energy -= loss / 2;
			printf("Acik alandasiniz, hasar aldiniz ve yoruldunuz! (Saglik: -%d, Enerji: -%d)\n", loss, loss / 2);
		}

		// Değerlerin 0'ın altına düşmesini engelleme
		if (health < MIN_VALUE) health = MIN_VALUE;
		if (energy < MIN_VALUE) energy = MIN_VALUE;

		// Kritik durum kontrolü
		if (health <= 0) {
			printf("Karakterinizin sagligi kalmadi. Simülasyon sona erdi.\n");
			break; // Tehlike döngüsünü durdur
		}
	}
	printf(">> Tehlike dalgasi simülasyonu sona erdi.\n");
}

// DO-WHILE Döngüsü: Şifre veya engel aşma mekanizması
void try_to_escape() {
	int correct_code = 1234; // Aşılması gereken sabit engel şifresi
	int entered_code;       // Oyuncunun girdiği şifre
	int attempts = 0;       // Deneme sayısı
	int max_attempts = 3;   // Maksimum deneme hakkı

	printf(">> Bir sifreli engeli asmaya calisiyorsunuz (Sifre 4 haneli bir sayi).\n");

	// DO-WHILE Döngüsü: Doğru şifre girilene veya deneme hakkı bitene kadar devam eder.
	do {
		printf("Sifreyi girin (%d hakkiniz kaldi): ", max_attempts - attempts);
		scanf("%d", &entered_code);
		attempts++;

		// IF-ELSE Yapısı: Şifre kontrolü
		if (entered_code == correct_code) {
			printf("TEBRIKLER! Engeli basariyla astiniz.\n");
			// Aritmetik İşlem: Başarı ödülü
			food_count += 1;
			printf("Odul: 1 Yemek kazandiniz.\n");
			break; // Döngüden çık
		} else {
			// Aritmetik İşlem: Başarısızlık cezası
			energy -= 10;
			if (energy < MIN_VALUE) energy = MIN_VALUE;
			printf("Yanlis sifre. Enerji kaybettiniz. (Enerji: -10)\n");

			// Kritik durum kontrolü
			if (energy <= 0) {
				printf("Enerjiniz kalmadi. Engeli asma girisimi basarisiz oldu.\n");
				break;
			}
		}

	} while (entered_code != correct_code && attempts < max_attempts); // DO-WHILE Koşulu

	// Eğer döngü, doğru şifre girilmeden bittiyse
	if (entered_code != correct_code) {
		printf("Engeli asma hakkiniz bitti. Geri cekilmek zorunda kaldiniz.\n");
	}
}