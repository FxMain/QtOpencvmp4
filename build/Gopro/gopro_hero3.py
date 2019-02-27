import os
from goprocam import GoProCamera
from goprocam import constants
gpCam = GoProCamera.GoPro()
print("GoProOK")
file = open('GoProOK','w')
file.close()

while True:
    video_start_flag = os.path.isfile('Start')
    video_stop_flag = os.path.isfile('Stop')
    video_download_flag = os.path.isfile('Download')

    if(video_start_flag):
        gpCam.video_settings("720p", "30")
        gpCam.shoot_video()
        os.remove('Start')
        print("Start")
    if(video_stop_flag):
        gpCam.shutter(constants.stop)
        os.remove('Stop')
        print("Stop")
    if(video_download_flag):
        os.remove('Download')
        file = open('Downloading', 'w')
        print("Downloading")
        file.close()
        print("Downloading2")
        gpCam.downloadLastMedia()
        print("Downloading3")
        os.remove('Downloading')
        file = open('Download_OK', 'w')
        print("Download_OK")
        file.close()
