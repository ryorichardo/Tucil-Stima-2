#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct prereq *alamat;
typedef struct prereq
{
    char name[50];
    alamat next;
} prereq;

typedef struct matkul *address;
typedef struct matkul
{
    char name[50];            // Nama matkul
    int count_prereq;       // Jumlah prereq matkul
    alamat list_prereq;    // Array prereq
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

address alokasiMatkul(char name[50]){
    // I.S. String nama matkul
    // F.S. Terbentuk matkul M

    address M = (address) malloc(sizeof(matkul));
    if (M != NULL){
        strcpy(M->name, name);
        M->count_prereq = 0;
        M->list_prereq = NULL;
        M->next = NULL;
    }
    return M;
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

void delPrereq(matkul *M, char P[50]){
    // I.S. Matkul M, string P
    // F.S. Prereq pada matkul M dihapus jika bersesuaian dgn P


    if (M->list_prereq != NULL){
        alamat PQ = M->list_prereq;
        if (strcmp(PQ->name, P) == 0){
            M->list_prereq = PQ->next;
            PQ->next = NULL;
            M->count_prereq--;
            free(PQ);
        }

        else{
            while (PQ->next != NULL && strcmp(PQ->next->name, P) != 0){
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


    // Mencari alamat prereq
    //alamat MKb = M->list_prereq;
    //int hasDel = 0;
    //while (MKb!= NULL && !hasDel){
//
    //    // Jika prereq P adalah first element
    //    if (strcmp(M->list_prereq->name, P) == 0){
    //        M->list_prereq = MKb->next;
    //        M->count_prereq--;
    //        hasDel = 1;
    //    }
//
    //    // Jika prereq P bukan first element
    //    else if (MKb->next != NULL && strcmp(MKb->next->name, P) == 0){
    //        alamat MD = MKb->next;
    //        MKb->next = MD->next;
    //        M->count_prereq--;
    //        free(MD);
    //        hasDel = 1;
    //    }
//
    //    // Jika prereq P belum ditemukan
    //    else{
    //        MKb = MKb->next;
    //    }
    //}
}

void delMatkul(List *L, address M){
    // I.S. List matkul L, alamat matkul M
    // F.S. Matkul M dihapus dari list, matkul lain yg prereqnya M dihapus dgn prosedur delPrereq

    // Memanggil prosedur delPrereq untuk semua matkul
    address MK = L->First;
    while (MK != NULL){
        delPrereq(MK, M->name);
        MK = MK->next;
    }

    // Menghapus matkul M jika elemen pertama
    if (L->First == M){
        L->First = M->next;
    }
    // Menghapus matkul M jika bukan elemen pertama
    else{
        address MKb = L->First;
        while (strcmp(MKb->next->name, M->name) != 0){
            MKb = MKb->next;
        }
        MKb->next = M->next;
        M->next = NULL;
    }
    //free(M);
}

void bacaFile(List *L, char namafile[100]){
    // I.S. List kosong L, string namafile
    // F.S. Membaca file dan menyalinnya menjadi list L

    // CONSTANT LIST
    #define splitter ','
    #define stopper '.'
    #define mark '!'
    #define blank ' '
    #define enter '\n'

    // OPEN FILE
    FILE *f;
    f = fopen(namafile, "r");
    if (f == NULL){
        printf("Error!");
        exit(1);
    }

    // READ FILE
    char c;
    int retval = fscanf(f, "%c", &c);

    // stop reading if mark
    while (c != mark){

        // init count: bedain mk biasa dgn prereq
        int count = 0;
        address MK;

        // reset count if stopper
        while (c != stopper && c != mark){

            // buffer to store word
            char name[50];
            int i = 0;

            // remove blank or enter
            while (c == blank || c == enter){
                retval = fscanf(f, "%c", &c);
            }

            // read until splitter
            while (c != splitter && c != stopper && c != mark){
                name[i] = c;
                i++;
                retval = fscanf(f, "%c", &c);
            }
            name[i] = '\0';

            // count = 0 -> mk
            if (count == 0){
                MK = alokasiMatkul(name);
            }

            // count > 0 -> prereq
            else{
                alamat MP = alokasiPrereq(name);
                addPrereq(MK, MP);
            }

            // increment
            count++; 
            if (c == splitter){
                retval = fscanf(f, "%c", &c);
            }
        }

        // add MK to array of matkul M
        addMatkul(L, MK);
        
        if (c == stopper){
            retval = fscanf(f, "%c", &c);
        }
    }
    fclose(f);
}

void printString(char name[50]){
    int i = 0;
    while (name[i] != '\0'){
        printf("%c", name[i]);
        i++;
    }
}

int main(){
    char namafile[100] = "tc1.txt";
    List L;
    createEmpty(&L);
    bacaFile(&L, namafile);

    /*
    address M = L.First;
    address MK;
    while (M != NULL){
        printf("%s: ", M->name);
        alamat P = M->list_prereq;
        while (P != NULL){
            printf("%s ", P->name);
            P = P->next;
        }
        M = M->next;
    }

    delMatkul(&L, L.First);
    M = L.First;
    while (M != NULL){
        printf("%s", M->name);
        M = M->next;
    }*/

    
    int i = 1;
    while (L.First != NULL){
        address M = L.First;
        printf("Semester %d: ", i);

        while (M != NULL){
            if (M->count_prereq == 0){
                printString(M->name);
                delMatkul(&L, M);
                M = NULL;
            }
            else{
                M = M->next;
            }
        }
        printf("\n");
        i++;
    }
    return 0;
}