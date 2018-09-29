#include <lib.h>
#include<sound.h>
int loopcounter1,loopcounter2;
int waitcount,cyc;
int maxheight=22;
int lastheight=10;
int shipx=4,shipy=10;
int score = 0;
int a=0;
int shipcolour=4;
int aliencolour=1;
int alienflag=0;
int aliencounter=0;
int bufferstart= 44960; //start memory location of screen buffer
int bufferend =46079; //end memory location of text screen
int scrnstart=48000; //start memory location of text screen
int scrnend =49119; //end memory location of text screen
int shipmem =46856; //end memory location of ship characters
const char blanks[4] = "    ";
char *writePtr;  //declare pointers for screen and ship memory locations
char *writePtr2;
char *shipPtr;
char *shipPtr2;
char *scrnshipPtr;
char *scrnshipPtr2;
char *alienPtr;
char *alienPtr2;
char *scrnalienPtr;
char *scrnalienPtr2;
char *tmpPtr; //temp pointer for various routines
char *keyPtr; //mem location for keyboard scan
char *x; // pointer for plotship routine
char y[4]="    ";  //blanks to erase last ship position
int z;
char *w; //pointer for plotship routine
int touch; //keyboard scan result
int terrain;

char ship[4]="abcd";
char ship1 [4]= "abcd";
char ship2 [4]= "efgh";
char alien[4]="ijk ";
char redefchar[88]=
{
0,36,16,31,8,36,0,0,  
15,0,0,63,31,0,0,0,   
63,2,7,58,54,58,31,15, 
63,0,48,40,38,51,63,62, 

0,8,16,63,8,16,0,0,  
0,0,0,63,31,0,0,0,   
15,2,7,58,54,58,31,15, 
32,0,48,40,38,51,63,62,

0,0,3,15,3,0,0,0,
32,63,42,21,42,63,36,0,
32,32,56,30,56,32,32,0
};

char intros[1120]={
16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
16,1,32,32,32,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,16,32,32,32,
16,1,32,32,32,20,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,20,16,32,32,32,
16,1,32,32,32,20,18,127,127,127,18,127,18,127,18,127,127,127,18,127,127,127,18,127,127,127,18,127,127,127,18,127,127,127,18,20,16,32,32,32,
16,1,32,32,32,20,18,127,18,18,18,127,18,127,18,127,18,127,18,127,18,127,18,127,18,127,18,127,18,18,18,127,18,127,18,20,16,32,32,32,
16,1,32,32,32,20,18,127,18,18,18,127,18,127,18,127,18,127,18,127,18,127,18,127,18,127,18,127,18,18,18,127,18,127,18,20,16,32,32,32,
16,1,32,32,32,20,18,127,18,18,18,127,127,127,18,127,18,127,18,127,127,127,18,127,127,127,18,127,127,127,18,127,127,18,18,20,16,32,32,32,
16,1,32,32,32,20,18,127,18,18,18,127,18,127,18,127,18,127,18,127,18,18,18,127,18,18,18,127,18,18,18,127,127,18,18,20,16,32,32,32,
16,1,32,32,32,20,18,127,18,18,18,127,18,127,18,127,18,127,18,127,18,18,18,127,18,18,18,127,18,18,18,127,18,127,18,20,16,32,32,32,
16,1,32,32,32,20,18,127,127,127,18,127,18,127,18,127,127,127,18,127,18,18,18,127,18,18,18,127,127,127,18,127,18,127,18,20,16,32,32,32,
16,7,32,32,32,20,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,20,16,32,32,32,
16,7,32,32,32,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,16,32,32,32,
16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
16,7,32,32,32,32,32,32,32,32,32,32,32,32,75,69,89,83,58,65,45,85,80,32,32,32,32,32,1,105,106,107,7,32,32,32,32,32,32,32,
16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
16,7,32,4,97,98,99,100,7,32,32,32,32,32,32,32,32,32,32,90,45,68,79,87,78,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,75,45,76,69,70,84,32,32,32,32,32,1,1,105,106,107,7,32,32,32,32,
16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,76,45,82,73,71,72,84,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
16,7,32,32,4,97,98,99,100,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
16,7,32,32,32,32,32,32,32,32,32,32,80,82,69,83,83,32,69,78,84,69,82,32,84,79,32,83,84,65,82,84,32,32,32,32,32,32,32,32,
16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32
};
 
char level1[1120]={
22,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,0,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,0,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,0,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,0,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,0,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,0,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,0,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,2,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,2,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,2,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,2,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,2,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,2,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,2,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
22,2,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32
};
int lvl1cols[26]={7,7,7,7,7,7,7,7,7,7,7,7,7,0,0,0,0,0,0,2,2,2,2,2,2,2
};


