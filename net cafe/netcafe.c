#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct netcafe
{
    int masa[30];
    int masa_secim;
    int fatura[30];
    int masa_no;
    int fatura_s;
    clock_t start_time;  
    clock_t end_time;
}a1;

void okuma();//siparisleri dosyadan okuyan fonksiyon
void isletme_degerlendir();//kullanicilarin yorum girmesini ve kaydetmesini sağlayan fonksiyon
void atama(a1 *net);//tüm masaların kapalı olarak açıldığı fonksiyon
void siparis(int siparis,int *a);//siparis alma fonksiyonu
void masa_yazdir(a1*net);//masalarin açık mı kapali mi olduğunu yazan fonksiyon
void menu();//siparis menüsü
int siparis_ver(int *a, a1* net);
void masa_ac(a1*net);
void masa_kapat(a1*net,int *p);
void deger_dosyasi_okuma();
int toplam_tutar(int *f,int *p);
void masa_kayit(a1*net);
void atama2(a1 *net); 
void zaman_kaydet();
double gecen_sure_hesapla();
void masa_kapat2(a1*net, int *p);

int main(){
int sifre=12345;
int sifre2;
int fatura1;
int fatura=0;
clock_t start, end;
double cpu_time_used;


a1*net=(a1 *)malloc(sizeof(a1));//bellek bloğu tahsis etmek için 
int oturum=3;
int *x;
int secim = 1;
int secim2=1;
int secim3=1;
int masa_numara;
int*a=&masa_numara;
while (secim!=0)
{
    printf("\n\t\t-KAMPUSNET KAFEYE HOSGELDINIZ-\n\n");
    printf("1-Isletme Girisi\n");
    printf("2-Musteri Girisi\n");
    printf("0-cikis\n");
    printf("Yapmak istediginiz islemi seciniz: ");
    scanf("%d", &secim);
 switch (secim)
 {
    case 0:
    masa_kayit(net);
    zaman_kaydet();
    printf("Programdan cikis yapiliyor...\n");
    break;
    case 1:
    printf("sifreyi giriniz: ");
    scanf("%d",&sifre2);
    if (sifre2==sifre)
    {
        
        printf("Giriş başarılı!\n");
        secim2 = 1; // İşletme girişi menüsünü yeniden başlat
        while (secim2!=0)
        {
            
        
        
    printf("\n1-Masa ac\n");
    printf("2-Masa kapat\n");
    printf("3-Siparis Durumu\n");
    printf("4-Kullanici yorumlari\n");
    printf("Yapmak istediginiz islemi seciniz: ");
    scanf("%d", &secim2);
    if (secim2==1)
    {
         if (oturum==3)
    {
        printf("\nEski oturum tekrar yuklensin mi?\n");
        printf("1-Evet\n");
        printf("2-Hayir\n");
        scanf("%d", &oturum);
        if (oturum==1)
        {
            atama2(net);
        }
        else{
            atama(net);
        }
    }
        
        masa_yazdir(net);
        masa_ac(net);
    }
    else if (secim2==2)
    {
        if (oturum==1)
        {
        masa_yazdir(net);
        masa_kapat(net,x);
        }
        else
        {
        masa_yazdir(net);
        masa_kapat2(net,x);
        }
        
        
    }
  
    else if (secim2==3)
    {
        okuma();
    }
    
    else if (secim2==4)
    {
        deger_dosyasi_okuma();
    }
    }
    if(sifre!=sifre2){
        printf("sifre yanlis\n");
    }
    }
    else
    {
        printf("giremediniz\n");
    }
    break;
    case 2:
    
    
    printf("Hangi masada oturuyorsunuz: ");
    scanf("%d",&masa_numara);
    if (net->masa[masa_numara-1]==1)
    {
    printf("1-Siparis ver\n");
    printf("2-Isletmeyi degerlendir\n");
    printf("0- cikis\n");
    printf("Yapmak istediginiz islemi seciniz: ");
    scanf("%d", &secim3);
    if (secim3==1){
        menu();
        while (1)
        {
            fatura1=siparis_ver(a,net);
            fatura+=fatura1;
            if (fatura1==0)
            {
                break;
            }
            
        }
        int *p=&fatura;
        x=p;
        printf("siparis ucreti: %d TL\n", fatura);
        fatura=0;
    } 
      else if (secim3==2)
    {
        isletme_degerlendir();
    }
    }
    else{
        printf("bu masa kapalidir\n");
    
    }
    
    break;
  }
}


    return 0;
} 




