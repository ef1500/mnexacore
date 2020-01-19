//Code by ef1500, following the guide provided on opencv's website
//NOTE TO SELF: ADD OPENCV TO PROJECT WHEN I GET OTHER COMPUTER BACK FROM BEST BUY
//SVM ENGINE

//WHAT NEEDS TO HAPPEN WITH THIS FILE

// +----------------------+------------------------------------------------------+
// |                        WHAT NEEDS TO HAPPEN                                 |
// +----------------------+------------------------------------------------------+
// | 1.                   | Figure out how to feed data from the user to the SVM |
// +----------------------+------------------------------------------------------+
// | 2.                   | Figure out how to re-scale the visualization graph   |
// +----------------------+------------------------------------------------------+
// | 3.                   | Resolve any errors with the library                  |
// +----------------------+------------------------------------------------------+

//Define the Header files
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>

//declare our namespaces
using namespace cv;
using namespace cv::ml;


int main(int, char**)
{
    // Set up training data
    int labels[4] = {1, -1, -1, -1};

    //Ideally, I'd like to have this data come from the user's input
    float trainingData[4][2] = { {501, 10}, {255, 10}, {501, 255}, {10, 501} };
    Mat trainingDataMat(4, 2, CV_32F, trainingData);
    Mat labelsMat(4, 1, CV_32SC1, labels);

    // Train the SVM
    Ptr<SVM> svm = SVM::create();
    svm->setType(SVM::C_SVC);

    //Later on, once I get the ANN (Artificial Nueral Network) up and running,
    //We might be jumping into some Non-linear Kernels. (i.e radial basis kernel).
    svm->setKernel(SVM::LINEAR);

    //The SVM training procedure is implemented solving a constrained quadratic
    //optimization problem in an iterative fashion. Here we specify a maximum
    //number of iterations and a tolerance error so we allow the algorithm to
    //finish in less number of steps even if the optimal hyperplane has not been computed yet.
    svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
    svm->train(trainingDataMat, ROW_SAMPLE, labelsMat);

    // Data for visual representation
    //The (x,y) should be (amount right, amount wrong), andthe size should change
    //as the user answers more questions. For now, 512 is a good starting point.
    int width = 512, height = 512;
    Mat image = Mat::zeros(height, width, CV_8UC3);

    // Show the decision regions given by the SVM
    // Here we have used this method in order to color the space depending
    //on the prediction done by the SVM. In other words, an image is traversed interpreting
    //its pixels as points of the Cartesian plane. Each of the points is colored depending
    //on the class predicted by the SVM; in green if it is the class with label 1
    //and in blue if it is the class with label -1.
    Vec3b green(0,255,0), blue(255,0,0);
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            Mat sampleMat = (Mat_<float>(1,2) << j,i);
            float response = svm->predict(sampleMat);
            if (response == 1)
                image.at<Vec3b>(i,j)  = green;
            else if (response == -1)
                image.at<Vec3b>(i,j)  = blue;
        }
    }

    // Show the training data
    int thickness = -1;
    circle( image, Point(501,  10), 5, Scalar(  0,   0,   0), thickness );
    circle( image, Point(255,  10), 5, Scalar(255, 255, 255), thickness );
    circle( image, Point(501, 255), 5, Scalar(255, 255, 255), thickness );
    circle( image, Point( 10, 501), 5, Scalar(255, 255, 255), thickness );

    // Show support vectors
    //We use here a couple of methods to obtain information about the support vectors.
    //The method cv::ml::SVM::getSupportVectors obtain all of the support vectors.
    //We have used this methods here to find the training examples that are support vectors and highlight them.
    thickness = 2;
    Mat sv = svm->getUncompressedSupportVectors();
    for (int i = 0; i < sv.rows; i++)
    {
        const float* v = sv.ptr<float>(i);
        circle(image,  Point( (int) v[0], (int) v[1]), 6, Scalar(128, 128, 128), thickness);
    }
    imwrite("result.png", image);        // save the image
    imshow("SVM Simple Example", image); // show it to the user
    waitKey();
    return 0;
}
