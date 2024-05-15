from .models import FileInfo
from django.http import JsonResponse
from django.http import JsonResponse
from .models import UploadedFile
from django.views.decorators.csrf import csrf_exempt
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

@csrf_exempt
def uploadfile(request):
    if request.method == 'POST':
        if 'file' in request.FILES:
            file_obj = request.FILES['file']
            # 保存文件到模型
            uploaded_file = UploadedFile(file=file_obj)
            uploaded_file.save()
            
            # 返回成功响应，可根据需要调整响应内容
            return JsonResponse({"status": "success", "message": "File uploaded successfully."})
        else:
            # 如果没有文件，返回错误
            return JsonResponse({"status": "error", "message": "No file was uploaded."}, status=400)
    else:
        return JsonResponse({"status": "error", "message": "Invalid request method."}, status=405)