void masa_kayit(a1*net)
{
FILE*ptr;
ptr=fopen("masa_kayit.txt", "w");
if (ptr==NULL){
    printf("dosya acilamadi");


}
else
{
    for (int i = 0; i < 30; i++)
    {
        fprintf(ptr,"%d   %d\n",net->masa[i],net->fatura[i]);
    }
    
}
}

void masa_ac(a1*net){

printf("\nIslem bittikten sonra '0' i tuslayiniz.");
printf("\nHangi masa acilsin: ");
scanf("%d", &net -> masa_secim);


if (net -> masa[net -> masa_secim - 1] == 1){
    printf("\nUYARI!! BU MASA ZATEN ACIK\n");
}
else{
    net -> masa[net -> masa_secim - 1] = 1;
    net->fatura[net->masa_secim - 1] = 0;
    net->start_time = clock();
   
}

if (net->masa_secim!=0)
{
    return masa_ac(net);
}
else
{
    masa_yazdir(net);
}


}

void masa_kapat(a1*net, int *p) {
    printf("\nIslem bittikten sonra '0' i tuslayiniz.");
    printf("\nHangi masa kapatilsin: ");
    scanf("%d", &net->masa_secim);
    if (net->masa_secim==0)
    {
        return masa_yazdir(net);
    }
    

    if (net->masa[net->masa_secim - 1] == 0) {
        printf("\nUYARI!! BU MASA ZATEN KAPALI\n");
    } 
    else if(net->masa[net->masa_secim - 1] == 1) {
        net->masa[net->masa_secim - 1] = 0;  // Masa kapalı
        net->end_time = clock();  // Bitiş zamanı
        double elapsed_time = ((double)(net->end_time - net->start_time)) / CLOCKS_PER_SEC;
        elapsed_time+=gecen_sure_hesapla();

        // Saat, dakika ve saniye cinsine dönüştürme
        int hours = (int)(elapsed_time) / 3600;
        int minutes = ((int)(elapsed_time) % 3600) / 60;
        int seconds = (int)(elapsed_time) % 60;

      
        
        printf("\nMasa %d kapandi. Gecen sure: %02d:%02d:%02d\n", net->masa_secim, hours, minutes, seconds);
        net->fatura_s = hours * 25 + minutes * 1.5 + 20;  // Masa ücreti hesapla
        printf("Masa borcunuz: %d TL\n", net->fatura_s);
        printf("Toplam borcunuz: %d TL\n", net->fatura[net->masa_secim - 1] + net->fatura_s); // Masa faturası + zaman ücreti
    }

    if (net->masa_secim != 0) {
        return masa_kapat(net, p);
    }
}

