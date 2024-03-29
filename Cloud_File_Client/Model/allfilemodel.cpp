#include "allfilemodel.h"

AllFileModel * AllFileModel::Instance = new AllFileModel();

AllFileModel::~AllFileModel()
{

}

AllFileModel *AllFileModel::getInstance()
{
    return Instance;

}
AllFileModel::AllFileModel(QObject *parent)
{

}

int AllFileModel::rowCount(const QModelIndex &parent) const
{
    return file_list.size();
}

QHash<int, QByteArray> AllFileModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[FileNameRole] = "fileName";
    roles[FileUrlRole] = "fileUrl";
    roles[InfoIndexRole] = "infoIndex";
    roles[FileTypeRole] = "fileType";
    roles[FileSizeRole] = "FileSize";
    roles[FileIdRole] = "FileID";
    return roles;
}

QVariant AllFileModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= file_list.count()) {
        return QVariant();
    }

    const FileInfo &data = file_list[row];
    switch (role) {
    case FileNameRole:
        return data.fileName;
    case FileUrlRole:
        return data.fileUrl;
    case InfoIndexRole:
        return data.index;
    case FileTypeRole:
        return data.fileType;
    case FileSizeRole:
        return data.fileSize;
    case FileIdRole:
        return data.id;
    default:
        return QVariant();
    }
}

void AllFileModel::updateInfo(int index, FileInfo &info)
{

}

void AllFileModel::append(FileInfo &info)
{
    emit beginInsertRows(QModelIndex(),file_list.size(),file_list.size());
    file_list.append(info);
    emit endInsertRows();
}

void AllFileModel::remove(int index)
{
    emit beginRemoveRows(QModelIndex(),index,index);
    file_list.removeAt(index);
    emit endRemoveRows();
    for(int i=0;i<this->file_list.size();i++)
    {
        file_list[i].index = i;
    }
}

void AllFileModel::removeAll()
{
    emit beginResetModel();
    file_list.clear();
    emit endResetModel();
}
