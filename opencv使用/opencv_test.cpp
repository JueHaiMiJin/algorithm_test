#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>

using namespace std;

void Video_To_Image(string filename);

int main()
{
    string video_name = "test.avi"; //注意，使用string时，若不用using namespace std，需要使用std::string
    Video_To_Image(video_name);
    Image_To_Video();
    return 0;
}
void Video_To_Image(string filename)
{
    cout << "---------------Video_To_Image-----------------" << endl;
    cv::VideoCapture capture(filename);
    if (!capture.isOpened())
    {
        cout << "open video error";
    }

    /*
    CV_CAP_PROP_POS_MSEC        – 视频的当前位置（毫秒）
    CV_CAP_PROP_POS_FRAMES      – 视频的当前位置（帧）
    CV_CAP_PROP_FRAME_WIDTH     – 视频流的宽度
    CV_CAP_PROP_FRAME_HEIGHT    – 视频流的高度
    CV_CAP_PROP_FPS             – 帧速率（帧 / 秒）
    */

    int frame_width = (int)capture.get(CV_CAP_PROP_FRAME_WIDTH);
    int frame_height = (int)capture.get(CV_CAP_PROP_FRAME_HEIGHT);
    float frame_fps = capture.get(CV_CAP_PROP_FPS);
    int frame_number = capture.get(CV_CAP_PROP_FRAME_COUNT); //总帧数
    cout << "frame_width is " << frame_width << endl;
    cout << "frame_height is " << frame_height << endl;
    cout << "frame_fps is " << frame_fps << endl;

    int num = 0; //统计帧数
    cv::Mat img;
    string img_name;
    char image_name[20];
    cv::namedWindow("MyVideo", CV_WINDOW_AUTOSIZE);
    while (true)
    {
        cv::Mat frame;
        //从视频中读取一个帧
        bool bSuccess = capture.read(frame);
        if (!bSuccess)
        {
            cout << "不能从视频文件读取帧" << endl;
            break;
        }

        //在MyVideo窗口上显示当前帧
        imshow("MyVideo", frame);

        //保存的图片名
        sprintf(image_name, "%s%d%s", "image", ++num, ".jpg"); //保存的图片名
        img_name = image_name;
        imwrite(img_name, frame); //保存保存一帧图片
        if (cv::waitKey(30) == 27 || num == frame_number)
        {
            cout << "按下ESC键" << endl;
            break;
        }
    }
    capture.release(); //这句话貌似不需要
}