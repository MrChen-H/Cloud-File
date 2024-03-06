# Cloud-File
This is a Cloud file storage project,this project include a server and a client   
support multi-thread

# Preview   
## Upload
- ### Add an upload task to the upload task queue and uploading by now
![](https://github.com/MrChen-H/Cloud-File/blob/main/resource/UpLoad_one.gif)   

- ### Add some upload tasks to the upload task queue and upload them at the same time
![](https://github.com/MrChen-H/Cloud-File/blob/main/resource/UpLoad_mulit.gif)   

- ### Start,Pause or Remove one or more upload tasks
![](https://github.com/MrChen-H/Cloud-File/blob/main/resource/opt.gif)

- ### Other
  - Visual,real-time upload progress and speed
  - Theoretical maximum transferable file size of 50G(In fact, it can be configured higher, but it has not been tested...)
  - Tips when you are working without a task

# Future
- File download
- The transfer is interrupted and the transfer is made again according to the progress of the last transfer
- Add md5 check at Transport
- Luggage support(Simple Chinese and Engilsh)

# Third-Party Dependency and library
### Client
 - Qt(6.2.4)
 - [FluentUI(1.6.9)](https://github.com/zhuzichu520/FluentUI) by [zhuzichu520](https://github.com/zhuzichu520)
 - nlohmann json
### Server
 - Nginx(1.25.4)
 - Spawn-CGI(1.6.5)
 - Fast-CGI(2.4.1)
 - MySQL(8.0.36)
 - nlohmann json
 - spdlog

**Note**: The docker image is being prepared

