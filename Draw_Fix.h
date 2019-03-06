#ifndef DRAW_FIX_H_INCLUDED
#define DRAW_FIX_H_INCLUDED

void frame(char* imaginein, unsigned int x,unsigned int y, unsigned int *c,pixel ***arr)
{
    FILE *f;
    f=fopen(imaginein,"rb");
    unsigned int w,h,i,j,cont;

    fseek(f, 18, SEEK_SET);
    fread(&w, sizeof(unsigned int), 1, f);
    fread(&h, sizeof(unsigned int), 1, f);
    fclose(f);

    for(i=0;i<h;i++)
      for(j=0;j<w;j++)
        {
            if(i==x && j==y)
            {
                cont=11;
                while(cont)
                {
                    (*arr)[i][j].b=c[2];
                    (*arr)[i][j].g=c[1];
                    (*arr)[i][j].r=c[0];
                    j++;
                    cont--;
                }
            }
    else if (i==x+1)
            {
            cont=13;
            while(cont)
                {
                (*arr)[i][y].b=c[2];
                (*arr)[i][y+10].b=c[2];
                (*arr)[i][y].g=c[1];
                (*arr)[i][y+10].g=c[1];
                (*arr)[i][y].r=c[0];
                (*arr)[i][y+10].r=c[0];
                cont--;
                i++;
                }
            }
    else if(i==x+14 && j==y)
        {
          cont=11;
          while(cont)
          {
            (*arr)[i][j].b=c[2];
            (*arr)[i][j].g=c[1];
            (*arr)[i][j].r=c[0];
            j++;
            cont--;
          }
        }
    }
}


double minim (double a,double b)
{
    return (a<b) ? a : b;
}

double maxim (double a,double b)
{
    return (a>b) ? a : b;
}

int cmp(const void *a,const void *b)
{
    corr *A=((corr*)a);
    corr *B=((corr*)b);
    if(B->corelatie > A->corelatie)
        return 1;
    return-1;
}

void Non_maxim_elimination(corr **D,int *n)  // Eliminarea non-maximelor
{
   qsort(*D,*n,sizeof(corr),cmp);
   int i,j,ariaI,ariaJ,l,ii,jj,iii,jjj,intersectie,ok;
   unsigned int ws=11,hs=15;
   double suprapunere,prag=0.2,reuniune;

   for(i=0;i<(*n);i++)
       {
      for(j=i+1;j<(*n);j++)
            {
                ariaJ=ws*hs;
                ariaI=ws*hs;
                intersectie=0;

        for(ii=(*D)[i].x;ii<((*D)[i].x+15);ii++)  // Parcurgerea primei ferestre pentru a verifica intersectia pixelilor
           for(jj=(*D)[i].y;jj<((*D)[i].y+11);jj++)
            {
                ok=0;
                for(iii=(*D)[j].x;iii<((*D)[j].x+15);iii++)  // Parcurgerea ferestrei a doua
                   {
                    for(jjj=(*D)[j].y;jjj<((*D)[j].y+11);jjj++)
                       {
                        if(ii==iii && jjj==jj)
                         {
                             intersectie++;
                             ok=1;
                         }
                         if(ok==1)
                            break;
                       }
                       if(ok==1)
                        break;
                   }
            }

                reuniune=ariaI+ariaJ-intersectie;
                suprapunere=intersectie/reuniune;

                if(suprapunere>prag)
                    {
                    for(l=j;l<(*n)-1;l++)
                            (*D)[l]=(*D)[l+1];
                        (*n)--;
                        j--;
                    }
            }
    }

        printf("Numarul final de detectii al imaginii este %d \n",*n);
}


#endif // DRAW_FIX_H_INCLUDED
