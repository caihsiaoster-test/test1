// Compute disparity maps for rectified stereo pairs
// using dynamic programming
// input:
//      argv[1] : path to left image
//      argv[2] : path to right image

#include <iostream>
#include <cv.h>
#include <highgui.h>

using namespace std;

#define PIXEL(img,x,y)	((unsigned char *)(&img->imageData[img->widthStep*y+img->nChannels*(img->depth/8)*x]))
const double OC = 0.01;	// Occlusion Constant (value of 0.01 should be fine, adjust if needed)
const int INF = 99999;

int main(int argc, char** argv) {
  if (argc != 3) {
    cerr << "usage: "<< argv[0] << "   [left image file]  [right image file]"<<endl;
    return 1;
  }
  IplImage *left_image = cvLoadImage(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  IplImage *right_image = cvLoadImage(argv[2], CV_LOAD_IMAGE_GRAYSCALE);
  if (!left_image || !right_image) {
    cerr<< "Error reading input image!"<< endl;
    return 1;
  }
  
  int width_l = left_image->width;
  int width_r = right_image->width;
  int height_l = left_image->height;
  int height_r = right_image->height;
  
  // initialize cost matrix
  double **cost = new double*[width_l+1];
  for (int i = 0; i < width_l+1; ++i) {
    cost[i] = new double[width_r+1];
  }
  // initialize matching table
  int **match = new int*[width_l+1];
  for (int i = 0; i < width_l+1; ++i) {
    match[i] = new int[width_r+1];
  }
  
  // initialize disparity table
  int **dis = new int*[height_l];
  for (int i = 0; i < height_l; ++i) {
    dis[i] = new int[width_l];
  }
  
  double min = 9999;
  double max = 0;
  
  for (int i = 0; i < height_l; ++i) {
    // Compute 1D disparity map between two vectors
    // using dynamic programming.
    //
    // clear matrix for every scanline
    for (int j = 0; j < width_l+1; ++j) {
      for (int k = 0; k < width_r+1; ++k) {
	cost[j][k] = 0.0;
	match[j][k] = 0;
      }
    }
    
    // ********** Problem 1-3 START ********** //



    // ********** Problem 1-3 END ************ //

  }
  
  // Display the Disparity Map
  double range = max - min;
  for (int j = 0; j < height_l; ++j) {
    for (int k = 0; k < width_l; ++k) {
      if (dis[j][k] == INF) {
	dis[j][k] = max;
      }
      dis[j][k] = dis[j][k] / range * 255;
    }
  }
    
  IplImage *out_img = cvCreateImage(cvSize(width_l, height_l), 8, 1);
  for (int j = 0; j < height_l; ++j) {
    for (int k = 0; k < width_l; ++k) {
      *PIXEL(out_img, k, j) = (int)dis[j][k];
    }
  } 

  cvNamedWindow("Output",1);
  cvShowImage("Output", out_img);
  cvSaveImage("disparity.png", out_img);
  cout << "Saved to file disparity.png" << endl;
  cvWaitKey(0);

  // ********** Problem 5 START **********         //
  //                                               //
  // Write your interpolation code here            //
  // use function cvSaveImage() to save the output //
  // show your output in the PDF file              //
  //                                               //
  // ********** Problem 5 END ************         //



  // ********** Problem 6 START **********         //
  //                                               //
  // Write your code for shortest path             //
  // use function cvSaveImage() to save the output //
  // upload the disparity map as PNG file          //
  //                                               //
  // ********** Problem 6 END ************         //

  // release memory  
  cvReleaseImage(&out_img);
  cvReleaseImage(&left_image);
  cvReleaseImage(&right_image);

  for (int i = 0; i < width_l+1; ++i) {
    delete[] cost[i];
    delete[] match[i];
  }
  for (int i = 0; i < height_l; ++i) {
    delete[] dis[i];
  }
  delete[] cost;
  delete[] match;
  delete[] dis;
  
  return 0;
}
