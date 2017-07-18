

#include "ri.h"
#include "Global.h"
#include <stdio.h>

FILE *FPTR ;


RtVoid imageToFile_init()
{
  
  char str[100];

    sprintf(str,"%s.rgb",filename);
    FPTR=fopen(str,"w+");
    if ( FPTR == NULL ) exit(0);
    fprintf(FPTR,"x:%d y:%d  type:RGBA \n\f", resolution_x, resolution_y);
    
}

RtVoid  imageToFile(RtColor ligne[])
{
 char ch ;
 char alpha = 0 ;
	
    for (int loop=0; loop < resolution_x ; loop++) {

	fwrite(&alpha, sizeof(char), 1, FPTR);	
	fwrite(&(ch=(unsigned char)ligne[loop].bleu), sizeof(char), 1, FPTR);
	fwrite(&(ch=(unsigned char)ligne[loop].vert ), sizeof(char), 1, FPTR);
    	fwrite(&(ch=(unsigned char)ligne[loop].rouge), sizeof(char), 1, FPTR);
	
		
    	
   } // for
	
} // image to file




RtVoid  imageToFile_close()
{
  fclose(FPTR);
}



 

