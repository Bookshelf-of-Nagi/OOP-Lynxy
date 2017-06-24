#include "similarity.h"

similarity::similarity(int numNtoken, int numHash)
{
    set_Progname();
    set_ntoken();
    set_Thresh();
    set_Zerobits();
    set_Ntoken(numNtoken);
    Hash.set_numHash(numHash);
}

std::vector<Token> similarity::get_word(std::string fileName)
{
    std::vector<Token> t;
    Reader read(fileName);
    Token tmp;
    while(true)
    {
        tmp = read.read_word();
        if(tmp.type ==ENDOF)
            break;
        else
            t.push_back(tmp);
    }
    return t;
}

int cmp(const void *p1, const void *p2)
{
	unsigned long v1, v2;

	v1 = *(unsigned long *) p1;
	v2 = *(unsigned long *) p2;
	if (v1 < v2)
		return -1;
	else if (v1 == v2)
		return 0;
	else
		return 1;
}

unsigned long similarity::ChoseHash(char *tok[], int* type)
{
    unsigned long value = 0;
    value = Hash.ChoseHash(tok, Ntoken, type);
    return value;
}

void similarity::init_token_array(void)
{
	int i;
	token = (char**)malloc(Ntoken * sizeof(char*));
	for (i=0; i < Ntoken; i++)
		token[i] = NULL;
}

Sig * similarity::signature(std::vector<Token> t)
{
	int nv, na;
	unsigned long *v, h;
	char *str;
	int i, ntoken;
	Sig *sig;

	/* start loading hash values, after we have Ntoken of them */
	v  = NULL;
	na = 0;
	nv = 0;
	ntoken = 0;
    for(int j = 0; j < t.size(); j++)
	{
		/* step words down by one */
		free(token[0]);
		for (i=0; i < Ntoken-1; i++)
			token[i] = token[i+1];

		/* add new word into array */
		token[Ntoken - 1] = (char*)t[j].content.c_str();
        //typetoken[Ntoken - 1] = (int)t[j].type;
		/* if we don't yet have enough words in the array continue */
		ntoken++;
		if (ntoken < Ntoken)
			continue;
		/* hash the array of words */
		h = ChoseHash(token, typetoken);

		if ((h & zeromask) != 0)
			continue;
		/* discard zeros from end of hash value */
		h = h >> Zerobits;

		/* add value into the signature array, resizing if needed */
		if (nv == na)
        {
			na += 100;
			v = (unsigned long *)realloc(v, na*sizeof(unsigned long));
		}
		v[nv++] = h;
	}

	/* sort the array of hash values for speed */
	qsort(v, nv, sizeof(v[0]), cmp);

	/* allocate and return the Sig structure for this file */
	sig = (Sig*)malloc(sizeof(Sig));
	sig->Ntokenval = nv;
	sig->value     = v;
	return sig;
}

int similarity::compare(Sig *s0, Sig *s1)
{
	int i0, i1, nboth, nsimilar;
	unsigned long v;

	i0 = 0;
	i1 = 0;
	nboth = 0;
	while (i0 < s0->Ntokenval && i1 < s1->Ntokenval)
    {
		if (s0->value[i0] == s1->value[i1])
        {
			v = s0->value[i0];
			while (i0 < s0->Ntokenval && v == s0->value[i0])
            {
				i0++;
				nboth++;
			}
			while (i1 < s1->Ntokenval && v == s1->value[i1])
            {
				i1++;
				nboth++;
			}
			continue;
		}
		if (s0->value[i0] < s1->value[i1])
			i0++;
		else
			i1++;
	}

	if (s0->Ntokenval + s1->Ntokenval == 0)
		return 0;	/* ignore if both are empty files */

	if (s0->Ntokenval + s1->Ntokenval == nboth)
		return 100;	/* perfect match if all hash codes match */

	nsimilar = nboth / 2;
	return 100 * nsimilar / (s0->Ntokenval + s1->Ntokenval - nsimilar);
}

void similarity::startDetect(int argc, char *argv[])
{
	int        i, j, nfiles, percent;
	char       *s, *outname;
	Sig        **sig;

	nfiles = argc - 1;

	/* initialise */

	init_token_array();
	zeromask = (1<<Zerobits)-1;
	sig = (Sig **)(malloc(nfiles * sizeof(Sig *)));


	for (i=0; i < nfiles; i++)
    {
        std::vector<Token> t;
        t = get_word(argv[i + 1]);
		sig[i] = signature(t);
	}
	/* compare each signature pair-wise */
	for (i=0; i < nfiles; i++)
		for (j=i+1; j < nfiles; j++)
        {
			percent = compare(sig[i], sig[j]);
			if (percent >= Thresh)
                std::cout<<argv[i + 1]<<" and "<<argv[j + 1]<<": "<<percent<<std::endl;
        }

	return ;
}
