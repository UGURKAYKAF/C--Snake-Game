#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

//May�n eklenecek May�n� y�lan yerse oyun biter
//Zehirli Elma eklenecek y�lan elmay� yedi�inde boyu k�salacak

int saha[80][23]={0};
int kuyrukSutun[500];
int kuyrukSatir[500];
int maap[80][23]={0};

void gotoxy(short x, short y) { //istedi�imiz konuma istedi�imiz �eyi atamam�z� sa�l�yor
	HANDLE hConsoleOutput;
	COORD Cursor_Pos = {x-1, y-1};

	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_Pos);
}

void cerceve(int x1, int y1, int x2, int y2,int tur){
    int i;

    for(i=x1; i<=x2;i++){ //yataydaki s�n�rlar� belirliyor
        saha[i][y1] = tur; //sol
        saha[i][y2] = tur;//sa�
    }
    for(i=y1; i<=y2;i++){ // dikeydeki s�n�rlar� belirliyor
        saha[x1][i] = tur; //sol
        saha[x2][i] = tur;//sa�
    }
}

void ekrani_bas(){
    int x,y;
    for(x=0;x<80;x++){
        for(y=0;y<23;y++){
        gotoxy(x+1,y+1);
            if(saha[x][y]==1){
                printf("%c",219);
            }
            else if(saha[x][y]==2){
                //printf("%c",176);
               printf("%c",219);
            }
            else if(saha[x][y]==3){
            	//printf("%c",88);
				//printf("%c",219);
			}
        }
    }
}

int k,l;
void randomAta(){ //yem at�yor random
    srand(time(NULL)); //zamana ba�l� olarak farkl� de�erler at�yoe
    k=4+rand()%65; // 4 den 69 tane de�er atayacak k ya
    l=4+rand()%15; // 4 den ba�layacak 19 tane de�er atayacak l ye


}

int main()
{basla:
//	system("color 4F");
    randomAta();
    cerceve(0,0,79,22,2);//oyun alan�n� belirliyor
    ekrani_bas();
    int sx=40,sy=12;//ba�lang�� konumu
    int dy=0,dx=0;//y�lan�n sonras�nda oldu�u konumlar�n de�erlerinin atand��� yer
    unsigned char tus;
    unsigned char yem;
    int a=0;
    int devam=0;

    do{    
        if(kbhit()){ //kbhit tu�a bas�lma durumunu al�yor      
            tus=getch();
            if(tus==224)//hareket veriyoruz 
            {
                tus=getch();
                switch(tus)
                {
                    case 72:dy=-1; dx=0; // 72 yukar�
                        break;
                    case 80:dy=1; dx=0; // 80 a�a��
                        break;
                    case 77: dx=1; dy=0; // 77 sa�
                        break;
                    case 75: dx=-1; dy=0; // 75 sol
                }
            }
        }

        sx=sx+dx;
        sy=sy+dy;
        
        if(sx>78){//s�n�rlar� a�arsa di�er taraftan ��kmas� mant���
        	sx=2;
		}    
        if(sx<2){
        	sx=78;
		}            
        if(sy>22){
        	sy=2;
		}           
        if(sy<2){
        	sy=22;
		}
		
        kuyrukSutun[0]=sx; //kuyru�un sutununun ilk yerini sutun de�erine at�yor
        kuyrukSatir[0]=sy;
        int i;


        for(i=1;i<=a;i++){
            if((sx==kuyrukSutun[i] && sy==kuyrukSatir[i])){
                gotoxy(30,12);printf("~~KAYBETTINIZ~~");
                
				//gotoxy(sx,sy);printf("--YANDINIZ--");
                getch();
                //devam=1;
                system("cls");
                goto basla;
            }
        }

        gotoxy(sx,sy);printf("%c",170);//printf("*");

        for(i=0;i<=a;i++){//kuyruk harekeini yazd�r�yor
            gotoxy(kuyrukSutun[i],kuyrukSatir[i]);printf("%c",170);//printf("*");

        }


        if(sx==k && sy==l){
            randomAta();
            a++;
            gotoxy(83,3);printf("Puan: %d",a);
        }
		
        gotoxy(k,l);printf("*");//yem ==>denemee//printf("%c",248);
        //gotoxy(83,5);printf("*");printf("Yem => %c",248);

        Sleep(130);

        gotoxy(sx,sy);printf(" ");


        for(i=0;i<=a;i++){ //kuyruk hareketini sildiriyor
            gotoxy(kuyrukSutun[i],kuyrukSatir[i]);printf(" ");

        }


        for(i=a;i>0;i--){ //y�lan�n kuyru�unun takip etmesini yap�yo
            kuyrukSutun[i]=kuyrukSutun[i-1]; //bir �nceki indisi bir sonraki indise at�yor
            kuyrukSatir[i]=kuyrukSatir[i-1];
        }

    } while (devam==0);
    
    
    return 0 ;
}
