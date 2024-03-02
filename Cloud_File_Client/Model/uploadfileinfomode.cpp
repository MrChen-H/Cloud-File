#include "uploadfileinfomode.h"

UpLoadfileInfoMode* UpLoadfileInfoMode::Instance = new UpLoadfileInfoMode();

UpLoadfileInfoMode::~UpLoadfileInfoMode()
{
    if(Instance!=nullptr)
    {
        delete Instance;
        Instance = nullptr;
    }
}

UpLoadfileInfoMode *UpLoadfileInfoMode::getInstance()
{
    return Instance;
}

int UpLoadfileInfoMode::rowCount(const QModelIndex &parent) const
{
    return this->upLoadInfoList.size();
}

QHash<int, QByteArray> UpLoadfileInfoMode::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[FileNameRole] = "fileName";
    roles[DownLoadSizeRole] = "downLoadSize";
    roles[DownLoadSpeedRole] = "downLoadSpeed";
    roles[CountSizeRole] = "countSize";
    roles[InfoIndexRole] = "infoIndex";
    roles[FileTypeRole] = "fileType";
    return roles;
}

QVariant UpLoadfileInfoMode::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= upLoadInfoList.count()) {
        return QVariant();
    }

    const UpLoadInfo &data = upLoadInfoList[row];
    switch (role) {
    case FileNameRole:
        return data.fileName;
    case DownLoadSizeRole:
        return data.downLoadSize;
    case DownLoadSpeedRole:
        return data.downLoadSpeed;
    case CountSizeRole:
        return data.countSize;
    case InfoIndexRole:
        return data.infoIndex;
    case FileTypeRole:
        return data.fileType;
    default:
        return QVariant();
    }
}


void UpLoadfileInfoMode::append(const UpLoadInfo &info)
{
    emit beginInsertRows(QModelIndex(),upLoadInfoList.size(),upLoadInfoList.size());
    upLoadInfoList.append(info);
    emit endInsertRows();
}

void UpLoadfileInfoMode::remove(int index)
{
    emit beginRemoveRows(QModelIndex(),index,index);
    upLoadInfoList.removeAt(index);
    emit endRemoveRows();

    for(int i=0;i<this->upLoadInfoList.size();i++)
    {
        upLoadInfoList[i].infoIndex = i;
    }
}

void UpLoadfileInfoMode::removeAll()
{
    emit beginResetModel();
    upLoadInfoList.clear();
    emit endResetModel();
}

UpLoadfileInfoMode::UpLoadfileInfoMode(QObject *parent)
{

}
