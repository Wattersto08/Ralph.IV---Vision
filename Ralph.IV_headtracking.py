import cv2
import numpy as np
import serial


ser = serial.Serial('COM11', 9600, timeout=1)
sercount = 0

Xmin = 20
Xmax = 450
Ymin = 20
Ymax = 300

Xorig = int((Xmax-Xmin)/2)
Yorig = int((Ymax-Ymin)/2)


Green = (0,255,0)
Red = (0,0,255)
Teal = (255,255,25)
White = (255,255,255)

face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
eye_cascade = cv2.CascadeClassifier('haarcascade_eye.xml')  
cap = cv2.VideoCapture(0)

def make_720p():
    cap.set(3,1280)
    cap.set(4,720)

def make_480p():
    cap.set(3, 640)
    cap.set(4, 480)

make_480p()


while 1:
    sercount = sercount+1
    print(sercount)
    ret, img = cap.read()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)
    #img	=	cv2.drawMarker(	img, (320,240), (100,100,100), cv2.MARKER_CROSS, 640,1,4)	
    #cv2.rectangle(img,(310,230),(330,250),Red,-1)
    font = cv2.FONT_HERSHEY_SIMPLEX 
    cv2.putText(img,'Ralphs Eye v.1.0',(20,20), font, 0.5,(255,255,255),1,cv2.LINE_AA)
    for (x,y,w,h) in faces:
        img	=	cv2.drawMarker(	img, (320,240), (100,100,100), cv2.MARKER_CROSS, 640,1,4)
        
        if (320>x and 320<(x+w)and 240>y and 240<(y+h)):
            CentrePointstatus = Green
            cv2.putText(img,'Face Centered',(20,40), font, 0.5,(255,255,255),1,cv2.LINE_AA)
            
        else:
            CentrePointstatus = Red
            
        cv2.rectangle(img,(310,230),(330,250),CentrePointstatus,-1)
        fmidx = int(x+w/2)
        fmidy = int(y+h/2)
        img = cv2.arrowedLine(img,(320,240),(fmidx,fmidy),White,1,8,0,0.0)
        img = cv2.line(img,(fmidx,240),(fmidx,fmidy),White,1,8)
        img = cv2.line(img,(320,fmidy),(fmidx,fmidy),White,1,8)
        cv2.rectangle(img,(x,y),(x+w,y+h),Teal,2)
        roi_gray = gray[y:y+h, x:x+w]
        roi_color = img[y:y+h, x:x+w]
         
        

  #      eyes = eye_cascade.detectMultiScale(roi_gray)
  #      for (ex,ey,ew,eh) in eyes:
  #          cv2.rectangle(roi_color,(ex,ey),(ex+ew,ey+eh),(100,100,100),2)

        xoffset = x-Xorig
        yoffset = (y-Yorig)*-1
        print(x," X: ",xoffset, " Y: ",yoffset)
        if (sercount>10):
            cmd = '[MAN],'+str(yoffset)+','+str(xoffset)+',70;'
            ser.write(cmd.encode('UTF-8'))
            sercount = 0
       
        cv2.putText(img,'X offset: '+str(xoffset)+'  Y offset: '+str(yoffset),(20,60), font, 0.5,(255,255,255),1,cv2.LINE_AA)
        
    cv2.imshow('Ralphs Eye',img)
    if cv2.waitKey(20) & 0xFF == ord('k'):
        break

cap.release()
cv2.destroyAllWindows()

