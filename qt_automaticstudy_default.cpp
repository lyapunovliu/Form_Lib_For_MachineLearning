#include "qt_automaticstudy_default.h"
#include "ui_qt_automaticstudy_default.h"
#include <QFileDialog>

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

void Qt_AutomaticStudy_Default::on_action_SaveModel_triggered()
{

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

}
