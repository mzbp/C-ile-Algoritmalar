#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define sonsuz 100000
int i=1,a;                      //ihtiyac�m olan de�i�kenleri belirledim 
int **matris;
char *karekter;
bool *durum; 
int ulasma=1,ek=1,islem=1;
bool *durum2;
int *maliyet;
int *parent;
void dosyadan_al();         //ihtiyac�m olan fonksiyonlar� belirliyorum
void matris_olustur();
void matris_goster();
int dugum_derece();
void graf_kenar();
void comple_graf();
void dugum_durum();
void mydfs(int root,bool durum[]);
void dugum_kontrol();
int myprim_mst();
void myprim(int);
void prim_goster(int);
int main(){                        //tan�mlad���m fonsiyonlar� �a��r�yorum 
  dosyadan_al();
  matris_olustur();
  matris_goster();
  int devam=1;
  while(devam==1){
  	int derece=dugum_derece();
  if(derece!=-1)
     printf("GIRDIGINIZ DUGUMUN DERECESI--->%d\n",derece);
   else
     printf("GIRDIGINIZ DUGUM NUMARASI HATALI\n");
	printf("Devam etmek icin '0' basiniz.\nYeni dugum numarasi hesaplamak icin '1' basiniz--->");    
    scanf("%d",&devam);
  }
  graf_kenar();
  comple_graf();
  dugum_durum();	 	
  printf("\n-DFS--ULASMA ZAMANLARI---\n");
  mydfs(0,durum);
  dugum_kontrol();
  int a=1,sayi;
  while(a==1){
  printf("\n\nPRIM ALGORITMASI ICIN DUGUM NUMARASI GIRINIZ-->");
  scanf("%d",&sayi);
  printf("PRIM ALGORITMASI ILE MINIMUM SPANINIG TREE");
  printf("\nU---V\n");
  myprim(sayi);
  printf("\ndevam etmek icin '1' basiniz");
  scanf("%d",a);
 }
  system("pause");
}

void dosyadan_al(){
  	// bu fonksiyon dosyadan matrisi almaya yar�yor 
 FILE *dosya;
   	dosya=fopen("KomsulukMatrisi.txt","r");
	while(!feof(dosya)){
    a=getc(dosya);
    if(a==10){  //a=10 deme sebebim 10 asc�� tabloda char olarak kar��l��� yeni sat�ra ge�me i�lemidir 
    i++;       	//dosya ka� sat�rl� bunu bulmaya yar�yor b�ylece �ift boyutlu matrisin ka�a ka� olu�turaca��m�z� anlar�z 
	}
     }
	 karekter=new char[i*i*2];
	 int d=0;   
    dosya=fopen("KomsulukMatrisi.txt","r");
		while(!feof(dosya)){
		 karekter[d]=getc(dosya); //dosyadaki t�m karekterleri bir boyutlu diziye aktar�yoruz
      d++;
     }	
}
void matris_olustur(){
	matris=new int*[i];
	for(int k=0; k<i; k++){
		matris[k]=new int[i]; //�ift boyutlu matris olu�turuyoruz
	}
	char karekter2[1];
	 int j=0;
   for(int k=0; k<i; k++){
   	for(int a=0; a<i; a++){
   			karekter2[0]=karekter[j];     //dosyadan tek boyutlu matrise atad���m�z karekterleri burda int tipinde �ift boyutlu matrise aktar�yorum
		 	matris[k][a]=atoi(karekter2);//burda atoi fonksiyonu karekter dizisindeki sayilari int matrisine atmam�za yar�yor
			   j=j+2;                     //burda j'yi iki art�rma sebebim karekter dizisindeki bosluk ve enter karekterlerini atlamak 
	   }
   }
}
void matris_goster(){
	printf("GRAFIN KOMSULUK MATRISI ILE GOSTERIMI\n");
    for(int k=0; k<i; k++){
   	for(int a=0; a<i; a++){
      printf("%d ",matris[k][a]);
      }
      printf("\n");
   }   	
}
int dugum_derece(){
	
	int dugum,derece=0;
   printf("\nLUTFEN %d*%d MATRISINE UYUMLU DUGUM NUMARASI GIRINIZ------>>",i,i);
   scanf("%d",&dugum);
   if(dugum<i&&dugum>=0){
   for(int a=0; a<i; a++){
   	      if(matris[dugum][a]!=0){  //burda kullan�c�dan al�nan dugumun sat�rlar�ndaki 0 olmayan ka� sayi varsa hesaplan�r derece olarak yaz�l�r
			 derece++;
			 }   
       }
		  return derece;
		  }	  
    else{
          return -1;
	  }	 
}
void graf_kenar(){
	int kenar=0;
   for(int k=0; k<i; k++){ //kenar bulmak i�in graftaki 0 olmayan sayilar hesaplan�r
   	for(int a=0; a<i; a++){
      if(matris[k][a]!=0){
      	kenar++;
	  }
      }
   }
   printf("\n\nGRAFIN KENAR SAYISI---->%d",kenar); 
}
void comple_graf(){
	int comple=1;
   for(int k=0; k<i; k++){ //comple graf i�in k��eler hari� di�er kenarlar�n olup olmad��� kontrol edilir 
   	for(int a=0; a<i; a++){ 
   		if(k!=a){
		   if(matris[k][a]==0){
       comple=0;
	  }
	  }
      }
   }
   if(comple==1){
   	printf("\n\nGRAF COMPLETE GRAF'TIR\n");
   }
   else{
   	printf("\n\nGRAF COMPLE GRAF DEGILDIR\n");
   }
}
void dugum_durum(){
	durum=new bool[i];
	for(int a=0; a<i; a++) //bunu yapma amac�m dfs kodunda u�ranm�� dugumleri tutmak
	durum[a]=false;
}
void mydfs(int root,bool durum[]){
	durum[root]=true;  
	printf("\n--%d---ulasma->%d ",root,ulasma); // burda u�ranm�� dugumleri s�rayla ekrana bas�yorum 
	for(int d=0; d<i; d++){
		if(matris[root][d]!=0 && durum[d]==false){ //burda u�ranmam�� dugumu buluyorum ve kenar varsa if i�ine giriyorum
		    ulasma++;                //bunu yazma sebebim di�er d���me ge�i� s�ras�nda ka� ad�m at�lm�� bunu tutmak 
		    ek++;                    //bir dugumle i�im bitti�inde i�leme sayisini tutmak i�in yazd�m
			mydfs(d,durum);         //buldu�um dugumu tekrar foksiyonu �a��r�p yolluyorum
			ulasma++;
			ek++;   
		}
		
	}
		printf(" --%d---islem->%d",root,islem+ek);  //burda atlam��sa i�lem demektir root de�erindeki dugumle i�im bitmi�tir griden siyaha d�n��m��t�r
                                                    //ve siyaha d�n��en dugumun i�lem say�s� ekrana bas�l�r		
         
}
void dugum_kontrol(){
   for(int x=0; x<i; x++){//bu fonksiyonu yazma amac�m u�ranmam�� dugumu bulup dfs ile ziyaret etmek b�ylece ba�lant�s� olmayan dugume ge�i� yapar�m 
    	if(durum[x]==0){
    		ulasma=ulasma+islem+1; //bunlar� tekrar burda yazma sebebim fonksiyonda ula�ma ad�m�n en son dugumun i�lem ad�m� say�s�ndan ba�latmak
    		ek=ek+islem+1;
    		mydfs(x, durum);       //u�ranmam�� dugum mydfs fonksiyonu �a�r�l�p yollan�r
		} 
	}
}

