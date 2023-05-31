/*********************************
* Class: MAGSHIMIM C2			*
* Week:                		   *
* Name:                        *
* Credits:                      *
**********************************/

#include <stdio.h>
#include "dirent.h"
#include <string.h>
#include <stdbool.h>


#define WELCOME "Anti-virus began! Welcome!\n\nThe folder you want to scan: %s\nThe virus signature you entered: %s\n\nPress 0 to do a normal scan or press any other key to do a quick scan: "
#define LOG_WELCOME "Anti-virus began! Welcome!\n\nFolder to scan: % s\nVirus sign: %s\n\n"
#define LOG_NAME "/MagshiAVLog.txt"
#define INFECTED_FIRST "Infected! (first 20%%)\n"
#define INFECTED_LAST "Infected! (last 20%%)\n"
#define INFECTED "Infected!\n"
#define NOT_INFECTED "clean\n"
#define LOG_LOCATION "the scan is over.\nyou can see the logs in %s\\MagshiAVLog.txt\n"

int FileScanning(char* filePath, FILE* virusSigniture, int qScan);
void QuickOrNormal(bool choice, FILE* logFile);

int main(int argc, char** argv)
{
	int i = 0, j = 0, result = 0;
	char* switcher = NULL;
	DIR* folder = NULL;
	FILE* sign = NULL;
	struct dirent* dir = 0;

	if (argc != 3)
		printf("NOT ENOUGH ARGUMENTS/TOO MANY ARGUMENTS");

	else {
		int choice = 0;
		printf(WELCOME, argv[1], argv[2]);
		scanf("%d", &choice);

		folder = opendir(argv[1]);


		if (folder == NULL)
			printf("error opening the folder.");


		sign = fopen(argv[2], "rb");

		if (sign == NULL)
		{
			closedir(folder);
			printf("error opening the virus signiture.");
		}

		char* logLocation = (char*)calloc(strlen(argv[1]) + 16, sizeof(char));

		strcat(logLocation, argv[1]);
		strcat(logLocation, LOG_NAME);

		FILE* logFile = fopen(logLocation, "w");

		fprintf(logFile, LOG_WELCOME, argv[1], argv[2]);

		QuickOrNormal(choice, logFile); //writes to the log file if the scan was a quick one or normal one


		printf("\n\nScanning:\n");

		int numOfFiles = 0, virus = 0, i = 0;
		size_t sizePath;
		char* filePath = NULL;
		char** files = NULL;

		while ((dir = readdir(folder)) != NULL)
		{

			sizePath = strlen((*dir).dirName) + strlen(argv[1]) + 1;
			filePath = (char*)calloc(sizePath, sizeof(char));

			strcat(filePath, argv[1]);
			strcat(filePath, "/");
			strcat(filePath, (*dir).dirName);

			files = (char**)realloc(files, sizeof(char*) * (numOfFiles + 1));
			files[numOfFiles] = (char*)calloc(strlen(filePath), sizeof(char));
			strcpy(files[numOfFiles], filePath);

			numOfFiles++;

		}

		for (i = 0; i < numOfFiles - 1; i++)
			for (j = 0; j < numOfFiles - i - 1; j++)

				if (strcmp(files[j], files[j + 1]) > 0)
				{
					switcher = files[j];
					files[j] = files[j + 1];
					files[j + 1] = switcher;
				}

		for (i = 0; i < numOfFiles; i++)
		{
			virus = FileScanning(files[i], sign, choice);

			if (choice) //checks if there was a quick scan or not
			{
				fprintf(logFile, "%s - ", files[i]);
				if (virus == 2)
					fprintf(logFile, INFECTED_FIRST);

				else if (virus == 3)
					fprintf(logFile, INFECTED_LAST);


				else if (virus == 4)
					fprintf(logFile, INFECTED);


				else
					fprintf(logFile, NOT_INFECTED);



				printf("%s - ", files[i]);
				if (virus == 2)
					printf(INFECTED_FIRST);

				else if (virus == 3)
					printf(INFECTED_LAST);


				else if (virus == 4)
					printf(INFECTED);


				else
					printf(NOT_INFECTED);

			}


			else
			{
				fprintf(logFile, "%s - ", files[i]);
				if (virus)

					fprintf(logFile, INFECTED);

				else

					fprintf(logFile, NOT_INFECTED);

				printf("%s - ", files[i]);

				if (virus)

					printf(INFECTED);

				else

					printf(NOT_INFECTED);
			}
		}

		printf(LOG_LOCATION, argv[1]);


	}

	getchar();
	getchar();
	return 0;
}






void QuickOrNormal(bool choice, FILE* logFile)
{
	/*
		this function prints to the log file if the scan was a quick scan or not
	*/
	if (choice)
		fprintf(logFile, "Scanning option: %s\n", "Quick scan");

	else
		fprintf(logFile, "Scanning option: %s\n", "Normal scan");
}







int FileScanning(char* filePath, FILE* virusSign, int qScan)
{
	/*
	this fucntion returns true if there is a virus and false if there isnt, also check if a quick scanf is needed
	*/
	int i = 0;
	FILE* curr = NULL;
	curr = fopen(filePath, "rb");
	int virusType = 0;





	if (curr == NULL)
		return false;

	else
	{
		char fc = ' ', vc = ' ';
		int virusSignature = 0, last = 0, first = 0;

		int vSize = 0; //virus signature size
		fseek(virusSign, 0, SEEK_END);
		vSize = ftell(virusSign);
		fseek(virusSign, 0, SEEK_SET);



		int fileSize = 0; //file size
		fseek(curr, 0, SEEK_END);
		fileSize = ftell(curr);
		fseek(curr, 0, SEEK_SET);

		int twenty = (int)(0.2 * fileSize); //getting the 20 precent




		while ((fread(&fc, sizeof(char), 1, curr)) > 0 && (fread(&vc, sizeof(char), 1, virusSign)) > 0)
		{
			if (qScan)
			{

				if (virusSignature < (vSize - 1) && !last && ftell(curr) == fileSize)
				{
					virusSignature = 0;
					fseek(virusSign, 0, SEEK_SET);
					fseek(curr, 0, SEEK_SET);
					last = 1;

				}
				else if (!first && ftell(curr) == (twenty - 1))
				{
					virusSignature = 0;
					fseek(curr, -twenty, SEEK_END);
					fseek(virusSign, 0, SEEK_SET);
					first = 1;
				}
			}





			if (fc != vc)
			{
				virusSignature = 0;
				fseek(virusSign, 0, SEEK_SET);
			}

			virusSignature++;
		}






		if (virusSignature >= vSize)
		{
			// 2 means the virus was found in the first 20%, 3 means the virus was found in the last 20% and 4 mean normal scan was initiated
			if (first == false && last == false)
				virusType = 2;

			else if (first && last == false)
				virusType = 3;

			else
				virusType = 4;
		}
	}
	fclose(curr);

	return virusType;
}
