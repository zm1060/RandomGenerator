#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <random>

using namespace std;

int cnt[10][100];
string class_name[10];
int stu_num[10];
int class_num = 0;
int n = 0;
int flag = 0;
int clicknum = 0;
int option = 0;
int first = 0;
void read_from_file(){
    ifstream has(to_string(option)+"_"+"config.txt");
    has>>flag;
    class_num = flag;
    has.close();
    for(int i = 0;i<class_num;i++){
        ifstream rea(to_string(option)+"_"+to_string(i)+".txt");
        rea>>class_name[i]>>stu_num[i]>>clicknum;
        int temp;
        for(int j = 1;j<=stu_num[i];j++){
            rea>>temp>>cnt[i][j];
        }
        rea.close();
    }
}

void write_to_file(){

    ofstream outconfig(to_string(option)+"_"+"config.txt");
    outconfig<<class_num;
    outconfig.close();
    for(int i = 0;i<class_num;i++){
           ofstream outfile(to_string(option)+"_"+to_string(i)+".txt");

           outfile<<class_name[i]<<"\t"<<stu_num[i]<<"\t"<<clicknum<<"\n";
           for(int j = 1;j<=stu_num[i];j++){
               outfile<<j<<"\t"<<cnt[i][j]<<"\n";
           }
           outfile.close();
    }
    first = 1;
    ofstream fir("first.txt");
    fir<<first;
    fir.close();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEditclassnum->setFocus();
    ui->lineEditOption->setText(QString::fromStdString("0"));
    ifstream isfirst("first.txt");
    isfirst>>first;
    isfirst.close();
    if(first != 0){
        read_from_file();
        ui->textEditInfo->append(QString::fromStdString("Local file "+to_string(option) + " has been loaded!!!"));
        ui->labelclassnum->setVisible(false);
        ui->labelclassstunum->setVisible(false);
        ui->lineEditclassname->setVisible(false);
        ui->lineEditclassnum->setVisible(false);
        ui->lineEditclassstunum->setVisible(false);
        ui->label->setVisible(false);
        ui->pushButtonAdd->setVisible(false);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButtonAdd_clicked()
{
    option = ui->lineEditOption->text().toInt();
    class_num = ui->lineEditclassnum->text().toInt();
    class_name[n] = ui->lineEditclassname->text().toStdString();
    stu_num[n] = ui->lineEditclassstunum->text().toInt();
    ui->lineEditclassstunum->clear();
    ui->lineEditclassname->clear();
    ui->textEditInfo->append(QString::fromStdString(class_name[n] + " has been appended!!!"));
    n++;
    if(n == class_num){
        ui->lineEditclassnum->clear();
        ui->textEditInfo->append(QString::fromStdString("class "+to_string(option)+ " has been appended!!!"));
        n = 0;
        ui->labelclassnum->setVisible(false);
        ui->labelclassstunum->setVisible(false);
        ui->lineEditclassname->setVisible(false);
        ui->lineEditclassnum->setVisible(false);
        ui->lineEditclassstunum->setVisible(false);
        ui->label->setVisible(false);
        ui->pushButtonAdd->setVisible(false);
    }

}

void MainWindow::on_pushButtonGenerate_clicked()
{
    std::random_device rd;

    clicknum++;
    int cn =  rand()%class_num;
    int min = INT_MAX;
    for(int i = 1;i<=stu_num[cn];i++){
        if(cnt[cn][i] < min){
            min = cnt[cn][i];
        }
    }
    int i = 0;
    while(1){
        i = (rd() % stu_num[cn])+1;
        if(cnt[cn][i] == min){
            cnt[cn][i]++;
            break;
        }else{
            continue;
        }
    }
    QFont f( "Arial", 36, QFont::Bold);
    ui->labelresult->setText(QString::fromStdString(class_name[cn] +":"+to_string(i)+"号"));
    ui->labelresult->setFont(f);

    ui->labelclassnum->setVisible(false);
    ui->labelclassstunum->setVisible(false);
    ui->lineEditclassname->setVisible(false);
    ui->lineEditclassnum->setVisible(false);
    ui->lineEditclassstunum->setVisible(false);
    ui->label->setVisible(false);
    ui->pushButtonAdd->setVisible(false);
    write_to_file();
}

void MainWindow::on_pushButtonOption_clicked()
{
    option = ui->lineEditOption->text().toInt();
    read_from_file();
    ui->labelclassnum->setVisible(false);
    ui->labelclassstunum->setVisible(false);
    ui->lineEditclassname->setVisible(false);
    ui->lineEditclassnum->setVisible(false);
    ui->lineEditclassstunum->setVisible(false);
    ui->label->setVisible(false);
    ui->pushButtonAdd->setVisible(false);
    ui->textEditInfo->append(QString::fromStdString("Local file "+to_string(option) + " has been loaded!!!"));
}

void MainWindow::on_lineEditOption_textChanged(const QString &arg1)
{
    ui->labelclassnum->setVisible(true);
    ui->labelclassstunum->setVisible(true);
    ui->lineEditclassname->setVisible(true);
    ui->lineEditclassnum->setVisible(true);
    ui->lineEditclassstunum->setVisible(true);
    ui->label->setVisible(true);
    ui->pushButtonAdd->setVisible(true);
}
