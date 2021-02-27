#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// boolean.h
#define boolean unsigned char
#define true 1
#define false 0


// TIPE PREREQ, KONSTRUKTOR DAN DESTRUKTOR //
typedef struct prereq *alamat;
typedef struct prereq
{
    char name[50];
    alamat next;
} prereq;

alamat alokasiPrereq(char name[50]){
    // I.S. String nama prereq
    // F.S. Terbentuk prereq P

    alamat P = (alamat) malloc(sizeof(prereq));
    if (P != NULL){
        strcpy(P->name, name);
        P->next = NULL;
    }
    return P;
}

void addPrereq(matkul* M, alamat P){
    // I.S. Matkul M, alamat prereq P
    // F.S. Menambah P menjadi prereq M

    
    // Jika list prereq masih kosong
    if (M->list_prereq == NULL){
        M->list_prereq = P; 
    }

    // Jika list prereq sudah terisi
    else{
        alamat Last = M->list_prereq;
        while (Last->next != NULL){
            Last = Last->next;
        }
        Last->next = P;
    }

    // Menambah jumlah prereq
    M->count_prereq++;
}

void delPrereq(matkul *M, char P[50]){
    // I.S. Matkul M, string P
    // F.S. Prereq pada matkul M dihapus jika bersesuaian dgn P

    // Prekondisi: list prereq ada isinya
    if (M->list_prereq != NULL){
        alamat PQ = M->list_prereq;

        // Menghapus prereq PQ jika elemen pertama
        if (!strcmp(PQ->name, P)){
            M->list_prereq = PQ->next;
            PQ->next = NULL;
            M->count_prereq--;
            free(PQ);
        }

        // Menghapus prereq PQ jika bukan elemen pertama
        else{
            while (PQ->next != NULL && strcmp(PQ->next->name, P)){
                PQ = PQ->next;
            }

            if (PQ->next != NULL){
                alamat PK = PQ->next;
                PQ->next = PK->next;
                PK->next = NULL;
                M->count_prereq--;
                free(PK);
            }
        }
    }
}
////////////////////////////////////////////////////////////


// TIPE MATKUL, KONSTRUKTOR, DAN DESTRUKTOR //
typedef struct matkul *address;
typedef struct matkul
{
    char name[50];          // Nama matkul
    int count_prereq;       // Jumlah prereq matkul
    alamat list_prereq;     // Array prereq
    boolean delete_soon;    // 
    address next;
} matkul;

typedef struct {
	address First;
} List;

void createEmpty(List *L){
    // I.S. List L
    // F.S. L.First menunjuk NULL
    L->First = NULL;
}

address alokasiMatkul(char name[50]){
    // I.S. String nama matkul
    // F.S. Terbentuk matkul M

    address M = (address) malloc(sizeof(matkul));
    if (M != NULL){
        strcpy(M->name, name);
        M->count_prereq = 0;
        M->list_prereq = NULL;
        M->delete_soon = false;
        M->next = NULL;
    }
    return M;
}

void addMatkul(List* L, address M){
    // I.S. List L, alamat matkul M
    // F.S. Menambah M menjadi anggota L

    // Jika L masih kosong
    if (L->First == NULL){
        L->First = M;
    }

    // Jika L sudah terisi
    else{
        address N = L->First;
        while (N->next != NULL){
            N = N->next;
        }
        N->next = M;
    }
}

void delMatkul(List *L, address M){
    // I.S. List matkul L, alamat matkul M
    // F.S. Matkul M dihapus dari list, matkul lain yg prereqnya M dihapus dgn prosedur delPrereq

    // Memanggil prosedur delPrereq untuk semua matkul
    address MKb, MK = L->First;
    while (MK != NULL){

        // Menyimpan address matkul sebelum M
        if (MK->next != NULL && !strcmp(MK->next->name, M->name)){
            MKb = MK;
        }
        delPrereq(MK, M->name);
        MK = MK->next;
    }

    // Menghapus matkul M jika elemen pertama
    if (L->First == M){
        L->First = M->next;
    }
    // Menghapus matkul M jika bukan elemen pertama
    else{
        MKb->next = M->next;
        M->next = NULL;
    }
}
///////////////////////////////////////////////////////////////////


// FUNGSI MEMBACA FILE //
void bacaFile(List *L, char namafile[100]){
    // I.S. List kosong L, string namafile
    // F.S. Membaca file dan menyalinnya menjadi list L

    // Kamus konstanta
    #define splitter ','
    #define stopper '.'
    #define blank ' '
    #define enter '\n'

    // Membuka file
    FILE *f;
    f = fopen(namafile, "r");
    if (f == NULL){
        printf("Error!");
        exit(1);
    }

    // Membaca file
    char c;
    c = getc(f);

    // EOF
    while (c != EOF){

        // Var count berfungsi membedakan matkul dgn prereqnya
        int count = 0;
        address MK;

        // Membaca tiap matkul
        while (c != stopper){

            // Inisialisasi tempat penyimpanan kata
            char name[50];
            int i = 0;

            // Membuang blank atau enter
            while (c == blank || c == enter){
                c = getc(f);
            }

            // Membaca dan memisahkan matkul dan prereqnya
            while (c != splitter && c != stopper){
                name[i] = c;
                i++;
                c = getc(f);
            }
            name[i] = '\0';

            // Jika count = 0, maka adalah matkul
            if (count == 0){
                MK = alokasiMatkul(name);
            }
            // Jika count > 0, maka adalah prereq
            else{
                alamat MP = alokasiPrereq(name);
                addPrereq(MK, MP);
            }

            // Next element
            count++; 
            if (c == splitter){
                c = getc(f);
            }
        }

        // Menambah MK ke list L
        addMatkul(L, MK);

        // Next element
        if (c == stopper){
            c = getc(f);
        }
    }

    // Jika terjadi kesalahan pada getc()
    if (!feof(f)){
        printf("Terjadi kesalahan pada proses pembacaan file.\n");
    }
    fclose(f);
}
////////////////////////////////////////////////////////////////////


// MAIN PROGRAM //
int main(){
    // KAMUS DAN DEKLARASI VARIABEL //
    char namafile[100] = "tc2.txt";     // Letak file yang akan dibuka
    int i = 1;                          // Counter semester ke-i
    int found = 1;                      // Counter ditemukan matkul tanpa prereq
    List L;                             // List matkul
    address M;                          // Variabel penyimpanan matkul


    // ALGORITMA PROGRAM UTAMA //

    // Inisialisasi
    createEmpty(&L);
    bacaFile(&L, namafile);
    
    // Proses sorting
    while (L.First != NULL && found){
        found = 0;
        M = L.First;
        printf("Semester %d: ", i);

        // Mencari matkul dengan jumlah prereq = 0 untuk dihapus
        while (M != NULL){
            if (M->count_prereq == 0){

                // Elemen pertama 
                if (found == 0){
                    printf("%s", M->name);
                }

                // Bukan elemen pertama
                else{
                    printf(", %s", M->name);
                }

                // Menambah matkul ke list matkul yang akan dihapus
                M->delete_soon = true;
                found++;
            }
            M = M->next;
        }

        // Jika terdapat matkul yang akan dihapus
        if (found){
            M = L.First;

            // Menghapus matkul yang sudah ditandai
            while (M != NULL){
                if (M->delete_soon){
                    delMatkul(&L, M);
                }
                M = M->next;
            }
        }
        printf("\n");
        i++;
    }

    // Jika tidak ada matkul lain yang bisa diambil
    if (!found){
        printf("Proses tidak bisa diselesaikan karena tidak ada matkul lain yang bisa diambil.\n");
    }

    return 0;
}