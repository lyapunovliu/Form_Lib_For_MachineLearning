#include "my_algorithm.h"
//#include "My_OpenCV_IPP_Trans.h"
#include <fstream>
#include <iostream>
using namespace cv;
using namespace std;

my_algorithm::my_algorithm(void)
: norm(0)
{
    for(int i=0;i<256;i++)
    {
        *(hist_LBP_Map_Table+i)=0;
    }
}

my_algorithm::~my_algorithm(void)
{
}

void my_algorithm::getHistogram(int* temp_array, cv::Mat img_bin, cv::Mat img_lbp)
{
    //temp_array: the array stores 256 histogram
    //img_bin : contour image
    //img_lbp: the image of the contour
    uchar* p;
    uchar* p1;
    int ind=0;
    for(int i=0;i<256;i++)
    {
        *(temp_array+i)=0;
    }

    int nRows=img_bin.rows*img_bin.channels();
    //避免出现单通道乘以2；
    if(img_bin.dims==2)
    {

        nRows=img_bin.rows;
    }
    int nCols=img_bin.cols;

    for (int i=0;i<nRows;i++)
    {
        p=img_lbp.ptr<uchar>(i);
        p1=img_bin.ptr<uchar>(i);
        for (int j=0;j<nCols;j++)
        {
            int val=(int)img_bin.at<uchar>(i,j);
            if (img_bin.at<uchar>(i,j)>0)
            {
                ind=(int)img_lbp.at<uchar>(i,j);
                *(temp_array+ind)=*(temp_array+ind)+1;

            }
        }
    }
}
void my_algorithm::getHistogram_rect(int* temp_array,cv::Mat img_lbp)
{
    //temp_array: the array stores 256 histogram
    //img_bin : contour image
    //img_lbp: the image of the contour
    uchar* p;
    uchar* p1;
    int ind=0;
    for(int i=0;i<256;i++)
    {
        *(temp_array+i)=0;
    }

    cv::Mat img_bin=img_lbp;
    int nRows=img_lbp.rows*img_lbp.channels();
    //避免出现单通道乘以2；
    if(img_bin.dims==2)
    {

        nRows=img_bin.rows;
    }
    int nCols=img_bin.cols;

    for (int i=0;i<nRows;i++)
    {
        p=img_lbp.ptr<uchar>(i);
        p1=img_bin.ptr<uchar>(i);
        for (int j=0;j<nCols;j++)
        {
            int val=(int)img_bin.at<uchar>(i,j);
            ind=(int)img_lbp.at<uchar>(i,j);
            *(temp_array+ind)=*(temp_array+ind)+1;
        }
    }
}

void my_algorithm::Mat_com_M1_3Mat(int* temp_a, cv::Mat a1_bin, cv::Mat a1_gray, cv::Mat a_lbp)
{

    uchar* p;
    uchar* pd1;
    uchar* pa1;
    int nRows=a1_gray.rows;
    int nCols=a1_gray.cols;

    for (int i=1;i<nRows-1;i++)
    {
        pd1=a1_gray.ptr<uchar>(i-1);
        p=a1_gray.ptr<uchar>(i);
        pa1=a1_gray.ptr<uchar>(i+1);
        for (int j=1;j<nCols-1;j++)
        {
            if (a1_bin.at<uchar>(i,j)==255)
            {
                *temp_a=*(pd1+j-1);
                *(temp_a+1)=*(pd1+j);
                *(temp_a+2)=*(pd1+j+1);

                *(temp_a+3)=*(p+j-1);
                *(temp_a+4)=*(p+j);
                *(temp_a+5)=*(p+j+1);

                *(temp_a+6)=*(pa1+j-1);
                *(temp_a+7)=*(pa1+j);
                *(temp_a+8)=*(pa1+j+1);
                a_lbp.at<uchar>(i,j)=lbp_basic_circle(temp_a);
            }
            else
            {
                a_lbp.at<uchar>(i,j)=0;

            }
        }
    }

}

