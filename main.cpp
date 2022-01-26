#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

// Video capture with face detection
int main()
{
    cv::Mat image;
    cv::VideoCapture cap(0);
    cap.set(cv::CAP_PROP_FRAME_WIDTH , 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    while (true)
    {
        cap.read(image);

        cv::CascadeClassifier faceCascade;
        faceCascade.load("resources/haarcascade_frontalface_default.xml");
        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(image, faces, 1.1, 3, 0, cv::Size(50, 50));

        for (int i = 0; i < faces.size(); i++)
        {
            cv::rectangle(image, faces[i].tl(), faces[i].br(), cv::Scalar(0, 255, 0), 3);
        }

        cv::imshow("Webcam", image);
        cv::waitKey(1);
    }
    return 0;
}