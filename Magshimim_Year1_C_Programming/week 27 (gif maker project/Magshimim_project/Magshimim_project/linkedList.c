#define CV_IGNORE_DEBUG_BUILD_GUARD
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include "view.h"
#include "linkedList.h"

Frame* createFrame(char* name, unsigned int duration, char* path)
{
	Frame* frame = (Frame*)malloc(sizeof(Frame));
	frame->duration = duration;
	frame->name = name;
	frame->path = path;

	return frame;
}

FrameNode* createNode(Frame* frame)
{
	FrameNode* frameNode = (FrameNode*)malloc(sizeof(FrameNode));
	frameNode->frame = frame;
	frameNode->next = NULL;
	return frameNode;
}
void AddNewFrame(FrameNode** gif)
{
    int frames = 0, i = 0, durr = 0;
    char* path = malloc((100) * sizeof(char));
    char* name = malloc((50) * sizeof(char));

    Frame* frame = NULL;
    FrameNode* newFrame = NULL;

    printf("\nenter gif path:");
    myFgets(path, 100);
	path[strlen(path) - 1] = '\0';


    printf("\nenter frame name: ");
    myFgets(name, 50);
	name[strlen(name) - 1] = '\0';


	printf("\nenter frame duration: ");
	scanf_s("%d", &durr);
	getchar();

    frame = createFrame(name, durr, path);

    newFrame = createNode(frame);

    insertAtEnd(gif, newFrame);



}

void deletePosition(FrameNode** head, int n)
{
    FrameNode* temp = *head;
    FrameNode* previous = NULL;


    int size = getCurrSize(*head);


    if (n < 1 || n > size) {
        printf("Enter valid position\n");
        return;
    }


    if (n == 1) {

        *head = (*head)->next;
        free(temp);
        return;
    }


    while (--n)
    {

        previous = temp;
        temp = temp->next;
    }

    previous->next = temp->next;


    free(temp);
}


int getCurrSize(FrameNode* node) {
    int size = 0;

    while (node != NULL) {
        node = node->next;
        size++;
    }
    return size;
}

void writeToFile(FrameNode** head, char* name)
{
	FrameNode* temp = *head;

	FILE* fp = fopen(strcat(name, ".txt"), "w");
	while (temp != NULL)
	{
		fprintf(fp, ".\n%s\n%s\n%d\n", temp->frame->name, temp->frame->path, temp->frame->duration);
		temp = temp->next;
	}
	fclose(fp);
}

void writeToFile2(FrameNode** head, char* name)
{
	FrameNode* temp = *head;

	FILE* fp = fopen(name, "w");
	while (temp != NULL)
	{
		fprintf(fp, ".\n%s\n%s\n%d\n", temp->frame->name, temp->frame->path, temp->frame->duration);
		temp = temp->next;
	}
	fclose(fp);
}

void readFromFile(FrameNode** head, char* name)
{

	char line[100];


	FILE* file = fopen(strcat(name, ".txt"), "r");

	while (fgets(line, 50, file) != NULL)
	{
		FrameNode* temp = *head;
		Frame* frame = NULL;
		FrameNode* newFrame = NULL;
		int duration = 0;
		char* path = malloc((100) * sizeof(char));
		char* namee = malloc((50) * sizeof(char));
		char* durr = malloc((50) * sizeof(char));

		fgets(namee, 50, file);
		namee[strlen(namee) - 1] = '\0';
		fgets(path, 100, file);
		path[strlen(path) - 1] = '\0';
		fgets(durr, 100, file);
		duration = atoi(durr);

		frame = createFrame(namee, duration, path);

		newFrame = createNode(frame);

		insertAtEnd(head, newFrame);

	}
	fclose(file);
}



void insertAtEnd(FrameNode** head, FrameNode* newNode)
{

	if (!*head)
	{
		*head = newNode;
	}
	else
	{
		FrameNode* p = *head;
		while (p->next)
		{
			p = p->next;
		}
		p->next = newNode;
	}
}

void changeDurr1frame(FrameNode** head, int durr, int n)
{
	FrameNode* temp = *head;
	FrameNode* previous = NULL;

	int size = getCurrSize(*head);

	if (n < 1 || n > size) {
		printf("Enter valid position\n");
		return;
	}

	if (n == 1) {

		temp->frame->duration = durr;
		return;
	}


	while (--n)
	{
		previous = temp;
		temp = temp->next;
	}

	temp->frame->duration = durr;
	printf("Frame %s durations was changed to: %d\n", temp->frame->path, durr);
	return;

}

void changeDurrAllframe(FrameNode** head, int durr)
{
	FrameNode* temp = *head;
	FrameNode* curr = *head;

	while (curr)
	{
		temp = temp->next;
		curr->frame->duration = durr;
		curr = temp;
	}
}

void PrintListFrame(FrameNode** head)
{
	FrameNode* temp = *head;

	printf("\t\tName \t\t Duration\t\t Path");
	while (temp != NULL)
	{
		printf("\n\t\t%s \t\t %d ms\t\t %s", temp->frame->name, temp->frame->duration, temp->frame->path);
		temp = temp->next;
	}
	printf("\n\n");
}

void changeIndex2(FrameNode** head, char* name, int index)
{
	FrameNode* beforeMoved = NULL;
	FrameNode* beforeIndex = NULL;
	FrameNode* atIndex = *head;
	FrameNode* toMove = *head;

	int counter = 0;
	int flag = 0;


	while (toMove && flag == 0)
	{
		if (strcmp(toMove->frame->name, name) == 0)
		{
			flag = 1;

		}
		else
		{
			beforeMoved = toMove;
			toMove = toMove->next;
		}
	}


	while (atIndex && (counter != index))
	{

		counter++;
		beforeIndex = atIndex;
		atIndex = atIndex->next;
	}

	if (toMove && (atIndex || index + 1 == counter) && (toMove != atIndex))
	{
		if (beforeMoved == NULL)
			*head = (*head)->next;
		else
			beforeMoved->next = toMove->next;   // splice moving node out of linked list

		if (beforeIndex == NULL)
			*head = toMove;
		else
			beforeIndex->next = toMove;         // add moving node to correct location

		toMove->next = atIndex;             // reconnect node previously at index
	}
}