#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>


// Video capture with face detection
int main()
{
    cv::Mat image, gray;
    cv::VideoCapture cap(0);
    cap.set(cv::CAP_PROP_FRAME_WIDTH , 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    while (true)
    {
        cap.read(image);
        cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

        cv::CascadeClassifier faceCascade;
        faceCascade.load("resources/haarcascade_frontalface_default.xml");
        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(gray, faces, 1.0485258, 6, 0, cv::Size(100, 100));

        for (int i = 0; i < faces.size(); i++)
        {
            //cv::rectangle(image, faces[i].tl(), faces[i].br(), cv::Scalar(0, 255, 0), 3);
            cv::Rect roi = cv::Rect(faces[i].tl(), faces[i].br());
            cv::GaussianBlur(image(roi), image(roi), cv::Size(51, 51), 0);
        }

        cv::imshow("Webcam", image);
        cv::waitKey(1);
    }
    return 0;
}