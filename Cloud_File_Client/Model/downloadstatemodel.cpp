#include "downloadstatemodel.h"

DownLoadStateModel* DownLoadStateModel::Instance = nullptr;
std::mutex* DownLoadStateModel::threadLock = new std::mutex();

DownLoadStateModel::~DownLoadStateModel()
{
    if(Instance!=nullptr)
    {
        delete Instance;
        Instance = nullptr;
    }
    if(threadLock!=nullptr)
    {
        delete threadLock;
        threadLock = nullptr;
    }
}

DownLoadStateModel *DownLoadStateModel::getInstance()
{
    if(Instance != nullptr)
    {
        return Instance;
    }
    else
    {
        threadLock->lock();
        Instance = new DownLoadStateModel();
        DownLoadInfo info;
        info.countSize = 1000;
        info.downLoadSize = 1000;
        info.downLoadSpeed = 100;
        info.fileName = "test.txt";
        info.infoIndex = 0;
        info.fileType = "txt";
        Instance->append(info);
        threadLock->unlock();
    }
    return Instance;

}
int DownLoadStateModel::rowCount(const QModelIndex &parent) const
{
    return this->downLoadInfo.size();
}

QHash<int, QByteArray> DownLoadStateModel::roleNames() const
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

QVariant DownLoadStateModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= downLoadInfo.count()) {
        return QVariant();
    }

    const DownLoadInfo &data = downLoadInfo[row];
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

void DownLoadStateModel::updateInfo(int index, DownLoadInfo &Newinfo)
{
    for(auto &info : this->downLoadInfo)
    {
        if(info.infoIndex == index)
        {
            info = Newinfo;
            break;
        }
    }
}

void DownLoadStateModel::append(DownLoadInfo& info)
{
    emit beginInsertRows(QModelIndex(),downLoadInfo.size(),downLoadInfo.size());
    downLoadInfo.append(info);
    emit endInsertRows();
}

void DownLoadStateModel::remove(int index)
{
    emit beginRemoveRows(QModelIndex(),index,index);
    downLoadInfo.removeAt(index);
    emit endRemoveRows();

    for(int i=0;i<this->downLoadInfo.size();i++)
    {
        downLoadInfo[i].infoIndex = i;
    }

}

void DownLoadStateModel::removeAll()
{
    emit beginResetModel();
    downLoadInfo.clear();
    emit endResetModel();
}

DownLoadStateModel::DownLoadStateModel(QObject *parent)
{

}
