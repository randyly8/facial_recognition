#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

// Filters
void blur(cv::Mat& image, cv::Rect& roi)
{
    cv::GaussianBlur(image(roi), image(roi), cv::Size(51, 51), 0);
}

// Handler
void filter_handler(int& option)
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
            switch(option)
            {
                case 1:
                blur(image, roi);
                break;
            }
        }

        cv::imshow("Webcam", image);
        cv::waitKey(1);
    }
}

int main()
{
    int option;
    std::cout << "Blur: 1" << "\n";
    std::cout << "Exit: 0" << "\n";
    std::cout << "Please choose a filter: ";
    std::cin >> option;
    switch (option)
    {
        case 0:
            break;
        case 1:
            filter_handler(option);
            break;
    }
    std::cout << "Program ended." << std::endl;;
    return 0;
}