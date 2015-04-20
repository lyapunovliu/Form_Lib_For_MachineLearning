#ifndef QT_AUTOMATICSTUDY_DEFAULT_H
#define QT_AUTOMATICSTUDY_DEFAULT_H

#include <QMainWindow>
#include <QStandardItemModel>

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

private slots:
    void on_action_exit_triggered();

    void on_pushButton_insert_clicked();

    void on_pushButton_rightmove_clicked();

    void on_pushButton_delete_clicked();

    void on_tableView_QueXianReady_List_pressed(const QModelIndex &index);

    void on_tableView_QueXianForStudy_List_pressed(const QModelIndex &index);

    void on_pushButton_leftmove_clicked();

    void on_pushButton_PathSelect_clicked();

private:
    Ui::Qt_AutomaticStudy_Default *ui;
};

#endif // QT_AUTOMATICSTUDY_DEFAULT_H
