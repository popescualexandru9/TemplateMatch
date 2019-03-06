#ifndef BMPIMAGE_H_INCLUDED
#define BMPIMAGE_H_INCLUDED

typedef struct{
unsigned char r;
unsigned char g;
unsigned char b;
}pixel;

pixel** load (char* imaginein)
{
    FILE *f;
    f=fopen(imaginein,"rb");
    int i,j;
    unsigned int w,h;
    pixel** arr;

    fseek(f, 18, SEEK_SET);
    fread(&w, sizeof(unsigned int), 1, f);
    fread(&h, sizeof(unsigned int), 1, f);

    fseek(f,54,SEEK_SET);
    int padding=(4-(w*3%4))%4;

    arr=malloc(h*sizeof(pixel*));
    for(i=0;i<h;i++)
        arr[i]=malloc(w*sizeof(pixel));


      for (i = h-1 ;  i >=0 ; i--)
        {
        for (j = 0; j < w; j++)
         {
           fread(&arr[i][j].b,1,1,f);
           fread(&arr[i][j].g,1,1,f);
           fread(&arr[i][j].r,1,1,f);
         }
         fseek(f,padding,SEEK_CUR);
        }
    fclose(f);
    return arr;
}

void save(char *imaginein,  char* result , pixel **arr)
{
    int i,j,l,header_oct;
    unsigned int w,h;
    char zero=0;

    FILE* fout ,*f;
    f=fopen(imaginein,"rb");
    fout=fopen(result,"wb");

    for (i = 0; i < 54; ++i)
	{
		fread(&header_oct, 1, 1, f);
		fwrite(&header_oct, 1, 1, fout);
	}

    fseek(f, 18, SEEK_SET);
    fread(&w, sizeof(unsigned int), 1, f);
    fread(&h, sizeof(unsigned int), 1, f);
    fclose(f);

    int padding=(4-(w*3%4))%4;

    for (i = h-1 ;  i >= 0; i--)
        {
        for(j = 0; j < w; j++)
        {
           fwrite(&arr[i][j].b,1,1,fout);
           fwrite(&arr[i][j].g,1,1,fout);
           fwrite(&arr[i][j].r,1,1,fout);
           fflush(fout);
        }
        for(l=0;l<padding;l++)
            fwrite(&zero,1,1,fout);
        }

        fclose(fout);
        for(i=0;i<h;i++)
            free(arr[i]);
        free(arr);
}

pixel** gray(char *imaginein)  //Grayscale
{
    FILE *f;
    f=fopen(imaginein,"rb");
    int i,j;
    unsigned char auxr,auxg,auxb;
    unsigned int w,h;
    pixel** arr;


    fseek(f, 18, SEEK_SET);
    fread(&w, sizeof(unsigned int), 1, f);
    fread(&h, sizeof(unsigned int), 1, f);


    fseek(f,54,SEEK_SET);
    int padding=(4-(w*3%4))%4;

    arr=malloc((h)*sizeof(pixel*));
    for(i=0;i<h;i++)
        arr[i]=malloc(w*sizeof(pixel));


      for (i = h-1 ;  i >=0 ; i--)
        {
        for (j = 0; j < w; j++)
         {
           fread(&auxb,1,1,f);
           fread(&auxg,1,1,f);
           fread(&auxr,1,1,f);

           arr[i][j].b=arr[i][j].g=arr[i][j].r=0.114*auxb+0.587*auxg+0.299*auxr;
         }
         fseek(f,padding,SEEK_CUR);
        }
    fclose(f);
    return arr;
}

#endif // BMPIMAGE_H_INCLUDED
