#ifndef CHARACTERS_STRIP_CONTOUR_H
#define CHARACTERS_STRIP_CONTOUR_H
#pragma once
using namespace cv;
using namespace std;
struct character_contour
{
    float contour_area;//轮廓面积
    float contour_length;//轮廓周长
    float rect_width;//轮廓外包矩形的宽度mm
    float rect_height;//轮廓外包矩形的高度mm
    float background_avg_gray;//背景平均灰度
    float background_avg_rgb[3];//背景平均RGB颜色
    float object_avg_gray;//目标物体平均灰度
    float object_avg_rgb[3];//目标物体平均RGB颜色
    float object_lbp[59];//物体纹理
    float distance_DS;//轮廓距离传动侧最近距离mm
    float distance_OS;//轮廓距离操作侧最近距离mm
};
#endif // CHARACTERS_STRIP_CONTOUR_H
