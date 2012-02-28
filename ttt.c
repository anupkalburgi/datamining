#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXFLDS 200 /* maximum possible number of fields */
#define MAXFLDSIZE 32 /* longest possible field + 1 = 31 byte field */
     
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
    
    FILE *in_tr=fopen("/home/monty/Dropbox/datamining/train.csv","r"); 
     
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

    printf("\n");

    int i=0,j=0,l=0,k=0;
    float dist;
    for(i=1;i<=60;i++)
    {
        for(j=1;j<91;j++)
        {
            for(k=0;k<=3;k++)
            { 
                for(l=0;l<=3;l++)
                {
                    printf("tsd %dx%d: %f",i,k,testdata[i][k]);
		    float x = testdata[i][k]; //p
                    printf("trnd %dx%d: %f",j,l,traindata[j][l]);
		    float y = traindata[j][l];//
                }
                printf("\n");
            }    
        }
    }

    //printf("%f\n",traindata[2][3] );
    //printf("%f\n",testdata[2][3] );
	/*int i=0,j=0;
	for(i=1;i<=60;i++)
	{
		for(j=0;j<4;j++)
		{
		printf("%dx%d:%f\n",i,j,testdata[i][j]);
		}
	}*/
    return 0;
}
