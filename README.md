# Project-UAS-Operating-System
Repository ini berisi project pengganti **Ujian Akhir Semester (UAS)** untuk mata kuliah **Praktikum Sistem Operasi**.

Project ini dikembangkan oleh:

- **Nama** : Delviana Setiani  
- **NIM**  : 20230910049  
- **Kelas**: SINFC-2023-02  
- **Program Studi**: Sistem Informasi  
- **Universitas**: Universitas Kuningan  

---

## Deskripsi Project

Project ini terdiri dari dua program berbasis bahasa pemrograman **C** yang dirancang untuk mendemonstrasikan konsep-konsep fundamental dalam **Sistem Operasi**, khususnya pada topik:

1. **Manajemen Memori Dinamis**
2. **Manajemen File dan Sistem Berkas**

Kedua program dikembangkan dan diuji menggunakan **Google Cloud Shell (Linux Ubuntu)** serta dikompilasi menggunakan **GCC**.

---

## Daftar Program

### 1. Memory Management System (`memory_management.c`)

Program ini mensimulasikan sistem manajemen data mahasiswa dengan pendekatan **dynamic memory allocation**.

#### Fitur:
- Menambah data mahasiswa menggunakan `malloc` dan `realloc`
- Menampilkan seluruh data mahasiswa
- Mencari data mahasiswa berdasarkan NIM
- Menghapus seluruh data dan membebaskan memori menggunakan `free`
- Pencegahan memory leak melalui manajemen pointer yang benar

#### Konsep Sistem Operasi yang Diterapkan:
- Dynamic Memory Allocation (`malloc`, `realloc`, `free`)
- Pointer dan Address Management
- Struct sebagai representasi data
- Heap Memory Management

---

### 2. File Management System (`file_management.c`)

Program ini merupakan sistem manajemen perpustakaan sederhana berbasis **file teks**, yang menerapkan operasi CRUD pada file.

#### Fitur:
- Menambahkan data buku ke file database
- Menampilkan seluruh data buku dari file
- Mencari buku berdasarkan kode
- Memperbarui stok buku
- Menghapus file database
- Menampilkan informasi detail file

#### Konsep Sistem Operasi yang Diterapkan:
- File Handling (`fopen`, `fclose`, `fgets`, `fprintf`)
- System Calls (`open`, `close`, `access`)
- File Descriptor
- Strategi file sementara (temporary file) untuk update data

---

## Status Implementasi Fitur

| Program | Fitur | Status |
|-------|-------|--------|
| Memory Management | Dynamic Allocation | Selesai |
| Memory Management | Reallocation | Selesai |
| Memory Management | Deallocation | Selesai |
| Memory Management | Search & Display | Selesai |
| File Management | Create Data | Selesai |
| File Management | Read Data | Selesai |
| File Management | Update Data | Selesai |
| File Management | Delete Data | Selesai |
| File Management | File Information | Selesai |

---

## Cara Menjalankan Program

### Prasyarat
Pastikan sistem telah terpasang:
- GCC Compiler
- Lingkungan Linux/Unix  
  (atau Windows menggunakan WSL / MinGW)

### Langkah Penggunaan

```bash
# Clone repository
git clone https://github.com/DelvianaSetiani/Project-UAS-Operating-System.git
cd Project-UAS-Operating-System

# Kompilasi dan jalankan program Memory Management
gcc memory_management.c -o memory_management
./memory_management

# Kompilasi dan jalankan program File Management
gcc file_management.c -o file_management
./file_management
````

### Kompilasi dengan Warning

```bash
gcc memory_management.c -Wall -o memory_management
gcc file_management.c -Wall -o file_management
```

---

## Struktur Data

### Struct Mahasiswa

```c
typedef struct {
    char nim[15];
    char nama[50];
    float ipk;
} Mahasiswa;
```

### Struct Buku

```c
typedef struct {
    char kode[10];
    char judul[100];
    char pengarang[50];
    int stok;
    int harga;
} Buku;
```

---

## Teknologi yang Digunakan

* Bahasa Pemrograman: C
* Compiler: GCC (GNU Compiler Collection)
* Sistem Operasi: Linux (Google Cloud Shell - Ubuntu)
* Library:

  * stdio.h
  * stdlib.h
  * string.h
  * unistd.h
  * fcntl.h

---

## Dokumentasi

Dokumentasi lengkap berupa laporan praktikum, analisis program, benchmark sistem, dan hasil pengujian akan disertakan dalam file:

* **Laporan_Praktikum_Sistem_Operasi.pdf**

---

## Pembelajaran yang Diperoleh

Melalui project ini, diperoleh pemahaman mengenai:

1. Cara kerja alokasi memori dinamis pada heap
2. Manajemen pointer dan pencegahan memory leak
3. Operasi file dan sistem berkas pada Linux
4. Perbedaan standard library dan system calls
5. Implementasi konsep CRUD pada level sistem operasi

---

## Kontak

Email  : [20230910049@uniku.ac.id](mailto:20230910049@uniku.ac.id)
GitHub : [https://github.com/DelvianaSetiani](https://github.com/DelvianaSetiani)

---

## Lisensi

Project ini dibuat untuk keperluan akademik
Mata Kuliah **Praktikum Sistem Operasi**
Universitas Kuningan

---

© 2025 Delviana Setiani
Fakultas Ilmu Komputer
Universitas Kuningan

