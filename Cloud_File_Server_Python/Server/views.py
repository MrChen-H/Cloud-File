from datetime import datetime
import json
import os
from django.db import IntegrityError
from .models import FileInfo, UserFileInfo
from django.http import HttpResponseServerError, JsonResponse, UnreadablePostError
from django.http import HttpResponse
from .models import UserInfo
import random
from django.views.decorators.csrf import csrf_exempt
from django.core.files.storage import default_storage
import zipfile
from django.forms.models import model_to_dict
import qrcode
# Create your views here.
def getfileinfo(request):
    file_info_list = FileInfo.objects.all()
    custom_data = [
        {
            'id': str(obj.id),
            'file_name': str(obj.file_name),
            'file_size': str(obj.file_size),
            'file_type': str(obj.file_type),
            'file_dir': str(obj.file_dir),
            'file_suffix': str(obj.file_suffix),
        } for obj in file_info_list
    ]
    return JsonResponse(custom_data, safe=False)
#end

def extract_zip(zip_file_path, target_dir):
    with zipfile.ZipFile(zip_file_path, 'r') as zip_ref:
        zip_ref.extractall(target_dir)
@csrf_exempt
def uploadfile(request):
    try:
        # 保存上传的文件到临时路径
        user_phone = request.POST.get('user_phone')
        org_file_name = request.POST.get('org_file_name')
        server_file_name = request.POST.get('server_file_name')
        md5_value = request.POST.get('md5_value')
        file_org_size = request.POST.get('file_org_size')
        make_qr_code = request.POST.get('make_qr_code')

        if UserFileInfo.objects.filter(file_server_name=server_file_name).exists():
            return JsonResponse({'status': 'error', 'message': '文件已存在'+' '+org_file_name})
        
        if request.method == 'POST':
        
            if 'file' in request.FILES:
                file_obj = request.FILES['file']
                try:
                    temp_file_path = default_storage.save(user_phone+'/'+server_file_name, file_obj)

                    if make_qr_code == 'true':
                        make_qr_code = True

                        data = "Hello, World!"
                        qr = qrcode.QRCode(
                            version=1,
                            error_correction=qrcode.constants.ERROR_CORRECT_L,
                            box_size=10,
                            border=4,
                        )
                        qr.add_data(data)
                        qr.make(fit=True)

                        # 创建二维码图像并保存到临时文件
                        temp_qr_file = "temp_qrcode.png"
                        img_qr = qr.make_image(fill="black", back_color="white")
                        img_qr.save(temp_qr_file)

                        # 已有ZIP压缩包的路径
                        existing_zip_path = os.path.abspath('.')+'/'+temp_file_path

                        # 打开已有ZIP文件以追加模式
                        with zipfile.ZipFile(existing_zip_path, 'a', zipfile.ZIP_DEFLATED) as zipf:
                            # 将临时二维码图片文件添加到ZIP压缩包
                            zipf.write(temp_qr_file, os.path.basename(temp_qr_file))

                        # 删除临时二维码图片文件（可选）
                        os.remove(temp_qr_file)
                    else:
                        make_qr_code = False
                except Exception as e:
                    return JsonResponse({'statue': 'error', 'msg': '文件保存失败'},statue=400)
                '''
                如果需要接收后解压启用一下代码块和修改上面save函数中的user_phone到一个临时路径即可
                '''
                #try:
                #    
                #    # 获取文件名（不包括扩展名）
                #    base_filename = os.path.splitext(file_obj.name)[0]
                #    # 创建与原始文件同名的文件夹
                #    target_dir = os.path.join(user_phone, base_filename)
                #    os.makedirs(target_dir, exist_ok=True)
                #    # 检查文件是否为ZIP文件
                #    if zipfile.is_zipfile(temp_file_path):
                #        # 解压缩ZIP文件
                #        with zipfile.ZipFile(temp_file_path, 'r') as zip_ref:
                #            zip_ref.extractall(target_dir)
                #    else:
                #        # 如果不是ZIP文件，使用pyunpack解压缩
                #        with open(temp_file_path, 'rb') as f:
                #            archive = pyunpack.Archive(f)
                #            archive.extractall(target_dir)
                #    # 清理临时文件
                #    default_storage.delete(temp_file_path)
                #except Exception as e:
                #    # 处理解压缩过程中的错误
                #    print(f"Error decompressing file: {e}")
                #    return JsonResponse({"status": "error", "message": "Error decompressing the file."}, status=500) 
                # 返回成功响应
                file_info = UserFileInfo(file_org_name = org_file_name,
                                         file_server_name = server_file_name,
                                         file_size = file_org_size,
                                         file_path = os.path.abspath('.')+'/'+temp_file_path,
                                         file_md5 = md5_value,
                                         file_finish_time = datetime.now(),
                                         has_qr_code = make_qr_code)
                try:
                    file_info.save()
                except Exception as e:
                    return JsonResponse({"status": "error", "message": "save file info to sql failed"},status=400)
                
                return JsonResponse({"status": "success", "message": "File uploaded successfully."}, status=200)

            else:
                return JsonResponse({"status": "error", "message": "No file was uploaded."}, status=400)
        else:
            return JsonResponse({"status": "error", "message": "Invalid request method."}, status=405)
    except UnreadablePostError as e:
        print("client close connect")
        return HttpResponseServerError("The connection was reset. Please try again.")