int my_algorithm::lbp_basic_circle(int* a)
{
    int j;
    int k;
    int b[9]={0,1,2,7,8,3,6,5,4};
    int temp[9]={0,0,0,0,0,0,0,0,0};
    for(int i=1;i<=9;i++)
    {
        j=i%3;
        k=(i-j)/3;

        if (i==5)
        {
            temp[8]=*(a+4);
        }
        else
        {
            if (*(a+i-1)>*(a+4))
            {
                temp[b[i-1]]=1;
            }
            else
            {
                temp[b[i-1]]=0;
            }
        }


    }

    return *(temp+0)*128+*(temp+1)*64+*(temp+2)*32+*(temp+3)*16+*(temp+4)*8+*(temp+5)*4+*(temp+6)*2+*(temp+7);

    //return 0;
}

void my_algorithm::LBP_256_259(int* source_array, int* dst , int* Map_Table)
{

    int i=0;
    while(i<59)
    {
        *(dst+i)=0;
        i++;
    }
    i=0;
    while(i<256)
    {
        *(dst+Map_Table[i]-1)=*(dst+Map_Table[i]-1)+source_array[i];
        i++;
    }

}

void my_algorithm::edge_detect(cv::Mat img_source, cv::Mat img_dst, int* ind,bool B_mingan)
{
    int nRows;
    int nCols;
    nRows=img_source.rows;
    nCols=img_source.cols;
    uchar* p;
    uchar* p1;
    for(int i=0;i<nRows;i++)
    {
        p=img_source.ptr<uchar>(i);
        p1=img_dst.ptr<uchar>(i);

        for(int j=0;j<nCols;j++)
        {
            *(ind+i)=nCols-1;
            if (B_mingan)
            {
                if(p[nCols-j]==255)
                {
                    *(ind+i)=j;
                    for(int k=0;k<nCols-j-1;k++)
                    {
                        p1[k]=0;
                    }
                    break;
                }
            }
            else
            {
                if(p[j]==0)
                {
                    *(ind+i)=j;
                    for(int k=0;k<nCols-j;k++)
                    {
                        p1[k]=255;
                    }
                    break;
                }

            }

        }
    }
}

double my_algorithm::angle(cv::Point pt1, cv::Point pt2)
{
    //计算边缘角度；
    double dx1 = pt1.x ;
    double dy1 = pt1.y ;
    double dx2 = pt2.x;
    double dy2 = pt2.y;
    return abs((dx1-dx2)/(dy1-dy2));
    //return 0;
}

double my_algorithm::length(cv::Point pt1, cv::Point pt2)
{
    double dx1 = pt1.x ;
    double dy1 = pt1.y ;
    double dx2 = pt2.x;
    double dy2 = pt2.y;
    return sqrt((dx1-dx2)*(dx1-dx2)+(dy1-dy2)*(dy1-dy2));
}


void my_algorithm::my_find_boudary(IplImage* src_thresh, int thresh_value,int x_low, int x_high, int y_ini,int* y_low, int* y_high,int paper_f1,int paper_f2)
{


    int x_f1=paper_f1;
    int x_f2=paper_f2;
    int f1,f2;
    bool bool_y_begin=false;
    bool bool_y_pro=false;
    bool bool_y_end=false;
    uchar* ptr=(uchar* )src_thresh->imageData;
    int test_element;



    for(int i=y_ini;i<src_thresh->height;i++)
    {
        test_element=(int)*(ptr+i*src_thresh->widthStep+x_low);
        f1=*(ptr+i*src_thresh->widthStep+x_f1);
        f2=*(ptr+i*src_thresh->widthStep+x_f2);
        //if ((*(ptr+i*src_thresh->widthStep+x_low)>10))
        if ((*(ptr+i*src_thresh->widthStep+x_f1)>10)&&((*(ptr+i*src_thresh->widthStep+x_f2)>10)))
        {
            if ((!bool_y_begin))
            {

                bool_y_begin=true;
            }
            else
            {
            }
            if ((*(ptr+i*src_thresh->widthStep+x_high)<10)&&bool_y_begin&&(!bool_y_pro))
            {
               *y_low=i;
                //*y_high=i;
                bool_y_pro=true;

            }
            if ((*(ptr+i*src_thresh->widthStep+x_high)>10)&&bool_y_pro&&(!bool_y_end))
            {
               *y_high=i;

                bool_y_end=true;
            }

            if (bool_y_end)
            {
                break;
            }
            }

            if((i==src_thresh->height-1)&&(*y_low>0))
            {
                *y_high=i;

            }
    }

    //cvDestroyWindow("cv_thresh");
}

