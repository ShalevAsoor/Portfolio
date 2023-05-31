///*********************************
//* Class: MAGSHIMIM C2			 *
//* openCV template      			 *
//**********************************/
//#define CV_IGNORE_DEBUG_BUILD_GUARD
//#include "view.h"
//#include <opencv2/imgcodecs/imgcodecs_c.h>
//#include <stdio.h>
//#include <opencv2/core/core_c.h>
//#include <opencv2/highgui/highgui_c.h>
//
//int main(void)
//{
//	int i;
//	cvNamedWindow("Display window", CV_WINDOW_AUTOSIZE); //create a window
//	//create an image
//	IplImage* image = cvLoadImage("C:\\Users\\USER\\Desktop\\kof.jpg", 1);
//	if (!image)//The image is empty.
//	{
//		printf("could not open image\n");
//	}
//	else
//	{
//		cvShowImage("kof.jpg", image);
//		cvWaitKey(0);
//		system("pause");
//		cvReleaseImage(&image);
//	}
//	return 0;
//}