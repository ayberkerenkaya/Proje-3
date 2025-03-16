#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_HASTA 10 // Maksimum hasta say�s�n� belirtiyoruz

// Hasta bilgilerini tutan yap�
typedef struct Hasta {
    char tc[12];  // tc kimlik numaras� (11 haneli olucak)
    int aciliyet; // aciliyet durumu (1: KIRMIZI, 2: SARI, 3: YESIL)
    int kayitNo;  // hastan�n kay�t numaras�
} Hasta;

// Kuyru�u olu�turan d���m yap�s�
typedef struct Node {
    Hasta hasta;
    struct Node *next;
} Node;

// Kuyruk yap�s�
typedef struct Kuyruk {
    Node *front; // ba��
    Node *rear; // sonu
    int count; // kuyruktaki hasta say�s�
} Kuyruk;

// Kuyru�a yeni hasta ekleme fonksiyonu
void kuyrukEkle(Kuyruk *kuyruk, Hasta hasta) {
    Node *yeni = (Node*)malloc(sizeof(Node)); // bellekten yer ay�r�yoruz
    yeni->hasta = hasta;
    yeni->next = NULL;
    
    if (kuyruk->rear == NULL) { // kuyruk bo�sa ba�a ve sona ekliyoruz
        kuyruk->front = kuyruk->rear = yeni;
    } else {
        kuyruk->rear->next = yeni;
        kuyruk->rear = yeni;
    }
    kuyruk->count++; // hasta say�s�n� artt�r�yoruz
}

// Kuyruktaki ilk hastay� ��karma fonksiyonu
Hasta siradakiHastayiAl(Kuyruk *kuyruk) {
    if (kuyruk->front == NULL) { // e�er kuyruk bo�sa
        printf("Sirada hasta yok!\n");
        Hasta bosHasta = {"", 0, 0}; // bo� hasta d�nd�r�yoruz
        return bosHasta;
    }
    
    Node *temp = kuyruk->front;
    Hasta hasta = temp->hasta;
    kuyruk->front = kuyruk->front->next;
    if (kuyruk->front == NULL) {
        kuyruk->rear = NULL;
    }
    free(temp); // bellekten siliyoruz
    kuyruk->count--;
    return hasta;
}

// Hastalar� aciliyet ve kay�t numaras�na g�re s�ralayan fonksiyon
void hastalariSirala(Hasta hastalar[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (hastalar[j].aciliyet > hastalar[j + 1].aciliyet ||
                (hastalar[j].aciliyet == hastalar[j + 1].aciliyet && hastalar[j].kayitNo > hastalar[j + 1].kayitNo)) {
                Hasta temp = hastalar[j];
                hastalar[j] = hastalar[j + 1];
                hastalar[j + 1] = temp;
            }
        }
    }
}

// Doktor re�ete yaz�yor
void doktorRecete(Hasta hasta) {
    if (hasta.kayitNo == 0) { // hasta yoksa
        printf("Recete yazmak icin hasta yok!\n");
        return;
    }
    
    char ilac[50];
    int receteNo = rand() % 9000 + 1000; // rastgele re�ete numaras� olu�tur
    printf("Ilac ismi gir: ");
    scanf("%s", ilac);
    printf("Recete No: %d, TC: %s, Ilac: %s\n", receteNo, hasta.tc, ilac);
}

int main() {
    Kuyruk kuyruk = {NULL, NULL, 0}; // bo� kuyruk olu�turduk
    Hasta hastalar[MAX_HASTA]; // hasta listesi
    int hastaSayisi = 0;
    int secim;
    srand(time(NULL)); // rastgele say� �retimi i�in ba�lat�yoruz

    while (1) {
        printf("\n1. Hasta Ekle\n2. Doktor Recete Yaz\n3. Hastalari Sirala\n4. Siradaki Hasta\n5. Cikis\nSecim: ");
        scanf("%d", &secim);
        
        if (secim == 1) {
            if (hastaSayisi >= MAX_HASTA) { // e�er hasta kapasitesi dolmu�sa
                printf("Hasta kapasitesi dolu!\n");
                continue;
            }
            
            Hasta yeniHasta;
            yeniHasta.kayitNo = hastaSayisi + 1; // kay�t numaras� s�rayla gidiyor
            printf("TC Kimlik: ");
            scanf("%s", yeniHasta.tc);
            printf("Aciliyet (1: KIRMIZI, 2: SARI, 3: YESIL): ");
            scanf("%d", &yeniHasta.aciliyet);
            
            hastalar[hastaSayisi++] = yeniHasta; // listeye ekliyoruz
            kuyrukEkle(&kuyruk, yeniHasta); // kuyru�a ekliyoruz
        } else if (secim == 2) {
            doktorRecete(siradakiHastayiAl(&kuyruk)); // s�radaki hastaya re�ete yaz
        } else if (secim == 3) {
            int i;
            hastalariSirala(hastalar, hastaSayisi); // hastalar� s�rala
            printf("\nHastalar siralandi:\n");
            for (i = 0; i < hastaSayisi; i++) {
                printf("%d. TC: %s, Aciliyet: %d\n", i + 1, hastalar[i].tc, hastalar[i].aciliyet);
            }
        } else if (secim == 4) {
            Hasta siradaki = siradakiHastayiAl(&kuyruk);
            if (siradaki.kayitNo != 0) {
                printf("Siradaki hasta: TC: %s, Aciliyet: %d\n", siradaki.tc, siradaki.aciliyet);
            }
        } else if (secim == 5) {
            break; // program� bitir
        } else {
            printf("Gecersiz secim!\n");
        }
    }
    return 0;
}

