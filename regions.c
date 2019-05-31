//-----------------------------------------
// NAME: Zhuoqun Li
// STUDENT NUMBER: 7740173
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Franklin Bristow
// ASSIGNMENT: assignment 4, QUESTION: question 1
//
// REMARKS: Memory Regions funtions
//
//-----------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "regions.h"

//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES
//-------------------------------------------------------------------------------------
typedef struct REGION Region;
typedef struct BLOCK Block;
struct REGION
{
	char *rName;
	char* startAddress;
	char *arrayR;
	int numBlock;
	r_size_t rSize;
	r_size_t usedSpace;
	Region *next;

};

struct BLOCK
{
	char* blockStart;
	r_size_t bSize;
	char *regionName;
	Block *next;
};


//-------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------

static Region *headRegion = NULL;
static Block *headBlock = NULL;
static Region *currentRegion = NULL;
static int numR = 0;

//-------------------------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------------------------

Boolean rinit(const char *region_name, r_size_t region_size);
int initBlock();
Boolean NameDet(const char *region_name);
Boolean rchoose(const char *region_name);
Boolean findRegion(const char *region_name);
const char *rchosen();
void *ralloc(r_size_t block_size);
r_size_t rsize(void *block_ptr);
Boolean rfree(void *block_ptr);
void rdestroy(const char *region_name);
void rdump();
void logicalCheck();

//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------
Boolean rinit(const char *region_name, r_size_t region_size)
{
	Boolean inited = false;
	Boolean invalidName;
	Region *temp = (Region*)malloc(sizeof(Region));

	invalidName = NameDet(region_name);

	if (temp != NULL && invalidName == false && region_size != 0 && region_name != NULL)
	{

		if (region_size % 8 == 0)
		{
		}
		else
		{
			region_size = ((region_size / 8) + 1) * 8;
		}
		numR = numR + 1;
		temp->rName = (char*)region_name;
		temp->rSize = region_size;
		temp->arrayR = malloc(sizeof(char)*(region_size + 1));
		temp->numBlock = 0;
		temp->startAddress = temp->arrayR;
		temp->next = headRegion;
		temp->usedSpace = 0;
		headRegion = temp;

		currentRegion = temp;
		initBlock();
		inited = true;

		assert((temp->usedSpace) == 0);
		assert((temp->usedSpace) < temp->rSize);
		assert(headRegion != NULL);
	}

	return inited;
}

int initBlock()
{
	int i;
	char *start;

	assert(currentRegion->startAddress != NULL);

	start = currentRegion->startAddress;

	for (i = 0; i < currentRegion->rSize; i++)
	{
		*((currentRegion->arrayR) + i) = '1';
	}
	*((currentRegion->arrayR) + i) = '\0';

	assert(currentRegion->arrayR != NULL);

	return 0;
}

Boolean NameDet(const char *region_name)
{
	Boolean findSame = false;
	Region *currentptr = NULL;

	if (headRegion != NULL)
	{
		currentptr = headRegion;
	}
	while ((currentptr != NULL) && (findSame == false) && (headRegion != NULL) && (region_name != NULL) && (strcmp("", region_name) != 0))
	{
		if (strcmp(currentptr->rName, region_name) == 0)
		{
			findSame = true;
		}
		else
		{
			currentptr = currentptr->next;
		}
	}

	return findSame;
}

Boolean rchoose(const char *region_name)
{
	//Region *chosen;
	Boolean foundRegion;
	if (region_name != NULL)
	{
		foundRegion = findRegion(region_name);
	}
	else
	{
		foundRegion = false;
	}

	if (foundRegion)
	{
		foundRegion = true;
	}
	else
	{
		foundRegion = false;
	}

	return foundRegion;
}

Boolean findRegion(const char *region_name)
{
	Boolean findSame = false;
	Region *currentptr = headRegion;

	while ((currentptr != NULL) && (findSame == false))
	{
		if (strcmp(currentptr->rName, region_name) == 0)
		{
			currentRegion = currentptr;
			findSame = true;
		}
		else
		{
			currentptr = currentptr->next;
		}
	}

	return findSame;
}

const char *rchosen()
{
	char *name;

	if (currentRegion == NULL)
	{
		name = NULL;
	}
	else
	{
		name = currentRegion->rName;
	}
	return name;
}

