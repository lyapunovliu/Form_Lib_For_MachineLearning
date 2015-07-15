#include "qt_automaticstudy_default.h"
#include "ui_qt_automaticstudy_default.h"
#include <QFileDialog>
#include <fstream>
#include "character_select_dlg.h"
#include <QTextStream>

using namespace std;
Qt_AutomaticStudy_Default::Qt_AutomaticStudy_Default(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Qt_AutomaticStudy_Default)
{
    ui->setupUi(this);
    QueXianReady_ListHeaderDraw();
    QueXianForStudy_ListHeaderDraw();
    defaultSequenceNum=0;
    defaultStudyNum=0;
}

Qt_AutomaticStudy_Default::~Qt_AutomaticStudy_Default()
{
    delete ui;
}

void Qt_AutomaticStudy_Default::on_action_exit_triggered()
{
    this->close();
}
void Qt_AutomaticStudy_Default::QueXianReady_ListHeaderDraw()
{
    quexianClass_model = new QStandardItemModel();
    quexianClass_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("缺陷定义")));
    quexianClass_model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("缺陷索引")));
    quexianClass_model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("样本路径")));

    //利用setModel()方法将数据模型与QTableView绑定
    ui->tableView_QueXianReady_List->setModel(quexianClass_model);
}

void Qt_AutomaticStudy_Default::QueXianForStudy_ListHeaderDraw()
{
    quexianForStudy_model = new QStandardItemModel();
    quexianForStudy_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("缺陷定义")));
    quexianForStudy_model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("缺陷索引")));
    quexianForStudy_model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("样本路径")));

    //利用setModel()方法将数据模型与QTableView绑定
    ui->tableView_QueXianForStudy_List->setModel(quexianForStudy_model);
}

void Qt_AutomaticStudy_Default::on_pushButton_insert_clicked()
{
    QString quexian_name=ui->lineEdit_ClassName->text();
    QString quexian_name_index=ui->lineEdit_ClassTyep_Index->text();
    QString quexian_path=ui->lineEdit_Path->text();
    quexianClass_model->setItem(defaultSequenceNum, 0, new QStandardItem(quexian_name));
    quexianClass_model->setItem(defaultSequenceNum, 1, new QStandardItem(quexian_name_index));
    quexianClass_model->setItem(defaultSequenceNum, 2, new QStandardItem(quexian_path));
    defaultSequenceNum++;

}

void Qt_AutomaticStudy_Default::on_pushButton_rightmove_clicked()
{
    QString quexian_name=ui->tableView_QueXianReady_List->model()->data(ui->tableView_QueXianReady_List->model()->index(current_index_Readylist,0)).toString();
    QString quexian_name_index=ui->tableView_QueXianReady_List->model()->data(ui->tableView_QueXianReady_List->model()->index(current_index_Readylist,1)).toString();
    QString quexian_path=ui->tableView_QueXianReady_List->model()->data(ui->tableView_QueXianReady_List->model()->index(current_index_Readylist,2)).toString();

    quexianForStudy_model->setItem(defaultStudyNum, 0, new QStandardItem(quexian_name));
    quexianForStudy_model->setItem(defaultStudyNum, 1, new QStandardItem(quexian_name_index));
    quexianForStudy_model->setItem(defaultStudyNum, 2, new QStandardItem(quexian_path));

    defaultStudyNum++;
    defaultSequenceNum--;

    quexianClass_model->removeRow(current_index_Readylist);

}

void Qt_AutomaticStudy_Default::on_pushButton_delete_clicked()
{
    defaultSequenceNum--;

    quexianClass_model->removeRow(current_index_Readylist);

}

void Qt_AutomaticStudy_Default::on_tableView_QueXianReady_List_pressed(const QModelIndex &index)
{
    current_index_Readylist=index.row();
}

void Qt_AutomaticStudy_Default::on_tableView_QueXianForStudy_List_pressed(const QModelIndex &index)
{
    current_index_StudyList=index.row();
}

void Qt_AutomaticStudy_Default::on_pushButton_leftmove_clicked()
{
    QString quexian_name=ui->tableView_QueXianForStudy_List->model()->data(ui->tableView_QueXianForStudy_List->model()->index(current_index_StudyList,0)).toString();
    QString quexian_name_index=ui->tableView_QueXianForStudy_List->model()->data(ui->tableView_QueXianForStudy_List->model()->index(current_index_StudyList,1)).toString();
    QString quexian_path=ui->tableView_QueXianForStudy_List->model()->data(ui->tableView_QueXianForStudy_List->model()->index(current_index_StudyList,2)).toString();

    quexianClass_model->setItem(defaultSequenceNum, 0, new QStandardItem(quexian_name));
    quexianClass_model->setItem(defaultSequenceNum, 1, new QStandardItem(quexian_name_index));
    quexianClass_model->setItem(defaultSequenceNum, 2, new QStandardItem(quexian_path));

    defaultStudyNum--;
    defaultSequenceNum++;
    quexianForStudy_model->removeRow(current_index_StudyList);
}

