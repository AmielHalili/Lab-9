#include <stdio.h>
#include <stdlib.h>

struct RecordType
{
    int id;
    char name;
    int order;
    struct RecordType* next;
};

struct HashType
{
    struct RecordType* pData;
};

int hash(int x)
{
    return x % 11;
}

int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;

    *ppData = NULL;
    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }

        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d %c %d\n", &pRecord->id, &pRecord->name, &pRecord->order);
            pRecord->next = NULL;
        }

        fclose(inFile);
    }
    return dataSz;
}

void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords: \n");
    for (i = 0; i < dataSz; ++i)
		{
			printf("\n%d %c %d", pData[i].id, pData[i].name, pData[i].order);
		}
    printf(" \n");
}

void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
    
    int index = hash(record->id);

    
    if (hashTable[index].pData == NULL)
    {
        hashTable[index].pData = record;
    }
    else
    {
        
        struct RecordType* Data = hashTable[index].pData;
        while (Data->next != NULL)
        {
            Data = Data->next;
        }
        Data->next = record;
        Data->next->next = NULL;
    }
}

void displayRecordsInHash(struct HashType *hashTable, int tableSize)
{
	int i;

    for (i = 0; i < tableSize; ++i)
    {
        if (hashTable[i].pData != NULL)
        {
            printf("Index %d -> ", i);
            struct RecordType* Data = hashTable[i].pData;
            while (Data != NULL)
            {
                printf("%d, %c, %d -> ", Data->id, Data->name, Data->order);
                Data = Data->next;
            }
        }
           printf("NULL\n");
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    
    int hashTableSize = 11;
    struct HashType* hashTable = (struct HashType*)calloc(hashTableSize, sizeof(struct HashType));// Insert records into the hash table
    
	for (int i = 0; i < recordSz; ++i)
	{
    	insertRecord(hashTable, &pRecords[i], hashTableSize);
    }

    
    displayRecordsInHash(hashTable, hashTableSize);

   
    free(pRecords);
    free(hashTable);

    return 0;
}