void *ralloc(r_size_t block_size)
{
	int used = currentRegion->usedSpace;
	int total = currentRegion->rSize;
	int i;
	int j;
	int contBytes = 0;
	Boolean enoughSpace = false;
	char *startUse;
	Block *tempB = (Block*)malloc(sizeof(Block));

	assert(currentRegion != NULL);
	assert(numR > 0);
	assert(headRegion != NULL);

	if (block_size%8 != 0)
	{
    block_size = ((block_size / 8) + 1) * 8;
	}

	if ((block_size > (total - used)) || (block_size == 0) || (block_size>total) || (used == total))
	{
		return NULL;
	}
	else
	{
		for (i = 0; (i < currentRegion->rSize) && (enoughSpace == false); i++)
		{
			if ((*((currentRegion->startAddress) + i)) == '1')
			{
				contBytes++;
				if (contBytes == block_size)
				{

					enoughSpace = true;
					startUse = (currentRegion->startAddress) + i - contBytes + 1;
					currentRegion->usedSpace = currentRegion->usedSpace + block_size;
					currentRegion->numBlock = currentRegion->numBlock + 1;
				}
			}
			if ((*((currentRegion->startAddress) + i)) != '1')
			{
				contBytes = 0;
			}
		}
	}

	assert(currentRegion != NULL);
	assert(numR > 0);
	assert(headRegion != NULL);

	if (enoughSpace)
	{

		tempB->blockStart = startUse;
		tempB->bSize = block_size;
		tempB->regionName = currentRegion->rName;
		tempB->next = headBlock;
		headBlock = tempB;

		for (j = 0; j < block_size; j++)
		{
			*((startUse)+j) = '0';
		}

		assert(tempB != NULL);
		assert(tempB->blockStart != NULL);
		assert(tempB->bSize >= 0);
		assert(headBlock != NULL);
	}
	else
	{
		return NULL;
	}

	return startUse;
}

r_size_t rsize(void *block_ptr)
{
	Boolean findBlock = false;
	Block *currentBlock = headBlock;
	int tempBsize;

	while ((currentBlock != NULL) && (findBlock == false))
	{
		if (block_ptr == currentBlock->blockStart)
		{
			findBlock = true;
		}
		else
		{
			currentBlock = currentBlock->next;
		}
	}

	if (findBlock && ((currentBlock->blockStart) >= (currentRegion->startAddress)) && ((currentBlock->blockStart)<((currentRegion->startAddress) + (currentRegion->rSize))))
	{
		assert(currentBlock != NULL);
		assert(currentBlock->bSize >= 0);

		tempBsize = currentBlock->bSize;
	}
	else
	{
		tempBsize = 0;
	}

	assert(tempBsize >= 0);

	return tempBsize;
}

Boolean rfree(void *block_ptr)
{
	Boolean findBlock = false;
	Block *ptrForDelete = headBlock;
	Block *before = ptrForDelete;
	Block *t;

	while ((ptrForDelete != NULL) && (findBlock == false))
	{
		if (ptrForDelete->blockStart == block_ptr)
		{
			findBlock = true;
		}
		else
		{
			before = ptrForDelete;
			ptrForDelete = ptrForDelete->next;
		}
	}

	if (findBlock)
	{
		int j;
		char *blockStart = ptrForDelete->blockStart;
		currentRegion->usedSpace = currentRegion->usedSpace - ptrForDelete->bSize;

		assert(ptrForDelete != NULL);
		assert(numR > 0);
		assert(currentRegion != NULL);
		assert(blockStart != NULL);

		for (j = 0; j < ptrForDelete->bSize; j++)
		{
			*((blockStart)+j) = '1';
		}

		if (ptrForDelete == headBlock)
		{
			headBlock = ptrForDelete->next;
		}
		else
		{
			t = ptrForDelete->next;
			before->next = t;
		}

		free(ptrForDelete);
	}

	return findBlock;
}

void rdestroy(const char *region_name)
{
	Boolean findSame = false;
	Region *ptrForDelete = headRegion;
	Region *before = ptrForDelete;
	Region *t;

	while ((ptrForDelete != NULL) && (findSame == false))
	{
		if (ptrForDelete->rName == region_name)
		{
			findSame = true;
		}
		else
		{
			before = ptrForDelete;
			ptrForDelete = ptrForDelete->next;
		}
	}

	if (findSame)
	{
		if (ptrForDelete == headRegion)
		{
			headRegion = ptrForDelete->next;
			numR--;
		}
		else
		{
			t = ptrForDelete->next;
			before->next = t;
			numR--;
		}

		assert(numR >= 0);

		free(ptrForDelete);
	}
}

void rdump()
{
	Region *printCurrentR;
	Block *printCurrentB;
	float percentage;

	printCurrentR = headRegion;
	printCurrentB = headBlock;

	while (printCurrentR != NULL)
	{
		printCurrentB = headBlock;

		printf("Name:%s\n", printCurrentR->rName);

		while ((printCurrentB != NULL))
		{
			if (strcmp(printCurrentB->regionName, printCurrentR->rName)==0)
			{
				printf("%p   ", printCurrentB->blockStart);
				printf("%d\n", printCurrentB->bSize);
				printCurrentB = printCurrentB->next;
			}
			else
			{
				printCurrentB = printCurrentB->next;
			}
		}
		percentage = (float)(printCurrentR->rSize - printCurrentR->usedSpace) / (printCurrentR->rSize) * 100.0;
		printf("Percentage of free space is %.2f%%\n", percentage);

		printCurrentR = printCurrentR->next;
	}
	printf("\n");

}

