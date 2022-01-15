
/*************************************************************************
   LAB 1

	Edit this file ONLY!

*************************************************************************/


#include <stdio.h>
#include "dns.h"


const int SIZE_OF_DB = 12838;//size of data base with hosts
const int MAX_LENGTH_OF_HOST_NAME = 101;


typedef struct Pair
{
	IPADDRESS ip;
	char *domen;
	struct Pair *nextPair;
} Pair;

const size_t PAIR_SIZE = sizeof(Pair);

DNSHandle InitDNS()
{
	DNSHandle hDNS = (unsigned int)(Pair *)calloc(SIZE_OF_DB, PAIR_SIZE);
	if ((Pair *)hDNS != NULL)
	{
		return hDNS;
	}
	return INVALID_DNS_HANDLE;
}

/*
* hash function
*/
unsigned int HashFunc(const char *str)
{
	unsigned int hash = 0;

	int c;
	while (c = *str++)
	{
		hash = ((hash << 5) + hash) + c;
	}

	return hash % SIZE_OF_DB;
}

/*
* Function that adds element to hash table
*/
void AddToTable(DNSHandle hDNS, char *str, IPADDRESS ip)
{
	unsigned int lengthOfHost = strlen(str);
	unsigned int indexOfElement = HashFunc(str);

	if (((Pair *)hDNS)[indexOfElement].domen == NULL)
	{
		((Pair *)hDNS)[indexOfElement].ip = ip;
		((Pair *)hDNS)[indexOfElement].domen = (char *)malloc(lengthOfHost + 1);
		strcpy(((Pair *)hDNS)[indexOfElement].domen, str);
		((Pair *)hDNS)[indexOfElement].nextPair = NULL;
	} else
	{
		Pair *p;
		p = (Pair *)malloc(PAIR_SIZE);
		p->ip = ip;
		p->domen = (char *)malloc(lengthOfHost + 1);
		strcpy(p->domen, str);
		p->nextPair = ((Pair *)hDNS)[indexOfElement].nextPair;
		((Pair *)hDNS)[indexOfElement].nextPair = p;
	}

}


void LoadHostsFile(DNSHandle hDNS, const char *hostsFilePath)
{
	FILE *fInput = fopen(hostsFilePath, "r");
	char *string = (char *)malloc(MAX_LENGTH_OF_HOST_NAME);
	unsigned int num1 = 0, num2 = 0, num3 = 0, num4 = 0;

	if (fInput == NULL)
	{
		return;
	}

	while (fscanf_s(fInput, "%d.%d.%d.%d %s", &num1, &num2, &num3, &num4, string, 100) != EOF)
	{
		IPADDRESS ip = (num1 & 0xFF) << 24 | (num2 & 0xFF) << 16 | (num3 & 0xFF) << 8 | (num4 & 0xFF);
		AddToTable(hDNS, string, ip);
	}

	free(string);
	fclose(fInput);
}


IPADDRESS DnsLookUp(DNSHandle hDNS, const char *hostName)
{
	unsigned int index = HashFunc(hostName);
	Pair *it = &((Pair *)hDNS)[index];
	while (it != NULL && strcmp(it->domen, hostName) != 0)
	{
		it = it->nextPair;
	}
	if (it != NULL)
	{
		return it->ip;
	}
	return INVALID_IP_ADDRESS;
}


void ShutdownDNS(DNSHandle hDNS)
{
	for (int i = 0; i < SIZE_OF_DB; i++)
	{
		Pair *q = &(((Pair *)hDNS)[i]);
		if (q != NULL)
		{
			if (q->domen != NULL)
			{
				free(q->domen);
			}
			q = q->nextPair;
			while (q != NULL)
			{
				Pair *p = q;
				q = q->nextPair;
				if (p->domen != NULL)
				{
					free(p->domen);
				}
				free(p);
			}
		}
	}

	if ((Pair *)hDNS != NULL)
	{
		free((Pair *)hDNS);
	}
}