// 用来在给定区域内将阈值化图像以边缘为基准进行二值分割
void my_algorithm::edge_detect_region(cv::Mat img_source, cv::Mat img_dst, int* ind, bool B_mingan, int x1, int x2, int y1, int y2)
{

    int nRows;
    int nCols;
    nRows=img_source.rows;
    nCols=img_source.cols;
    uchar* p;
    uchar* p1;

    for(int i=0;i<nRows;i++)
    {
        p1=img_dst.ptr<uchar>(i);
        for(int j=0;j<nCols;j++)
        {
            if ((i>x1)&&(i<x2)&(j>y1)&&(j<y2))
            {}
            else
            {
                p1[j]=0;

            }
        }
    }


    for(int i=x1;i<x2;i++)
    {
        p=img_source.ptr<uchar>(i);
        p1=img_dst.ptr<uchar>(i);

        for(int j=y1;j<y2;j++)
        {
            *(ind+i)=nCols-1;
            if (B_mingan)
            {
                if(p[y2-j]==255)
                {
                    *(ind+i)=j;
                    for(int k=y1;k<y2-j-1;k++)
                    {
                        p1[k]=0;
                    }
                    break;
                }
            }
            else
            {
                if(p[j]==0)
                {
                    *(ind+i)=j;
                    for(int k=y1;k<y2-j;k++)
                    {
                        p1[k]=255;
                    }
                    break;
                }

            }

        }
    }
}

double my_algorithm::norm_calc(double* array_1, double* array_2, int norm_type,int array_length)
{
    double sum_a=0;
    double diff=0;
    if(norm_type==2)
    {
        for (int i=0;i<array_length;i++)
        {
            diff=(*(array_1+i))-(*(array_2+i));

            sum_a=sum_a+diff*diff;
        }
        return sqrt(sum_a);
    }
    else if(norm_type==1)
    {}
    return 0;
}

