#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *sabda_wara[] = {"redite", "soma", "anggara", "budha", "wrespati", "sukra", "saniscara"};
const char *panca_wara[] = {"umanis", "paing", "pon", "wage", "kliwon"};
const char *wuku[] = {"sinta", "landep", "ukir", "kulantir", "tolu", "gumbreg", "wariga", "warigadian", "julungwangi", "sungsang", 
   "dungulan", "kuningan", "langkir", "medangsia", "pujut", "pahang", "krulut", "merakih", "tambir", "medangkungan",
   "matal", "uye", "menail", "prangbakat", "bala", "ugu", "wayang", "kelawu", "dukut", "watugunung"};

#define TOTAL_SABDA_WARA 7
#define TOTAL_PANCA_WARA 5
#define TOTAL_WUKU 30

int tahun_kabisat(int tahun) {
   return ((tahun % 4 == 0 && tahun % 100 != 0) || tahun % 400 == 0);
}

int find_index(const char *arr[], int size, const char *key) {
   for (int i = 0; i < size; i++) {
      if (strcmp(arr[i], key) == 0) {
         return i;
      }
   }
   return -1; // Tidak ditemukan
}

int main() {
   int tahun_awal = 1900, tahun_input, selisih, jumlah_hari = 0;
   int hasil_rumus, selisih_hari;
   
   printf("Masukkan tahun yang ingin dihitung: ");
   scanf("%d", &tahun_input);
   
   selisih =(tahun_input - tahun_awal);
   
   int start = (tahun_input > tahun_awal) ? tahun_awal : tahun_input;
   int end = (tahun_input > tahun_awal) ? tahun_input : tahun_awal;
   
   for (int i = start; i < end; i++) {
      if (tahun_kabisat(i)) {
         jumlah_hari += 366;
      } else {
         jumlah_hari += 365;
      }
   }
   
   hasil_rumus = ((jumlah_hari / 210) + 1) * 210;
   
   selisih_hari = hasil_rumus - jumlah_hari;
   
   char input_sabda[20], input_panca[20], input_wuku[20];
   
   printf("Masukkan Sabda Wara: ");
   scanf("%s", input_sabda);
   printf("Masukkan Panca Wara: ");
   scanf("%s", input_panca);
   printf("Masukkan Wuku: ");
   scanf("%s", input_wuku);
   
   // Posisi patokan (1 Januari 1900)
   int patokan_sabda_idx = 1; // "soma"
   int patokan_panca_idx = 1; // "paing"
   int patokan_wuku_idx = 12; // "langkir"
   
   int target_sabda_idx = find_index(sabda_wara, TOTAL_SABDA_WARA, input_sabda);
   int target_panca_idx = find_index(panca_wara, TOTAL_PANCA_WARA, input_panca);
   int target_wuku_idx = find_index(wuku, TOTAL_WUKU, input_wuku);
   
   if (target_sabda_idx == -1 || target_panca_idx == -1 || target_wuku_idx == -1) {
      printf("Input tidak valid. Pastikan Sabda Wara, Panca Wara, dan Wuku sesuai dengan daftar!\n");
      return 1;
   }
   
   int jarak_sabda = (target_sabda_idx - patokan_sabda_idx + TOTAL_SABDA_WARA) % TOTAL_SABDA_WARA;
   int jarak_panca = (target_panca_idx - patokan_panca_idx + TOTAL_PANCA_WARA) % TOTAL_PANCA_WARA;
   int jarak_wuku = (target_wuku_idx - patokan_wuku_idx + TOTAL_WUKU) % TOTAL_WUKU * 7;
   
   int total_hari = jarak_wuku;
   while (total_hari % TOTAL_SABDA_WARA != jarak_sabda || total_hari % TOTAL_PANCA_WARA != jarak_panca) {
      total_hari++;
   }
   
   int hasil_akhir = selisih_hari + total_hari;
   
   int day = 1, month = 1, year = tahun_input;
   int days_in_month[] = {31, tahun_kabisat(year) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

   for (int i = 0; i < hasil_akhir; i++) {
      day++;
      if (day > days_in_month[month - 1]) {
         day = 1;
         month++;
         if (month > 12) {
            month = 1;
            year++;
            days_in_month[1] = tahun_kabisat(year) ? 29 : 28;
         }
      }
   }

   int day2 = day, month2 = month, year2 = year;
   int days_in_month2[] = {31, tahun_kabisat(year2) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

   for (int i = 0; i < 210; i++) {
      day2++;
      if (day2 > days_in_month2[month2 - 1]) {
         day2 = 1;
         month2++;
         if (month2 > 12) {
            month2 = 1;
            year2++;
            days_in_month2[1] = tahun_kabisat(year2) ? 29 : 28;
         }
      }
   }

   if (year2 == tahun_input) {
      printf("perkiraan kelahiran anda yaitu %d-%d-%d atau %d-%d-%d\n", day, month, year, day2, month2, year2);
   } else {
      printf("perkiraan kelahiran anda adalah %d-%d-%d\n", day, month, year);
   }
   return 0;
}