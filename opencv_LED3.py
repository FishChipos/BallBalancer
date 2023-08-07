import cv2
import mediapipe as mp
import time
import math
import HandTrackingModule as htm
import serial

# arduino = serial.Serial(port='COM4',baudrate=9600,timeout=1)
pTime = 0
cTime = 0
cap = cv2.VideoCapture(0)
detector = htm.handDetector(mode=False,maxHands=1)
while True:
    SUCCESS, img = cap.read()
    img = detector.findHands(img)
    lmList = detector.findPosition(img)
       
    if len(lmList) != 0:        
        fingerUpList = [0,0,0,0]
        fingerCheckList = [7,11,15,19]
        amount = 0
        for i in fingerCheckList:
            length1 = math.hypot(lmList[i][1]+lmList[0][1],lmList[i][2]+lmList[0][2])
            length2 = math.hypot(lmList[i-1][1]+lmList[0][1],lmList[i-1][2]+lmList[0][2])
            
            if (length1 > length2):
                fingerUpList[fingerCheckList.index(i)] = 1
            else:
                fingerUpList[fingerCheckList.index(i)] = 0                                
        #print(fingerUpList)
        
        #if (fingerUpList == [1,1,1,1]):
                        
        
        #arduino.write(length.encode())
        #arduino.write('\n'.encode())
      
    cTime = time.time()
    fps = 1/(cTime-pTime)
    pTime = cTime
    cv2.putText(img, f'FPS: {int(fps)}', (0,20) , cv2.FONT_HERSHEY_PLAIN, 1, (0,0,0), 2)
      
    cv2.imshow("Video",img)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    