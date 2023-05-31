#ifndef LINKEDLISTH
#define LINKEDLISTH

#define FALSE 0
#define TRUE !FALSE

// Frame struct
typedef struct Frame
{
	char* name;
	unsigned int duration;
	char* path;  
} Frame;


// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;

Frame* createFrame(char* name, unsigned int duration, char* path);
FrameNode* createNode(Frame* frame);
void insertAtEnd(FrameNode** head, FrameNode* newNode);
void AddNewFrame(FrameNode** gif);
void deletePosition(struct FrameNode** head, int n);
int getCurrSize(struct FrameNode* node);
void changeDurr1frame(FrameNode** head, int durr, int n);
void changeDurrAllframe(FrameNode** head, int durr);
void PrintListFrame(FrameNode** head);
void changeIndex2(FrameNode** head, char* name, int index);
void writeToFile(FrameNode** head, char* name);
void writeToFile2(FrameNode** head, char* name);
void readFromFile(FrameNode** head, char* name);
#endif
