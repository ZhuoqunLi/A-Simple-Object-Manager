//-----------------------------------------
// NAME: Zhuoqun Li
// STUDENT NUMBER: 7740173
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Franklin Bristow
// ASSIGNMENT: assignment 4, QUESTION: question 1
//
// REMARKS: Testing framework
//
//-----------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "regions.h"
//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------
static int testsPassed;
static int testsFailed;
char *ptr1;
char *ptr2;
char *ptr3;
//-------------------------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------------------------
void initSuite();
void testRegionInit();
void testRegionChoose();
void testMakeBlock();
void testBlockSize();
void testFreeBlock();
void testDestroyRegion();
void conclusion();
//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------

int main()
{
	printf("Start Testing.\n\n");

	initSuite();
	testRegionInit();
	testRegionChoose();
	testMakeBlock();
	testFreeBlock();
	testDestroyRegion();
	conclusion();

	fprintf(stderr, "\nEnd of processing.\n");

	return EXIT_SUCCESS;
}

void initSuite()
{
	testsPassed = 0;
	testsFailed = 0;
}

void testRegionInit()
{
	printf("Test rinit() Function.\n");

	printf("Case 1: Initialize a normal region.\n");
	if (rinit("gta 5", 640) == true)
	{
		printf("Case 1 passed.\n");
		testsPassed++;
	}
	else
	{
		printf("Case 1 failed\n");
		testsFailed++;
	}

	printf("Case 2: Initialize another normal region.\n");
	if (rinit("fallout 4", 400) == true)
	{
		printf("Case 2 passed.\n");
		testsPassed++;
	}
	else
	{
		printf("Case 2 failed\n");
		testsFailed++;
	}

	printf("Case 3: Initialize a region with an used name.\n");
	if (rinit("fallout 4", 500) == false)
	{
		printf("Case 3 passed.\n");
		testsPassed++;
	}
	else
	{
		printf("Case 3 failed\n");
		testsFailed++;
	}

	printf("Case 4: Initialize a region with no name.\n");
	if (rinit(NULL, 3000) == false)
	{
		printf("Case 4 passed.\n");
		testsPassed++;
	}
	else
	{
		printf("Case 4 failed\n");
		testsFailed++;
	}

	printf("Case 5: Initialize a region with size of 0.\n");
	if (rinit("half life 3", 0) == false)
	{
		printf("Case 5 passed.\n");
		testsPassed++;
	}
	else
	{
		printf("Case 5 failed\n");
		testsFailed++;
	}

	printf("Now, It's the all regions we got:\n");
	rdump();
}

void testRegionChoose()
{
	printf("Test rchoose() and rchosen() Functions.\n");

	printf("Case 1: choose an exist region.\n");
	if (rchoose("gta 5") == true)
	{
		printf("Case 1 passed.\n");
		testsPassed++;
	}
	else
	{
		printf("Case 1 failed\n");
		testsFailed++;
	}

	if (strcmp(rchosen(), "gta 5")==0)
	{
		printf("rchosen() funtion shows the corret region name.\n");
		testsPassed++;
	}
	else
	{
		printf("rchosen() funtion shows the wrong region name.\n");
		testsFailed++;
	}

	printf("Case 2: choose a not exist region.\n");
	if (rchoose("Uncharted 5") == false)
	{
		printf("Case 2 passed.\n");
		testsPassed++;
	}
	else
	{
		printf("Case 2 failed\n");
		testsFailed++;
	}

	if (strcmp(rchosen(), "gta 5") == 0)
	{
		printf("rchosen() funtion shows the corret region name.\n");
		testsPassed++;
	}
	else
	{
		printf("rchosen() funtion shows the wrong region name.\n");
		testsFailed++;
	}

	printf("Now, It's the all regions we got:\n");
	rdump();
}