void Qt_AutomaticStudy_Default::on_pushButton_PathSelect_clicked()
{
    QString DirectoryName = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/home",QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->lineEdit_Path->setText(DirectoryName);



}

//学习文件保存
void Qt_AutomaticStudy_Default::on_action_SaveModel_triggered()
{
    ofstream outFile;
    outFile.open("D:\\my_study_model.txt",ofstream::out);
    outFile<<"class_name\t "<<"class_ID\t "<<"class path"<<endl;
    for(int i=0;i<defaultStudyNum;i++)
    {
        QString quexian_name=ui->tableView_QueXianForStudy_List->model()->data(ui->tableView_QueXianForStudy_List->model()->index(i,0)).toString();
        QString quexian_name_index=ui->tableView_QueXianForStudy_List->model()->data(ui->tableView_QueXianForStudy_List->model()->index(i,1)).toString();
        QString quexian_path=ui->tableView_QueXianForStudy_List->model()->data(ui->tableView_QueXianForStudy_List->model()->index(i,2)).toString();
        outFile<<quexian_name.toStdString()<<"\t"<<quexian_name_index.toStdString()<<"\t"<<quexian_path.toStdString()<<endl;


    }
    outFile.close();



}

void Qt_AutomaticStudy_Default::on_pushButton_study_clicked()
{
    PR_Processsing();

}
void Qt_AutomaticStudy_Default::PR_Processsing()
{
    std::vector<QString> data_list;
    std::vector<int> data_label;
    PR_ready_data(data_list,data_label);
//    PR_Characters compute_result1;
//    init_Character(compute_result1);
//    cv::Mat vector_mat_whole=cv::Mat::zeros(data_list.size(),74,CV_32FC1);
//    cv::Mat vector_mat=vector_mat_whole.colRange(0,73);
//    cv::Mat vector_label=vector_mat_whole.col(73);

//    for(int i=0;i<data_list.size();i++)
//    {
//        QString str=data_list[i];
//        cv::Mat img_mat=cv::imread(str.toStdString().c_str());
//        computer_PR_character1(img_mat,characters_flag,compute_result1,data_label[i]);
//        vector_to_Mat(compute_result1,vector_mat.row(i));
//        vector_label.at<float>(i,0)=(float)data_label[i];
//    }
//    write_to_csv(vector_mat_whole);
//    cv::FileStorage fs("D:\\test.yml", FileStorage::WRITE);
//    fs<<"mat"<<vector_mat;
//    fs.release();

//    if(ui->comboBox_LearningMethod->currentText()=="SVM")
//        compute_SVM_withNormalize(vector_mat,vector_label);
//    if(ui->comboBox_LearningMethod->currentText()=="DT")
//        compute_DecisionTree_withNormalize(vector_mat,vector_label);
//    if(ui->comboBox_LearningMethod->currentText()=="RT")
//        compute_RandomForest_withNormalize(vector_mat,vector_label);
//    if(ui->comboBox_LearningMethod->currentText()=="Boost")
//        compute_Boost_withNormalize(vector_mat,vector_label);
//    if(ui->comboBox_LearningMethod->currentText()=="ANN")
//        compute_ANN_withNormalize(vector_mat,vector_label);

}

