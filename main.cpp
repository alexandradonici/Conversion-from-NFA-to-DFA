#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int cautare_litera(char alfabet[], int nr, char lit)
{
    int i;

    for(i=0;i<nr;i++)
        if(alfabet[i]==lit)
        return i+1;

    return -1;
}

void citire(char a[][100][100], int &n,int &m, int &si,int &nr, char alfabet[], int sf[],int &k)
{
    int i,q1,q2,j,poz;
    char lit;

    ifstream fin ("AFN-AFD.in");

    fin>>n;//numarul de stari

    fin>>si;//starea initiala

    fin>>k;//numarul starilor finale
    for(i=1;i<=k;i++)
    fin>>sf[i];//starile finale

    fin>>nr;//numarul de litere din alfabet
    for(i=0;i<nr;i++)
        fin>>alfabet[i];

    fin>>m; //numarul de muchii
    for(i=1;i<=m;i++)
    {
        fin>>q1>>q2>>lit;
        poz=cautare_litera(alfabet,nr,lit);
        a[q1][poz][strlen(a[q1][poz])]=q2+'0';
        a[q1][poz][strlen(a[q1][poz])]=',';
        a[q1][poz][strlen(a[q1][poz])]='\0';
    }

     for(i=0;i<n;i++)
   {
       for(j=1;j<=nr;j++)
        if(a[i][j][0]!='\0')
           a[i][j][strlen(a[i][j])-1]='\0';//sterge ultima virgula
   }


}

void afis(char a[][100][100],char b[][100][100],int linii, int n, int nr)
{
    int i,j;

    ofstream fout ("AFN-AFD.out");

    fout<<"AFN:"<<'\n';
    for(i=0;i<n;i++)
   {
       for(j=1;j<=nr;j++)
        if(a[i][j][0]=='\0')
            fout<<"- ";
        else
            fout<<a[i][j]<<" ";

        fout<<'\n';
   }

   fout<<'\n'<<"AFD:"<<'\n';

       for(i=0;i<linii;i++)
   {
       for(j=0;j<=nr;j++)
        if(b[i][j][0]=='\0')
            fout<<"- ";
        else
            fout<<b[i][j]<<" ";

        fout<<'\n';
   }

}

int cautare_stare(int linii, char b[][100][100],char cuv[],int n)
{
    int i,j,v[100],var,k,poz,ok;

        for(j=0;j<linii;j++)
        {
            ok=1;

            for(i=0;i<n;i++)
            v[i]=0;

            if(strlen(b[j][0])!=strlen(cuv))
                ok=0;

            k=0;
            while(b[j][0][k]!='\0')
            {
                poz=0;
                 while(b[j][0][k]!=',' && b[j][0][k]!='\0')
                 {
                    var=b[j][0][k]-'0';
                    poz=poz*10+var;
                    k++;

                 }
                 v[poz]++;
                 if(b[j][0][k]!='\0')
                    k++;
            }

                k=0;
                while(cuv[k]!='\0')
                {
                    poz=0;
                     while(cuv[k]!=',' && cuv[k]!='\0')
                     {
                        var=cuv[k]-'0';
                        poz=poz*10+var;
                        k++;
                    }
                    v[poz]--;
                    if(cuv[k]!='\0')
                        k++;
                }


               for(i=0;i<n;i++)
                if(v[i]!=0)
                ok=0;

                if(ok==1)
                    return j;
            }

    return 0;

}

int gasit(char x[], char y[])
{
    char *p;
    p=new char[100];

    p=strstr(x,y);

    if(p==NULL)
        return 0;

    if(p[strlen(y)]==',')
        return 1;

    return 0;
}