void testMakeBlock()
{

	printf("Test ralloc() and rsize() Functions.\n");

	printf("Shows the current select Region.\n");
	if (strcmp(rchosen(), "gta 5") == 0)
	{
		printf("The current region is \"gta 5\".\n");
		testsPassed++;
	}
	else
	{
		printf("rchosen() funtion shows the wrong region name.\n");
		testsFailed++;
	}

	printf("Case 1: allocate a normal block in the current region: Add a block in to \"gta 5\", size is 400.\n");
	ptr1 = ralloc(400);
	if (rsize(ptr1)==400)
	{
		printf("Case 1 passed.\n");
		testsPassed++;
	}
	else
	{
		printf("Case 1 failed\n");
		testsFailed++;
	}

	printf("Case 2: allocate a 0 size block in the current region: Add a block in to \"gta 5\", size is 0.\n");
	if (rsize(ralloc(0))==0)
	{
		printf("Case 2 passed.\n");
		testsPassed++;
	}
	else
	{
		printf("Case 2 failed\n");
		testsFailed++;
	}

	printf("Case 3: allocate a normal size block in the current region: Add a block in to \"gta 5\", size is 240.\n");
	ptr2 = ralloc(240);
	if (rsize(ptr2)==240)
	{
		printf("Case 3 passed.\n");
		testsPassed++;
	}
	else
	{
		printf("Case 3 failed\n");
		testsFailed++;
	}

	printf("Case 4: allocate a normal block in the current region with no space: Add a block in to \"gta 5\", size is 1.\n");
	if (rsize(ralloc(1))==0)
	{
		printf("Case 4 passed.\n");
		testsPassed++;
	}
	else
	{
		printf("Case 4 failed\n");
		testsFailed++;
	}

	printf("Now, It's the all regions we got:\n");
	rdump();

}

void testFreeBlock()
{
	printf("Test rfree() Function.\n");

	printf("Shows the current select Region.\n");
	if (strcmp(rchosen(), "gta 5") == 0)
	{
		printf("The current region is \"gta 5\".\n");
		testsPassed++;
	}
	else
	{
		printf("rchosen() funtion shows the wrong region name.\n");
		testsFailed++;
	}

	printf("Case 1: free the block which size is 400.\n");
	if (rfree(ptr1))
	{
		printf("Case 1 passed.\n");
		testsPassed++;
	}
	else
	{
		printf("Case 1 failed.\n");
		testsFailed++;
	}

	printf("Case 2: free the block which pointer to NULL.\n");
	if (!rfree(NULL))
	{
		printf("Case 2 passed.\n");
		testsPassed++;
	}
	else
	{
		printf("Case 2 failed.\n");
		testsFailed++;
	}

	printf("Case 3: free the block which size is 240.\n");
	if (rfree(ptr2))
	{
		printf("Case 3 passed.\n");
		testsPassed++;
	}
	else
	{
		printf("Case 3 failed.\n");
		testsFailed++;
	}

	printf("Case 4: allocate a 640 size block in the current region: Add a block in to \"gta 5\", size is 640.\n");
	ptr3 = ralloc(640);
	if (rsize(ptr3)==640)
	{
		printf("Case 4 passed.\n");
		testsPassed++;
	}
	else
	{
		printf("Case 4 failed.\n");
		testsFailed++;
	}

	printf("Case 5: free the block which size is 640.\n");
	if (rfree(ptr3))
	{
		printf("Case 5 passed.\n");
		testsPassed++;
	}
	else
	{
		printf("Case 5 failed.\n");
		testsFailed++;
	}

	printf("Now, It's the all regions we got:\n");
	rdump();
}

void testDestroyRegion()
{
	printf("Test rDestroy() Function.\n");

	printf("Shows the current select Region.\n");
	if (strcmp(rchosen(), "gta 5") == 0)
	{
		printf("The current region is \"gta 5\".\n");
		testsPassed++;
	}
	else
	{
		printf("rchosen() funtion shows the wrong region name.\n");
		testsFailed++;
	}

	printf("Case 1: destroy the block named \"gta 5\".\n");
	rdestroy("gta 5");
	if (rchoose("gta 5")==false)
	{
		printf("Case 1 passed.\n");
		testsPassed++;
	}
	else
	{
		printf("Case 1 failed.\n");
		testsFailed++;
	}

	printf("Case 2: destroy the block named \"fallout 4\".\n");
	rdestroy("fallout 4");
	if (rchoose("fallout 4") == false)
	{
		printf("Case 2 passed.\n");
		testsPassed++;
	}
	else
	{
		printf("Case 2 failed.\n");
		testsFailed++;
	}

	printf("Case 3: Initialize a new region named \"fallout 4\".\n");
	if (rinit("fallout 4", 640))
	{
		printf("Case 3 passed.\n");
		testsPassed++;
	}
	else
	{
		printf("Case 3 failed.\n");
		testsFailed++;
	}

	printf("Now, It's the all regions we got:\n");
	rdump();
}
void conclusion()
{

	printf("\nTest results:\n");
	printf("%d tests were run.\n", testsPassed + testsFailed);
	printf("%d tests passed.\n", testsPassed);
	printf("%d tests failed.\n", testsFailed);
}