void Qt_AutomaticStudy_Default::PR_ready_data(std::vector<QString>,std::vector<int>)
{
    //读入各文件目录及目录类别
    QStringList quexian_pathList;
    QStringList quexian_pathlabelList;

    for(int i=0;i<defaultStudyNum;i++)
    {
        QString quexian_name=ui->tableView_QueXianForStudy_List->model()->data(ui->tableView_QueXianForStudy_List->model()->index(i,0)).toString();
        QString quexian_name_index=ui->tableView_QueXianForStudy_List->model()->data(ui->tableView_QueXianForStudy_List->model()->index(i,1)).toString();
        QString quexian_path=ui->tableView_QueXianForStudy_List->model()->data(ui->tableView_QueXianForStudy_List->model()->index(i,2)).toString();
        quexian_pathList.append(quexian_path);
        quexian_pathlabelList.append(quexian_name_index);
    }


    //读入各目录文件

    QStringList quexian_fileList;
    QStringList quexian_filelabelList;
    for(int i=0;i<defaultStudyNum;i++)
    {
        show_fileinList(quexian_pathList.at(i),quexian_pathlabelList.at(i).toInt(),quexian_fileList,quexian_filelabelList);
    }
    //读取设定特征
    QStringList quexian_charactersList;
    ifstream f_read("D:\\my_character_model.txt");
    char buffer[256];
    f_read.getline(buffer,256,'\n');//getline(char *,int,char) 表示该行字符达到256个或遇到换行就结束

    while(!f_read.eof())
    {
       f_read.getline(buffer,256,'\n');//getline(char *,int,char) 表示该行字符达到256个或遇到换行就结束
       QString qline(buffer);
       QStringList strlist =qline.split('\t');
       if(strlist.count()<1)
           break;
       quexian_charactersList.append(strlist[0]);
    }



    //根据文件进行特征计算,写入文件 第一：写入标签名称

    ofstream outFile;
    outFile.open("D:\\characters_quexian.txt",ofstream::out);
//    ofstream labeloutFile;
//    outFile.open("D:\\charactersLabel_quexian.txt",ofstream::out);

//    labeloutFile<<"label"<<"\n";
    for(int j=0;j<quexian_charactersList.count();j++)
    {
        int dim=getDimesionOfGivenCharacter(quexian_charactersList.at(j));
        if (dim>1)
        {
            for(int k=0;k<dim;k++)
                outFile<<quexian_charactersList.at(j).toStdString()<<"_"<<k<<"\t";
        }
        else
        {
            outFile<<quexian_charactersList.at(j).toStdString()<<"\t";

        }
    }
    outFile<<"\n";

    cv::Mat src;
    cv::Mat mask;
    float quexian_characters[100];

    //根据文件进行特征计算,写入文件 第二：写入样本特征
    //样本数量
    for(int i=0;i<quexian_fileList.count();i++)
    {
//        labeloutFile<<quexian_filelabelList.at(i).toStdString()<<"\n";
        //特征循环
        for(int j=0;j<quexian_charactersList.count();j++)
        {
            //读入文件到变量
            src=cv::imread(quexian_fileList.at(i).toStdString().c_str());
            mask=src.clone();
            float *ptr_characers;
            ptr_characers=quexian_characters;
            //得到对应特征的浮点数值
            getCharacter(src,mask,ptr_characers,quexian_charactersList.at(j));
            int dim=getDimesionOfGivenCharacter(quexian_charactersList.at(j));
            if (dim>1)
            {
                //特征元素输入
                for(int k=0;k<dim;k++)
                    outFile<<1.01*i<<"\t";
            }
            else
            {
                //特征元素输入k
//                outFile<<1.01*i<<"\t";
                outFile<<*ptr_characers<<"\t";

            }
        }
        outFile<<"\n";

    }


    //根据文件进行特征计算,写入文件 第三：结束文件
    outFile.close();
//    labeloutFile.close();


    //特征归一化



}

void Qt_AutomaticStudy_Default::on_action_OpenModel_triggered()
{
    QString openfileName=QFileDialog::getOpenFileName(this);
    ifstream f_read(openfileName.toStdString().c_str());
    char buffer[256];
    f_read.getline(buffer,256,'\n');//getline(char *,int,char) 表示该行字符达到256个或遇到换行就结束

    while(!f_read.eof())
    {
       f_read.getline(buffer,256,'\n');//getline(char *,int,char) 表示该行字符达到256个或遇到换行就结束
//       cout<<buffer<<endl;
       QString qline(buffer);
       QStringList strlist =qline.split('\t');
       if(strlist.count()<3)
           break;

       QString quexian_name=strlist.at(0);
       QString quexian_name_index=strlist.at(1);
       QString quexian_path=strlist.at(2);

       quexianForStudy_model->setItem(defaultStudyNum, 0, new QStandardItem(quexian_name));
       quexianForStudy_model->setItem(defaultStudyNum, 1, new QStandardItem(quexian_name_index));
       quexianForStudy_model->setItem(defaultStudyNum, 2, new QStandardItem(quexian_path));

       defaultStudyNum++;

       int i=0;
    }


}

void Qt_AutomaticStudy_Default::on_action_Features_ManSelect_2_triggered()
{
    Character_Select_Dlg* w=new Character_Select_Dlg;
    w->show();
}


