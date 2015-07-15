#ifndef QT_AUTOMATICSTUDY_DEFAULT_H
#define QT_AUTOMATICSTUDY_DEFAULT_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace Ui {
class Qt_AutomaticStudy_Default;
}

class Qt_AutomaticStudy_Default : public QMainWindow
{
    Q_OBJECT

public:
    explicit Qt_AutomaticStudy_Default(QWidget *parent = 0);
    ~Qt_AutomaticStudy_Default();
    void QueXianReady_ListHeaderDraw();
    void QueXianForStudy_ListHeaderDraw();
    QStandardItemModel *quexianClass_model;
    QStandardItemModel *quexianForStudy_model;
    int defaultSequenceNum;
    int defaultStudyNum;
    int current_index_Readylist;
    int current_index_StudyList;
    void PR_Processsing();
    void PR_ready_data(std::vector<QString>,std::vector<int>);
    void show_fileinList(QString dir_path,int class_ID,QStringList&,QStringList&);
    int getDimesionOfGivenCharacter(QString name);//得到特征维数，用于计算特征及保存用
    void getCharacter(cv::Mat src,cv::Mat mask,float* ptr_dst,QString quexian_type);
    void computer_LBP59(cv::Mat src,cv::Mat mask,float* ptr_dst);
    void computer_AvgGreyValue(cv::Mat src,cv::Mat mask,float* ptr_dst);
    void computer_MinGreyValue(cv::Mat src,cv::Mat mask,float* ptr_dst);
    void computer_MaxGreyValue(cv::Mat src,cv::Mat mask,float* ptr_dst);
    void computer_SURF(cv::Mat src,cv::Mat mask,float* ptr_dst);
    void computer_SIFT(cv::Mat src,cv::Mat mask,float* ptr_dst);
    void computer_GFFT(cv::Mat src,cv::Mat mask,float* ptr_dst);
    void computer_Harris(cv::Mat src,cv::Mat mask,float* ptr_dst);
    void computer_ORB(cv::Mat src,cv::Mat mask,float* ptr_dst);
    void computer_HOG(cv::Mat src,cv::Mat mask,float* ptr_dst);

private slots:
    void on_action_exit_triggered();

    void on_pushButton_insert_clicked();

    void on_pushButton_rightmove_clicked();

    void on_pushButton_delete_clicked();

    void on_tableView_QueXianReady_List_pressed(const QModelIndex &index);

    void on_tableView_QueXianForStudy_List_pressed(const QModelIndex &index);

    void on_pushButton_leftmove_clicked();

    void on_pushButton_PathSelect_clicked();

    void on_action_SaveModel_triggered();

    void on_pushButton_study_clicked();

    void on_action_OpenModel_triggered();

    void on_action_Features_ManSelect_2_triggered();

private:
    Ui::Qt_AutomaticStudy_Default *ui;
};

#endif // QT_AUTOMATICSTUDY_DEFAULT_H