void main()
{
 //set up basic conditions - redef chars, curso and keyclicks
 
 //void w8912(unsigned char reg,unsigned char value); Future use for sound?
keyPtr=(char*)520; //mem location for keyboard scanning
memcpy((unsigned char*)shipmem,redefchar,88); //redine characters 
tmpPtr=(char*)618;
*tmpPtr=10; // turn off cursor and keyboard click
introscreen();
cls();  //clear screen - oric specific command to be replaced
memcpy(ship,ship1,4);

play (58,80,100,60); //chopper sound - oric specifc command to be replaced
startgame();
}

void scroll()
{
	int ret = strcmp(ship, ship1); //animate chopper - flip between 2 characters
	if (ret<0)
	{
		memcpy(ship,ship2,4);
	}
	else
	{
	 	memcpy(ship,ship1,4);
	}
	memcpy((unsigned char*)shipPtr,blanks,4); //blank out ship
	memcpy((unsigned char*)shipPtr+1,ship,4);
	writePtr= (char*)bufferstart +82	;
	writePtr2=(char*)bufferstart+83;
	for (loopcounter1=1;loopcounter1<26;loopcounter1++)
		{
		memcpy((void*)writePtr,(void*)writePtr2,38); // scroll buffer memory for each row
		writePtr+=40;
		writePtr2+=40;
		}
	memcpy(y,ship,4);
	plotship(scrnshipPtr,4,shipPtr,shipcolour);
	aliencounter ++;
	if(aliencounter>=40)
		{
			aliencounter = 0;
			alienflag =1;
			alienPtr=(char*)(bufferstart+33+((26-lastheight)/2*40));
			alienPtr2=(char*)(bufferstart+32+((26-lastheight)/2*40));
			scrnalienPtr=(char*)(scrnstart+33+((26-lastheight)/2*40));
			scrnalienPtr2=(char*)(scrnstart+32+((26-lastheight)/2*40));
		}
	if (alienflag==1)
		{
			memcpy(y,alien,4);
			plotship(scrnalienPtr,4,alienPtr,aliencolour);
			alienflag=0;
		}
}

void nextmountain()
{
if (rand()%100>=50) // random up or down on terrain
				{
				lastheight=lastheight + 1;
				}
			else
				{
				lastheight=lastheight - 1;
				}
			if (lastheight>maxheight)
				{
				lastheight = maxheight-1;
				}
			if (lastheight<3)
				{
				lastheight = 3;
				}
		writePtr= (char*)(bufferstart+117 ) ; //set pointer for screen buffer
			for (loopcounter1=26;loopcounter1>1;loopcounter1--) 
				{

					if (lastheight>loopcounter1)
					{
					*writePtr=127;		
					}
					else
					{
						*writePtr=32;		 // add new characters to ernd column
					}
					writePtr+=40;
				}
}


void init_terrain() //create start terrain and  put characters into buffer
{
	for (loopcounter1=3;loopcounter1<41;loopcounter1++)
		{
			if (rand()%100>=50)
				{
				lastheight=lastheight + 1;
				}
			else
				{
				lastheight=lastheight - 1;
				}
			if (lastheight>maxheight)
				{
				lastheight = maxheight-1;
				}
			if (lastheight<2)
				{
				lastheight = 2;
				}
	
		writePtr= (char*)(bufferstart+loopcounter1+79 ) ; //set pointer for screen buffer
			for (loopcounter2=26;loopcounter2>1;loopcounter2--) 
				{
					if (lastheight>loopcounter2)
					{
											
					*writePtr=127;		
					}
					else
					{
						*writePtr=32;		 // add new characters to end column
					}
					writePtr+=40;
				}
		}
		flipscrn();
}

void init_screen()
{
	memcpy((unsigned char*)bufferstart,(unsigned char*)scrnstart,bufferend-bufferstart); //copy buffer to screen

}

void wait(int cyc)
{
	for (waitcount=1;waitcount<cyc;waitcount++) 
	{
		// just a wait 
	}
}

void startgame()
{
	a=0;
    memcpy((unsigned char*)bufferstart,level1,1120);
	 memcpy((unsigned char*)scrnstart,level1,1120);
	init_screen(); 
	init_terrain(); //create starting terrain
	wait(25000);
	score=0; 
	shipx=4; //ship x 
	shipy=10; //ship y
	shipPtr= (char*)(bufferstart+shipx+shipy*40) ; //set pointer for screen buffer
	shipPtr2= (char*)(bufferstart+shipx+shipy*40-1) ; //set pointer for screen buffer to blank after scroll
	scrnshipPtr= (char*)(scrnstart+shipx+shipy*40) ; //set pointer for screen buffer
	scrnshipPtr2= (char*)(scrnstart+shipx+shipy*40-1) ; //set pointer for screen buffer to blank after scroll
	memcpy(y,ship,4);
	plotship(scrnshipPtr,4,shipPtr,shipcolour);
	playgame();
}

