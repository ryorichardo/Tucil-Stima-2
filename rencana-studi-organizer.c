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

alamat alokasiPrereq(char name[50]){
    alamat P = (alamat) malloc(sizeof(name[50]));
    if (P != NULL){
        strcpy(P->name, name);
        P->next = NULL;
    }
    return P;
}

address alokasiMatkul(char name[50]){
    address M = (address) malloc(sizeof(name[50]));
    if (M != NULL){
        strcpy(M->name, name);
        M->count_prereq = 0;
        M->list_prereq = NULL;
        M->next = NULL;
    }
    return M;
}

void addPrereq(matkul* M, alamat P){
    alamat Last = M->list_prereq;
    // Jika First = null
    if (Last == NULL){
        M->list_prereq = P; 
    }

    // Jika engga
    else{
        while (Last->next != NULL){
            Last = Last->next;
        }
        Last->next = P;
    }
}

void addMatkul(matkul* M, address N){
    if (M == NULL){
        M = N;
    }
    else{
        while (M->next != NULL){
            M = M->next;
        }
        M->next = N;
    }
}

void delPrereq(matkul *M, char P[50]){
    alamat MKb = M->list_prereq;
    while (MKb != NULL){
        alamat MK = MKb->next;
        if (MK != NULL && strcmp(MK->name, P)){
            MKb->next = MK->next;
            free(MK);
            M->count_prereq--;
        }
        MKb = MK;
    }
}

void delMatkul(matkul *M, address MD){
    address MKb = M;
    while (MKb->next != MD){
        MKb = MKb->next;
    }

    while (M != NULL){
        delPrereq(M, MD->name);
        M = M->next;
    }

    MKb->next = MD->next;
    free(MD);
}

void bacaFile(matkul *M, char namafile[100]){
    #define splitter ','
    #define stopper '.'
    #define mark '!'
    #define blank ' '

    FILE *f;
    f = fopen(namafile, "r");

    if (f == NULL){
        printf("Error!");
        exit(1);
    }

    char c;
    int retval = fscanf(f, "%c", c);
    while (c != mark){
        int count = 0;
        address MK;
        while (c != stopper){
            char name[50];
            int i = 0;
            while (c == blank){
                retval = fscanf(f, "%c", c);
            }
            while (c != splitter){
                name[i] = c;
                i++;
                retval = fscanf(f, "%c", c);
                }
            if (count == 0){
                MK = alokasiMatkul(name);
            }
            else{
                alamat MP = alokasiPrereq(name);
                addPrereq(MK, MP);
            }
            count++;
        }
        addMatkul(M, MK);
    }
}

int main(){
    char namafile[100] = "tc1.txt";
    matkul *M;
    bacaFile(M, namafile);

    while (M != NULL){
        printf("%s", M->name);
        M = M->next;
    }
    return 0;
}