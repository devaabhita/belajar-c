/*
mengolah array
secara umum, program bisa menginput nilai array, array bisa diisi manual oleh user, atau diisi secara otomatis menggunakan random (pakai seed waktu)
dan bisa memberikan batas untuk nilai terkecil dan terbesarnya menggunakan modulo (batas bisa bilangan negatif, (cara memberikan batas negatif adalah mengurangi hasil dari modulo tersebut 
dengan selisih bilangan negatif sampai 0), berisi bilangan bulat.

program juga bisa memisahkan bilangan genap dan bilangan ganjil menjadi dua array yang berbeda.

juga bisa menggabungkan dua buah array, menggabungkan bisa dengan 2 cara :
1. a b c dan d e => a b c d e
2. a b c dan d e => a d b e c

program juga bisa membalik array
1. a b c => c b a


statistika:
mencari nilai terkecil dan terbesar, mendapatkan bilangan genap terkecil dan terbesar (juga ganjil), mendapatkan jumlah dari seluruhnya (SUM), mendapatkan rata-rata,
mencari variant dan standar deviasi

bisa mengubah semua bilangan menjadi bilangan genap (jika dia genap, biarkan. jika dia ganji, + 1)

mendapatkan jumlah kemunculan suatu bilangan, misal x muncul berapa kali diinput user.

menormalisasi data menggunakan minmax (cari rentang data => nilai maksimal-minimal || dibagi rentang nilai

menormalisasikan data menggunakan setscore (maksimal-rata", dibagi dengan standar deviasi)
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() {
   int arr[100], genap[100], ganjil[100];
   int hasil1[200], hasil2[200];
   int size, i, pilihan, min, max, searchNum;
   int j_genap = 0, j_ganjil = 0;
   int count = 0;
   
   printf("Ukuran array: ");
   scanf("%d", &size);
   
   if (size > 100) {
      printf("Ukuran terlalu besar.\n");
      return 1;
   }
   
   printf("1. Isi manual\n2. Isi otomatis\nPilihan: ");
   scanf("%d", &pilihan);
   
   if (pilihan == 1) {
      for (i = 0; i < size; i++) {
         printf("Elemen ke-%d: ", i + 1);
         scanf("%d", &arr[i]);
      }
   } else if (pilihan == 2) {
      printf("Batas bawah: "); scanf("%d", &min);
      printf("Batas atas : "); scanf("%d", &max);
      srand(time(NULL));
      for (i = 0; i < size; i++) {
         arr[i] = rand() % (max - min + 1) + min;
      }
   } else {
      printf("Pilihan tidak valid.\n");
      return 1;
   }

   // Tampilkan array awal
   printf("\nArray awal: ");
   for (i = 0; i < size; i++) printf("%d ", arr[i]);

   // Balik array
   for (i = 0; i < size / 2; i++) {
      int tmp = arr[i];
      arr[i] = arr[size - 1 - i];
      arr[size - 1 - i] = tmp;
   }

   printf("\nArray setelah dibalik: ");
   for (i = 0; i < size; i++) printf("%d ", arr[i]);

   // Pisah genap dan ganjil
   for (i = 0; i < size; i++) {
      if (arr[i] % 2 == 0)
         genap[j_genap++] = arr[i];
      else
         ganjil[j_ganjil++] = arr[i];
   }

   printf("\nGenap: ");
   for (i = 0; i < j_genap; i++) printf("%d ", genap[i]);
   printf("\nGanjil: ");
   for (i = 0; i < j_ganjil; i++) printf("%d ", ganjil[i]);

   // Gabung cara 1
   for (i = 0; i < j_genap; i++) hasil1[i] = genap[i];
   for (i = 0; i < j_ganjil; i++) hasil1[j_genap + i] = ganjil[i];
   
   printf("\nGabungan langsung: ");
   for (i = 0; i < j_genap + j_ganjil; i++) printf("%d ", hasil1[i]);

   // Gabung cara 2 (berselang-seling)
   int idx = 0, x = 0, y = 0;
   while (x < j_genap || y < j_ganjil) {
      if (x < j_genap) hasil2[idx++] = genap[x++];
      if (y < j_ganjil) hasil2[idx++] = ganjil[y++];
   }

   printf("\nGabungan selang-seling: ");
   for (i = 0; i < idx; i++) printf("%d ", hasil2[i]);

   // Statistik: Nilai terkecil dan terbesar pada array utama
   int minValue = arr[0], maxValue = arr[0];
   long sum = 0;

   for (i = 0; i < size; i++) {
      if (arr[i] < minValue) minValue = arr[i];
      if (arr[i] > maxValue) maxValue = arr[i];
      sum += arr[i];
   }

   double mean = sum / (double)size;
   double variance = 0.0, stddev;

   for (i = 0; i < size; i++) {
      variance += pow(arr[i] - mean, 2);
   }

   variance /= size;
   stddev = sqrt(variance);

   printf("\n\nStatistik array utama:\n");
   printf("Nilai terkecil: %d\n", minValue);
   printf("Nilai terbesar: %d\n", maxValue);
   printf("Jumlah (SUM): %ld\n", sum);
   printf("Rata-rata (Mean): %.2f\n", mean);
   printf("Varians: %.2f\n", variance);
   printf("Standar deviasi: %.2f\n", stddev);

   int minGenap = genap[0], maxGenap = genap[0];
   for (i = 0; i < j_genap; i++) {
      if (genap[i] < minGenap) minGenap = genap[i];
      if (genap[i] > maxGenap) maxGenap = genap[i];
   }

   printf("\nStatistik array Genap:\n");
   printf("Nilai terkecil: %d\n", minGenap);
   printf("Nilai terbesar: %d\n", maxGenap);

   int minGanjil = ganjil[0], maxGanjil = ganjil[0];
   for (i = 0; i < j_ganjil; i++) {
      if (ganjil[i] < minGanjil) minGanjil = ganjil[i];
      if (ganjil[i] > maxGanjil) maxGanjil = ganjil[i];
   }

   printf("\nStatistik array Ganjil:\n");
   printf("Nilai terkecil: %d\n", minGanjil);
   printf("Nilai terbesar: %d\n", maxGanjil);

   for (i = 0; i < size; i++) {
      if (arr[i] % 2 != 0) {
         arr[i] += 1;
      }
   }

   printf("\nArray setelah diubah menjadi genap: ");
   for (i = 0; i < size; i++) {
      printf("%d ", arr[i]);
   }

   printf("\n\nMasukkan bilangan yang ingin dicari jumlah kemunculannya: ");
   scanf("%d", &searchNum);

   for (i = 0; i < size; i++) {
      if (arr[i] == searchNum) {
         count++;
      }
   }

   printf("Bilangan %d muncul sebanyak %d kali dalam array.\n", searchNum, count);

   int minArr = arr[0], maxArr = arr[0];
   for (i = 0; i < size; i++) {
      if (arr[i] < minArr) minArr = arr[i];
      if (arr[i] > maxArr) maxArr = arr[i];
   }

   printf("\nNormalisasi Min-Max:\n");
   for (i = 0; i < size; i++) {
      double normalized = (double)(arr[i] - minArr) / (maxArr - minArr);
      printf("Nilai %d : %.2f\n", arr[i], normalized);
   }

   printf("\nNormalisasi Z-score:\n");
   double zScore;
   for (i = 0; i < size; i++) {
      zScore = (arr[i] - mean) / stddev;
      printf("Nilai %d : %.2f\n", arr[i], zScore);
   }

   return 0;
}