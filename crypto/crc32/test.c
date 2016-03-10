/*
 * Improved calculation of CRC-64 values for protein sequences
 * By David T. Jones (dtj@cs.ucl.ac.uk)  - September 28th 2002
 * 
 * Modified from code at URL:
 * ftp://ftp.ebi.ac.uk/pub/software/swissprot/Swissknife/old/SPcrc.tar.gz
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* If you want to try the old CRC-64 function, currently employed in
   SWISSPROT/TrEMBL then uncomment the next line */
/* #define OLDCRC */

#define POLY64REV     0xeff67c77d13835f7ULL
#define INITIALCRC    0xFFFFFFFFFFFFFFFFULL



void crc64(char *seq, char *res)
{
    int i, j, low, high;
    unsigned long long crc = INITIALCRC, part;
    static int init = 0;
    static unsigned long long CRCTable[256];
    
    if (!init)
    {
	init = 1;
	for (i = 0; i < 256; i++)
	{
	    part = i;
	    for (j = 0; j < 8; j++)
	    {
		if (part & 1)
		    part = (part >> 1) ^ POLY64REV;
		else
		    part >>= 1;
	    }
	    CRCTable[i] = part;
		printf("%lx\n", part);
	}
    }
    
    while (*seq)
	crc = CRCTable[(crc ^ *seq++) & 0xff] ^ (crc >> 8);

    /* 
     The output is done in two parts to avoid problems with 
     architecture-dependent word order
     */
    low = crc & 0xffffffff;
    high = (crc >> 32) & 0xffffffff;
    sprintf (res, "%08X%08X", high, low);

    return;
}

void main (int argc, char *argv[])
{
    char *testseq1 = "MNIIQGNLVGTGLKIGIVVGRFNDFITSKLLSGAEDALLRHGVDTNDIDVAWVPGAFEIPFAAKKMAETKKYDAIITLGTVIRGATTSYDYVCNEAAKGIAQAANTTGVPVIFGIVTTENIEQAIERAGTKAGNKGVDCAVSAIEMANLNRSFE";
    char *testseq2 = "MNIIQGNLVGTGLKIGIVVGRFNDFITSKLLSGAEDALLRHGVDTNDIDVAWVPGAFEIPFAAKKMAETKKYDAIITLGDVIRGATTHYDYVCNEAAKGIAQAANTTGVPVIFGIVTTENIEQAIERAGTKAGNKGVDCAVSAIEMANLNRSFE"; /* Differs from 1st seq in two places */
    char result[20];


    crc64(testseq1, result);
    printf("The CRC-64 for sequence %s is %s\n", testseq1, result);

    crc64(testseq2, result);
    printf("The CRC-64 for sequence %s is %s\n", testseq2, result);
}
