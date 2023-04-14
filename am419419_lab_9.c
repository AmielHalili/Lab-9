#include <stdio.h>
#include <stdlib.h> 

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
	struct RecordType* next;
};

// Fill out this structure
struct HashType
{
	struct RecordType* pData; // Pointer to RecordType data
	int isOccupied; // Flag to indicate if the index is occupied or not
};

// Compute the hash function
int hash(int x)
{
	// Your hash function implementation here
	return x % 31;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		if (pHashArray[i].isOccupied == 1) // check if index is occupied
		{
			printf("index %d -> %d, %c, %d\n", i, pHashArray[i].pData->id, pHashArray[i].pData->name, pHashArray[i].pData->order);
		}
		
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation

	// Hash table size
	int hashSz = recordSz; // You can adjust this as needed

	// Create hash table
	struct HashType *pHashArray = (struct HashType*) malloc(sizeof(struct HashType) * hashSz);
	if (pHashArray == NULL)
	{
		printf("Cannot allocate memory for hash table\n");
		exit(-1);
	}

	// Initialize hash table
	int i;
	for (i = 0; i < hashSz; ++i)
	{
		pHashArray[i].pData = NULL;
		pHashArray[i].isOccupied = 0;
	}

	// Insert records into hash table
	for (i = 0; i < recordSz; ++i)
	{
		int index = hash(pRecords[i].id);// Compute hash index
		while (pHashArray[index].isOccupied == 1) // Linear probing to handle collisions
		{
			index = (index + 1) % hashSz; // Move to next index
		}
		pHashArray[index].pData = &pRecords[i]; // Set pointer to record
		pHashArray[index].isOccupied = 1; // Set occupied flag
	}

	// Display records in hash table
	displayRecordsInHash(pHashArray, hashSz);

	// Free dynamically allocated memory
	free(pRecords);
	free(pHashArray);

	return 0;
}