void my_algorithm::my_normalize(int* src, double* dst, int length)
{
    int sum_array=0;
    for(int i=0;i<length;i++)
    {
        sum_array=sum_array+(*(src+i));
    }
    for(int i=0;i<length;i++)
    {
        if(sum_array>0)
        {
            *(dst+i)=((double)(*(src+i)))/sum_array;
        }
        else
        {
            *(dst+i)=0.0;
        }
    }
}
// 孔洞检测
void my_algorithm::kongdong_detect(cv::Mat src, struct default_bool_class* default_s1, cv::Mat dst,int* length,int kongdong_thresh_value, int pos_x_begin,int pos_x_end,int min_kongdong_area, bool mingan)
{

     struct default_bool_class* default_s=default_s1;
    Mat src_thresh;
    int max_kongdong_area=1000;
    //int kongdong_thresh_value=50;
    Scalar color=Scalar(0,0,255);
    Rect rect_kongdong;
    int j=0;

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    if (mingan)
    {
        threshold(src,src_thresh,kongdong_thresh_value,255,CV_THRESH_BINARY);
    }
    else
    {
        threshold(src,src_thresh,kongdong_thresh_value,255,CV_THRESH_BINARY_INV);
    }

    findContours(src_thresh,contours,hierarchy,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE,Point(0,0));



    for(int i=0;i < contours.size();i++)
    {
        //利用面积进行轮廓排除，提取出较大的轮廓作为焊缝判断；
        if(contourArea(contours[i])> min_kongdong_area)
        {

            rect_kongdong=boundingRect(contours[i]);
            if ((rect_kongdong.x>pos_x_begin)&&(rect_kongdong.x<pos_x_end))
            {
                drawContours(dst,contours,i,color,5,18,hierarchy,0,Point());
                default_s->default_type=true;//裂边
                default_s->default_center[0]=(float)(rect_kongdong.x+rect_kongdong.width/2);//x
                default_s->default_center[1]=(float)(rect_kongdong.y+rect_kongdong.height/2);//y
                default_s->default_size[0]=(float)rect_kongdong.width;//width
                default_s->default_size[0]=(float)rect_kongdong.height;//height
                default_s->default_area=(float)contourArea(contours[i]);//area
                default_s->default_length=(float)arcLength(contours[i],true);//
                j=j+1;
                default_s=default_s1+j;
            }

        }

    }
    *length=j;


}
//数组转换为cv::Mat格式，便于运算
void my_algorithm::array2mat(double* src_array,cv::Mat dst,int nRows)
{
    for(int i=0;i<nRows;i++)
    {
        dst.at<float>(i,0)=(float)(*(src_array+i));
    }
}
//读入LBP 256->59映射表
int my_algorithm::set_hist_LBP_Map_Table()
{

    ifstream ifs("D:/Qt_CisdiCV_Setting/LBP_Map.txt");
    if(ifs)
    {
        int i=0;
        while(i<256)
        {
            int value;
            ifs>>value;
            *(this->hist_LBP_Map_Table+i)=value;
            i++;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

//将酸洗缺陷样本数据库PCA的训练结果——映射空间、映射矩阵、均值读入到指定矩阵
void my_algorithm::Proj_presetting()
{


    FileStorage ifs("E:\\my_setting_data\\Proj_presetting.yml",FileStorage::READ);
    ifs["Proj_mat"]>>Proj_mat;
    ifs["yangben_Mean"]>>yangben_Mean;
    ifs["Proj_W"]>>Proj_W;
    ifs["yangben_class_type"]>>yangben_class_type;
}

int my_algorithm::Pattern_Recognition(cv::Mat vector_test,int method_type)
{
    Mat result_1;
    Mat result_2=cv::Mat(Proj_mat.cols,1,CV_32F);
    Mat result_sort;
    //PCA方法
    if(method_type==1)
    {
        result_1=Proj_W.t()*(vector_test-yangben_Mean);
        for(int i=0;i<Proj_mat.cols;i++)
        {
            result_2.at<float>(i,0)=cv::norm((result_1-Proj_mat.col(i)),NORM_L2);

        }
        //对数组进行排序，返回最小值的索引
        sortIdx(result_2,result_sort,CV_SORT_ASCENDING);
        //对索引对应的类别数组中数值，也就是根据最近邻方法返回类别。
        return yangben_class_type.at<int>(0,result_sort.at<int>(0,0));

    }
    else
    {

        return 0;
    }
}
//模式识别
void my_algorithm::PR_img_mat(cv::Mat img_mat,Qt_GUI_global_Variable qt_a)
{
    //blob分割
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::Mat morph_img_mat;
    segment_img_mat(img_mat,morph_img_mat,contours,hierarchy);//分割

    std::vector<character_contour> img_character;
    //计算blob特征及识别
    compute_character(img_mat,morph_img_mat,contours,qt_a);
}
//计算轮廓特征包括目标颜色、面积、长度、纹理、边缘距离等特征
void my_algorithm::compute_character(cv::Mat img_mat,cv::Mat morph_img_mat,std::vector<std::vector<cv::Point>> contours,Qt_GUI_global_Variable qt_a)
{
    cv::Mat bw_img_mat;//黑白图像
    cv::cvtColor(img_mat,bw_img_mat,CV_RGB2GRAY);
    //LBP变量开始
    int hist_array[256];
//    int temp_lbp_histogram[256];
    int array_LBP_Map[59];
    int j=0;
    while(j<59)
    {
        array_LBP_Map[j]=0;
        j++;
    }
    double array_LBP_Map_Normalize[59];
    Mat array_LBP_Map_mat(59,1,CV_32F);
    int save_file_flag=0;
    cv::Mat img_multi_rect=img_mat.clone();//定义矩阵为了显示一幅图像上的多个缺陷
    //LBP变量结束

    for(int i=0;i<contours.size();i++)
    {
        character_contour a;
        a.contour_area=cv::contourArea(contours[i]);
        if(a.contour_area>qt_a.min_default_area)
        {
            cv::Rect rect=boundingRect(contours[i]);
            a.rect_height=rect.height;
            a.rect_width=rect.width;
            a.contour_length=cv::arcLength(contours[i],true);
            a.background_avg_gray=0;//每一幅图像的背景颜色等于每一个轮廓的背景颜色
            a.background_avg_rgb[0]=0;
            a.background_avg_rgb[1]=0.0;
            a.background_avg_rgb[2]=0.0;
            cv::Mat bw_img_empty=cv::Mat::zeros(bw_img_mat.rows,bw_img_mat.cols,CV_8UC3);
            cv::Mat bw_img_result=cv::Mat::zeros(bw_img_mat.rows,bw_img_mat.cols,CV_8UC3);
            cv::Mat bw_img_empty_gray;
            cv::Mat bw_img_result_gray;
            drawContours(bw_img_empty,contours,i,cv::Scalar(1,1,1),-1);
            cv::cvtColor(bw_img_empty,bw_img_empty_gray,CV_RGB2GRAY);
            cv::multiply(bw_img_mat,bw_img_empty_gray,bw_img_result_gray);
            cv::multiply(img_mat,bw_img_empty,bw_img_result);
            cv::Scalar sum1=cv::sum(bw_img_result_gray);//计算轮廓对应图像数值和
            float sum_gray=(float)sum1[0];
            cv::Scalar num1=cv::sum(bw_img_empty_gray);//计算轮廓内部数目
            float sum_num=(float)num1[0];

            cv::Scalar sum_color=cv::sum(bw_img_result);//计算轮廓对应彩色图像数值和

            a.object_avg_gray=sum_gray/sum_num;//计算灰度平均值
            a.object_avg_rgb[0]=sum_color[0]/sum_num;//计算彩色分量平均值
            a.object_avg_rgb[1]=sum_color[1]/sum_num;//计算彩色分量平均值
            a.object_avg_rgb[2]=sum_color[2]/sum_num;//计算彩色分量平均值

            //计算LBP
            getHistogram(hist_array,bw_img_empty_gray,img_mat);

            LBP_256_259(hist_array,array_LBP_Map,hist_LBP_Map_Table);

            //归一化计算
            my_normalize(array_LBP_Map,array_LBP_Map_Normalize,59);
            //进行结构体赋值
            for(int k=0;k<59;k++)
            {
                a.object_lbp[k]=array_LBP_Map_Normalize[k];
            }

            //压入栈
            //        img_character.push_back(a);


            cv::Mat new_image=img_mat.clone();
            cv::drawContours(new_image,contours,i,cv::Scalar(255,0,255),5);
            if(qt_a.global_SaveTo_Pic_En==1)//带钢每一幅图像都需要保存
            {
                cv::drawContours(img_multi_rect,contours,i,cv::Scalar(255,0,255),5);
            }

            cv::waitKey(1);
            save_file_flag=1;
            write_ML_txt(a,i,qt_a);
            cv::Mat Feature_online=cv::Mat(1,sizeof(a)/sizeof(float),CV_32F);
            vector_to_Mat(a,Feature_online);//转换成opencv向量并进行纵向归一化
            int class_num=find_show_classification(Feature_online);//模式识别

//            if(default_en_array[class_num]==1)
//            {
//                default_table_compute(class_num);//缺陷统计表计算
//                send_default_table(default_table_show);//修改缺陷统计表
//                send_strip_rect_small_pic(rect,class_num);//显示缺陷
//                send_strip_rect_big_pic(rect,class_num);
//                send_Default_Name(default_array[class_num]);//显示缺陷名称
//                if(global_SaveTo_Pic_En==1)
//                {
//                    global_cv_mat_rect=new_image.clone();
//                    save_default_pic(new_image,global_Default_ID_Per_Strip);
//                    global_Default_ID_Per_Strip++;
//                }
//            }

        }
        if(qt_a.contour_i_processing_en==false)
        {
            break;
        }
    }

    //每个分割部分都要保存，作为图像学习初步筛选
    if(qt_a.global_SaveTo_Pic_En==1)
    {
//        save_pic_whole_strip(img_multi_rect, global_Pic_ID_Per_Strip);
        qt_a.global_Pic_ID_Per_Strip++;


    }

}
//写入文本文件
int my_algorithm::write_ML_txt(character_contour a,int contour_num,Qt_GUI_global_Variable qt_a)
{


         ofstream myfile;//输出流文件
    myfile<<qt_a.global_offline_Filename<<"\t";
    myfile<<"D:\\CISDICV_temp\\a"<<qt_a.frame_number<<".bmp"<<"\t";
    myfile<<qt_a.frame_number<<"\t";
    myfile<<contour_num<<"\t";
    myfile<<a.background_avg_gray<<"\t";
    myfile<<a.background_avg_rgb[0]<<"\t";
    myfile<<a.background_avg_rgb[1]<<"\t";
    myfile<<a.background_avg_rgb[2]<<"\t";
    myfile<<a.contour_area<<"\t";
    myfile<<a.contour_length<<"\t";
    myfile<<a.distance_DS<<"\t";
    myfile<<a.distance_OS<<"\t";
    myfile<<a.object_avg_gray<<"\t";
    myfile<<a.object_avg_rgb[0]<<"\t";
    myfile<<a.object_avg_rgb[1]<<"\t";
    myfile<<a.object_avg_rgb[2]<<"\t";
    for(int i=0;i<59;i++)
    {
        myfile<<a.object_lbp[i]<<"\t";
    }

    myfile<<a.rect_height<<"\t";
    myfile<<a.rect_width;
    myfile<<"\n";
    return 0;

}
//将vector转换成opencv向量并进行基于样本的归一化
void my_algorithm::vector_to_Mat(character_contour a, Mat Feature_online)
 {
     Feature_online.at<float>(0,0)=(float)a.background_avg_gray;
     Feature_online.at<float>(0,1)=(float)a.background_avg_rgb[0];
     Feature_online.at<float>(0,2)=(float)a.background_avg_rgb[1];
     Feature_online.at<float>(0,3)=(float)a.background_avg_rgb[2];
     Feature_online.at<float>(0,4)=(float)a.contour_area;
     Feature_online.at<float>(0,5)=(float)a.contour_length;
     Feature_online.at<float>(0,6)=(float)a.distance_DS;
     Feature_online.at<float>(0,7)=(float)a.distance_OS;
     Feature_online.at<float>(0,8)=(float)a.object_avg_gray;
     Feature_online.at<float>(0,9)=(float)a.object_avg_rgb[0];
     Feature_online.at<float>(0,10)=(float)a.object_avg_rgb[1];
     Feature_online.at<float>(0,11)=(float)a.object_avg_rgb[2];
     for(int i=0;i<59;i++)
     {
         Feature_online.at<float>(0,i+12)=(float)a.object_lbp[i];
     }

     Feature_online.at<float>(0,71)=(float)a.rect_height;
     Feature_online.at<float>(0,72)=(float)a.rect_width;
     for(int i=0;i<73;i++)
     {
         float d=diff_character_array[i];
         if(d==0)
         {

         }
         else
         {
              Feature_online.at<float>(0,i)= (Feature_online.at<float>(0,i)-min_character_array[i])/d;
         }
     }
 }
//计算最小距离的类别,并进行显示
int my_algorithm::find_show_classification(cv::Mat Feature_online)
{
    return 1;
}
void  my_algorithm::segment_img_mat(cv::Mat img_mat,cv::Mat morph_img_mat, std::vector<std::vector<cv::Point>> &contours,std::vector<cv::Vec4i> &hierarchy)
{

}
//进行二值图像的特征点筛选，密度小的点被置零，想法源自北科的书籍
void my_algorithm::similar_median_filter(cv::Mat img,int maxvalue,int blocksize,int threshvalue)
{
    cv::Mat img_block;
    int row_number=img.rows-blocksize+1;
    int col_number=img.cols-blocksize+1;
    int i,j;
    for(int k=0;k<row_number*col_number;k++)
    {
        i=k/col_number;
        j=k%col_number;
        int i1=i+(blocksize-1)/2;
        int j1=j+(blocksize-1)/2;
//        if(img.at<uchar>(i,j)>0)//限制关注点,提高效率
        if(img.at<uchar>(i1,j1)>0)//限制关注点,提高效率
        {

            img_block =img.rowRange(i,i+blocksize-1).colRange(j,j+blocksize-1);
            if(img_block.at<uchar>((blocksize-1)/2,(blocksize-1)/2)>0)
            {
                if(cv::sum(img_block)[0]<threshvalue*maxvalue)
                {
//                    img_block.at<uchar>(0,0)=0;
                    img_block.at<uchar>((blocksize-1)/2,(blocksize-1)/2)=0;
                }
            }
        }

    }
//    cv::imshow("img",img);


}
