/*********************************
* Class: MAGSHIMIM Final Project *
* Play function				 	 *
**********************************/
#define CV_IGNORE_DEBUG_BUILD_GUARD
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <stdio.h>
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui_c.h>
#include "view.h"
#include "linkedList.h"

/**
play the movie!!
display the images each for the duration of the frame one by one and close the window
input: a linked list of frames to display
output: none
**/
void play(FrameNode* list)
{
	cvNamedWindow("Display window", CV_WINDOW_AUTOSIZE); //create a window
	FrameNode* head = list;
	int imgNum = 1, playCount = 0;
	IplImage* image;
	while (playCount < GIF_REPEAT)
	{
		while (list != 0)
		{
			image = cvLoadImage(list->frame->path, 1);

			IplImage* pGrayImg = 0;
			pGrayImg = cvCreateImage(cvSize(image->width, image->height), image->depth, 1);
			if (!image) //The image is empty - shouldn't happen since we checked already.
			{
				printf("Could not open or find image number %d", imgNum);
			}
			else
			{
				cvShowImage("Display window", image); //display the image
				cvWaitKey(list->frame->duration); //wait
				list = list->next;
				cvReleaseImage(&image);
			}
			imgNum++;
		}
		list = head; // rewind
		playCount++;
	}
	cvDestroyWindow("Display window");
}