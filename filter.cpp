#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
void showMenu(){
        cout << "********MENU********" << endl;
        cout << "0. original" << endl;
        cout << "1. grayScale" << endl;
        cout << "2. sepia" << endl;
        cout << "3. blur" << endl;
        cout << "4. sharpen" << endl;
        cout << "5. edged" << endl;
        cout << "6. canny" << endl;
        cout << "7. exit" << endl;
        cout << "********MENU********" << endl;
    }
int main()
{
    int option;
    // Load the input image
    Mat image = imread("/Users/sahilraj/Desktop/Photos/IMG-20230630-WA0064.jpg", IMREAD_COLOR);
    
    if (image.empty())
    {
        std::cout << "Error: Could not read the image file." << std::endl;
        return -1;
    }
    
    do {
        showMenu();
        
        cout << "Option: ";
        cin >> option;
        system("clear");
        
        
        switch (option) {
            case 1: {
                Mat grayImage;
                cvtColor(image, grayImage, COLOR_BGR2GRAY);
                imshow("Grayscale", grayImage);
                break;
            }
            case 2: {
                Mat sepiaImage = image.clone();
                for (int y = 0; y < sepiaImage.rows; ++y)
                {
                    for (int x = 0; x < sepiaImage.cols; ++x)
                    {
                        int blue = sepiaImage.at<Vec3b>(y, x)[0];
                        int green = sepiaImage.at<Vec3b>(y, x)[1];
                        int red = sepiaImage.at<Vec3b>(y, x)[2];
                        
                        sepiaImage.at<Vec3b>(y, x)[0] = saturate_cast<uchar>(0.272 * red + 0.534 * green + 0.131 * blue);
                        sepiaImage.at<Vec3b>(y, x)[1] = saturate_cast<uchar>(0.349 * red + 0.686 * green + 0.168 * blue);
                        sepiaImage.at<Vec3b>(y, x)[2] = saturate_cast<uchar>(0.393 * red + 0.769 * green + 0.189 * blue);
                    }
                }
                imshow("Sepia", sepiaImage);
                break;
            }
            case 3: {
                Mat blurredImage;
                blur(image, blurredImage, Size(5, 5));
                imshow("Blur", blurredImage);
                break;
            }
            case 4: {
                Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
                Mat sharpenedImage;
                filter2D(image, sharpenedImage, image.depth(), kernel);
                
                imshow("Sharpen", sharpenedImage);
                break;
            }
            case 5: {
                Mat gradientX, gradientY;
                Mat absGradientX, absGradientY;
                Sobel(image, gradientX, CV_16S, 1, 0);
                Sobel(image, gradientY, CV_16S, 0, 1);
                convertScaleAbs(gradientX, absGradientX);
                convertScaleAbs(gradientY, absGradientY);
                Mat edgeImage;
                addWeighted(absGradientX, 0.5, absGradientY, 0.5, 0, edgeImage);
                imshow("Edge Detection (Sobel)", edgeImage);
                break;
            }
            case 6: {
                Mat cannyImage;
                Canny(image, cannyImage, 100, 200);
                imshow("Canny Edge Detection", cannyImage);
                break;
            }
        }
        waitKey(0);
    } while (option != 7);
    return 0;
}