void Qt_AutomaticStudy_Default::show_fileinList(QString dir_path,int class_ID,QStringList& fileList,QStringList& labelList)
{
    QTextStream cin(stdin, QIODevice::ReadOnly);
    QTextStream cout(stdout, QIODevice::WriteOnly);
    if(1)
    {
        QDir dir(dir_path);
        dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        dir.setSorting(QDir::Size | QDir::Reversed);
        QFileInfoList list = dir.entryInfoList();
        printf("Bytes Filename\n");
        for (int i = 0; i < list.size(); ++i)
        {
            QFileInfo fileInfo = list.at(i);
            cout << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10)
                                                    .arg(fileInfo.fileName()));
            cout << endl;
            fileList <<dir_path+"/"+fileInfo.fileName(); //list中添加内容
            labelList<<QString::number(class_ID);

        }
    }
    int j=0;
    j=1;
}
int Qt_AutomaticStudy_Default::getDimesionOfGivenCharacter(QString name)
{
    if (name.compare("length")==0)
    {

        return 1;
    }
    if (name.compare("Width")==0)
    {

        return 1;
    }
    if (name.compare("Area")==0)
    {

        return 1;
    }
    if (name.compare("LBP59")==0)
    {

        return 59;
    }
    if (name.compare("AvgGreyValue")==0)
    {

        return 1;
    }
    if (name.compare("MinGreyValue")==0)
    {

        return 1;
    }
    if (name.compare("MaxGreyValue")==0)
    {

        return 1;
    }
    if (name.compare("SURF")==0)
    {

        return 1;
    }
    if (name.compare("OriginInput")==0)
    {

        return 1;
    }
    return 0;

}
void Qt_AutomaticStudy_Default::getCharacter(cv::Mat src,cv::Mat mask,float* ptr_dst,QString name)
{
    if (name.compare("length")==0)
    {
        *ptr_dst=2.0*(src.cols+src.rows);

        return;
    }
    if (name.compare("Width")==0)
    {
        *ptr_dst=1.0*src.cols;

        return;
    }
    if (name.compare("Area")==0)
    {
        *ptr_dst=1.0*(src.cols*src.rows);

        return;
    }
    if (name.compare("LBP59")==0)
    {
        computer_LBP59(src,mask,ptr_dst);


        return;
    }
    if (name.compare("AvgGreyValue")==0)
    {
        computer_AvgGreyValue(src,mask,ptr_dst);
        return;
    }
    if (name.compare("MinGreyValue")==0)
    {

        computer_MinGreyValue(src,mask,ptr_dst);

        return;
    }
    if (name.compare("MaxGreyValue")==0)
    {
        computer_MaxGreyValue(src,mask,ptr_dst);

        return;
    }
    if (name.compare("SURF")==0)
    {
        computer_SURF(src,mask,ptr_dst);

        return;
    }
    if (name.compare("OriginInput")==0)
    {

        return;
    }
    if (name.compare("SIFT")==0)
    {

        return;
    }
    if (name.compare("GFFT")==0)
    {

        return;
    }
    if (name.compare("Harris")==0)
    {

        return;
    }
    if (name.compare("ORB")==0)
    {

        return;
    }
    if (name.compare("HOG")==0)
    {

        return;
    }

}
void Qt_AutomaticStudy_Default::computer_LBP59(cv::Mat src, cv::Mat mask, float* ptr_dst)
{

}
void Qt_AutomaticStudy_Default::computer_SURF(cv::Mat src, cv::Mat mask, float* ptr_dst)
{

}

void Qt_AutomaticStudy_Default::computer_AvgGreyValue(cv::Mat src, cv::Mat mask, float* ptr_dst)
{

}

void Qt_AutomaticStudy_Default::computer_MinGreyValue(cv::Mat src, cv::Mat mask, float* ptr_dst)
{

}

void Qt_AutomaticStudy_Default::computer_MaxGreyValue(cv::Mat src, cv::Mat mask, float* ptr_dst)
{

}
void Qt_AutomaticStudy_Default::computer_SIFT(cv::Mat src, cv::Mat mask, float* ptr_dst)
{

}
void Qt_AutomaticStudy_Default::computer_GFFT(cv::Mat src, cv::Mat mask, float* ptr_dst)
{

}
void Qt_AutomaticStudy_Default::computer_Harris(cv::Mat src, cv::Mat mask, float* ptr_dst)
{

}
void Qt_AutomaticStudy_Default::computer_ORB(cv::Mat src, cv::Mat mask, float* ptr_dst)
{

}
void Qt_AutomaticStudy_Default::computer_HOG(cv::Mat src, cv::Mat mask, float* ptr_dst)
{

}
