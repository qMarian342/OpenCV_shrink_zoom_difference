#include "stdafx.h"
#include "common.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>

using namespace cv;
using namespace std;

wchar_t* projectPath;

/*
	Nearest Neighbor
Calculeaza pixelul corespunzator imaginii noi din imaginea originala - 
	apoi alege pixelul cel mai apropiat
*/
void resizeNearest(Mat src, Mat& dst, float scale)
{
	int srcH = src.rows;
	int srcW = src.cols;

	//resize
	int dstH = (int)(srcH * scale);
	int dstW = (int)(srcW * scale);

	dst = Mat(dstH, dstW, CV_8UC1);

	for (int i = 0; i < dstH; i++)
	{
		for (int j = 0; j < dstW; j++)
		{
			//calcul coordonata corespunzatoare
			float y = i / scale;
			float x = j / scale;

			//rotunjire
			int ys = (int)(y + 0.5);
			int xs = (int)(x + 0.5);

			if (ys >= srcH) ys = srcH - 1;
			if (xs >= srcW) xs = srcW - 1;

			dst.at<uchar>(i, j) = src.at<uchar>(ys, xs);
		}
	}
}

/*
	Bilinear Interpolation
Ia un singur pixel din imaginea sursa si foloseste 
	media ponderata a celor 4 vecini ai pixelului
Fiecare pixel e calculat gradual
*/

void resizeBilinear(Mat src, Mat& dst, float scale)
{
	int srcH = src.rows;
	int srcW = src.cols;

	int dstH = (int)(srcH * scale);
	int dstW = (int)(srcW * scale);

	dst = Mat(dstH, dstW, CV_8UC1);

	for (int i = 0; i < dstH; i++)
	{
		for (int j = 0; j < dstW; j++)
		{
			float y = i / scale;
			float x = j / scale;

			//pixel LU
			int y0 = (int)floor(y);
			int x0 = (int)floor(x);

			//pixel jos-dreapta - ultimul valid
			int y1 = min(y0 + 1, srcH - 1);
			int x1 = min(x0 + 1, srcW - 1);

			//greutatea - practic cat e de departe poz reala fata de y0
			float a = x - x0;
			float b = y - y0;

			float val =
				(1 - a) * (1 - b) * src.at<uchar>(y0, x0) + //LU
				a * (1 - b) * src.at<uchar>(y0, x1) + //RU
				(1 - a) * b * src.at<uchar>(y1, x0) + //LD
				a * b * src.at<uchar>(y1, x1); //RD

			dst.at<uchar>(i, j) = (uchar)val;
		}
	}
}

// TEST 

void testZoomShrink()
{
	char fname[MAX_PATH];

	while (openFileDlg(fname))
	{
		Mat src = imread(fname, IMREAD_GRAYSCALE);

		if (!src.data)
		{
			printf("Image could not be opened\n");
			return;
		}

		float scale;

		printf("Zoom > 1 | Shrink < 1\n");
		printf("Scale factor = ");

		scanf("%f", &scale);

		Mat dstNearest;
		Mat dstBilinear;

		resizeNearest(src, dstNearest, scale);
		resizeBilinear(src, dstBilinear, scale);

		imshow("Original", src);
		imshow("Nearest Neighbor", dstNearest);
		imshow("Bilinear Interpolation", dstBilinear);

		waitKey(0);
	}
}

// MAIN

int main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_FATAL);
	projectPath = _wgetcwd(0, 0);

	int op;

	do
	{
		system("cls");
		destroyAllWindows();

		printf("Menu:\n");
		printf("1 - Open image\n");
		printf("2 - Zoom / Shrink image\n");
		printf("0 - Exit\n\n");

		printf("Option: ");
		scanf("%d", &op);

		switch (op)
		{

		case 1:
		{
			char fname[MAX_PATH];

			while (openFileDlg(fname))
			{
				Mat src = imread(fname);
				imshow("Image", src);
				waitKey();
			}
			break;
		}

		case 2:
			testZoomShrink();
			break;

		}

	} while (op != 0);

	return 0;
}