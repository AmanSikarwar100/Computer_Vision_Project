#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap(0);  // Open the default camera (you may need to change the index)

    if (!cap.isOpened()) {
        cout << "Error: Could not open the camera" << endl;
        return -1;
    }

    CascadeClassifier faceCascade;
    faceCascade.load("Resources/haarcascade_frontalface_default.xml");

    if (faceCascade.empty()) {
        cout << "XML file not loaded" << endl;
        return -1;
    }

    while (true) {
        Mat frame;
        cap >> frame;  // Read a frame from the camera

        if (frame.empty()) {
            cout << "End of video stream" << endl;
            break;
        }

        vector<Rect> faces;
        faceCascade.detectMultiScale(frame, faces, 1.1, 10);

        for (int i = 0; i < faces.size(); i++) {
            rectangle(frame, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);

            // Add a label "Face" next to each detected face
            putText(frame, "Face", Point(faces[i].x, faces[i].y - 10), FONT_HERSHEY_SIMPLEX, 0.9, Scalar(255, 0, 255), 2);
        }

        imshow("Webcam Face Detection", frame);

        if (waitKey(1) == 27) {  // Break the loop on Esc key
            break;
        }
    }

    cap.release();
    destroyAllWindows();

    return 0;
}