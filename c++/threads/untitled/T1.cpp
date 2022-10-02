#include "T1.h"

T1::T1(){}

void T1::appendText(QString text){
    que.push(text);
}

void T1::thread(){
    ofstream file;
    file.open("out.txt", ios::out);
    if (!file.is_open()) return;
    work = true;
    while (work){
        if (que.empty()) continue;
        string mes = que.front().toStdString();
        file << "Mes: " << mes << "\n";
        que.pop();
    }
    file.close();
    qDebug() << "Stop work";
}

void T1::stopWork(){
    work = false;
}
