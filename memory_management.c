/*
 * Program: Sistem Manajemen Data Mahasiswa dengan Dynamic Memory
 * Topik: Manajemen Memori (malloc, free, realloc, pointer)
 * Deskripsi: Program untuk mengelola data mahasiswa menggunakan 
 *            dynamic memory allocation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur data mahasiswa
typedef struct {
    char nim[15];
    char nama[50];
    float ipk;
} Mahasiswa;

// Fungsi untuk menampilkan menu
void tampilkanMenu() {
    printf("\n========================================\n");
    printf("   SISTEM MANAJEMEN DATA MAHASISWA\n");
    printf("========================================\n");
    printf("[1] Tambah Mahasiswa\n");
    printf("[2] Tampilkan Semua Mahasiswa\n");
    printf("[3] Cari Mahasiswa berdasarkan NIM\n");
    printf("[4] Hapus Semua Data\n");
    printf("[0] Keluar\n");
    printf("========================================\n");
    printf("Pilihan: ");
}

// Fungsi untuk menambah mahasiswa
Mahasiswa* tambahMahasiswa(Mahasiswa *data, int *jumlah) {
    // Alokasi memori baru atau realokasi
    Mahasiswa *temp = (Mahasiswa*) realloc(data, (*jumlah + 1) * sizeof(Mahasiswa));
    
    if (temp == NULL) {
        printf("Error: Gagal mengalokasikan memori!\n");
        return data;
    }
    
    data = temp;
    
    printf("\n--- Tambah Mahasiswa Baru ---\n");
    printf("NIM: ");
    scanf("%s", data[*jumlah].nim);
    getchar(); // Membersihkan buffer
    
    printf("Nama: ");
    fgets(data[*jumlah].nama, 50, stdin);
    data[*jumlah].nama[strcspn(data[*jumlah].nama, "\n")] = 0; // Hapus newline
    
    printf("IPK: ");
    scanf("%f", &data[*jumlah].ipk);
    
    (*jumlah)++;
    
    printf("\n✓ Data mahasiswa berhasil ditambahkan!\n");
    printf("Total memori yang dialokasikan: %lu bytes\n", 
           (*jumlah) * sizeof(Mahasiswa));
    
    return data;
}

// Fungsi untuk menampilkan semua mahasiswa
void tampilkanMahasiswa(Mahasiswa *data, int jumlah) {
    if (jumlah == 0) {
        printf("\n✗ Belum ada data mahasiswa.\n");
        return;
    }
    
    printf("\n========================================\n");
    printf("        DAFTAR MAHASISWA\n");
    printf("========================================\n");
    printf("%-15s %-30s %-6s\n", "NIM", "Nama", "IPK");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < jumlah; i++) {
        printf("%-15s %-30s %.2f\n", 
               data[i].nim, 
               data[i].nama, 
               data[i].ipk);
    }
    
    printf("========================================\n");
    printf("Total mahasiswa: %d\n", jumlah);
    printf("Total memori terpakai: %lu bytes\n", jumlah * sizeof(Mahasiswa));
}

// Fungsi untuk mencari mahasiswa berdasarkan NIM
void cariMahasiswa(Mahasiswa *data, int jumlah) {
    if (jumlah == 0) {
        printf("\n✗ Belum ada data mahasiswa.\n");
        return;
    }
    
    char nimCari[15];
    printf("\nMasukkan NIM yang dicari: ");
    scanf("%s", nimCari);
    
    int ditemukan = 0;
    for (int i = 0; i < jumlah; i++) {
        if (strcmp(data[i].nim, nimCari) == 0) {
            printf("\n--- Data Ditemukan ---\n");
            printf("NIM  : %s\n", data[i].nim);
            printf("Nama : %s\n", data[i].nama);
            printf("IPK  : %.2f\n", data[i].ipk);
            printf("Alamat memori: %p\n", (void*)&data[i]);
            ditemukan = 1;
            break;
        }
    }
    
    if (!ditemukan) {
        printf("\n✗ Mahasiswa dengan NIM %s tidak ditemukan.\n", nimCari);
    }
}

// Fungsi untuk menghapus semua data dan free memory
void hapusSemuaData(Mahasiswa **data, int *jumlah) {
    if (*data != NULL) {
        printf("\n⚠ Membebaskan memori sebesar %lu bytes...\n", 
               (*jumlah) * sizeof(Mahasiswa));
        free(*data);
        *data = NULL;
        *jumlah = 0;
        printf("✓ Semua data berhasil dihapus dan memori dibebaskan!\n");
    } else {
        printf("\n✗ Tidak ada data yang perlu dihapus.\n");
    }
}

int main() {
    Mahasiswa *dataMahasiswa = NULL;
    int jumlahMahasiswa = 0;
    int pilihan;
    
    printf("========================================\n");
    printf("  PROGRAM MANAJEMEN MEMORI DINAMIS\n");
    printf("  Demonstrasi malloc, realloc, free\n");
    printf("========================================\n");
    
    do {
        tampilkanMenu();
        scanf("%d", &pilihan);
        
        switch(pilihan) {
            case 1:
                dataMahasiswa = tambahMahasiswa(dataMahasiswa, &jumlahMahasiswa);
                break;
            case 2:
                tampilkanMahasiswa(dataMahasiswa, jumlahMahasiswa);
                break;
            case 3:
                cariMahasiswa(dataMahasiswa, jumlahMahasiswa);
                break;
            case 4:
                hapusSemuaData(&dataMahasiswa, &jumlahMahasiswa);
                break;
            case 0:
                printf("\nKeluar dari program...\n");
                break;
            default:
                printf("\n✗ Pilihan tidak valid!\n");
        }
    } while(pilihan != 0);
    
    // Membersihkan memori sebelum keluar
    if (dataMahasiswa != NULL) {
        printf("\nMembebaskan memori sebelum keluar...\n");
        free(dataMahasiswa);
    }
    
    printf("Program selesai.\n");
    return 0;
}
