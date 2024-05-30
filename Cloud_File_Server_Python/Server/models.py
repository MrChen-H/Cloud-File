from django.db import models
import uuid
import random
from phonenumber_field.modelfields import PhoneNumberField
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

    phone_number = PhoneNumberField(validators=[RegexValidator(
        regex=r'^\+?1?\d{9,15}$',
        message="手机号格式不正确",
    )])

    user_password = models.CharField(null=False,max_length=16)
    