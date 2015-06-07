#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <iostream>
#include <cv.h>
#include <highgui.h> 

int main()
{
	int x = 0, y = 0;
	char Cr = 0, Cb = 0;
	int width = 640, height = 320;

	IplImage *frame = 0;
	//CvCapture* capture = cvCaptureFromCAM(0);//download avi from cam
	CvCapture *capture = cvCaptureFromFile("test1.3gp");
	frame = cvQueryFrame(capture);//captured image from cam save to the pointer frame	
	cvNamedWindow("Original",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Result",0);

	height = frame->height;//chosen frame's height
	width = frame->width;//chosen frame's width


 	IplImage *bkgImage = cvLoadImage( "bg1.png", CV_LOAD_IMAGE_GRAYSCALE); 
	//first back ground image  
	cvCvtColor(bkgImage,bkgImage,CV_RGB2YCrCb);    
	cvCvtColor(bkgImage, bkgImage, CV_BGR2GRAY);
	//back groung image convert to YCrCb to gray
	


	IplImage* YCrCb = cvCreateImage(cvGetSize(frame),8,3);
	IplImage *grayImage = cvCreateImage(cvGetSize(frame), 8, 1); 
	IplImage *diffImage = cvCreateImage(cvGetSize(frame), 8, 1);
	int t=0;

	height = frame->height;
	width = frame->width;
	
	while(capture)
	{
		frame = cvQueryFrame(capture);
		if(!frame)
			break;
		t++;
		std::cout << t << std::endl; 
		cvShowImage("Original",frame);
		cvCvtColor(frame,YCrCb,CV_RGB2YCrCb);
		cvCvtColor(frame, grayImage, CV_RGB2GRAY);
		cvAbsDiff(grayImage, bkgImage, diffImage);                

		cvThreshold(diffImage, diffImage,50 , 255, CV_THRESH_BINARY);
		
		cvSmooth(diffImage,diffImage,CV_BLUR,7,7,0,0);
		                
		cvShowImage("YCrCbImage", YCrCb); 
		cvShowImage("grayImage", grayImage);        
		cvShowImage("diffImage", diffImage);
// diffImage에서 0인 화소는 변화가 없는 화소이며, 값이 크면 클수록 배경 영상과의 차이가 크게 일어난 화소이다.        
// cvThreshold 함수를 사용하여 cvThreshold=50 이상인 화소만을 255로 저장하고, 임계값 이하인 값은 0으로 저장한다.        
               
		char chKey = cvWaitKey(10);        
		if( chKey == 27 )    {    // Esc           
		break;        
		}    
	}
		/*for(y=0; y<height;y++) //seohyun's cording
		  {
			for(x=0; x<width; x++)
			 {
				Cr = (char)YCrCb->imageData[y*YCrCb->widthStep+3*x+1];
				Cb = (char)YCrCb->imageData[y*YCrCb->widthStep+3*x+2];
	
				if( (77<Cr&&Cr<127) && (133<Cb&&Cb<173) )
					Skin->imageData[y*Skin->widthStep+x] = 0;
				else
	
					Skin->imageData[y*Skin->widthStep+x] = 255;
			}
		}

		cvShowImage("Result",Skin);
		if(cvWaitKey(33) >= 27)
			break;
	}*/

	
	cvReleaseImage(&grayImage);    
	cvReleaseImage(&diffImage);    
	cvReleaseCapture(&capture);
	
		return 0;
}
