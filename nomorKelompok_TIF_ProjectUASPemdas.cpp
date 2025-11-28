#include <iostream>
#include <string>
#include <fstream>
#include <limits> // Untuk membersihkan buffer input

using namespace std;

// 1. STRUCT & POINTER (Syarat Plus)
struct Pasien {
    string nama;
    int umur;
    string keluhan;
    Pasien* next; // Pointer
};

Pasien* head = NULL;
Pasien* tail = NULL;

// Cek apakah antrean kosong
bool isEmpty() {
    return head == NULL;
}

// 2. FUNGSI UTILITAS (Pendaftaran - Enqueue)
void tambahAntrean(string nama, int umur, string keluhan) {
    Pasien* baru = new Pasien;
    baru->nama = nama;
    baru->umur = umur;
    baru->keluhan = keluhan;
    baru->next = NULL;

    if (isEmpty()) {
        head = tail = baru;
    } else {
        tail->next = baru;
        tail = baru;
    }
}


void daftarPasienBaru() {
    string nama, keluhan;
    int umur;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bersihkan buffer sebelum getline
    
    cout << "Masukkan Nama    : ";
    getline(cin, nama);
    
    cout << "Masukkan Umur    : ";
    cin >> umur;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bersihkan buffer lagi
    
    cout << "Masukkan Keluhan : ";
    getline(cin, keluhan);

    tambahAntrean(nama, umur, keluhan);
    cout << "[SUKSES] Pasien " << nama << " berhasil didaftarkan.\n";
}

// 3. FUNGSI PEMANGGILAN (Dequeue)
void panggilPasien() {
    if (isEmpty()) {
        cout << "[INFO] Antrean kosong!\n";
    } else {
        Pasien* hapus = head;
        cout << "--------------------------------------\n";
        cout << "PANGGILAN PASIEN\n";
        cout << "Nama    : " << head->nama << endl;
        cout << "Umur    : " << head->umur << " th" << endl;
        cout << "Keluhan : " << head->keluhan << endl;
        cout << "--------------------------------------\n";
        cout << "Silakan masuk ke ruang dokter.\n";

        head = head->next;
        delete hapus; // Hapus dari memori (Penting untuk Pointer!)

        if (head == NULL) tail = NULL;
    }
}

// 4. REKURSIF (Syarat Plus)

// A. Rekursif Menghitung Jumlah Antrean
int hitungAntrean(Pasien* current) {
    if (current == NULL) return 0;
    return 1 + hitungAntrean(current->next);
}

// B. Rekursif Mencari Pasien
void cariPasienRekursif(Pasien* current, string target) {
    // Base Case 1: Jika sudah sampai ujung dan tidak ketemu
    if (current == NULL) {
        cout << "[HASIL] Pasien atas nama '" << target << "' TIDAK DITEMUKAN.\n";
        return;
    }
    // Base Case 2: Jika ketemu
    if (current->nama == target) {
        cout << "[HASIL] DITEMUKAN: " << current->nama 
             << " (" << current->umur << " th) - " << current->keluhan << endl;
        return; // Berhenti mencari
    }
    // Recursive Case: Cek node berikutnya
    cariPasienRekursif(current->next, target);
}

// Wrapper pencarian
void menuCariPasien() {
    if (isEmpty()) {
        cout << "Antrean kosong, tidak ada yang bisa dicari.\n";
        return;
    }
    string nama;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Masukkan nama pasien yang dicari: ";
    getline(cin, nama);
    cariPasienRekursif(head, nama);
}

// Menampilkan semua (Iteratif biasa untuk display)
void lihatDaftarAntrean() {
    if (isEmpty()) {
        cout << "Antrean kosong!\n";
    } else {
        cout << "Daftar Antrean Saat Ini (" << hitungAntrean(head) << " orang):\n";
        Pasien* current = head;
        int no = 1;
        while (current != NULL) {
            cout << no << ". " << current->nama << " (" << current->umur << " th) - " << current->keluhan << endl;
            current = current->next;
            no++;
        }
    }
}

// 5. FILE PROCESSING (Wajib)
void simpanKeFile() {
    ofstream file("database_klinik.txt"); 
    
    Pasien* current = head;
    while (current != NULL) {
        file << current->nama << "|" << current->umur << "|" << current->keluhan << endl;
        current = current->next;
    }
    file.close();
    cout << "[SYSTEM] Data berhasil diperbarui ke 'database_klinik.txt'.\n";
}

void loadDariFile() {
    ifstream file("database_klinik.txt");
    if (!file.is_open()) return; 

    string nama, strUmur, keluhan;
    while (getline(file, nama, '|')) {
        getline(file, strUmur, '|');
        getline(file, keluhan);
        
        if (nama != "") {
            tambahAntrean(nama, stoi(strUmur), keluhan);
        }
    }
    file.close();
    cout << "[SYSTEM] Data lama berhasil dimuat.\n";
}

int main() {
    loadDariFile();
    
    int pilihan;
    do {
        cout << "\n==========================================\n";
        cout << "   SISTEM ANTREAN KLINIK SEHAT SENTOSA    \n";
        cout << "==========================================\n";
        cout << "1. Daftar Pasien Baru (Enqueue)\n";
        cout << "2. Panggil Pasien Masuk (Dequeue)\n";
        cout << "3. Lihat Daftar Antrean\n";
        cout << "4. Cari Pasien (Rekursif)\n";
        cout << "5. Simpan Data & Keluar\n";
        cout << "==========================================\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cout << endl;

        switch (pilihan) {
            case 1:
                daftarPasienBaru();
                break;
            case 2:
                panggilPasien();
                break;
            case 3:
                lihatDaftarAntrean();
                break;
            case 4:
                menuCariPasien();
                break;
            case 5:
                simpanKeFile();
                cout << "Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
                break;
        }
    } while (pilihan != 5);

    return 0;
}