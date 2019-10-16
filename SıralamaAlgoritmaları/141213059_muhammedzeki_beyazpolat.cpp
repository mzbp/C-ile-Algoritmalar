#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include <sys/time.h>
int heapSize;
float getdiff(struct timeval endtv, struct timeval starttv){
    float diff=0;
    diff=(endtv.tv_sec-starttv.tv_sec)*1000000+(endtv.tv_usec-starttv.tv_usec);
    return diff;}
void Heapify(int dizi[], int i)
{
  int l = 2 * i + 1;
  int r = 2 * i + 2;
  int buyuk;

  if(l <= heapSize && dizi[l] > dizi[i])
    buyuk = l;
  else
    buyuk = i;
  if(r <= heapSize && dizi[r] > dizi[buyuk])
    buyuk = r;
  if(buyuk != i)
    {
      int gecici = dizi[i];
      dizi[i] = dizi[buyuk];
      dizi[buyuk] = gecici;
      Heapify(dizi, buyuk);
    }
}

void BuildHeap(int dizi[],int boyut)
{
  heapSize = boyut - 1;
  int i;
  for(i = (boyut - 1) / 2; i >= 0; i--)
    Heapify(dizi, i);
}

void myheapsort(int dizi[],int boyut)
{
  BuildHeap(dizi,boyut);
  int i;
  for(i = boyut - 1; i > 0; i--)
    {
      int gecici = dizi[heapSize];
      dizi[heapSize] = dizi[0];
      dizi[0] = gecici;
      heapSize--;
      Heapify(dizi, 0);
    }
}    
void myquicksort(int dizi[], int baslangic, int son)
{
    if(baslangic < son)
    { int gecici;
        int sol = baslangic+1, sag = son, pivot = dizi[baslangic];
        while(sag<sol)
        {
            if(dizi[sol] <= pivot)
                sol++;
            else if(dizi[sag] >= pivot)
                sag--;
            else
           gecici=dizi[sol];
           dizi[sol]=dizi[sag];
           dizi[sag]=gecici;
}
        if(dizi[sol] < pivot)
        {
        
           gecici=dizi[sol];
           dizi[sol]=dizi[baslangic];
           dizi[baslangic]=gecici;
            sol--;
        }
        else
        {
            sol--;
           gecici=dizi[sol];
           dizi[sol]=dizi[baslangic];
           dizi[baslangic]=gecici;
		}
        myquicksort(dizi, baslangic, sol);
        myquicksort(dizi, sag, son);
    }
}
void mymerge(int dizi[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = dizi[l + i];
    for (j = 0; j < n2; j++)
        R[j] = dizi[m + 1+ j];
    i = 0; 
    j = 0;
    k = l;
    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            dizi[k] = L[i];
            i++;}
        else{
            dizi[k] = R[j];
            j++;}
        k++;}
   while (i < n1)  {
        dizi[k] = L[i];
        i++;
        k++;}
  while (j < n2)  {
        dizi[k] = R[j];
        j++;
        k++;}}
void mymergesort(int dizi[], int l, int r){ 
        if (l < r)  {
        int m = l+(r-l)/2;
        mymergesort(dizi, l, m);
        mymergesort(dizi, m+1, r);
        mymerge(dizi, l, m, r);}}    
void mybubblesort(int dizi[],int boyut){
	struct timeval starttv, endtv;
    struct timezone starttz, endtz;
    gettimeofday(&starttv, &starttz);	
	int gecici;
	for(int i=0; i<boyut-1; i++){
		for(int k=0; k<boyut-i-1; k++){
			if(dizi[k]>dizi[k+1]){
			gecici=dizi[k];
			dizi[k]=dizi[k+1];
			dizi[k+1]=gecici;	}}}
    gettimeofday(&endtv, &endtz);
    float fark1=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark1);}
void myselectionsort(int dizi[],int boyut){
	struct timeval starttv, endtv;
    struct timezone starttz, endtz;
    gettimeofday(&starttv, &starttz);	
	int gecici;
	for(int i=0; i<boyut-1; i++){
		int min=i;
		for(int k=i+1; k<boyut; k++){
			if(dizi[min]>dizi[k]){
				min=k;			}}
		if(min!=i){
		gecici=dizi[i];
		dizi[i]=dizi[min];
		dizi[min]=gecici;}}
		 gettimeofday(&endtv, &endtz);
    float fark1=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark1);}  
void myinsertionsort(int dizi[],int boyut){
	struct timeval starttv, endtv;
    struct timezone starttz, endtz;
    gettimeofday(&starttv, &starttz);	
	int d,gecici;
	for(int k=1; k<boyut; k++){
	  d=k;
		while(d>0&&dizi[d-1]>dizi[d]){
			gecici=dizi[d-1];
			dizi[d-1]=dizi[d];
			dizi[d]=gecici;
		d--;}}
    gettimeofday(&endtv, &endtz);
    float fark1=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark1);}

