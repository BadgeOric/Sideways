#include <lib.h>
int loopcounter1,loopcounter2;
int waitcount,cyc;
int maxheight=22;
int lastheight=20;
int shipx=4,shipy=10;
int score = 0;
int a=0;
int bufferstart= 44960; //start memory location of screen buffer
int bufferend =46079; //end memory location of text screen
int scrnstart=48000; //start memory location of text screen
int scrnend =49119; //end memory location of text screen
char *writePtr;  //declare pointers for screen and ship memory locations
char *writePtr2;
char *shipPtr;
char *shipPtr2;
char *scrnshipPtr;
char *scrnshipPtr2;
char touch;
void main()
{
cls();  //clearscreen
startgame();
}

void scroll()
{
	writePtr= (char*)bufferstart +82	;
	writePtr2=(char*)bufferstart+83;
	for (loopcounter1=1;loopcounter1<26;loopcounter1++)
		{
		memcpy((void*)writePtr,(void*)writePtr2,38); // scroll buffer memory
		writePtr+=40;
		writePtr2+=40;
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
	*shipPtr=65;
	playgame();
}

void playgame()
{
	do  // main play loop
	{
		getkeys(); // check for key press
		if(peek(bufferstart+shipx+1+shipy*40)!=32) //basic collision check
		{
		 	collision();
		}
		scroll(); 
		nextmountain(); //generate last column of terrain after scrolling
		*shipPtr=65; 	//dont scroll the ship
		*shipPtr2=32;
		*scrnshipPtr=65; 	//dont scroll the ship
		*scrnshipPtr2=32;
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
	
	if ((touch=='L') && (shipx!=35) )
	{
		*shipPtr=32;
		*shipPtr2=32;
		*scrnshipPtr=32;
		*scrnshipPtr2=32;
		shipx++;
		shipPtr++;
		shipPtr2++;
		scrnshipPtr++;
		scrnshipPtr2++;
		*shipPtr=65;
		*shipPtr2=32;
		*scrnshipPtr=65;
		*scrnshipPtr2=32;
	}	
		if ((touch=='K') && (shipx!=4)) 
	{
		*shipPtr=32;
		*shipPtr2=32;
		*scrnshipPtr=32;
		*scrnshipPtr2=32;
		shipx--;
		shipPtr--;
		shipPtr2--;
		scrnshipPtr--;
		scrnshipPtr2--;
		*shipPtr=65;
		*shipPtr2=32;
		*scrnshipPtr=65;
		*scrnshipPtr2=32;
	}
	if ((touch=='A') && (shipy!=2) )
	{
		*shipPtr=32;
		*shipPtr2=32;
		*scrnshipPtr=32;
		*scrnshipPtr2=32;
		shipy--;
		shipPtr=shipPtr-40;
		shipPtr2=shipPtr-1;
		scrnshipPtr=scrnshipPtr-40;
		scrnshipPtr2=scrnshipPtr-1;
		*shipPtr=65;
		*shipPtr2=32;
		*scrnshipPtr=65;
		*scrnshipPtr2=32;
	}
	if ((touch=='Z') && (shipy!=24) )
	{
*shipPtr=32;
*shipPtr=32;
		*shipPtr2=32;
		*scrnshipPtr=32;
		*scrnshipPtr2=32;
		shipy++;
		shipPtr=shipPtr+40;
		shipPtr2=shipPtr-1;
		scrnshipPtr=scrnshipPtr+40;
		scrnshipPtr2=scrnshipPtr-1;
		*shipPtr=65;
		*shipPtr2=32;
		*scrnshipPtr=65;
		*scrnshipPtr2=32;
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

void gameover()
{
	printf("You Hit a Mountain"); //basic collision
	wait(2000);
	cls;
	memcpy((unsigned char*)bufferstart,(unsigned char*)scrnstart,bufferend-bufferstart);
	startgame(); //just returns to scrolling action
}