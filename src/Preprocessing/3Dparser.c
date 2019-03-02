#include <stdio.h>
#include <stdlib.h> 

struct data { 
     double x;
     double y;
     double z;
     double dosage;
} ;        

struct data mydata[1331]; 

int main() { 

int i ;  
double x=4.35;
   
FILE *fp = fopen("datasets3D.csv", "r") ; 

if ( fp != NULL ) 
 { 
   char a[20];
char b[20];
char c[20];
char d[20];               
    i=0;
    while(i<1331)  
    {              
        fscanf(fp, "%s, %s, %s, %s \n",a);

         mydata[i].x = 1.0f*(double)atof(a);
         
         i++;   
    }
    i=0;
     while(i<1331)  
    {              
        fscanf(fp, "%s, %s, %s, %s \n",b);
       
         mydata[i].y = 1.0f*(double)atof(b);
         
         i++;   
    }
    i=0;
     while(i<1331)  
    {              
        fscanf(fp, "%s, %s, %s, %s \n",c);
        
         mydata[i].z = 1.0f*(double)atof(c);
         
         i++;   
    }         
    i=0;
     while(i<1331)  
    {              
        fscanf(fp, "%s, %s, %s, %s \n",d);
        
         mydata[i].dosage = 1.0f*(double)atof(d);
         
         i++;   
    }         

}    
else
{
  printf("unable to open");
}   
fclose(fp);   

int j; 

for(j=0; j<1331; j++)  
    {                                            
       printf("%lf, %lf, %lf, %lf, \n", mydata[j].x, mydata[j].y, mydata[j].z, mydata[j].dosage); 
    }
          
return 0;   
  
}