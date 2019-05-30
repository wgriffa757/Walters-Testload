#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#define notes 4096
#define ESC 0x1b
#define larrow 0x4b
#define rarrow 0x4d
#define kminus 0x2d
#define kplus  0x2b

long int delay=200000,sdelay;
int manual,mc,mflag=0,i;
char bindisp=0x00;

void boxes()
{
  int b,x1,x2,y1,y2;
  setcolor(3);
  for (b=1;b<17; b++)
    {
      x1=b*35-1;
      y1=50-2;
      x2=x1+22;
      y2=400+2;
      moveto(x1,y1);
      lineto(x2,y1);
      lineto(x2,y2);
      lineto(x1,y2);
      lineto(x1,y1);
    }
}


void light(p,c)
int p,c;
{ int x1,x2,y1,y2;
  x1=p*35; y1=50; x2=x1+20; y2=400;
   setfillstyle(1,c);
   bar(x1,y1,x2,y2);
}

void checkkey()
{
  long int loop;
  char keyhit;
  if(kbhit())
   {
     keyhit=getch();

     if(ESC == keyhit)
       {
         restorecrtmode();
         exit(0);
       }

     if ( kminus == keyhit )
       {

          if ( mflag != 1 )
	    { mc=i;
	      mflag=1;
	      sdelay=delay;
	      delay=1;
	    };
          mflag=1;
	  mc--;
       }
    if ( kplus == keyhit )
       {
          if ( mflag != 1 )
	    { mc=i;
	      mflag=1;
	      sdelay=delay;
	      delay=1;
	    };
          mflag=1;
	  mc++;
       }

     if(larrow == keyhit)
       {
	 delay=delay-10000;
	 if (delay<=0) delay=0;
       }
     if(rarrow == keyhit)
       {
	 delay=delay+50000;
	 if (delay>320000) delay=320000;
       }
     if( ('b' == keyhit) || ('B' == keyhit) )
       {
          bindisp = bindisp ^ 1 ;
	  if (bindisp==1) gotoxy(1,1);
	  if (bindisp==0)
	    { gotoxy(1,1);
	      printf("                                 ");
	    }
       }

    if( ('r' == keyhit) || ('R' == keyhit) )
      { mflag=0;
	delay=sdelay;
      };
   }
  for(loop=0; loop<=delay; loop++);
}

void main()
{
 FILE *ldata;
 int driver,mode,h1,b[16],c;
 int m[16]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768};
 unsigned int house[notes];
 unsigned int bite,t1,t2;

 driver=DETECT; /* autodetect graphics mode */
 mode=0;
 initgraph(&driver,&mode,"");
 boxes();

    if((ldata = fopen("xmas.prm","rb")) == NULL)
      { puts("Can't open or find xmas.prm");
		exit();  }

    for (i=0; i<=notes; i++)
      {
        bite=getw(ldata);
        t1=(bite & 0x00FF);
        t1=t1 * 256;
	t2=bite & 0xFF00;
	t2=t2 >> 8;
	bite=t1 | t2;
        house[i]=bite;
      }

for (i=0; i<notes; i++)
  {
    if(mflag) { i=mc; }
    for(c=15;c>=0;c--)
	  {
            if ((house[i] & m[c]) > 0)
               {  b[c]=0; if(bindisp) printf("1");  }
            else { b[c]=2; if(bindisp) printf("0"); }
	  };

    if(bindisp)
      {
         printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
         gotoxy(18,1);
         printf(" Byte = %d ",i);
         gotoxy(1,1);
      }

    for(c=15;c>=0;c--)  { light(16-c,b[c]); }

    checkkey();

  }

 getch();
 restorecrtmode();
}
