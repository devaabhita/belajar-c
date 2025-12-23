#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

//f(titik tengah)
double fungsi1(double x) {
   return exp(5.0 * x);
}

double fungsi2(double x) {
   return sqrt(x * x + 1.0);
}

double fungsi3(double x) {
   return pow(5.0, x);
}

double fungsi4(double x) {
   if (x <= 0) return 0.0;
   return log(x) / x;
}

double f(int pilihan, double x) {
   switch (pilihan) {
      case 1: return fungsi1(x);
      case 2: return fungsi2(x);
      case 3: return fungsi3(x);
      case 4: return fungsi4(x);
      default: return 0.0;
   }
}

double integralSejati1(double a, double b) {
   return (exp(5.0 * b) / 5.0) - (exp(5.0 * a) / 5.0);
}

double integralSejati2(double a, double b) {
   auto F = [](double x) { 
      double akar = sqrt(x * x + 1.0);
      return (x / 2.0) * akar + (1.0 / 2.0) * log(abs(x + akar)); 
   };
   return F(b) - F(a);
}

double integralSejati3(double a, double b) {
   double ln5 = log(5.0);
   return (pow(5.0, b) / ln5) - (pow(5.0, a) / ln5);
}

double integralSejati4(double a, double b) {
   if (a <= 0 || b <= 0) return 0.0; 
   auto F = [](double x) { return 0.5 * pow(log(x), 2.0); };
   return F(b) - F(a);
}

double hitungIntegralSejati(int pilihan, double a, double b) {
   switch (pilihan) {
      case 1: return integralSejati1(a, b);
      case 2: return integralSejati2(a, b);
      case 3: return integralSejati3(a, b);
      case 4: return integralSejati4(a, b);
      default: return 0.0;
   }
}
//fungsi disesuaikan
void metodeTitikTengah(int pilihanFungsi, double a, double b, double h) {
   string namaFungsi;
   switch (pilihanFungsi) {
      case 1: namaFungsi = "f(x) = e^(5x)"; break;
      case 2: namaFungsi = "f(x) = sqrt(x^2 + 1)"; break; 
      case 3: namaFungsi = "f(x) = 5^x"; break;
      case 4: namaFungsi = "f(x) = ln(x) / x"; break;
      default: namaFungsi = "Tidak Diketahui";
   }

   if (a >= b) {
      cout << "\n[!] Error: Batas bawah harus lebih kecil dari batas atas. Silakan coba lagi." << endl;
      return;
   }

   double n_double = (b - a) / h;
   int n = static_cast<int>(round(n_double));

   if (abs(n_double - n) > 1e-9 || n <= 0 || n > 100000) {
      cout << "\n[!] Peringatan: Nilai h (" << fixed << setprecision(4) << h << ") menghasilkan jumlah pias (N) yang tidak valid atau terlalu besar/kecil." << endl;
      cout << "[!] Nilai iterasi/poligon (N) diinisialisasi menjadi 0. Perkiraan Integral (Estimate) akan menjadi 0.0000." << endl;
      n = 0;
   }

   if (n > 0) {
      cout << "\n--- Hasil Perhitungan Metode Pias Titik Tengah ---" << endl;
      cout << "Fungsi: " << namaFungsi << endl;
      cout << "Batas Bawah (a) = " << fixed << setprecision(4) << a << endl;
      cout << "Batas Atas (b) = " << fixed << setprecision(4) << b << endl;
      cout << "Panjang Pias (h) = " << fixed << setprecision(4) << h << endl;
      cout << "Jumlah Pias (N) = " << n << endl;
      cout << string(65, '-') << endl;

      cout << left << setw(8) << "r"
            << setw(16) << "x_i"
            << setw(18) << "Titik Tengah"
            << setw(16) << "f(Titik Tgh)" << endl;
      cout << string(65, '-') << endl;

      double integralEstimate = 0.0;
      double sum_f_mid = 0.0;
      
      // Loop Iterasi
      for (int k = 0; k < n; ++k) {
         double x_k = a + k * h;
         double x_k_plus_1 = a + (k + 1) * h;
         double x_mid = (x_k + x_k_plus_1) / 2.0;
         double f_mid = f(pilihanFungsi, x_mid);
         double poligon = h * f_mid;

         integralEstimate += poligon;
         sum_f_mid += f_mid;

         cout << left << setw(8) << k 
               << fixed << setprecision(4) << setw(16) << x_k 
               << fixed << setprecision(4) << setw(18) << x_mid
               << fixed << setprecision(4) << setw(16) << f_mid << endl;
      }
      
      cout << left << setw(8) << n
            << fixed << setprecision(4) << setw(16) << b
            << string(34, ' ') << endl;

      cout << string(65, '-') << endl;

      cout << left << setw(42) << "Jumlah f(Titik Tgh):"
            << fixed << setprecision(4) << setw(16) << sum_f_mid << endl;
      cout << string(65, '=') << endl;

      double integralSejati = hitungIntegralSejati(pilihanFungsi, a, b);
      double galat = abs(integralSejati - integralEstimate);
      double integralCheck = h * sum_f_mid;

      cout << "\n[ Integrasi ]" << endl;
      cout << left << setw(35) << "Integral Sejati:"
            << fixed << setprecision(4) << integralSejati << endl;
      cout << left << setw(35) << "Integral Metode Titik Tengah:"
            << fixed << setprecision(4) << integralEstimate << endl;
      cout << left << setw(35) << "Galat Absolut (Error):"
            << fixed << setprecision(4) << galat << endl;
      cout << string(50, '=') << endl;

   } else {
      double integralEstimate = 0.0;
      double integralSejati = hitungIntegralSejati(pilihanFungsi, a, b);
      double galat = abs(integralSejati - integralEstimate);

      cout << "\n[ Integrasi ]" << endl;
      cout << left << setw(35) << "Integral Sejati:"
            << fixed << setprecision(4) << integralSejati << endl;
      cout << left << setw(35) << "Integral Metode Titik Tengah:"
            << fixed << setprecision(4) << integralEstimate << " (Estimate 0)" << endl;
      cout << left << setw(35) << "Galat Absolut (Error):"
            << fixed << setprecision(4) << galat << endl;
      cout << string(50, '=') << endl;
   }
}

