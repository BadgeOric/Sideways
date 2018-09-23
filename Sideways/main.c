#include <lib.h>
int i ,j,k,l,m,n,hgt,sl,cyc;
int maxheight=20;
int lastheight=5;
int shipx=4,shipy=10;
int score = 0;
int a=0;
int bufferstart= 44960; //start memory location of screen buffer
int bufferend = 46079; //end memory location of text screen
int scrnstart=48000; //start memory location of text screen
int scrnend = 49119; //end memory location of text screen
char touch;
void main()
{
cls();  //clearscreen
startgame();
}

void scroll()
{
	for (j=26;j>1;j--)
		{
		memcpy((unsigned char*)bufferstart+2+j*40,(unsigned char*)bufferstart+3+j*40,37); //copy buffermemory to screen
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
		hgt =26- lastheight; 
		//lastheight = hgt ;
			for (n=26;n>27-maxheight;n--) 
				{
					if (n>hgt)
					{
					poke(bufferstart+39+n*40,128);	
					}
					else
					{
						poke(bufferstart+39+n*40,32);	 // add new characters to ernd column
					}
				}
}


void init_terrain() //create start terrain and  put characters into buffer
{
	for (m=2;m<40;m++)
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
		hgt =26- lastheight; 
		for (n=26;n>27-maxheight;n--) 
				{
					if (n>hgt)
					{
					poke(bufferstart+m+n*40,128);	
					}
					else
					{
						poke(bufferstart+m+n*40,32);	
					}
				}
		}
		flipscrn();
}

void init_screen()
{
	memcpy((unsigned char*)bufferstart,(unsigned char*)scrnstart,bufferend-bufferstart); //copy buffer to screen
	for (m=15;m<26;m++)
		{
		poke(bufferstart+1+n*40,2); // future code for attribute plotting
		}
}

void wait()
{
	for (sl=1;sl <cyc;sl++) 
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
	poke(bufferstart+shipx+shipy*40,65); //plot ship in buffer
	poke(bufferstart+shipx-1+shipy*40,2); //will be used to colour ship
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
		poke(bufferstart+shipx+shipy*40,65);	//dont scroll the ship
		poke(bufferstart+shipx-1+shipy*40,0);	
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
		poke(bufferstart+shipx+shipy*40,32);
		poke(scrnstart+shipx+shipy*40,32);
		shipx++;
	}	
		if ((touch=='K') && (shipx!=4)) 
	{
		poke(bufferstart+shipx+shipy*40,32);
		poke(scrnstart+shipx+shipy*40,32);
		shipx--;
	}
	if ((touch=='A') && (shipy!=2) )
	{
		poke(bufferstart+shipx+shipy*40,32);
		poke(scrnstart+shipx+shipy*40,32);
		shipy--;
	}
	if ((touch=='Z') && (shipy!=24) )
	{
		poke(bufferstart+shipx+shipy*40,32);
		poke(scrnstart+shipx+shipy*40,32);
		shipy++;
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