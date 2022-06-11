#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#define maxk 40
#define MAXTICKET 3

struct list{
    // 1 = kursi sudah terisi
    // 0 = kursi kosong
    bool kursi[5][5][maxk];
};

struct tiket_t{
    char nama[20];
    char film[20];
    char cinema[20];
    char kursi[20];
    char ticketID[20];
    char jadwal[20];
};

struct tiket_t ticketList[MAXTICKET];

int count = 0;
int pil_F, pil_B, pil_J, pil_K;
struct list jadwal[3];
char jam[3][10]={"14:20", "17:00", "19:40"};
char film[5][20]={"Avanger", "Transformer", "Doctor Strange", "Spiderman", "Susah Sinyal"};
char bioskop[5][25]={"Beach Walk", "Galeria", "Level 21", "Park 23", "TSM"};
int saldo = 100000;
int harga = 45000;

// apakah suatu film ada di suatu bioskop
bool fb[5][5]=
{
    {1,1,1,1,1},
    {1,0,1,0,1},
    {0,1,0,1,0},
    {1,1,1,1,1},
    {0,0,0,1,0}
};


void UI2();
void screen();
void listFilm();
void listBioskop();
void listJam();
void pilihanKursi();
void billTiket();
void randomPelanggan();


void UI2(){
    system("cls");
    int pil;
    do{
        if(count>=MAXTICKET){
            printf("=========================================================\n");
            printf("Anda sudah mencapai batas pembelian tiket untuk hari ini!\n");
            printf("Silahkan beli kembali besok, terima kasih.\n\n");
            system("pause");
            return;
        }
        printf("\n================\n");
        printf("1. Pilih Kursi\n");
        printf("2. Kembali\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &pil);
        switch(pil){
            case 1:
                pilihanKursi();
                break;
            case 2:
                return;
                break;
            default:
                printf("Input tidak valid!");
                printf("Ulangi inputan!");
        }
    }while(pil != 3);
}

void screen(){
    printf("===============================================================================\n");
    printf("-----------------------------(    SCREEN AREA    )-----------------------------\n");
    printf("===============================================================================\n");
}

void listFilm(){
    for(int i=0; i<5; i++){
        printf("%d. %s\n", i+1, film[i]);
    }
}

void listBioskop(){
    for(int i=0; i<5; i++){
        printf("%d. %s\n", i+1, bioskop[i]);
    }
}

void listJam(){
    for(int i=0; i<3; i++){
        printf("%d. %s\n", i+1, jam[i]);
    }
}

void pilihanKursi(){
    if(count>=MAXTICKET){
        printf("Anda sudah mencapai batas pembelian tiket untuk hari ini!\n");
        printf("Silahkan beli kembali besok, terima kasih.\n");
        system("pause");
        return;
    }else{
        while(1){
            printf("\n===================\n");
            listFilm();
            printf("Masukkan pilihan atau ketik 0 untuk kembali: ");
            scanf("%d", &pil_F);
            if(pil_F == 0){
                printf("\n");
                break;
            }
            fflush(stdin);
            pil_F-=1;
            
            while(1){
                printf("\n===================\n");
                printf("Bioskop yang menayangkan film %s:\n", film[pil_F]);
                for(int i=0; i<5; i++){
                if(fb[pil_F][i]==1){
                    printf("%d. %s \n", i+1, bioskop[i]);
                }
                }
                printf("Masukkan pilihan atau tekan 0 untuk kembali: ");
                scanf("%d", &pil_B);
                if(pil_B == 0){
                    printf("\n");
                    break;
                }
                fflush(stdin);
                pil_B-=1;
                
                while(1){
                    printf("\n================\n");
                    printf("Jam Tayang:\n");
                    listJam();
                    printf("Masukkan pilihan atau tekan 0 untuk kembali: ");
                    scanf("%d", &pil_J);
                    if(pil_J == 0){
                        printf("\n");
                        break;
                    }
                    fflush(stdin);
                    pil_J -= 1;

                    while(1){
                        system("cls");
                        printf("\n===================\n");
                        randomPelanggan();
                        printf("Kursi yang tersedia:\n");
                        printf("\n%s|%s|%s\n", film[pil_F], bioskop[pil_B], jam[pil_J]);
                        screen();
                        printf("|");
                        for(int k=0; k<maxk; k++){
                            // pengaturan kursi
                            if(k != 0 && k%8 == 0){
                                printf("\n|");
                            }else if(k != 0 && k%4 ==0){
                                printf("     |");
                            }
                            
                            // memberi tanda
                            if(jadwal[pil_J].kursi[pil_F][pil_B][k] == 1){
                                printf(" %02d (X) |", k+1);
                            }else{
                                printf(" %02d (O) |", k+1);
                            }
                        }
                        printf("\n");
                        printf("pilih kursi atau tekan 0 untuk kembali: ");
                        scanf("%d", &pil_K);
                        if(pil_K == 0){
                            printf("\n");
                            break;
                        } 
                        fflush(stdin);
                        pil_K -= 1;
                        if(jadwal[pil_J].kursi[pil_F][pil_B][pil_K]==1){
                            printf("Kursi sudah terisi!\n");
                            printf("Pilih kursi lainnya!\n");
                            system ("pause");
                        }else{
                            if(saldo<harga){
                                printf("Saldo kurang!\n");
                                printf("Silahkan top up saldo terlebih dahulu.\n");
                                system("pause");
                                topUpSaldo();
                                return;
                            }else{
                                billTiket();
                            }
                            return;
                        }
                    }
                }
            }
        }
    }
}

void randomPelanggan(){
    srand(time(0));
    // random kursi sejumlah count
    int n=rand()%4+1;
    for(int i=0; i<n; i++){
        // random kursi antara nomor 1 sampai max kursi
        jadwal[pil_J].kursi[pil_F][pil_B][rand()%maxk]=1;
    }
}

void billTiket(){
    int confirm;
    srand(time(0));
    int tiketId = rand();
    char tiketid[20];
    char nama[20];
    sprintf(tiketid, "%d", tiketId);
    printf("Masukkan nama Anda: ");
    fflush(stdin);
    scanf("%[^\n]", &nama);
    printf("\n==========================\n");
    printf("Rincian Pembelian Tiket : \n");
    printf("Nama     :   %s\n", nama);
    printf("Tiket ID :   %s\n", tiketid);
	printf("Film     :   %s\n", film[pil_F]);
    printf("Bioskop  :   %s\n", bioskop[pil_B]);
    printf("Jam      :   %s\n", jam[pil_J]);
    printf("Kursi    :   %d\n", pil_K+1);
    printf("\nTotal Pembayaran: %d\n", harga);
    printf("Lakukan pembayaran? (1 = iya/0 = tidak): ");
    fflush(stdin);
    scanf("%d", &confirm);
    if(confirm == 1){
        saldo-=harga;
        jadwal[pil_J].kursi[pil_F][pil_B][pil_K]=1;

        fflush(stdin);
        strcpy(ticketList[count].nama, nama);
        strcpy(ticketList[count].film, film[pil_F]);
        strcpy(ticketList[count].cinema, bioskop[pil_B]);
        strcpy(ticketList[count].jadwal, jam[pil_J]);
        sprintf(ticketList[count].kursi, "%d", pil_K+1);
        sprintf(ticketList[count].ticketID, "%d", tiketId);

        count++;

        printf("Pembayaran berhasil!\n\n");
        system("pause");
    }
}