void masa_kapat2(a1*net, int *p) {
    printf("\nIslem bittikten sonra '0' i tuslayiniz.");
    printf("\nHangi masa kapatilsin: ");
    scanf("%d", &net->masa_secim);
    if (net->masa_secim==0)
    {
        return masa_yazdir(net);
    }
    

    if (net->masa[net->masa_secim - 1] == 0) {
        printf("\nUYARI!! BU MASA ZATEN KAPALI\n");
    } 
    else if(net->masa[net->masa_secim - 1] == 1) {
        net->masa[net->masa_secim - 1] = 0;  // Masa kapalı
        net->end_time = clock();  // Bitiş zamanı
        double elapsed_time = ((double)(net->end_time - net->start_time)) / CLOCKS_PER_SEC;
        

        // Saat, dakika ve saniye cinsine dönüştürme
        int hours = (int)(elapsed_time) / 3600;
        int minutes = ((int)(elapsed_time) % 3600) / 60;
        int seconds = (int)(elapsed_time) % 60;

      
        
        printf("\nMasa %d kapandi. Gecen sure: %02d:%02d:%02d\n", net->masa_secim, hours, minutes, seconds);
        net->fatura_s = hours * 25 + minutes * 1.5 + 20;  // Masa ücreti hesapla
        printf("Masa borcunuz: %d TL\n", net->fatura_s);
        printf("Toplam borcunuz: %d TL\n", net->fatura[net->masa_secim - 1] + net->fatura_s); // Masa faturası + zaman ücreti
    }

    if (net->masa_secim != 0) {
        return masa_kapat2(net, p);
    }
}

void isletme_degerlendir()
{
a1*net;
FILE*ptr;
char ad_soyad[30];
int yildiz;
char yorum[300];
ptr=fopen("deger.txt", "a");
if (ptr==NULL){
    printf("dosya acilamadi\n");


}
else{
    printf("Ad-soyad giriniz:");
    scanf("%s", ad_soyad);
    printf("isletmemizi nasil buldunuz 1 den 5 e kadar rakmlarla degerlendiriniz:  ");
    scanf("%d",&yildiz);
    printf("yorumunuzu giriniz  :");
    scanf(" %[^\n]", yorum);
    fprintf(ptr,"Ad-soyad: %s ", ad_soyad);
    fprintf(ptr,"Puan ve yorum: %d yildiz  %s\n",yildiz,yorum);
    fclose(ptr);
} 
}

void atama2(a1 *net){
    FILE *ptr;
    int satir,siparis; 
    int i=0;

    
    ptr = fopen("masa_kayit.txt", "r");
    if (ptr == NULL) {
        printf("Dosya okunamadi.\n");
        return;
    }

    for (int i = 0; i < 30; i++)
    {
        fscanf(ptr,"%d   %d",&satir,&siparis);
        net->masa[i]=satir;
        net->fatura[i]=siparis;
    }
    

    
    fclose(ptr);
    
}

void atama(a1 *net){

    for (int i = 0; i < 30; i++)
    {
        net->masa[i] = 0;
       
       
}
}

void masa_yazdir(a1*net)
{
    for (int  i = 0; i < 30; i++)
    {
    if (i % 5 == 0){
        printf("\n\n\n\n\n");
    }
    if (net->masa[i] == 1){
        if (i<10)
        {
            printf("\033[32m%d - ON         \033[0m ", i + 1);   
        }
        else{
            printf("\033[32m%d - ON        \033[0m ", i + 1);
        }
        
        
    }
    else{
        if (i<10)
        {
           printf("\033[31m%d - OFF        \033[0m ", i + 1);
        }
        else 
        {
            printf("\033[31m%d- OFF        \033[0m ", i + 1);
        }
        
    }
}
}