void transformare(char a[][100][100], char b[][100][100],int &linii,int n, int si, int nr)
{
    int i,j,poz,k,v,l_aux,x,q;
    char var[2], aux[100];

    var[0]=si+'0';
    var[1]='\0';

    linii=1;

    strcpy(b[0][0],var);

    for(i=1;i<=nr;i++)
        {
            strcpy(b[0][i],a[0][i]);

            if(b[0][i][0]!='\0')
            {
                x=cautare_stare(linii,b,b[0][i],n);
                if(x==0)
                {
                    strcpy(b[linii][0],b[0][i]);
                    linii++;
                }
                else
                    strcpy(b[0][i],b[x][0]);
            }

        }


    j=1;
    while(j<=linii)
    {

        k=0;
        poz=0;

        while(b[j][0][k]!=',' && b[j][0][k]!='\0')
            {
                v=b[j][0][k]-'0';
                poz=poz*10+v;
                k++;
            }

        for(i=1;i<=nr;i++)
            if(a[poz][i][0]!='\0')
            {
                strcpy(b[j][i],a[poz][i]);
                b[j][i][strlen(b[j][i])]=',';
            }

       if(b[j][0][k]!='\0')
            k++;

        while(b[j][0][k]!='\0')
        {
            poz=0;
            while(b[j][0][k]!=',' && b[j][0][k]!='\0')
            {
                v=b[j][0][k]-'0';
                poz=poz*10+v;
                k++;
            }

            for(i=1;i<=nr;i++)
            {
                if( a[poz][i][0]!='\0')
                {
                    q=0;
                    aux[0]='\0';
                    l_aux=0;

                    while(a[poz][i][q]!='\0')
                        {
                            while(a[poz][i][q]!=',' && a[poz][i][q]!='\0')
                                {
                                    aux[l_aux++]=a[poz][i][q];
                                    q++;
                                }

                            if(gasit(b[j][i],aux)==0)
                            {
                                strcat(b[j][i],aux);
                                b[j][i][strlen(b[j][i])]=',';
                            }

                            if(a[poz][i][q]!='\0')
                                q++;
                        }


                }
            }

            if(b[j][0][k]!='\0')
            k++;
        }

        for(i=1;i<=nr;i++)
        {
            if(b[j][i][strlen(b[j][i])-1]==',')
                b[j][i][strlen(b[j][i])-1]='\0';

           if(b[j][i][0]!='\0')
           {
                x=cautare_stare(linii,b,b[j][i],n);

                if(x==0)
                    {
                        strcpy(b[linii][0],b[j][i]);
                        linii++;
                    }
                else
                    strcpy(b[j][i],b[x][0]);
           }

        }

        j++;
    }



}

int verif_stare_finala(int sf[], int k, int x)
{
    int i;
    for(i=1;i<=k;i++)
        if(sf[i]==x)
        return 1;
    return 0;
}

void stari_finale(char b[][100][100],int linii,char stari_fin[][100],int &nr_st_fin,int sf[],int k)
{
int j,p,poz,ok,var;
nr_st_fin=0;

for(j=0;j<linii;j++)
{
    p=0;
    ok=0;
    while(b[j][0][p]!='\0' && ok==0)
        {
            poz=0;
            while(b[j][0][p]!=',' && b[j][0][p]!='\0' && ok==0)
             {
                var=b[j][0][p]-'0';
                poz=poz*10+var;
                p++;

             }

             if(verif_stare_finala(sf,k,poz)==1)
               {
                    strcpy(stari_fin[nr_st_fin++],b[j][0]);
                    ok=1;
               }

             if(b[j][0][p]!='\0')
                p++;
        }

}

cout<<"Starile finale sunt:"<<'\n';
for(j=0;j<nr_st_fin;j++)
    cout<<stari_fin[j]<<'\n';
}

void afisare_afd(char b[][100][100], int linii,int nr, char alfabet[])
{
    int i,j;

    cout<<"Muchiile sunt:"<<'\n';
    for(i=0;i<linii;i++)
        for(j=1;j<=nr;j++)
            if(b[i][j][0]!='\0')
                cout<<b[i][0]<<" "<<b[i][j]<<" "<<alfabet[j-1]<<'\n';

}

int main()
{
    char a[100][100][100], alfabet[100],b[100][100][100],stari_fin[100][100];
    int n,si,sf[100],k,m,nr,linii=1,nr_st_fin;

    citire(a,n,m,si,nr,alfabet,sf,k);
    transformare(a,b,linii,n,si,nr);
    afis(a,b,linii,n,nr);

    stari_finale(b,linii, stari_fin,nr_st_fin,sf,k);
    cout<<'\n';
    afisare_afd(b,linii,nr,alfabet);

    return 0;
}
