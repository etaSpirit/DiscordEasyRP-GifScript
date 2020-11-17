import time
import os
import array
   
#Set the delay between each frame (image) update / seconds
#WATCH OUT, values less than 1 second will cause discord to skip frames
framesDelay=1
select='null'
#Setting the time
#Set time in seconds
while 1:
    if (select == 'null'):
        select = str(input('Time goes forward or backward? (f / b)\n             '))
    else:
        select = str(input('what? Type F or B\n             '))
    if (select == 'b'):
        print("Goin' backwards <<")
        print("' mm:ss left'")
        tts= int(input ('Where should we start? (in seconds)\n              '))
        if tts>60:
            minutes=tts//60
            sec_minutes=minutes*60
            print('-- The timer will decrese from '+str(tts//60)+' Minutes and '+str(tts-sec_minutes)+' Seconds)) --\n\n')
            break
        else:
            print('-- The timer will decrese from '+tts+' Seconds --\n\n')
            break
    elif (select=='f'):
        print("Goin' forward >>")
        print("' mm:ss elapsed'\n\n")
        break
        #First and second row description
firstRow=str(input('Type what to insert in the First row\n             '))
secondRow=str(input('Type what to insert in the Second row\n             '))

   #Picture name used
#print('\n\nList of all Images:\n')
print("Zero two, 24")
numFrames=int(input('Insert the number of frames\n             '))

pics=[]
for x in range(numFrames):
  pics.append(x)
  
largeImgDescription=str(input("Insert the description of the Large image (enter nothing if you don't want the description)\n             "))
smallImage=str(input('Insert the name of the Small image (without extension)\n             '))
smallImgDescription=str(input("Insert the description of the Small image (enter nothing if you don't want the description)\n             "))
time.sleep(2)

print ('Done, starting Discord Rich Presence...')
print ('Keep this open or EasyRP won\' update')
time.sleep(0.65)
Time=time.time()
if (select=='b'):
	endTime=Time+tts
os.startfile('easyrp.exe')

c=-1
while 1:
	f = open("config.ini", "w")
	f.write(";########################################################################\n")
	f.write(";#         ______                _____  _____                           #\n")
	f.write(";#        |  ____|              |  __ \|  __ \                          #\n")
	f.write(";#        | |__   __ _ ___ _   _| |__) | |__) |                         #\n")
	f.write(";#        |  __| / _` / __| | | |  _  /|  ___/                          #\n")
	f.write(";#        | |___| (_| \__ \ |_| | | \ \| |                              #\n")
	f.write(";#        |______\__,_|___/\__, |_|  \_\_|                              #\n")
	f.write(";#                          __/ |                                       #\n")
	f.write(";#                         |___/  https://github.com/Pizzabelly/EasyRP  #\n")
	f.write(";#                                                                      #\n")
	f.write(";#                                                                      #\n")
	f.write(";# Optional Settings: SmallImage, LargeImageTooltip, SmallImageTooltip, #\n")
	f.write(";#                         StartTimestamp, EndTimestamp                 #\n")
	f.write(";#     *ALL OTHERS ARE REQUIRED*                                        #\n")
	f.write(";#                                                                      #\n")
	f.write(";# timestamps are in unix time -> https://www.epochconverter.com/       #\n")
	f.write(";#                                                                      #\n")
	f.write(";########################################################################\n\n")
	f.write("[Identifiers]\n")
	f.write("ClientID=477436364296814592\n\n")
	f.write("[State]\n")
	f.write("State="+secondRow+"\n")
	f.write("Details="+firstRow+"\n")
	f.write("StartTimestamp="+str(Time))
	f.write("\n\n")
	if (select=='f'):
		f.write("EndTimestamp=\n\n")
	else:
		f.write("EndTimestamp="+str(endTime))
		f.write("\n\n")
	f.write("[Images]\n")
	#condition that cycles through the frames
	if (c == numFrames):
		c=0
	else:
		c=c+1
	f.write("LargeImage="+str(c)+"\n")
	f.write("LargeImageTooltip="+largeImgDescription+"\n")
	f.write("SmallImage="+smallImage+"\n")
	f.write("SmallImageTooltip="+smallImgDescription+"---\n")
	f.close()
	time.sleep(framesDelay)

