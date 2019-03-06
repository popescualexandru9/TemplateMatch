#ifndef CORRELATION_H_INCLUDED
#define CORRELATION_H_INCLUDED

typedef struct{
    unsigned int x;
    unsigned int y;
    double corelatie;
    unsigned int lenght;
    unsigned int col[2];
}corr;

double medie_sablon(pixel **sab)  // Functie pentru calcularea mediei intensitatilor valorilor grayscale din sablon
{
    double s=0;
    unsigned i,j;
    for(i=0;i<15;i++)
        for(j=0;j<11;j++)
           s+=sab[i][j].r;

    s=s/165;
    return s;
}

double deviatie_sablon(pixel **sab) // Deviaytia standard a valorilor grayscale a pixelilor din sablon
{
    unsigned int i,j;
    double s=0 ,medie_sab;
    medie_sab=medie_sablon(sab);

    for(i=0;i<15;i++)
        for(j=0;j<11;j++)
          s=s+((sab[i][j].r-medie_sab)*(sab[i][j].r-medie_sab));

    s=sqrt(s/164)-0.06;
    return s;

}

double medie_fereastra(pixel **v,unsigned int a,unsigned int b)   // Functie pentru calcularea mediei intensitatilor valorilor grayscale din fereastra
{
    unsigned int i,j;
    double s=0;

    for(i=0;i<15;i++)
     for(j=0;j<11;j++)
        s+=v[i+a][j+b].r;

    s/=165;
    return s;
}

double deviatie_fereastra(pixel **v,unsigned int a,unsigned int b)  // Deviaytia standard a valorilor grayscale a pixelilor din fereastra
{
    int i,j;
    double s=0 ,medie_fi;
    medie_fi=medie_fereastra(v,a,b);

    for(i=0;i<15;i++)
        for(j=0;j<11;j++)
          s=s+((v[i+a][j+b].r-medie_fi)*(v[i+a][j+b].r-medie_fi));


    s=sqrt(s/164);
    return s;
}

corr* correlation(char *imaginein,char *sablon,double ps) // Functie pentru calcularea corelatiilor ,returneaza un tabloul unidimensional
{
    unsigned int w,h,i,j,ii,jj,nr=1;
    double sumaos,cor,suma,sumafi,medie_sab=0,medie_fi;
    FILE *f=fopen(imaginein,"rb");
    FILE *g=fopen(sablon,"rb");

    fseek(f,18,SEEK_SET);
    fread(&w, sizeof(unsigned int), 1, f);
    fread(&h, sizeof(unsigned int), 1, f);

    pixel **vec,**sab;
    vec=gray(imaginein);
    sab=gray(sablon);

    fclose(f);
    fclose(g);

    corr *v=malloc((nr+1)*sizeof(corr));
    medie_sab=medie_sablon(sab);
    sumaos=deviatie_sablon(sab);
    for(i=0;i<(h-15);i++)
     for(j=0;j<(w-11);j++)
      {
       medie_fi=medie_fereastra(vec,i,j);
       sumafi=deviatie_fereastra(vec,i,j);
       suma=0;
       for(ii=0;ii<15;ii++)
         for(jj=0;jj<11;jj++)
            suma=suma+((vec[ii+i][jj+j].r-medie_fi)*(sab[ii][jj].r-medie_sab))/(sumafi*sumaos);

       cor=suma/165;

      if(cor>=ps)
        {
            v[nr].x=i;
            v[nr].y=j;
            v[nr].corelatie=cor;
            nr++;
            v=realloc(v,(nr+1)*sizeof(corr));
        }

      }

    v[0].lenght=nr;
    for(i=0;i<15;i++)
        free(sab);

    free(sab);
    return v;
}




#endif // CORRELATION_H_INCLUDED