def get_phone_code(request):
    phone = request.POST.get("phone")
    
@csrf_exempt
def reg_account(request):
    if request.method == 'POST':
        try:
            data = json.loads(request.body.decode('utf-8'))
            phone_num = data.get("phone")
            password = data.get("password")
        except Exception as e:
            return JsonResponse({"status": "error", "message": "请求错误"}, status=400)
        
        if(phone_num == '' or password == ''):
            return JsonResponse({"status": "error", "message": "电话号或密码不可为空"}, status=400)
        
        if UserInfo.objects.filter(phone_number=phone_num).exists():
            return JsonResponse({"status": "error", "message": "电话已存在"}, status=400)
        
        account = str(random.randint(1000000000, 9999999999))
        while 1:
            if UserInfo.objects.filter(phone_number=phone_num).exists():
                account = str(random.randint(1000000000, 9999999999))
            else:
                break
        try:
            newUser = UserInfo(user_account=account,
                            user_password=password,
                            phone_number=phone_num)
            newUser.save()
            return HttpResponse("User created successfully.", status=200)
        except IntegrityError:
            # 可以根据需要处理错误，例如返回一个错误消息
            return HttpResponse("Failed to create user. Unkonw error", status=400)
    else:
        return JsonResponse({"status": "error", "message": "Invalid request method."}, status=405)

@csrf_exempt    
def user_sign_in(request):
    if not request.method == 'POST':
        return JsonResponse({"status": "error", "message": "Invalid request method."}, status=405)
    try:
        data = json.loads(request.body.decode('utf-8'))
        phone_num = data.get("phone")
        password = data.get("password")
    except Exception as e:
         return JsonResponse({"status": "error", "message": "请求错误"}, status=400)

    if(phone_num == '' or password == ''):
        return JsonResponse({"status": "error", "message": "电话号或密码不可为空"}, status=400)

    if not UserInfo.objects.filter(phone_number=phone_num).exists():
        return JsonResponse({"status": "error", "message": "电话不存在"}, status=400)
    
    user_info = UserInfo.objects.filter(phone_number=phone_num)
    if user_info.count() > 1 :
        return JsonResponse({"status": "error", "message": "存在多个相同账户,请联系管理员检查"}, status=400)

    if user_info[0].user_password == password:
        user_info_dict = model_to_dict(user_info[0])
        user_info_dict['create_time'] = user_info[0].create_time.isoformat()
        del user_info_dict['user_password']
        return JsonResponse({"status": "success", "message": "登录成功","user_info":user_info_dict}, status=200)
    else:
        return JsonResponse({"status": "error", "message": "密码错误"}, status=400)

@csrf_exempt
def getUserInfo(request):
    if not request.method == 'GET':
        return JsonResponse({"status": "error", "message": "请求方式错误"}, status=400)
    
    user_phone = request.GET.get('user_phone')
    user_phone = '13995941769'
    if not user_phone:
        return JsonResponse({"status": "error", "message": "参数异常"}, status=400)
    
    user_info = UserInfo.objects.get(phone_number=user_phone)

    if user_info:
        user_info = UserInfo.objects.get(phone_number=user_phone)
        # 将模型实例转换为字典
        user_info_dict = model_to_dict(user_info)
        user_info_dict['create_time'] = user_info.create_time.isoformat()
        del user_info_dict['user_password']
        return JsonResponse({"status": "success", "message": "查询成功", "user_info": user_info_dict}, status=200)
    else:
        return JsonResponse({"status": "error", "message": "用户不存在"}, status=400)
    
@csrf_exempt
def chech_file(request):
    if request.method == 'POST':
        data = json.loads(request.body.decode('utf-8'))
        server_file_name = data.get("server_file_name")
        if UserFileInfo.objects.filter(file_server_name=server_file_name).exists():
            return JsonResponse({"status": "error", "message": "文件已存在"}, status=400)
        else:
            return JsonResponse({"status": "success"}, status=200)
    else:
        return JsonResponse({"status": "error", "message": "请求方式错误"}, status=400)