void menu()
{ 
    printf("   -SICAK ICEKLER-   -FIYAT-              -SOGUK ICECEKLER-       -FIYAT-         -ATISTIRMALIKLAR-     -FIYAT-                      -YEMEKLER-                              -FIYAT-\n");
    printf("\033[31m 1-Cay \033[0m               -10TL-\033[36m          11-Coca Cola\033[0m                 -35TL-\033[33m        21-Ulker Albeni\033[0m         -15TL-\033[38;5;208m        31-Maydonoz Doner Menu (icecek + patates + tatli)\033[0m     -170TL-     \n");
    printf("\033[31m 2-Nescafe\033[0m            -15TL-\033[36m          12-Pepsi\033[0m                     -35TL-\033[33m        22-Ulker Caramio\033[0m        -15TL-\033[38;5;208m        32-Zater Doner Menu (icecek + patates)\033[0m                -150TL-     \n");
    printf("\033[31m 3-Sicak Cikolata\033[0m     -20TL-\033[36m          13-Fanta\033[0m                     -35TL-\033[33m        23-Ulker Laviva\033[0m         -15TL-\033[38;5;208m        33-Hatay Antakya Doner Menu (icecek + patates + tatli)\033[0m-160TL-       \n");
    printf("\033[31m 4-Salep\033[0m              -20TL-\033[36m          14-Zafer Gazoz\033[0m               -20TL-\033[33m        24-Ulker Gofret\033[0m         -10TL-\033[38;5;208m        34-Pau Doner Menu (icecek + patates)\033[0m                  -155TL-       \n");
    printf("\033[31m 5-Nane Limon\033[0m         -25TL-\033[36m          15-Lipton Ice Tea (seftali)\033[0m  -25TL-\033[33m        25-Eti Karam\033[0m            -15TL-\033[38;5;208m        35-Mc Donald's Menu (icecek + patates)\033[0m                -210TL-        \n");
    printf("\033[31m 6-Kusburnu Cayi\033[0m      -25TL-\033[36m          16-Lipton Ice Tea (limon)\033[0m    -25TL-\033[33m        26-Eti Browni\033[0m           -15TL-\033[38;5;208m        36-Burger King Menu (icecek + patates)\033[0m                -200TL-       \n");
    printf("\033[31m 7-Ada Cayi\033[0m           -25TL-\033[36m          17-Monster Enerji Icecegi\033[0m    -45TL-\033[33m        27-Eti Canga\033[0m            -15TL-\033[38;5;208m        37-Popeys Menu (icecek + patates)\033[0m                     -200TL-       \n");
    printf("\033[31m 8-Ihlamur\033[0m            -25TL-\033[36m          18-Redbull Enerji Icecegi\033[0m    -45TL-\033[33m        28-Saklikoy Biskuvi\033[0m     -10TL-\033[38;5;208m        38-Sbarro Menu (icecek + patates)\033[0m                     -170TL-      \n");
    printf("\033[31m 9-Oralet (muzlu)\033[0m     -25TL-\033[36m          19-Nescafe Express\033[0m           -40TL-\033[33m        29-Cizi Biskuvi\033[0m         -10TL-\033[38;5;208m        39-Dominos Pizza Menu (icecek + patates)\033[0m              -210TL-     \n");
    printf("\033[31m10-Oralet (cilekli)\033[0m   -25TL-\033[36m          20-Churchill\033[0m                 -20TL-\033[33m        30-Biskrem Biskuvi\033[0m      -10TL-\033[38;5;208m        40-Arbys Menu (icecek + patates)\033[0m                      -200TL-      \n");
}