int main(){
    struct timeval starttv, endtv;
    struct timezone starttz, endtz;
    int dizi2[10000],yedek2[10000],dizi3[50000],yedek3[50000],dizi4[100000],yedek4[100000];
	//**************sirali sayilar icin********************
	for(int i=0;i<10000;i++)
        dizi2[i]=i;
        memcpy(yedek2,dizi2,10000*sizeof(int));
    for(int i=0;i<50000;i++)
        dizi3[i]=i;
        memcpy(yedek3,dizi3,50000*sizeof(int));
    for(int i=0;i<100000;i++)
        dizi4[i]=i;
        memcpy(yedek4,dizi4,100000*sizeof(int));
    
	printf("\n--------------SIRALI SAYILAR ICIN ALGORITMA CALISMA SURELERI------------------\n");
    printf("\n\t-------10000 ELEMANLI DIZI ICIN SURELER-----\n\n");
    printf("bubble sort--->");
    mybubblesort(dizi2,10000);
    
	memcpy(dizi2,yedek2,10000*sizeof(int));
    printf("\nselection sort--->");
    myselectionsort(dizi2,10000);
    
	memcpy(dizi2,yedek2,10000*sizeof(int));
    printf("\ninsertion sort--->");
    myinsertionsort(dizi2,10000);
    
	memcpy(dizi2,yedek2,10000*sizeof(int));
    printf("\nmerge sort--->");
    gettimeofday(&starttv, &starttz);
	mymergesort(dizi2,0,10000);
    gettimeofday(&endtv, &endtz);
    float fark1=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark1);
	
	memcpy(dizi2,yedek2,10000*sizeof(int));
    printf("\nquick sort--->");
    gettimeofday(&endtv, &endtz);
	myquicksort(dizi2,0,10000);
    gettimeofday(&endtv, &endtz);
    float fark2=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark2);
    
    memcpy(dizi2,yedek2,10000*sizeof(int));
    printf("\nheap sort---->");
    gettimeofday(&endtv, &endtz);
    myheapsort(dizi2,10000);
    gettimeofday(&endtv, &endtz);
    float fark19=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark19);
     //-------------------------------------------------------------
    
    printf("\n\n\t-------50000 ELEMANLI DIZI ICIN SURELER------\n");
    printf("\nbubble sort--->");
    mybubblesort(dizi3,50000);
   
    memcpy(dizi3,yedek3,50000*sizeof(int));
    printf("\nselection sort--->");
    myselectionsort(dizi3,50000);

    memcpy(dizi3,yedek3,50000*sizeof(int));
    printf("\ninsertion sort--->");
    myinsertionsort(dizi3,50000);
    
    memcpy(dizi3,yedek3,50000*sizeof(int));
    printf("\nmerge sort--->");
    gettimeofday(&starttv, &starttz);
	mymergesort(dizi3,0,50000);
    gettimeofday(&endtv, &endtz);
    float fark3=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark3);
   
    memcpy(dizi3,yedek3,50000*sizeof(int));
    printf("\nquick sort--->");
    gettimeofday(&starttv, &starttz);
	myquicksort(dizi3,0,5000);
    gettimeofday(&endtv, &endtz);
    float fark4=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark4);
    
    memcpy(dizi3,yedek3,50000*sizeof(int));
    printf("\nheap sort---->");
    gettimeofday(&endtv, &endtz);
    myheapsort(dizi3,50000);
    gettimeofday(&endtv, &endtz);
    float fark20=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark20);
	 //----------------------------------------------------------------
    
    printf("\n\n\t-------100000 ELEMANLI DIZI ICIN SURELER-------\n\n");
    printf("bubble sort--->");
    mybubblesort(dizi4,100000);
    
    memcpy(dizi4,yedek4,100000*sizeof(int));
    printf("\nselection sort--->");
    myselectionsort(dizi4,100000);
    
    memcpy(dizi4,yedek4,100000*sizeof(int));
    printf("\ninsertion sort--->");
    myinsertionsort(dizi4,100000);
   
    memcpy(dizi4,yedek4,100000*sizeof(int));
    printf("\nmerge sort--->");
    gettimeofday(&starttv, &starttz);
    mymergesort(dizi4,0,100000);
    gettimeofday(&endtv, &endtz);
    float fark5=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark5);
    
	memcpy(dizi4,yedek4,100000*sizeof(int));
    printf("\nquick sort--->");
    gettimeofday(&starttv, &starttz);
	myquicksort(dizi4,0,100000);
    gettimeofday(&endtv, &endtz);
    float fark6=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark6);

    memcpy(dizi4,yedek4,100000*sizeof(int));
    printf("\nheap sort---->");
    gettimeofday(&endtv, &endtz);
    myheapsort(dizi4,100000);
    gettimeofday(&endtv, &endtz);
    float fark21=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark21);
	
	//**************rasgele sayilar icin********************
	for(int i=0;i<10000;i++)
        dizi2[i]=rand()%10000;
        memcpy(yedek2,dizi2,10000*sizeof(int));
    for(int i=0;i<50000;i++)
        dizi3[i]=rand()%50000;
        memcpy(yedek3,dizi3,50000*sizeof(int));
    for(int i=0;i<100000;i++)
        dizi4[i]=rand()%100000;
        memcpy(yedek4,dizi4,100000*sizeof(int));
    printf("\n\n--------------RASGELE SAYILAR ICIN ALGORITMA CALISMA SURELERI------------------\n");
    printf("\n\t-------10000 ELEMANLI DIZI ICIN SURELER-----\n\n");
    printf("bubble sort--->");
    mybubblesort(dizi2,10000);
    
	memcpy(dizi2,yedek2,10000*sizeof(int));
    printf("\nselection sort--->");
    myselectionsort(dizi2,10000);
    
	memcpy(dizi2,yedek2,10000*sizeof(int));
    printf("\ninsertion sort--->");
    myinsertionsort(dizi2,10000);
    
	memcpy(dizi2,yedek2,10000*sizeof(int));
    printf("\nmerge sort--->");
    gettimeofday(&starttv, &starttz);
	mymergesort(dizi2,0,10000);
    gettimeofday(&endtv, &endtz);
    float fark7=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark7);
	
	memcpy(dizi2,yedek2,10000*sizeof(int));
    printf("\nquick sort--->");
    gettimeofday(&endtv, &endtz);
	myquicksort(dizi2,0,10000);
    gettimeofday(&endtv, &endtz);
    float fark8=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark8);

    memcpy(dizi2,yedek2,10000*sizeof(int));
    printf("\nheap sort---->");
    gettimeofday(&endtv, &endtz);
    myheapsort(dizi2,10000);
    gettimeofday(&endtv, &endtz);
    float fark22=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark22);
	 //-------------------------------------------------------------
    
    printf("\n\n\t-------50000 ELEMANLI DIZI ICIN SURELER------\n");
    printf("\nbubble sort--->");
    mybubblesort(dizi3,50000);
   
    memcpy(dizi3,yedek3,50000*sizeof(int));
    printf("\nselection sort--->");
    myselectionsort(dizi3,50000);

    memcpy(dizi3,yedek3,50000*sizeof(int));
    printf("\ninsertion sort--->");
    myinsertionsort(dizi3,50000);
    
    memcpy(dizi3,yedek3,50000*sizeof(int));
    printf("\nmerge sort--->");
    gettimeofday(&starttv, &starttz);
	mymergesort(dizi3,0,50000);
    gettimeofday(&endtv, &endtz);
    float fark9=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark9);
   
    memcpy(dizi3,yedek3,50000*sizeof(int));
    printf("\nquick sort--->");
    gettimeofday(&starttv, &starttz);
	myquicksort(dizi3,0,50000);
    gettimeofday(&endtv, &endtz);
    float fark10=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark10);

    memcpy(dizi3,yedek3,50000*sizeof(int));
    printf("\nheap sort---->");
    gettimeofday(&endtv, &endtz);
    myheapsort(dizi3,50000);
    gettimeofday(&endtv, &endtz);
    float fark23=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark23);
	 //----------------------------------------------------------------
    
    printf("\n\n\t-------100000 ELEMANLI DIZI ICIN SURELER-------\n\n");
    printf("bubble sort--->");
    mybubblesort(dizi4,100000);
    
    memcpy(dizi4,yedek4,100000*sizeof(int));
    printf("\nselection sort--->");
    myselectionsort(dizi4,100000);
    
    memcpy(dizi4,yedek4,100000*sizeof(int));
    printf("\ninsertion sort--->");
    myinsertionsort(dizi4,100000);
   
    memcpy(dizi4,yedek4,100000*sizeof(int));
    printf("\nmerge sort--->");
    gettimeofday(&starttv, &starttz);
    mymergesort(dizi4,0,100000);
    gettimeofday(&endtv, &endtz);
    float fark11=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark11);
    
	memcpy(dizi4,yedek4,100000*sizeof(int));
    printf("\nquick sort--->");
    gettimeofday(&starttv, &starttz);
	myquicksort(dizi4,0,100000);
    gettimeofday(&endtv, &endtz);
    float fark12=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark12); 
 
    memcpy(dizi4,yedek4,100000*sizeof(int));
    printf("\nheap sort---->");
    gettimeofday(&endtv, &endtz);
    myheapsort(dizi4,100000);
    gettimeofday(&endtv, &endtz);
    float fark24=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark24);
    //**************ters sirali sayilar icin********************
	for(int i=0;i<10000;i++)
        dizi2[i]=10000-i-1;
        memcpy(yedek2,dizi2,10000*sizeof(int));
    for(int i=0;i<50000;i++)
        dizi3[i]=50000-i-1;
        memcpy(yedek3,dizi3,50000*sizeof(int));
    for(int i=0;i<100000;i++)
        dizi4[i]=100000-i-1;
        memcpy(yedek4,dizi4,100000*sizeof(int));
    
	printf("\n\n--------------TERS SIRALI SAYILAR ICIN ALGORITMA CALISMA SURELERI------------------\n");
    printf("\n\t-------10000 ELEMANLI DIZI ICIN SURELER-----\n\n");
    printf("bubble sort--->");
    mybubblesort(dizi2,10000);
    
	memcpy(dizi2,yedek2,10000*sizeof(int));
    printf("\nselection sort--->");
    myselectionsort(dizi2,10000);
    
	memcpy(dizi2,yedek2,10000*sizeof(int));
    printf("\ninsertion sort--->");
    myinsertionsort(dizi2,10000);
    
	memcpy(dizi2,yedek2,10000*sizeof(int));
    printf("\nmerge sort--->");
    gettimeofday(&starttv, &starttz);
	mymergesort(dizi2,0,10000);
    gettimeofday(&endtv, &endtz);
    float fark13=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark13);
	
	memcpy(dizi2,yedek2,10000*sizeof(int));
    printf("\nquick sort--->");
    gettimeofday(&endtv, &endtz);
	myquicksort(dizi2,0,10000);
    gettimeofday(&endtv, &endtz);
    float fark14=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark14);
    
    memcpy(dizi2,yedek2,10000*sizeof(int));
    printf("\nheap sort---->");
    gettimeofday(&endtv, &endtz);
    myheapsort(dizi2,10000);
    gettimeofday(&endtv, &endtz);
    float fark25=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark25);
     //-------------------------------------------------------------
    
    printf("\n\n\t-------50000 ELEMANLI DIZI ICIN SURELER------\n");
    printf("\nbubble sort--->");
    mybubblesort(dizi3,50000);
   
    memcpy(dizi3,yedek3,50000*sizeof(int));
    printf("\nselection sort--->");
    myselectionsort(dizi3,50000);

    memcpy(dizi3,yedek3,50000*sizeof(int));
    printf("\ninsertion sort--->");
    myinsertionsort(dizi3,50000);
    
    memcpy(dizi3,yedek3,50000*sizeof(int));
    printf("\nmerge sort--->");
    gettimeofday(&starttv, &starttz);
	mymergesort(dizi3,0,50000);
    gettimeofday(&endtv, &endtz);
    float fark15=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark15);
   
    memcpy(dizi3,yedek3,50000*sizeof(int));
    printf("\nquick sort--->");
    gettimeofday(&starttv, &starttz);
	myquicksort(dizi3,0,50000);
    gettimeofday(&endtv, &endtz);
    float fark16=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark16);
	
    memcpy(dizi3,yedek3,50000*sizeof(int));
    printf("\nheap sort---->");
    gettimeofday(&endtv, &endtz);
    myheapsort(dizi3,50000);
    gettimeofday(&endtv, &endtz);
    float fark26=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark26);
	 //----------------------------------------------------------------
    
    printf("\n\n\t-------100000 ELEMANLI DIZI ICIN SURELER-------\n\n");
    printf("bubble sort--->");
    mybubblesort(dizi4,100000);
    
    memcpy(dizi4,yedek4,100000*sizeof(int));
    printf("\nselection sort--->");
    myselectionsort(dizi4,100000);
    
    memcpy(dizi4,yedek4,100000*sizeof(int));
    printf("\ninsertion sort--->");
    myinsertionsort(dizi4,100000);
   
    memcpy(dizi4,yedek4,100000*sizeof(int));
    printf("\nmerge sort--->");
    gettimeofday(&starttv, &starttz);
    mymergesort(dizi4,0,100000);
    gettimeofday(&endtv, &endtz);
    float fark17=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark17);
    
	memcpy(dizi4,yedek4,100000*sizeof(int));
    printf("\nquick sort--->");
    gettimeofday(&starttv, &starttz);
	myquicksort(dizi4,0,100000);
    gettimeofday(&endtv, &endtz);
    float fark18=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark18);
 
    memcpy(dizi4,yedek4,100000*sizeof(int));
    printf("\nheap sort---->");
    gettimeofday(&endtv, &endtz);
    myheapsort(dizi4,100000);
    gettimeofday(&endtv, &endtz);
    float fark27=getdiff(endtv, starttv);
    printf("%f mikrosaniye",fark27);
    printf("\n\n\n");
    system("pause");
    
 return 0;
}

