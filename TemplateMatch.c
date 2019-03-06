#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "BmpImage.h"
#include "Correlation.h"
#include "Draw_Fix.h"

void template_match (char *imaginein, char *sablon, unsigned int *c, corr **D,int *n)  // Functie care formeaza tabloul de detectii si pentru fiecare element primeste culoarea ssablonului
{
    int i;
    static int suma=1;
    double ps=0.5;
    corr *v;

    v=correlation(imaginein,sablon,ps);
    (*n)=suma-1;
    suma+=v[0].lenght-1;
    (*D)=realloc((*D),(suma)*sizeof(corr));
    for(i=1;i<v[0].lenght;i++)
            {
                (*D)[*n].x=v[i].x;
                (*D)[*n].y=v[i].y;
                (*D)[*n].corelatie=v[i].corelatie;
                (*D)[*n].col[0]=c[0];
                (*D)[*n].col[1]=c[1];
                (*D)[*n].col[2]=c[2];
                (*n)++;
            }
    free(v);
}

int main()
{
    char imagine_initiala[101],resulted_image[101];
    unsigned int c0[2],c1[2],c2[2],c3[2],c4[2],c5[2],c6[2],c7[2],c8[2],c9[2];
    int i,n;
    pixel **tablou;
    corr *D;

    /// Template-matching

    printf("The name of the image: ");
    fgets(imagine_initiala, 101, stdin);
    imagine_initiala[strlen(imagine_initiala) - 1] = '\0';
    FILE *a = fopen(imagine_initiala, "rb");
    if(a == NULL)
    {
        printf("\nDid not find the image (%s)!\n", imagine_initiala);
        return 0;
    }
    printf("\n");

    D=malloc(sizeof(corr));

    c0[0]=255;c0[1]=0;c0[2]=0;
    template_match(imagine_initiala,"cifra0.bmp",c0,&D,&n);
    c1[0]=255;c1[1]=255;c1[2]=0;
    template_match(imagine_initiala,"cifra1.bmp",c1,&D,&n);
    c2[0]=0;c2[1]=255;c2[2]=0;
    template_match(imagine_initiala,"cifra2.bmp",c2,&D,&n);
    c3[0]=0;c3[1]=255;c3[2]=255;
    template_match(imagine_initiala,"cifra3.bmp",c3,&D,&n);
    c4[0]=255;c4[1]=0;c4[2]=255;
    template_match(imagine_initiala,"cifra4.bmp",c4,&D,&n);
    c5[0]=0;c5[1]=0;c5[2]=255;
    template_match(imagine_initiala,"cifra5.bmp",c5,&D,&n);
    c6[0]=192;c6[1]=192;c6[2]=192;
    template_match(imagine_initiala,"cifra6.bmp",c6,&D,&n);
    c7[0]=255;c7[1]=140;c7[2]=0;
    template_match(imagine_initiala,"cifra7.bmp",c7,&D,&n);
    c8[0]=128;c8[1]=0;c8[2]=128;
    template_match(imagine_initiala,"cifra8.bmp",c8,&D,&n);
    c9[0]=128;c9[1]=0;c9[2]=0;
    template_match(imagine_initiala,"cifra9.bmp",c9,&D,&n);


    printf("\n");
    printf("The name of the resulted image: ");
    fgets(resulted_image, 101, stdin);
    resulted_image[strlen(resulted_image) - 1] = '\0';
    printf("\n");

    Non_maxim_elimination(&D,&n);
    tablou=load(imagine_initiala);
    for(i=0;i<n;i++)
    frame(imagine_initiala,D[i].x,D[i].y,D[i].col,&tablou);
    save(imagine_initiala,resulted_image,tablou);


    for(i=0;i<400;i++)
        free(tablou[i]);
    free(tablou);
    free(D);


    return 0;
}
