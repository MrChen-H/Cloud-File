from django.db import models

# Create your models here.
class FileInfo(models.Model):
    '''地址表
    类里面的字段代表数据表中的字段(name)，数据类型则由CharField（相当于varchar）、DateField（相当于datetime）， max_length 参数限定长度'''
    
    file_name=models.CharField(max_length=50)
    file_size=models.CharField(max_length=50)
    file_type=models.CharField(max_length=50)
    file_dir=models.CharField(max_length=50)
    file_suffix=models.CharField(max_length=50)
    
    class Meta:
        #元类
        managed = False
        db_table = 't_file_info'#定义数据表名称
        verbose_name = '文件信息'#在网页端显示的名字
        verbose_name_plural = verbose_name#去复数形式
        
    def __str__(self):
        return self.file_name
#end

class UploadedFile(models.Model):
    file = models.FileField(upload_to='user_upload_file/')
    uploaded_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return self.file.name
#end