void playgame()
{
	do  // main play loop
	{
		getkeys(); // check for key press
		tmpPtr = (char*)(bufferstart+shipx+5+shipy*40);
		if (*tmpPtr>32)  //basic collision check
		{
		 	collision();
		}
		plotblanks();
		scroll(); 
		nextmountain(); //generate last column of terrain after scrolling
		memcpy(y,ship,4);
		plotship(scrnshipPtr,4,shipPtr,shipcolour);
		flipscrn(); // swap buffer to screen
	}
	while( a ==0 );
	gameover();
}

void flipscrn()
{
	memcpy((unsigned char*)scrnstart,(unsigned char*)bufferstart,bufferend-bufferstart); // buffer to screen
	memcpy((unsigned char*)bufferstart,(unsigned char*)scrnstart,bufferend-bufferstart); // copy new screen to buffer
}

void getkeys()
{
	touch=0x7f&*keyPtr; // keyboard check and basic screen limits for movement
	if(touch==56)
	{
		return;
	}
	if ((touch==15) && (shipx!=33) )
	{
		
		plotblanks();
		shipx++;
		shipPtr++;
		shipPtr2++;
		scrnshipPtr++;
		scrnshipPtr2++;
		memcpy((unsigned char*)scrnshipPtr-1,blanks,4);
		memcpy(y,ship,4);
		plotship(scrnshipPtr,4,shipPtr,shipcolour);
		return;
	}	
		if ((touch==3) && (shipx!=4)) 
	{
		plotblanks();
		shipx--;
		shipPtr--;
		shipPtr2--;
		scrnshipPtr--;
		scrnshipPtr2--;
		memcpy((unsigned char*)scrnshipPtr+1,blanks,4);
		memcpy(y,ship,4);
		plotship(scrnshipPtr,4,shipPtr,shipcolour);
		return;
	}
	if ((touch==46) && (shipy!=2) )
	{
		plotblanks();
		shipy--;
		shipPtr-=40;
		shipPtr2-=40;
		scrnshipPtr-=40;
		scrnshipPtr2-=40;
		memcpy((unsigned char*)scrnshipPtr+40,blanks,4);
		memcpy(y,ship,4);
		plotship(scrnshipPtr,4,shipPtr,shipcolour);
		return;
	}
	if ((touch==42) && (shipy!=24) )
	{
		plotblanks();
		shipy++;
		shipPtr+=40;
		shipPtr2+=40;
		scrnshipPtr+=40;
		scrnshipPtr2+=40;
		memcpy((unsigned char*)scrnshipPtr-40,blanks,4);
		memcpy(y,ship,4);
	    plotship(scrnshipPtr,4,shipPtr,shipcolour);
		
		return;
	}
}
void collision()
{
	a=1; // will stop the main do...while and go to game over routine
}

void firebullet()
{
	// use plotship routine after bullet init
}

void movebullet()
{
	// nothing as yet - use plotship routine

}
void plotship(x,z,w,thiscol) //actually plots any item to position sent to routine and colour and maintains terrain colours
{
	memcpy((unsigned char*)x,y,z);
	memcpy((unsigned char*)w,y,z);
	memset((unsigned char*)x-1,thiscol,1); // colour for item
	memset((unsigned char*)w-1,thiscol,1); // colour for item	
	memset((unsigned char*)x+4,lvl1cols[shipy-1],1);
	memset((unsigned char*)w+4,lvl1cols[shipy-1],1);
}


void plotblanks()
{
	memcpy((unsigned char*)shipPtr,blanks,4);
	//memcpy((unsigned char*)scrnshipPtr,blanks,4);
}


void gameover()
{
	play (58,80,100,60); 
	explode;
	printf("You Hit Something"); //basic collision
	wait(22000);
	//memcpy((unsigned char*)bufferstart,(unsigned char*)scrnstart,bufferend-bufferstart);
	main();
	//startgame(); //just returns to scrolling action
}

void introscreen()
{
	char c;
	memcpy((unsigned char*)bufferstart,intros,1120);
	flipscrn();
	while (0x7f&*keyPtr ==56); //repeat until enter 56
	{
	// wait for enter key
	}
		wait(5000);
}