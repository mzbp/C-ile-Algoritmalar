#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define sonsuz 100000
int i=1,a;                      //ihtiyacým olan deðiþkenleri belirledim 
int **matris;
char *karekter;
bool *durum; 
int ulasma=1,ek=1,islem=1;
bool *durum2;
int *maliyet;
int *parent;
void dosyadan_al();         //ihtiyacým olan fonksiyonlarý belirliyorum
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
int main(){                        //tanýmladýðým fonsiyonlarý çaðýrýyorum 
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
  	// bu fonksiyon dosyadan matrisi almaya yarýyor 
 FILE *dosya;
   	dosya=fopen("KomsulukMatrisi.txt","r");
	while(!feof(dosya)){
    a=getc(dosya);
    if(a==10){  //a=10 deme sebebim 10 ascýý tabloda char olarak karþýlýðý yeni satýra geçme iþlemidir 
    i++;       	//dosya kaç satýrlý bunu bulmaya yarýyor böylece çift boyutlu matrisin kaça kaç oluþturacaðýmýzý anlarýz 
	}
     }
	 karekter=new char[i*i*2];
	 int d=0;   
    dosya=fopen("KomsulukMatrisi.txt","r");
		while(!feof(dosya)){
		 karekter[d]=getc(dosya); //dosyadaki tüm karekterleri bir boyutlu diziye aktarýyoruz
      d++;
     }	
}
void matris_olustur(){
	matris=new int*[i];
	for(int k=0; k<i; k++){
		matris[k]=new int[i]; //çift boyutlu matris oluþturuyoruz
	}
	char karekter2[1];
	 int j=0;
   for(int k=0; k<i; k++){
   	for(int a=0; a<i; a++){
   			karekter2[0]=karekter[j];     //dosyadan tek boyutlu matrise atadýðýmýz karekterleri burda int tipinde çift boyutlu matrise aktarýyorum
		 	matris[k][a]=atoi(karekter2);//burda atoi fonksiyonu karekter dizisindeki sayilari int matrisine atmamýza yarýyor
			   j=j+2;                     //burda j'yi iki artýrma sebebim karekter dizisindeki bosluk ve enter karekterlerini atlamak 
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
   	      if(matris[dugum][a]!=0){  //burda kullanýcýdan alýnan dugumun satýrlarýndaki 0 olmayan kaç sayi varsa hesaplanýr derece olarak yazýlýr
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
   for(int k=0; k<i; k++){ //kenar bulmak için graftaki 0 olmayan sayilar hesaplanýr
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
   for(int k=0; k<i; k++){ //comple graf için köþeler hariç diðer kenarlarýn olup olmadýðý kontrol edilir 
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
	for(int a=0; a<i; a++) //bunu yapma amacým dfs kodunda uðranmýþ dugumleri tutmak
	durum[a]=false;
}
void mydfs(int root,bool durum[]){
	durum[root]=true;  
	printf("\n--%d---ulasma->%d ",root,ulasma); // burda uðranmýþ dugumleri sýrayla ekrana basýyorum 
	for(int d=0; d<i; d++){
		if(matris[root][d]!=0 && durum[d]==false){ //burda uðranmamýþ dugumu buluyorum ve kenar varsa if içine giriyorum
		    ulasma++;                //bunu yazma sebebim diðer düðüme geçiþ sýrasýnda kaç adým atýlmýþ bunu tutmak 
		    ek++;                    //bir dugumle iþim bittiðinde iþleme sayisini tutmak için yazdým
			mydfs(d,durum);         //bulduðum dugumu tekrar foksiyonu çaðýrýp yolluyorum
			ulasma++;
			ek++;   
		}
		
	}
		printf(" --%d---islem->%d",root,islem+ek);  //burda atlamýþsa iþlem demektir root deðerindeki dugumle iþim bitmiþtir griden siyaha dönüþmüþtür
                                                    //ve siyaha dönüþen dugumun iþlem sayýsý ekrana basýlýr		
         
}
void dugum_kontrol(){
   for(int x=0; x<i; x++){//bu fonksiyonu yazma amacým uðranmamýþ dugumu bulup dfs ile ziyaret etmek böylece baðlantýsý olmayan dugume geçiþ yaparým 
    	if(durum[x]==0){
    		ulasma=ulasma+islem+1; //bunlarý tekrar burda yazma sebebim fonksiyonda ulaþma adýmýn en son dugumun iþlem adýmý sayýsýndan baþlatmak
    		ek=ek+islem+1;
    		mydfs(x, durum);       //uðranmamýþ dugum mydfs fonksiyonu çaðrýlýp yollanýr
		} 
	}
}

int myprim_mst(){
	int min=sonsuz;    //minumum maliyeti baþta sonsuz tanýmlýyorum 
	int minindex;       
	for(int j=0; j<i; j++){
		if(durum2[j]==false && maliyet[j]<min){  //maliyeti en düþük olaný bulmamýza yarýyor
			min=maliyet[j];                                          
		    minindex=j;         
		}
	}
	return minindex;        //minimum maliyetin indisini dödürüp ana prim fonksiyona yolluyoruz
}

void myprim(int a){   
    parent=new int[i];  //dugum atasýný tutmak ve güncellemek için
    maliyet=new int[i];  //dugum maliyetini tutmak için ve güncellemek için
    durum2=new bool[i];  //ikinci bir durum tanýmlýyorum dfs'de ki durumla karýþmasýn diye dugumun ziyaret edilip edilmediðini tutar
	for(int j=0; j<i; j++){
	durum2[j]=false;         
	maliyet[j]=sonsuz; 
	}
	maliyet[a]=0;      //kullanýcýdan aldýðým dugum numarasýnýn maliyetini 0 ve atasýnýn olmadýðýný tanýmlýyorum
	parent[a]=-1;
 	for(int j=0; j<i; j++){  //burdaki for ana for dugum sayisi kadar iþlem yaptýrmamýza yarar
      int u=myprim_mst();	  //myprim fonksiyonundan minumum indis alýnýr
	  durum2[u]=true;          //minumum indisin dugumunu ziyaret edildi olarak atýyoruz  
	  for(int k=0; k<i; k++){
	  	if(matris[u][k] && durum2[k]==false && matris[u][k]<maliyet[k]){ //burda buldugumuz minumum maliyetli dugumun gidebileceði maliyeti en düþük yol bulunur 
		  
	  	maliyet[k]=matris[u][k];      //gidilen dugumun maliyeti atýlýr
	  	parent[k]=u;                  //gidilen dugumun atasý tutulur gerekirse gucellenir
	   }
	  }
	}
prim_goster(a);                 
}
void prim_goster(int a){
	printf(" ---%d--->%d\n",a,matris[a][a]);//burda minumum tree ekrana atasý ve maliyeti ile birlikte basýlýr 
	for(int j=0; j<i; j++){
		if(j!=a)
		printf("%d---%d--->%d\n",parent[j],j,matris[j][parent[j]]);
	}
}