int siparis_ver(int *a, a1* net){

int sec;    
    printf("\nseciminiz bittikten sonra '0' i tuslayiniz.\n");
    printf("lutfen seciminizi yapiniz: ");
    scanf("%d", &sec);
    siparis(sec, a);
    
 int fiyat = 0;
    switch (sec) {
        case 0:
            break;
        case 1:
            fiyat = 10;
            break;
        case 2:
            fiyat = 15;
            break;
        case 3:
            fiyat = 20;
            break;
        case 4:
            fiyat = 20;
            break;
        case 5:
            fiyat = 25;
            break;
        case 6:
            fiyat = 25;
            break;
        case 7:
            fiyat = 25;
            break;
        case 8:
            fiyat = 25;
            break;
        case 9:
            fiyat = 25;
            break;
        case 10:
            fiyat = 25;
            break;
        case 11:
            fiyat = 35;
            break;
        case 12:
            fiyat = 35;
            break;
        case 13:
            fiyat = 35;
            break;
        case 14:
            fiyat = 20;
            break;
        case 15:
            fiyat = 25;
            break;
        case 16:
            fiyat = 25;
            break;
        case 17:
            fiyat = 45;
            break;
        case 18:
            fiyat = 45;
            break;
        case 19:
            fiyat = 40;
            break;
        case 20:
            fiyat = 20;
            break;
        case 21:
            fiyat = 15;
            break;
        case 22:
            fiyat = 15;
            break;
        case 23:
            fiyat = 15;
            break;
        case 24:
            fiyat = 10;
            break;
        case 25:
            fiyat = 15;
            break;
        case 26:
            fiyat = 15;
            break;
        case 27:
            fiyat = 15;
            break;
        case 28:
            fiyat = 10;
            break;
        case 29:
            fiyat = 10;
            break;
        case 30:
            fiyat = 10;
            break;
        case 31:
            fiyat = 170;
            break;
        case 32:
            fiyat = 150;
            break;
        case 33:
            fiyat = 160;
            break;
        case 34:
            fiyat = 155;
            break;
        case 35:
            fiyat = 210;
            break;
        case 36:
            fiyat = 200;
            break;
        case 37:
            fiyat = 200;
            break;
        case 38:
            fiyat = 170;
            break;
        case 39:
            fiyat = 210;
            break;
        case 40:
            fiyat = 200;
            break;
        default:
            printf("lutfen gecerli bir secim yapiniz");
            return siparis_ver(a, net);
    }

    // Her masanın faturasını güncelle
    net->fatura[*a - 1] += fiyat;
    return fiyat;
}

void okuma() {
    FILE *ptr;
    char satir[150]; 
    int sonuc = 0;

    
    ptr = fopen("SIPARISLER.txt", "r");
    if (ptr == NULL) {
        printf("Dosya okunamadi.\n");
        return;
    }

    
    while (fgets(satir, sizeof(satir), ptr) != NULL) {
        sonuc = 1;
        printf("%s", satir); 
    }

    
    if (sonuc == 0) {
        printf("Sipariş yok.\n");
    }

    
    fclose(ptr);
}