//fungsi utama
int main() {
   cout << "Program Numerik: Integral Tentu Metode Pias Titik Tengah (Midpoint)" << endl;

   char lanjutkan;
   
   do {
      int pilihanFungsi;
      double a, b, h;
      bool validasiInput = false;
      
      while (!validasiInput) {
         cout << "\nPilih Fungsi yang Akan Diintegralkan:" << endl;
         cout << "1. f(x) = e^(5x)" << endl;
         cout << "2. f(x) = sqrt(x^2 + 1)" << endl; 
         cout << "3. f(x) = 5^x" << endl;
         cout << "4. f(x) = ln(x) / x" << endl;
         cout << "Masukkan Pilihan (1/2/3/4): ";
         cin >> pilihanFungsi;

         if (pilihanFungsi >= 1 && pilihanFungsi <= 4) {
               validasiInput = true;
         } else {
               cout << "[!] Pilihan tidak valid. Silakan masukkan 1, 2, 3, atau 4." << endl;
         }
      }

      cout << "\nMasukkan Batas Bawah Integral (a): ";
      cin >> a;
      cout << "Masukkan Batas Atas Integral (b): ";
      cin >> b;
      cout << "Masukkan Panjang Pias (h): ";
      cin >> h;

      metodeTitikTengah(pilihanFungsi, a, b, h);

      cout << "\nApakah Anda ingin melanjutkan perhitungan integral lain? (y/t): ";
      cin >> lanjutkan;

   } while (lanjutkan == 'y' || lanjutkan == 'Y');

   cout << "\nTerima kasih telah menggunakan program ini. Sampai jumpa!" << endl;

   return 0;
}