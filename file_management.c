/*
 * Program: Sistem Manajemen File Buku Perpustakaan
 * Topik: Manajemen File (open, read, write, close, fopen, fwrite, fread)
 * Deskripsi: Program untuk mengelola data buku dalam file dengan operasi
 *            CRUD (Create, Read, Update, Delete)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define FILENAME "perpustakaan.txt"
#define MAX_LINE 256

// Struktur data buku
typedef struct {
    char kode[10];
    char judul[100];
    char pengarang[50];
    int stok;
    int harga;
} Buku;

// Fungsi untuk menampilkan menu
void tampilkanMenu() {
    printf("\n========================================\n");
    printf("   SISTEM MANAJEMEN FILE PERPUSTAKAAN\n");
    printf("========================================\n");
    printf("[1] Tambah Buku ke File\n");
    printf("[2] Tampilkan Semua Buku dari File\n");
    printf("[3] Cari Buku dari File\n");
    printf("[4] Update Stok Buku\n");
    printf("[5] Hapus File Database\n");
    printf("[6] Informasi File\n");
    printf("[0] Keluar\n");
    printf("========================================\n");
    printf("Pilihan: ");
}

// Fungsi untuk inisialisasi file jika belum ada
void initFile() {
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Error: Tidak dapat membuat file!\n");
        return;
    }
    fclose(file);
}

// Fungsi untuk menambah buku ke file
void tambahBuku() {
    Buku buku;
    FILE *file;
    
    printf("\n--- Tambah Buku Baru ---\n");
    printf("Kode Buku: ");
    scanf("%s", buku.kode);
    getchar();
    
    printf("Judul Buku: ");
    fgets(buku.judul, 100, stdin);
    buku.judul[strcspn(buku.judul, "\n")] = 0;
    
    printf("Pengarang: ");
    fgets(buku.pengarang, 50, stdin);
    buku.pengarang[strcspn(buku.pengarang, "\n")] = 0;
    
    printf("Stok: ");
    scanf("%d", &buku.stok);
    
    printf("Harga: ");
    scanf("%d", &buku.harga);
    
    // Menulis ke file menggunakan fopen dan fprintf
    file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("\n✗ Error: Tidak dapat membuka file!\n");
        return;
    }
    
    fprintf(file, "%s;%s;%s;%d;%d\n", 
            buku.kode, buku.judul, buku.pengarang, buku.stok, buku.harga);
    
    fclose(file);
    
    printf("\n✓ Buku berhasil ditambahkan ke file '%s'!\n", FILENAME);
}

// Fungsi untuk menampilkan semua buku dari file
void tampilkanSemuaBuku() {
    FILE *file;
    char buffer[MAX_LINE];
    int count = 0;
    
    file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("\n✗ File belum ada atau belum ada data.\n");
        return;
    }
    
    printf("\n========================================\n");
    printf("        DAFTAR BUKU PERPUSTAKAAN\n");
    printf("========================================\n");
    printf("%-10s %-30s %-20s %-6s %-10s\n", 
           "Kode", "Judul", "Pengarang", "Stok", "Harga");
    printf("----------------------------------------\n");
    
    while (fgets(buffer, MAX_LINE, file) != NULL) {
        char kode[10], judul[100], pengarang[50];
        int stok, harga;
        
        sscanf(buffer, "%[^;];%[^;];%[^;];%d;%d", 
               kode, judul, pengarang, &stok, &harga);
        
        printf("%-10s %-30s %-20s %-6d Rp%-10d\n", 
               kode, judul, pengarang, stok, harga);
        count++;
    }
    
    fclose(file);
    
    printf("========================================\n");
    printf("Total buku: %d\n", count);
}

// Fungsi untuk mencari buku dari file
void cariBuku() {
    FILE *file;
    char buffer[MAX_LINE];
    char kodeCari[10];
    int ditemukan = 0;
    
    printf("\nMasukkan kode buku yang dicari: ");
    scanf("%s", kodeCari);
    
    file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("\n✗ File belum ada atau belum ada data.\n");
        return;
    }
    
    while (fgets(buffer, MAX_LINE, file) != NULL) {
        char kode[10], judul[100], pengarang[50];
        int stok, harga;
        
        sscanf(buffer, "%[^;];%[^;];%[^;];%d;%d", 
               kode, judul, pengarang, &stok, &harga);
        
        if (strcmp(kode, kodeCari) == 0) {
            printf("\n--- Data Buku Ditemukan ---\n");
            printf("Kode      : %s\n", kode);
            printf("Judul     : %s\n", judul);
            printf("Pengarang : %s\n", pengarang);
            printf("Stok      : %d\n", stok);
            printf("Harga     : Rp%d\n", harga);
            ditemukan = 1;
            break;
        }
    }
    
    fclose(file);
    
    if (!ditemukan) {
        printf("\n✗ Buku dengan kode '%s' tidak ditemukan.\n", kodeCari);
    }
}

// Fungsi untuk update stok buku
void updateStok() {
    FILE *file, *tempFile;
    char buffer[MAX_LINE];
    char kodeUpdate[10];
    int stokBaru;
    int ditemukan = 0;
    
    printf("\nMasukkan kode buku yang akan diupdate: ");
    scanf("%s", kodeUpdate);
    printf("Masukkan stok baru: ");
    scanf("%d", &stokBaru);
    
    file = fopen(FILENAME, "r");
    tempFile = fopen("temp.txt", "w");
    
    if (file == NULL || tempFile == NULL) {
        printf("\n✗ Error membuka file!\n");
        return;
    }
    
    while (fgets(buffer, MAX_LINE, file) != NULL) {
        char kode[10], judul[100], pengarang[50];
        int stok, harga;
        
        sscanf(buffer, "%[^;];%[^;];%[^;];%d;%d", 
               kode, judul, pengarang, &stok, &harga);
        
        if (strcmp(kode, kodeUpdate) == 0) {
            fprintf(tempFile, "%s;%s;%s;%d;%d\n", 
                    kode, judul, pengarang, stokBaru, harga);
            ditemukan = 1;
            printf("\n✓ Stok buku '%s' berhasil diupdate dari %d menjadi %d\n", 
                   judul, stok, stokBaru);
        } else {
            fprintf(tempFile, "%s", buffer);
        }
    }
    
    fclose(file);
    fclose(tempFile);
    
    remove(FILENAME);
    rename("temp.txt", FILENAME);
    
    if (!ditemukan) {
        printf("\n✗ Buku dengan kode '%s' tidak ditemukan.\n", kodeUpdate);
    }
}

// Fungsi untuk menghapus file database
void hapusFile() {
    char konfirmasi;
    
    printf("\n⚠ Apakah Anda yakin ingin menghapus semua data? (y/n): ");
    scanf(" %c", &konfirmasi);
    
    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        if (remove(FILENAME) == 0) {
            printf("\n✓ File '%s' berhasil dihapus!\n", FILENAME);
        } else {
            printf("\n✗ Error: File tidak dapat dihapus atau tidak ada.\n");
        }
    } else {
        printf("\n✗ Penghapusan dibatalkan.\n");
    }
}

// Fungsi untuk menampilkan informasi file
void infoFile() {
    FILE *file;
    int fd;
    long ukuran;
    int jumlahBaris = 0;
    char buffer[MAX_LINE];
    
    // Menggunakan fopen untuk mendapatkan ukuran file
    file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("\n✗ File belum ada.\n");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    ukuran = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    while (fgets(buffer, MAX_LINE, file) != NULL) {
        jumlahBaris++;
    }
    
    fclose(file);
    
    // Menggunakan open() system call untuk info tambahan
    fd = open(FILENAME, O_RDONLY);
    
    printf("\n========================================\n");
    printf("        INFORMASI FILE DATABASE\n");
    printf("========================================\n");
    printf("Nama File      : %s\n", FILENAME);
    printf("Ukuran File    : %ld bytes\n", ukuran);
    printf("Jumlah Record  : %d buku\n", jumlahBaris);
    printf("File Descriptor: %d\n", fd);
    
    if (access(FILENAME, R_OK) == 0) {
        printf("Permission     : Readable ✓\n");
    }
    if (access(FILENAME, W_OK) == 0) {
        printf("               : Writable ✓\n");
    }
    
    printf("========================================\n");
    
    if (fd != -1) {
        close(fd);
    }
}

int main() {
    int pilihan;
    
    printf("========================================\n");
    printf("  PROGRAM MANAJEMEN FILE PERPUSTAKAAN\n");
    printf("  Demonstrasi fopen, fread, fwrite\n");
    printf("========================================\n");
    
    initFile();
    
    do {
        tampilkanMenu();
        scanf("%d", &pilihan);
        
        switch(pilihan) {
            case 1:
                tambahBuku();
                break;
            case 2:
                tampilkanSemuaBuku();
                break;
            case 3:
                cariBuku();
                break;
            case 4:
                updateStok();
                break;
            case 5:
                hapusFile();
                break;
            case 6:
                infoFile();
                break;
            case 0:
                printf("\nKeluar dari program...\n");
                break;
            default:
                printf("\n✗ Pilihan tidak valid!\n");
        }
    } while(pilihan != 0);
    
    printf("Program selesai.\n");
    return 0;
}