void siparis(int siparis,int *a){
a1*net;
FILE*ptr;
ptr=fopen("SIPARISLER.txt", "a");
if (ptr==NULL){
    printf("dosya acilamadi");


}
else{
    if (siparis!=0){
    fprintf(ptr,"%d. masa\t",*a);
    }
    
switch (siparis)
{
    case 0:
    fprintf(ptr,"\n");
    break;
    case 1:
    fprintf(ptr,"Cay\n");
    break;
    case 2:
    fprintf(ptr,"Nescafe\n");
    break;
    case 3:
    fprintf(ptr,"Sicak Cikolata\n");
    break;
    case 4:
    fprintf(ptr,"Salep\n");
    break;
    case 5:
    fprintf(ptr,"Nane Limon\n");
    break;
    case 6:
    fprintf(ptr,"Kusburnu Cayi\n");
    break;
    case 7:
    fprintf(ptr,"Ada Cayi\n");
    break;
    case 8:
    fprintf(ptr,"Ihlamur\n");
    break;
    case 9:
    fprintf(ptr,"Oralet (muzlu)\n");
    break;
    case 10:
    fprintf(ptr,"Oralet (cilekli)\n");
    break;
    case 11:
    fprintf(ptr,"Coca Cola\n");
    break;
    case 12:
    fprintf(ptr,"Pepsi\n");
    break;
    case 13:
    fprintf(ptr,"Fanta\n");
    break;
    case 14:
    fprintf(ptr,"Zafer Gazoz\n");
    case 15:
    fprintf(ptr,"Lipton Ice Tea (seftali)\n");
    break;
    case 16:
    fprintf(ptr,"Limon Ive Tea (limon)\n");
    break;
    case 17:
    fprintf(ptr,"Monster Enerji Icecegi\n");
    break;
    case 18:
    fprintf(ptr,"Redbull Enerji Icecegi\n");
    break;
    case 19:
    fprintf(ptr,"Nescafe Express\n");
    break;
    case 20:
    fprintf(ptr,"Churchill\n");
    break;
    case 21:
    fprintf(ptr,"Ulker Albeni\n");
    break;
    case 22:
    fprintf(ptr,"Ulker Caramio\n");
    break;
    case 23:
    fprintf(ptr,"Ulker Laviva\n");
    break;
    case 24:
    fprintf(ptr,"Ulker Gofret\n");
    break;
    case 25:
    fprintf(ptr,"Eti Karam\n");
    break;
    case 26:
    fprintf(ptr,"Eti Browni\n");
    break;
    case 27:
    fprintf(ptr,"Eti Canga\n");
    break;
    case 28:
    fprintf(ptr,"Saklikoy Biskuvi\n");
    break;
    case 29:
    fprintf(ptr,"Cizi Biskuvi\n");
    break;
    case 30:
    fprintf(ptr,"Biskrem Biskuvi\n");
    break;
    case 31:
    fprintf(ptr,"Maydonoz Doner Menu (icecek + patates + tatli)\n");
    break;
    case 32:
    fprintf(ptr,"Zater Doner Menu (icecek + patates)\n");
    break;
    case 33:
    fprintf(ptr,"Hatay Doner Menu (icecek + patates + tatli)\n");
    break;
    case 34:
    fprintf(ptr,"Pau Doner Menu (icecek + patates)\n");
    break;
    case 35:
    fprintf(ptr,"Mc Donald's Menu (icecek + patates)\n");
    break;
    case 36:
    fprintf(ptr,"Burger King Menu (icecek + patates)\n");
    break;
    case 37:
    fprintf(ptr,"Popeyes Menu (icecek + patates)\n");
    break;
    case 38: 
    fprintf(ptr,"Sbarro Menu (icecek + patates)\n");
    break;
    case 39:
    fprintf(ptr,"Dominos Pizza Menu (icecek + patates)\n");
    break;
    case 40:
    fprintf(ptr,"Arbys Menu (icecek + patates)\n");
    break;

    
    
}
}
fclose(ptr);
}

void deger_dosyasi_okuma() {
    FILE *ptr;
    char satir[300]; 
    int sonuc = 0;

    
    ptr = fopen("deger.txt", "r");
    if (ptr == NULL) {
        printf("Deger dosyasi acilamadi.\n");
        return;
    }

    
    printf("\n--- Isletme Degerlendirme Yorumlari ---\n");
    while (fgets(satir, sizeof(satir), ptr) != NULL) {
        sonuc = 1;
        printf("%s", satir); 
    }

    
    if (sonuc == 0) {
        printf("Henüz değerlendirme yapılmamış.\n");
    }

  
    fclose(ptr);
}

int toplam_tutar(int *f,int *p){

int toplam_tutar = *f+*p;
return toplam_tutar;

}

void zaman_kaydet() {
    FILE *ptr = fopen("zaman_kayit.txt", "w");
    if (ptr == NULL) {
        printf("Zaman kaydi dosyasi acilamadi.\n");
        return;
    }

    time_t simdi = time(NULL);  // Şimdiki zaman
    fprintf(ptr, "%ld\n", simdi);  // Zamanı kaydet
    fclose(ptr);
    printf("Kapanis zamani kaydedildi: %s", ctime(&simdi));
}

double gecen_sure_hesapla() {
    FILE *ptr = fopen("zaman_kayit.txt", "r");
    if (ptr == NULL) {
        printf("Onceki zaman kaydi bulunamadi.\n");
        
    }

    time_t onceki_zaman;
    fscanf(ptr, "%ld", &onceki_zaman);
    fclose(ptr);

    time_t simdi = time(NULL);  // Şimdiki zaman
    double fark = difftime(simdi, onceki_zaman);  // Zaman farkı saniye cinsinden

    printf("Program kapaliyken gecen sure: %.0f saniye\n", fark);
    return fark;
}