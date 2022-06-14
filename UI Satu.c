#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "UIDua.c"


void UI1();
void topUpSaldo();
void myTicket();
void cetakTiket(int index);
void ticketInit();
void cariFilm();
void cariBioskop();

void UI1(){
    system("cls");
    int pil;
    while (true){
        system("cls");
        printf("saldo anda: %d\n", saldo);
        printf("1. Cari Film\n");
        printf("2. Cari Bioskop\n");
        printf("3. Pesan Tiket\n");
        printf("4. Top Up Saldo\n");
        printf("5. Lihat Tiket\n");
        printf("6. Kembali\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &pil);
        switch(pil){
            case 1:
                cariFilm(); 
                break;
            case 2:
                cariBioskop();
                break;
            case 3:
                UI2();
                break;
            case 4:
                topUpSaldo();
                break;
            case 5:
                myTicket();
                break;
            case 6:
                exit(0);
            default:
                printf("Input tidak valid!");
                printf("Ulangi inputan!");
                system("pause");
        }
    }
}

void cariFilm(){
    int pil1, pil2;
    while(1){
        printf("\n===================\n");
        printf("List Film:\n");
        listFilm();
        printf("Masukkan pilihan atau ketik 0 untuk kembali: ");
        fflush(stdin);
        scanf("%d", &pil1);
        if(pil1==0){
            return;
        }
        pil1-=1;
        while(1){
            printf("\n===================\n");
            printf("Bioskop yang menayangkan film %s:\n", film[pil1]);
            for(int i=0; i<5; i++){
                if(fb[pil1][i]==1){
                    printf("%d. %s \n", i+1, bioskop[i]);
                }
            }
            system("pause");
            break;
            
        }
    }
}

void cariBioskop(){
    int pil1, pil2;
    while(1){
        printf("\n===================\n");
        printf("List Bioskop: \n");
        listBioskop();
        printf("Masukkan pilihan atau ketik 0 untuk kembali: ");
        fflush(stdin);
        scanf("%d", &pil1);
        if(pil1==0){
            return;
        }
        pil1-=1;
        while(1){
            printf("\n===================\n");
            printf("Film yang ditayangkan di Bioskop %s:\n", bioskop[pil1]);
            for(int i=0; i<5; i++){
                if(fb[i][pil1]==1){
                    printf("%d. %s \n", i+1, film[i]);
                }
            }
            system("pause");
                break;
        }
    }

}
void topUpSaldo(){
    int total;
    int jumlah; 
    int choice;
    printf("\n===================\n");
    do {
    printf("\nJumlah Saldo yang ingin anda Top Up \n");
        printf(" 1. 100.000\n");
        printf(" 2. 200.000\n");
        printf(" 3. 500.000\n");
        printf(" 4. 1.000.000\n");
        printf(" 5. Back\n");
        printf("======================================================\n");
        printf("Enter your choice (1 - 5): "); scanf("%d", &choice); fflush(stdin);
        printf("\n");
            switch(choice){
            case 1:
                saldo+=100000 ;
                break;
            case 2:
                saldo+=200000 ;
                break;
            case 3:
                saldo+=500000 ;
                break;
            case 4:
                saldo+=1000000 ;
                break;
            default:
                break;
        }
    } while(choice < 1 || choice > 5);
    system("cls");
    printf("======================================================\n");
    printf("                Transaction Successful!               \n");
    printf("======================================================\n");
    printf(" Your new balance is : %d\n", saldo);
    
}

void ticketInit(){
    for (int i = 0; i < MAXTICKET; i++) strcpy(ticketList[i].nama, "");}

void myTicket(){
    char userInput;
    //char* id;
    char nama[20];
    int urutan, opsi;
    while (true){
        system("cls");
        for (int i = 0; i < MAXTICKET; i++){
            if (strcmp(ticketList[i].nama, "") != 0){
                //cetak tiketnya
                printf("tiket %d\n", i+1);
                printf("bioskop: %s\n", ticketList[i].cinema);
                printf("film   : %s\n", ticketList[i].film);
                printf("jadwal : %s\n", ticketList[i].jadwal);
                printf("kursi  : %s\n", ticketList[i].kursi);
                printf("ID     : %s\n\n", ticketList[i].ticketID);
            }

        }
        if (strcmp(ticketList[0].nama, "") == 0){
            printf("Anda belum memiliki tiket!\n");
            system("pause");
            return;
        }
        while (true){
            fflush(stdin);
            printf("Opsi:\n");
            printf("1. Cetak tiket\n");
            printf("2. Buang tiket tercetak\n");
            printf("3. Ubah nama tiket\n");
            printf("4. kembali\n");
            printf("pilih: ");
            scanf("%d", &opsi);
            
            if (opsi == 1 || opsi == 3){
                while (true){
                        printf("\nNomor urutan tiket yang ingin dicetak: ");
                        scanf("%d", &urutan);
                        if (urutan < 1 || urutan > 10 || strcmp(ticketList[urutan-1].nama,"") == 0)
                            printf("\nMasukkan angka yang valid!");
                        else break;
                    }
                if (opsi == 1) {
                    cetakTiket(urutan-1);
                    printf("\nTiket tercetak. Periksa text file!\n");
                    break;
                }
                else if (opsi == 3){
                    count--;
                    printf("\nmasukkan nama: ");
                    scanf("%s", nama);
                    strcpy(ticketList[urutan-1].nama, nama);
                    cetakTiket(urutan-1);
                    printf("\nNama berhasil diubah\n");
                    count++;
                    break;
                }
            }
            else if(opsi == 2){
                remove("file.txt");
                printf("\ntiket berhasil dibuang\n");
                break;
            }
            else if (opsi == 4) return;
            return;
        }
        system("pause");
        fflush(stdin);
    }
}

void cetakTiket(int index){
    int i;
    char* tmp;
    struct tiket_t tix = ticketList[index];
    FILE *fp;
    fp = fopen("file.txt", "wb+");
    if (fp == NULL){
        printf("Cannot open file!");
        system("pause");
        fflush(stdin);
        return;
    }
    //WRITE FILE
    //bioskop
    fputs("==== ", fp);
    for (i = 0; i < strlen(tix.cinema); i++){
        fputc(tix.cinema[i], fp);
    }
    fputs(" ====\n", fp);
    //film
    fputs("\n", fp);
    for (i = 0; i < strlen(tix.film); i++) fputc(tix.film[i], fp);

    //jadwal
    fputs("\n", fp);
    for (i = 0; i < strlen(tix.jadwal); i++) fputc(tix.jadwal[i], fp);

    //kursi
    fputs("\nSeat: ", fp);
    for (i = 0; i < strlen(tix.kursi); i++) fputc(tix.kursi[i], fp);
    
    // nama
    fputs("\n", fp);
    for (i = 0; i < strlen(tix.nama); i++) fputc(tix.nama[i], fp);
    
    //ticket id
    fputs("\nTicket ID: ", fp);
    for (i = 0; i < strlen(tix.ticketID); i++) fputc(tix.ticketID[i], fp);

    fclose(fp);
}
