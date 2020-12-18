#include <bits/stdc++.h>
using namespace std;
ifstream fin("trie.in");
ofstream fout("trie.out");
int t,ok;
char s[30];
struct trie
{
    int nrfii,inf;
    trie *f[26];
    trie()
    {
        inf=nrfii=0;
        for(int i=0; i<26; i++)
            f[i]=0;
    }
};
void inserez(trie *r,char *s)
{
    if(*s)
    {
        if(!r->f[*s-'a'])
        {
            r->f[*s-'a']=new trie;
            r->nrfii++;
        }
        if(*(s+1)==0)
        {
            r->f[*s-'a']->inf++;
        }
        else
            inserez(r->f[*s-'a'],s+1);
    }
}
void sterg(trie *r,char *s)
{
    if(*s)
    {
        sterg(r->f[*s-'a'],s+1);

        if(r->f[*s-'a']->nrfii!=0 || r->f[*s-'a']->inf!=0)
            ok=0;
        if(ok==1)
        {
            r->nrfii--;
            delete r->f[*s-'a'];
            r->f[*s-'a']=0;
        }
    }
    else
    {
        r->inf--;
        if( r->inf==0&& r->nrfii==0)
        {
            ok=1;
        }
    }
}
int nrap(trie *r,char *s)
{
    if(*s)
    {
        if(!r->f[*s-'a'])
            return 0;
        return nrap(r->f[*s-'a'],s+1);
    }
    else
    {
        return r->inf;
    }
}
void dfs(trie *r,string cuv)
{
    if(r->inf!=0)
    {
        for(int i=1; i<= (r->inf) ; i++ )
            cout<<cuv<<"\n";
    }
    for(int i=0; i<26; i++)
    {
        if(r->f[i])
        {
            dfs(r->f[i],cuv+char('a'+i));
        }
    }
}
void gasirecuprefix(trie *r,char *s,string cuv)
{
    if(*s)
    {
        if(r->f[*s-'a'])
            gasirecuprefix(r->f[*s-'a'],s+1,cuv+*s);
    }
    else
    {
        /// s-a terminat cuvantul de aici
        // trebuie sa vad ce cuvinte noi pot forma
        dfs(r,cuv);
    }
}
int prefix(trie *r,char *s)
{
    if(*s)
    {
        if(r->f[*s-'a']==0)
            return 0;
        return 1+prefix(r->f[*s-'a'],s+1);
    }
    return 0;
}
int main()
{
    trie *rad = new trie;
    while(fin>>t>>s)
    {
        if(t==0)
        {
            // inserez
            inserez(rad,s);

        }
        else if(t==1)
        {
            ok=0;
            // sterg
            sterg(rad,s);
        }
        else if(t==2)
        {
            // nrap
            fout<<nrap(rad,s)<<"\n";
        }
        else if(t==3)
        {
            // lungime pref comun
            fout<<prefix(rad,s)<<"\n";
        }
        else
        {
            /// toate cuvintele care incep cu un anumit prefix citit de la tastatura
            string cuv=""; /// cuvant initial gol
            gasirecuprefix(rad,s,cuv);
        }

    }


}
