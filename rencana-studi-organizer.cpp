#include <iostream>
#include <string>
#include <fstream>
using namespace std;

typedef struct prereq *address;
typedef struct prereq
{
    string name;
    address next;
} prereq;

typedef struct matkul *address;
typedef struct matkul
{
    string name;            // Nama matkul
    int count_prereq;       // Jumlah prereq matkul
    address list_prereq;    // Array prereq
    address next;
} matkul;

address alokasiPrereq(string name){
    address P = (address) malloc(sizeof(name));
    if (P != NULL){
        P->name = name;
        P->next = NULL;
    }
    return P;
}

address alokasiMatkul(string name){
    address M = (address) malloc(sizeof(name));
    if (M != NULL){
        M->name = name;
        M->count_prereq = 0;
        M->list_prereq = NULL;
        M->next = NULL;
    }
    return M;
}

void addPrereq(matkul* M, address P){
    address Last = M->list_prereq;
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

void delPrereq(matkul *M, address P){
    address MKb = M->list_prereq;
    while (MKb != NULL){
        address MK = MKb->next;
        if (MK != NULL && MK->name.compare(P->name)){
            MKb->next = MK->next;
            delete MK;
            M->count_prereq--;
        }
        MKb = MK;
    }
}

void delMatkul(matkul *M, address MD){
    address MKb = M->list_prereq;
    while (MKb->next != MD){
        MKb = MKb->next;
    }

    while (M != NULL){
        delPrereq(M, MD);
        M = M->next;
    }

    MKb->next = MD->next;
    delete MD;
}

void bacaFile(matkul *M, string namafile){
    ifstream file(namafile);
    const char splitter = ',';
    const char stopper = '.';

    if (file.is_open()){
        
    }
}


int main(){
    return 0;

}