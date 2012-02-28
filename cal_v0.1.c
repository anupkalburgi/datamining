#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXFLDS 200 /* maximum possible number of fields */
#define MAXFLDSIZE 32 /* longest possible field + 1 = 31 byte field */

float find_index(float a[], int num_elements, float value)
{
   int i;
   for (i=0; i<num_elements; i++)
   {
	 if (a[i] == value)
	 {
	    return(i);  /* it was found */
	 }
   }
   return(-1);  /* if it was not found */
}

int fm(float arr[], int b, int n) {
 int f = b;
 int c;

 for(c = b + 1; c < n; c++)
  if(arr[c] < arr[f]) 
   f = c;

 return f;
}

void isort(float arr[], int n) {
 int s, w;
 float sm;

 for(s = 0; s < n - 1; s++) {
  w = fm(arr, s, n);
  sm = arr[w];
  arr[w] = arr[s];
  arr[s] = sm;
 }
}
     
void parse( char *record, char *delim, char arr[][MAXFLDSIZE],int *fldcnt)
{
    char*p=strtok(record,delim);
    int fld=0;
     
    while(p)
    {
	    strcpy(arr[fld],p);
	    fld++;
	    p=strtok('\0',delim);
   }
	    *fldcnt=fld;
}
     
int main(int argc, char *argv[])
{
    char tmp[1024]={0x0};
    int fldcnt=0;
    int fldcnt_tr=0;
    char arr[MAXFLDS][MAXFLDSIZE]={0x0};
    char arr_tr[MAXFLDS][MAXFLDSIZE]={0x0};
    float testdata[62][4];
    float traindata[90][5];
    int recordcnt=0;
    int recordcnt_tr=0;
    
    
    
    FILE *in_tr=fopen("/home/monty/Dropbox/datamining/traindata.csv","r"); 
     
    if(in_tr==NULL)
    {
	    perror("File open error");
	    exit(EXIT_FAILURE);
    }

    while(fgets(tmp,sizeof(tmp),in_tr)!=0) 
    {
	    int i=0;
	    recordcnt_tr++;
	    parse(tmp,",",arr_tr,&fldcnt_tr); 
	    for(i=0;i<fldcnt_tr;i++)
    		{ 
			float tr_data;
			tr_data = atof(arr_tr[i]);				
           		traindata[recordcnt_tr][i] = tr_data;
    		}
    }
    
    

    char tmp1[1024]={0x0};
    recordcnt=0;
    FILE *in=fopen("/home/monty/Dropbox/datamining/testdata.csv","r");
    if(in==NULL)
    {
	    perror("File open error");
	    exit(EXIT_FAILURE);
    }
    while(fgets(tmp1,sizeof(tmp),in)!=0) 
    {
	    int i=0;
	    recordcnt++;
	    parse(tmp1,",",arr,&fldcnt); 
	    for(i=0;i<fldcnt;i++)
    		{ 
			float te_data;
			te_data = atof(arr[i]);			
          			testdata[recordcnt][i] = te_data;
    		}
    }
    fclose(in);
    fclose(in_tr);


    int i=0,j=0,l=0,k=0;
    float l_dist=0,low_dist=0,el[60];
    float dist;

    for(i=1;i<=60;i++)//testdata
    {
	float result[90];
	float a=0.0,b=0.0,c=0.0,d=0.0,w=0,x=0,y=0,z=0;
		a= testdata[i][0];
		b= testdata[i][1];
		c= testdata[i][2];
		d= testdata[i][3];

        for(j=1;j<=90;j++)//traindata
        {
		w= traindata[j][0];
		x= traindata[j][1];
		y= traindata[j][2];
		z= traindata[j][3];

		dist = pow((a-w),2)+pow((b-x),2)+pow((c-y),2)+pow((d-z),2);
		dist = sqrt(dist);
		//printf("%d-->%f\n",j,dist);
		result[j-1] = dist;
		//printf("%d -> %f\n", j,result[j-1]);
		
        }
		float dum[60];
		int o;
		for(o=0;o<=60;o++)
		{
			dum[o]=result[o];
			
		}

		isort(result, 60);//Sorting
		/*for (l=0; l<=60; l++) 
		{
 			 printf("%f ", result[l]);
  		}*/
		float value = result[0];
		   int index = find_index(dum, 60, value);
		   if (index == -1)
		   {
			 printf("The value %f was not found.\n", value);
		   }
		   else
		   {
			 printf("%d -- The value %f was found at %d and class is %f \n",i, value, index,traindata[index][4]);
		   }
		
    }
    return 0;
}
