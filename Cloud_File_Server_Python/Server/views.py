from .models import FileInfo
from django.http import JsonResponse
from django.http import JsonResponse
from .models import UploadedFile
from django.views.decorators.csrf import csrf_exempt
import zipfile
from django.http import JsonResponse
from django.views.decorators.csrf import csrf_exempt
from django.core.files.storage import default_storage
import zipfile
import os
import pyunpack
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
    if request.method == 'POST':
        if 'file' in request.FILES:
            file_obj = request.FILES['file']

            # 保存上传的文件到临时路径
            temp_file_path = default_storage.save('temp_files/' + file_obj.name, file_obj)

            try:
                # 获取文件名（不包括扩展名）
                base_filename = os.path.splitext(file_obj.name)[0]

                # 创建与原始文件同名的文件夹
                target_dir = os.path.join('user_upload_files', base_filename)
                os.makedirs(target_dir, exist_ok=True)

                # 检查文件是否为ZIP文件
                if zipfile.is_zipfile(temp_file_path):
                    # 解压缩ZIP文件
                    with zipfile.ZipFile(temp_file_path, 'r') as zip_ref:
                        zip_ref.extractall(target_dir)
                else:
                    # 如果不是ZIP文件，使用pyunpack解压缩
                    with open(temp_file_path, 'rb') as f:
                        archive = pyunpack.Archive(f)
                        archive.extractall(target_dir)

                # 清理临时文件
                default_storage.delete(temp_file_path)
                
                # 返回成功响应
                return JsonResponse({"status": "success", "message": "File uploaded and decompressed successfully."}, status=200)
            except Exception as e:
                # 处理解压缩过程中的错误
                print(f"Error decompressing file: {e}")
                return JsonResponse({"status": "error", "message": "Error decompressing the file."}, status=500)
        else:
            return JsonResponse({"status": "error", "message": "No file was uploaded."}, status=400)
    else:
        return JsonResponse({"status": "error", "message": "Invalid request method."}, status=405)