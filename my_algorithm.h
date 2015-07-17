#ifndef MY_ALGORITHM_H
#define MY_ALGORITHM_H
#pragma once
#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Characters_Strip_Contour.h"
using namespace cv;
using namespace std;
struct Qt_GUI_global_Variable
{
    bool global_SaveTo_Pic_En;
    int min_default_area;
    std::string global_offline_Filename;//离线视频文件名
    bool contour_i_processing_en;
    int global_Pic_ID_Per_Strip;
    int frame_number;
};

struct Qt_GUI_Variable_Structure
{
    bool global_SaveTo_Pic_En;
    int min_default_area;
    std::string global_offline_Filename;//离线视频文件名
    bool contour_i_processing_en;
    int global_Pic_ID_Per_Strip;
    bool* stop;
    std::string save_file_path;//图片保存文件路径
};
struct default_bool_class
{
    bool default_type;
    float default_center[2];
    float default_size[2];
    float default_area;
    float default_length;
};
struct default_int_class
{
    int default_type;
    float default_center[2];
    float default_size[2];
    float default_area;
    float default_length;
};
struct default_Detect_Setting_parameters
{
    float min_default_area;//最小缺陷面积
    int Dynamic_Default_show_en;
    int Dynamic_Type_Show_en;
    int hanfeng_show_en;
    int liebian_show_en;
    int tingcheban_show_en;
    int guosuanxi_show_en;
    int qiansuanxi_show_en;
    int kongdong_show_en;
    int aokeng_show_en;
    int huaheng_show_en;
    int youwu_show_en;
    int weizhi_show_en;
};
struct default_Table
{
    string ID;//最小缺陷面积
    string Strip_ID;
    int strip_class_type;
    string strip_Cailiao_type;
    int default_number_sum;
    int hanfeng_number;
    int liebian_number;
    int tingcheban_number;
    int guosuanxi_number;
    int qiansuanxi_number;
    int kongdong_number;
    int aokeng_number;
    int huaheng_number;
    int youwu_number;
    int weizhi_number;
};

class my_algorithm
{
private:
//    int hist_LBP_Map_Table[256];
    cv::Mat Proj_mat;
    cv::Mat yangben_Mean;
    cv::Mat Proj_W;
    cv::Mat yangben_class_type;
public:
    int hist_LBP_Map_Table[256];
    std::vector<float> max_character_array;//特征归一化最大值数组
    std::vector<float> min_character_array;//特征归一化最小值数组
    std::vector<float> diff_character_array;//特征归一化差分数组
public:
    my_algorithm(void);
    ~my_algorithm(void);
    //模式识别
    int Pattern_Recognition(cv::Mat vector_test,int method_type);
    //读入样本训练结果，为模式识别做准备；
    void Proj_presetting();
    int set_hist_LBP_Map_Table();
    void array2mat(double* src_array,cv::Mat dst,int nRows);
    void getHistogram(int* temp_array, cv::Mat img_bin, cv::Mat img_lbp);
    void getHistogram_rect(int* temp_array, cv::Mat img_lbp);

    void Mat_com_M1_3Mat(int* temp_a, cv::Mat a1_bin, cv::Mat a1_gray, cv::Mat a_lbp);
    int lbp_basic_circle(int* a);
    void LBP_256_259(int* source_array, int* dst , int* Map_Table);
//    void liebian_detect(cv::Mat dst_img_gray, struct default_bool_class* liebian_s,int Camera_ID);
    //void tingcheban_detect(cv::Mat dst_img_Hue, struct default_bool_class* tingche_s);
//    void tingcheban_detect(cv::Mat src_color,cv::Mat dst_HSV, vector<Mat>& img_for_tingcheban_H,cv::Mat dst_thresh_1,cv::Mat dst_thresh_2,cv::Mat dst_thresh_morph,int thresh_value_low,int thresh_value_high,int min_area_limit, struct default_bool_class* tingcheban_s);
    //其他缺陷检测如焊缝、酸洗缺陷、孔洞
//    void other_detect(cv::Mat dst_img_Hue, struct default_int_class* default_s);
//    void other_detect(cv::Mat dst_img_Hue, struct default_int_class* default_s,cv::Mat dst_img_out);
//    void my_algorithm::suanxi_detect(cv::Mat src_img, struct default_int_class* default_s,cv::Mat dst_img_out,int low_thresh,int high_thresh,int* suanxi_number);

    // 用来将阈值化图像以边缘为基准进行二值分割
    void edge_detect(cv::Mat img_source, cv::Mat img_dst, int* ind, bool B_mingan);
    //两点之间的角度
    double angle(cv::Point pt1, cv::Point pt2);
    //两点之间的长度
    double length(cv::Point pt1, cv::Point pt2);
    //本函数为了在实验中判断出感兴趣的区域，假设已知感兴趣的横坐标值，寻求纵坐标值，每次只找1块。如果多块区域，需要进行迭代寻找。
    void my_find_boudary(IplImage* src, int thresh_value,int x_low, int x_high, int y_ini,int* y_low, int* y_high,int paper_f21,int paper_f2);
    // 用来在给定区域内将阈值化图像以边缘为基准进行二值分割
    void edge_detect_region(cv::Mat img_source, cv::Mat img_dst, int* ind, bool B_mingan, int x1, int x2, int y1, int y2);
//    void liebian_detect_region(cv::Mat dst_img_gray, struct default_bool_class* liebian_s, int Camera_ID, int x1, int x2, int y1, int y2);
    // 两个数组之间的范数计算
    double norm;
    double norm_calc(double* array_1, double* array_2, int norm_type,int array_length);
    void my_normalize(int* src, double* dst, int length);

    void my_algorithm::kongdong_detect(cv::Mat src, struct default_bool_class* default_s1, cv::Mat dst,int* length,int kongdong_thresh_value, int pos_x_begin,int pos_x_end,int min_kongdong_area, bool mingan);

    //模式识别函数
    void PR_img_mat(cv::Mat img_mat,Qt_GUI_global_Variable qt_a);
    void segment_img_mat(cv::Mat img_mat,cv::Mat morph_img_mat, std::vector<std::vector<cv::Point>> &contours,std::vector<cv::Vec4i> &hierarchy);
    void compute_character(cv::Mat img_mat,cv::Mat morph_img_mat, std::vector<std::vector<cv::Point>> contours,Qt_GUI_global_Variable qt_a);
    int  write_ML_txt(character_contour a,int contour_num,Qt_GUI_global_Variable qt_a);
    void vector_to_Mat(character_contour a,cv::Mat Feature_online);//需要给矩阵向量预先分配空间
    int find_show_classification(cv::Mat Feature_online);//计算最小距离的类别,并进行显示

    //轮廓分析函数
    void similar_median_filter(cv::Mat img,int maxvalue,int blocksize,int threshvalue);
};

#endif // MY_ALGORITHM_H
