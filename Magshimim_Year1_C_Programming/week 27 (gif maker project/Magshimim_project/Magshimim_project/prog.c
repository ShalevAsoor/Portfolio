#define CV_IGNORE_DEBUG_BUILD_GUARD
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "view.h"
#include "linkedList.h"
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <stdio.h>
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui_c.h>

void myFgets(char str[], int n)
{
	fgets(str, n, stdin);
	str[strcspn(str, "\n")] = "\0";
}


int main()
{


	FrameNode* newFrame = NULL;
	FrameNode* gif = NULL;
	int choice, n = 0, x = 0;
	char* name = malloc((50) * sizeof(char));
	char* projName = malloc((50) * sizeof(char));

	printf("Welcome to magshimim movie maker! what would you like to do? \n");
	printf("  [0] Create a new project\n  [1] Load an existing project\n");
	scanf("%d", &choice);
	getchar();

	if (choice == 0)
	{
		do
		{

			printf("What would you like to do?\n [0] Exit\n [1] Add a new frame\n [2] Remove a frame\n [3] Change frame index\n [4] Change frame duration\n [5] Change duration of all frames\n [6] List frames\n [7] Play movie!\n [8] save Project\n [9] save Project and exit\n");
			scanf("%d", &choice);
			getchar();

			switch (choice)
			{
			case 0:
				break;
			case 1:
				AddNewFrame(&gif);
				break;
			case 2:
				printf("Enter frame postion: ");
				scanf("%d", &n);
				getchar();

				deletePosition(&gif, n);
				break;

			case 3:
				printf("Enter new frame index: ");
				scanf("%d", &n);
				getchar();

				printf("Enter frame name: ");
				myFgets(name, 50);

				printf("%s", name);
				changeIndex2(&gif, name, n);
				break;

			case 4:
				printf("Enter frame postion: ");
				scanf("%d", &n);
				getchar();

				printf("Enter new duration: ");
				scanf("%d", &x);
				getchar();

				changeDurr1frame(&gif, x, n);
				break;

			case 5:
				printf("Enter new duration: ");
				scanf("%d", &x);
				getchar();

				changeDurrAllframe(&gif, x);
				break;

			case 6:
				PrintListFrame(&gif);
				break;

			case 7:
				play(gif);
				break;
			case 8:
				printf("Enter your projects name: ");
				myFgets(projName, 50);
				projName[strlen(projName) - 1] = '\0';


				writeToFile(&gif, projName);
				break;
			case 9:
				printf("Enter your projects name: ");
				myFgets(projName, 50);
				projName[strlen(projName) - 1] = '\0';

				writeToFile(&gif, projName);
				choice = 0;
				break;
			default:
				printf("you can only pick an option from the ones listed below\n\n");
				break;
			}
		} while (choice != 0);
		printf("Bye!");
	}
	else if (choice == 1)
	{
		printf("Enter your projects name: ");
		myFgets(projName, 50);
		projName[strlen(projName) - 1] = '\0';
		readFromFile(&gif, projName);
		do {

			printf("What would you like to do?\n [0] Exit\n [1] Add a new frame\n [2] Remove a frame\n [3] Change frame index\n [4] Change frame duration\n [5] Change duration of all frames\n [6] List frames\n [7] Play movie!\n [8] save Project\n [9] save Project and exit\n");
			scanf("%d", &choice);
			getchar();

			switch (choice)
			{
			case 0:
				break;
			case 1:
				AddNewFrame(&gif);
				break;
			case 2:
				printf("Enter frame postion: ");
				scanf("%d", &n);
				getchar();

				deletePosition(&gif, n);
				break;

			case 3:
				printf("Enter new frame index: ");
				scanf("%d", &n);
				getchar();

				printf("Enter frame name: ");
				myFgets(name, 50);
				name[strlen(name) - 1] = '\0';

				printf("%s", name);
				changeIndex2(&gif, name, n);
				break;

			case 4:
				printf("Enter frame postion: ");
				scanf("%d", &n);
				getchar();

				printf("Enter new duration: ");
				scanf("%d", &x);
				getchar();

				changeDurr1frame(&gif, x, n);
				break;

			case 5:
				printf("Enter new duration: ");
				scanf("%d", &x);
				getchar();

				changeDurrAllframe(&gif, x);
				break;

			case 6:
				PrintListFrame(&gif);
				break;

			case 7:
				play(gif);
				break;
			case 8:
				writeToFile2(&gif, projName);
				break;
			case 9:
				writeToFile2(&gif, projName);
				choice = 0;
				break;
			default:
				printf("you can only pick an option from the ones listed below\n\n");
				break;
			}
		} while (choice != 0);
		printf("Bye!");

	}
	return 0;
	
}





