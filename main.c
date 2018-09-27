#include <lib.h>
#include<sound.h>
int loopcounter1,loopcounter2;
int waitcount,cyc;
int maxheight=22;
int lastheight=10;
int shipx=4,shipy=10;
int score = 0;
int a=0;
int shipcolour=2;
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
char *tmpPtr;
char *x;
char y[4]="    ";
int z;
char *w;
char touch;
char ship[4]="abcd";
char ship1 [4]= "abcd";
char ship2 [4]= "efgh";
char redefchar[64]=
{
0,36,16,31,8,36,0,0,  
15,0,0,63,31,0,0,0,   
63,2,7,58,54,58,31,15, 
63,0,48,40,38,51,63,62, 

0,8,16,63,8,16,0,0,  
0,0,0,63,31,0,0,0,   
15,2,7,58,54,58,31,15, 
32,0,48,40,38,51,63,62
};

char intros[1120]={
16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,16,1,32,32,32,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,16,32,32,32,16,1,32,32,32,20,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,20,16,32,32,32,16,1,32,32,32,20,18,127,127,127,18,127,18,127,18,127,127,127,18,127,127,127,18,127,127,127,18,127,127,127,18,127,127,127,18,20,16,32,32,32,16,1,32,32,32,20,18,127,18,18,18,127,18,127,18,127,18,127,18,127,18,127,18,127,18,127,18,127,18,18,18,127,18,127,18,20,16,32,32,32,16,1,32,32,32,20,18,127,18,18,18,127,18,127,18,127,18,127,18,127,18,127,18,127,18,127,18,127,18,18,18,127,18,127,18,20,16,32,32,32,16,1,32,32,32,20,18,127,18,18,18,127,127,127,18,127,18,127,18,127,127,127,18,127,127,127,18,127,127,127,18,127,127,18,18,20,16,32,32,32,16,1,32,32,32,20,18,127,18,18,18,127,18,127,18,127,18,127,18,127,18,18,18,127,18,18,18,127,18,18,18,127,127,18,18,20,16,32,32,32,16,1,32,32,32,20,18,127,18,18,18,127,18,127,18,127,18,127,18,127,18,18,18,127,18,18,18,127,18,18,18,127,18,127,18,20,16,32,32,32,16,1,32,32,32,20,18,127,127,127,18,127,18,127,18,127,127,127,18,127,18,18,18,127,18,18,18,127,127,127,18,127,18,127,18,20,16,32,32,32,16,7,32,32,32,20,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,20,16,32,32,32,16,7,32,32,32,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,16,32,32,32,16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,16,7,32,32,32,32,32,32,32,32,32,32,32,32,75,69,89,83,58,65,45,85,80,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,90,45,68,79,87,78,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,75,45,76,69,70,84,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,76,45,82,73,71,72,84,32,32,32,32,32,32,32,32,32,32,32,32,32,32,16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,16,7,32,32,32,32,32,32,32,32,32,32,80,82,69,83,83,32,69,78,84,69,82,32,84,79,32,83,84,65,82,84,32,32,32,32,32,32,32,32,16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,16,7,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32
};
 


void main()

{
 //set up basic conditions - redef chars, curso and keyclicks
 
 //void w8912(unsigned char reg,unsigned char value); Future use for sound?

memcpy((unsigned char*)shipmem,redefchar,64); //redine characters 
tmpPtr=(char*)618;
*tmpPtr=10; // turn off cursor and keyboard click
//exit(0);
cls(); //clear screen - oric specific command to be replaced
introscreen();
cls();  //clear screen - oric specific command to be replaced
memcpy(ship,ship1,4);

//tmpPtr=(char*)524;
//*tmpPtr=0; // caps lock off

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
			if (lastheight<2)
				{
				lastheight = 2;
				}
		writePtr= (char*)(bufferstart+117 ) ; //set pointer for screen buffer
			for (loopcounter1=26;loopcounter1>1;loopcounter1--) 
				{
					if (lastheight>loopcounter1)
					{
					*writePtr=128;		
					}
					else
					{
						*writePtr=32;		 // add new characters to ernd column
					}
					//memset((unsigned char*)writePtr-36,4,1);
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
					*writePtr=128;		
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
	cls;
	a=0;
	init_screen(); 
	init_terrain(); //create starting terrain
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
		if(peek(bufferstart+shipx+4+shipy*40)!=32) //basic collision check
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
	touch=key(); // keyboard check and basic screen limits for movement
	
	if ((touch=='L') && (shipx!=33) )
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
	}	
		if ((touch=='K') && (shipx!=4)) 
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
	}
	if ((touch=='A') && (shipy!=2) )
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
	}
	if ((touch=='Z') && (shipy!=24) )
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
	}
}
void collision()
{
	a=1; // will stop the main do...while and go to game over routine
}

void firebullet()
{
	// nothing as yet
}

void movebullet()
{
	// nothing as yet

}
void plotship(x,z,w,thiscol) //actually plots any item to position sent to routine and colour
{
	memcpy((unsigned char*)x,y,z);
	memcpy((unsigned char*)w,y,z);
	memset((unsigned char*)x-1,thiscol,1); // colour for item
	memset((unsigned char*)w-1,thiscol,1); // colour for item
}
void plotblanks()
{
	memcpy((unsigned char*)shipPtr,blanks,4);
	//memcpy((unsigned char*)scrnshipPtr,blanks,4);
}


void gameover()
{
	printf("You Hit a Mountain"); //basic collision
	wait(22000);
	cls;
	//memcpy((unsigned char*)bufferstart,(unsigned char*)scrnstart,bufferend-bufferstart);
	main();
	//startgame(); //just returns to scrolling action
}

void introscreen()
{
	char c;
	memcpy((unsigned char*)bufferstart,intros,1120);
	flipscrn();
	c = getchar();
	wait(5000);
}