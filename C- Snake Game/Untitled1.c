#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

//Mayýn eklenecek Mayýný yýlan yerse oyun biter
//Zehirli Elma eklenecek yýlan elmayý yediðinde boyu kýsalacak

int saha[80][23]={0};
int kuyrukSutun[500];
int kuyrukSatir[500];
int maap[80][23]={0};

void gotoxy(short x, short y) { //istediðimiz konuma istediðimiz þeyi atamamýzý saðlýyor
	HANDLE hConsoleOutput;
	COORD Cursor_Pos = {x-1, y-1};

	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_Pos);
}

void cerceve(int x1, int y1, int x2, int y2,int tur){
    int i;

    for(i=x1; i<=x2;i++){ //yataydaki sýnýrlarý belirliyor
        saha[i][y1] = tur; //sol
        saha[i][y2] = tur;//sað
    }
    for(i=y1; i<=y2;i++){ // dikeydeki sýnýrlarý belirliyor
        saha[x1][i] = tur; //sol
        saha[x2][i] = tur;//sað
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
void randomAta(){ //yem atýyor random
    srand(time(NULL)); //zamana baðlý olarak farklý deðerler atýyoe
    k=4+rand()%65; // 4 den 69 tane deðer atayacak k ya
    l=4+rand()%15; // 4 den baþlayacak 19 tane deðer atayacak l ye


}

int main()
{basla:
//	system("color 4F");
    randomAta();
    cerceve(0,0,79,22,2);//oyun alanýný belirliyor
    ekrani_bas();
    int sx=40,sy=12;//baþlangýç konumu
    int dy=0,dx=0;//yýlanýn sonrasýnda olduðu konumlarýn deðerlerinin atandýðý yer
    unsigned char tus;
    unsigned char yem;
    int a=0;
    int devam=0;

    do{    
        if(kbhit()){ //kbhit tuþa basýlma durumunu alýyor      
            tus=getch();
            if(tus==224)//hareket veriyoruz 
            {
                tus=getch();
                switch(tus)
                {
                    case 72:dy=-1; dx=0; // 72 yukarý
                        break;
                    case 80:dy=1; dx=0; // 80 aþaðý
                        break;
                    case 77: dx=1; dy=0; // 77 sað
                        break;
                    case 75: dx=-1; dy=0; // 75 sol
                }
            }
        }

        sx=sx+dx;
        sy=sy+dy;
        
        if(sx>78){//sýnýrlarý aþarsa diðer taraftan çýkmasý mantýðý
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
		
        kuyrukSutun[0]=sx; //kuyruðun sutununun ilk yerini sutun deðerine atýyor
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

        for(i=0;i<=a;i++){//kuyruk harekeini yazdýrýyor
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


        for(i=a;i>0;i--){ //yýlanýn kuyruðunun takip etmesini yapýyo
            kuyrukSutun[i]=kuyrukSutun[i-1]; //bir önceki indisi bir sonraki indise atýyor
            kuyrukSatir[i]=kuyrukSatir[i-1];
        }

    } while (devam==0);
    
    
    return 0 ;
}