int myprim_mst(){
	int min=sonsuz;    //minumum maliyeti ba�ta sonsuz tan�ml�yorum 
	int minindex;       
	for(int j=0; j<i; j++){
		if(durum2[j]==false && maliyet[j]<min){  //maliyeti en d���k olan� bulmam�za yar�yor
			min=maliyet[j];                                          
		    minindex=j;         
		}
	}
	return minindex;        //minimum maliyetin indisini d�d�r�p ana prim fonksiyona yolluyoruz
}

void myprim(int a){   
    parent=new int[i];  //dugum atas�n� tutmak ve g�ncellemek i�in
    maliyet=new int[i];  //dugum maliyetini tutmak i�in ve g�ncellemek i�in
    durum2=new bool[i];  //ikinci bir durum tan�ml�yorum dfs'de ki durumla kar��mas�n diye dugumun ziyaret edilip edilmedi�ini tutar
	for(int j=0; j<i; j++){
	durum2[j]=false;         
	maliyet[j]=sonsuz; 
	}
	maliyet[a]=0;      //kullan�c�dan ald���m dugum numaras�n�n maliyetini 0 ve atas�n�n olmad���n� tan�ml�yorum
	parent[a]=-1;
 	for(int j=0; j<i; j++){  //burdaki for ana for dugum sayisi kadar i�lem yapt�rmam�za yarar
      int u=myprim_mst();	  //myprim fonksiyonundan minumum indis al�n�r
	  durum2[u]=true;          //minumum indisin dugumunu ziyaret edildi olarak at�yoruz  
	  for(int k=0; k<i; k++){
	  	if(matris[u][k] && durum2[k]==false && matris[u][k]<maliyet[k]){ //burda buldugumuz minumum maliyetli dugumun gidebilece�i maliyeti en d���k yol bulunur 
		  
	  	maliyet[k]=matris[u][k];      //gidilen dugumun maliyeti at�l�r
	  	parent[k]=u;                  //gidilen dugumun atas� tutulur gerekirse gucellenir
	   }
	  }
	}
prim_goster(a);                 
}
void prim_goster(int a){
	printf(" ---%d--->%d\n",a,matris[a][a]);//burda minumum tree ekrana atas� ve maliyeti ile birlikte bas�l�r 
	for(int j=0; j<i; j++){
		if(j!=a)
		printf("%d---%d--->%d\n",parent[j],j,matris[j][parent[j]]);
	}
}
