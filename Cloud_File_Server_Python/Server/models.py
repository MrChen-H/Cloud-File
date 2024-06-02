from django.db import models
import uuid
import random
from django.core.validators import RegexValidator

# Create your models here.
class FileInfo(models.Model):
    '''地址表
    类里面的字段代表数据表中的字段(name)，数据类型则由CharField（相当于varchar）、DateField（相当于datetime）,max_length 参数限定长度'''
    
    file_name=models.CharField(max_length=50)
    file_size=models.CharField(max_length=50)
    file_type=models.CharField(max_length=50)
    file_dir=models.CharField(max_length=50)
    file_suffix=models.CharField(max_length=50)
    def __str__(self):
        return self.file_name
#end

class UploadedFile(models.Model):
    file = models.FileField(upload_to='user_upload_file/')
    uploaded_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return self.file.name
#end

def generate_account_number():
    return ''.join([str(random.randint(0, 9)) for _ in range(16)])
#end
class UserInfo(models.Model):
    user_id = models.UUIDField(primary_key=True,default=uuid.uuid4,verbose_name="账号ID")

    user_account = models.CharField(
        default=generate_account_number,  # 使用生成函数作为默认值
        verbose_name="账号",  # 友好的字段名称
        help_text="系统自动生成的16位数字账号",
        max_length=16)
    user_password = models.CharField(null=False,max_length=16)
    phone_number = models.CharField(max_length=50)
    create_time = models.DateTimeField(auto_now_add=True)

class UserFileInfo(models.Model):
    file_id = models.CharField(max_length=50,default=uuid.uuid4,primary_key=True,verbose_name="文件ID")
    file_org_name = models.CharField(max_length=255)
    file_server_name = models.CharField(max_length=255)
    file_size = models.CharField(max_length=255)
    file_path = models.CharField(max_length=255)
    file_md5 = models.CharField(max_length=50)
    file_finish_time = models.DateTimeField(null=True)
    has_qr_code = models.BooleanField(default=False)
    