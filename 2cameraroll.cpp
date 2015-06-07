#include <opencv/cv.h>
#include <opencv/highgui.h>

int main()
{
	IplImage* image = 0;
	IplImage* reverse = 0;

	CvCapture* video = cvCaptureFromCAM(-1);

	cvNamedWindow("Original Video",0);
	cvNamedWindow("Reverse Video",0);

	while(1)
	{
		cvGrabFrame(video);
		image = cvRetrieveFrame(video);
		cvShowImage("Original Video",image);

		reverse = cvCreateImage(cvGetSize(image),image->depth,image->nChannels);

		cvNot(image,reverse);

		if(cvWaitKey(10) >=0)
			break;

		reverse->origin=image->origin;
		cvShowImage("Reverse Video",reverse);
	}

	cvReleaseImage(&reverse);
	cvReleaseCapture(&video);
	cvDestroyWindow("Reverse Video");
	cvDestroyWindow("Original Video");
	return 0;
}

