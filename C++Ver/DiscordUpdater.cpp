
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <fstream>
#include <chrono>
#include <direct.h>
#include<limits.h>


using namespace std;

int main()
{
    //time vars
    float framesDelay;
    string select;
    int numFrames;
    int endTime;
    int tts; //time to start in seconds
    int minutes;
    int sec_minutes;

    //string vars
    string firstRow;
    string secondRow;
    string largeImgDesc;
    string smallImageName;
    string smallImageDesc;
    string clientID;
    bool clientIDFirstTime = false;


    //reading client id
    ifstream clid("clientID.ini");
    if (clid.is_open()) //if internal conf exists
    {
        string line;
        while (getline(clid, line))
        {
            clientID = line;
            cout << "Current clientID: " << line << endl;
        }
        clid.close();
    }
    else //client id not set, asking the user
    {
        cout << "The ClientID has not been set, please insert your client id\n";
        cout << "This will be asked only once, make sure it's right\n             ";
        cin >> clientID;
        remove(clientID.begin(), clientID.end(), ' ');

        ofstream clid("clientID.ini");
        clid << clientID;
        clid.close();
        clientIDFirstTime = true;
    }

    

    while (true)
    {
        //setting the time in seconds
        cout << "Time goes forward or backward? (f / b)\n             ";
        cin >> select;
        if (select=="b" || select=="B")
        {
            cout << "Going backwards <<";
            cout << " ' mm:ss left'\n";
            cout << "Where should we start? (in seconds)\n              ";
                cin >> tts;
            if (tts>60)
            {
                minutes = tts / 60;
                sec_minutes = minutes * 60;
                cout << "The timer will decrease from " << tts / 60 << " Minutes and " << tts - sec_minutes << " Seconds\n";
                break;
            }
            else
            {
                cout << "The timer will decrease from " << tts << " Seconds\n";
                break;
            }
        }
        else if (select=="f" || select=="F")
        {
            cout << "Going forward >>";
            cout << " 'mm:ss elasped '\n";
            break;
        }
        else
            cout << "what? Type F or B\n";
    }
    
    while (true)
    {
        //set the delay
        cout << "Insert the delay between frames in seconds\n             ";
        cin >> framesDelay;
        framesDelay *= 1000;
        if (framesDelay < 1000)
            cout << "Delay can't be less than one second for Discord limitations\n";
        else
            break;
    }

    //first and second row desc
    while (true)
    {
        cout << "Type what to insert in the First row\n             ";
        cin.ignore();
        getline(cin, firstRow);
        if (firstRow.size() < 2)
        {
            cout << "You must enter more than 2 characters\n";
        }
        else
        {
            break;
        }
    }
    while (true)
    {
        cout << "Type what to insert in the Second row\n             ";
        getline(cin, secondRow);
        if (secondRow.size() < 3)
        {
            cout << "You must enter more than 2 characters\n";
        }
        else
        {
            break;
        }
    }
    cout << "Insert the number of frames\n             ";
    cin >> numFrames;
    numFrames -= 1;
    while (true)
    {
        cout << "Insert the description of the Large image\n(enter nothing if you don't want the description)\n             ";
        cin.ignore();
        getline(cin, largeImgDesc);
        if (largeImgDesc.size() < 2 && largeImgDesc.size() != 0)
        {
            cout << "You must insert more than 2 characters or leave blank\n";
        }
        else
        {
            break;
        }
    }
        cout << "Insert the name of the Small image (without extension)\n             ";
        getline(cin, smallImageName);
        while (true)
        {
            cout << "Insert the description of the Small image (enter nothing if you don't want the description)\n             ";
            getline(cin, smallImageDesc);
            if (largeImgDesc.size() < 3 && largeImgDesc.size() != 0)
            {
                cout << "You must insert more than 2 characters or leave blank\n";
            }
            else
            {
                break;
            }
    }
    Sleep(1500);
    cout << "\n\n\n\n\n\nDone! - You can run EasyRP...\n";
    cout << "Keep this running or EasyRP won\'t update!\n";


    Sleep(650);
    chrono::system_clock::time_point tp = chrono::system_clock::now();
    chrono::system_clock::duration dtn = tp.time_since_epoch();
    int c = -1;
    while (true)
    {
        //output to file
        ofstream conf;
        conf.open("config.ini");
        conf << ";########################################################################\n";
        conf << ";#         ______                _____  _____                           #\n";
        conf << ";#        |  ____|              |  __ \\|  __ \\                          #\n";
        conf << ";#        | |__   __ _ ___ _   _| |__) | |__) |                         #\n";
        conf << ";#        |  __| / _` / __| | | |  _  /|  ___/                          #\n";
        conf << ";#        | |___| (_| \__ \ |_| | | \ \| |                              #\n";
        conf << ";#        |______\__,_|___/\__, |_|  \_\_|                              #\n";
        conf << ";#                          __/ |                                       #\n";
        conf << ";#                         |___/  https://github.com/Pizzabelly/EasyRP  #\n";
        conf << ";#                                                                      #\n";
        conf << ";#                                                                      #\n";
        conf << ";# Optional Settings: SmallImage, LargeImageTooltip, SmallImageTooltip, #\n";
        conf << ";#                         StartTimestamp, EndTimestamp                 #\n";
        conf << ";#     *ALL OTHERS ARE REQUIRED*                                        #\n";
        conf << ";#                                                                      #\n";
        conf << ";# timestamps are in unix time -> https://www.epochconverter.com/       #\n";
        conf << ";#                                                                      #\n";
        conf << ";########################################################################\n\n";
        conf << "[Identifiers]\n";
        conf << "ClientID=" << clientID << "\n\n";
        conf << "[State]\n";
        conf << "State=" + secondRow + "\n";
        conf << "Details=" << firstRow << "\n";
        conf << "StartTimestamp=" << dtn.count() * chrono::system_clock::period::num / chrono::system_clock::period::den << "\n";
        if (select == "f")
            conf << "EndTimestamp=\n\n";
        else
            conf << "EndTimestamp=" << (dtn.count() * chrono::system_clock::period::num / chrono::system_clock::period::den) + tts << "\n\n";

        //updating frames
        if (c == numFrames)
            c = 0;
        else
            c += 1;
        conf << "LargeImage=" << c << "\n";
        conf << "LargeImageTooltip=" << largeImgDesc << "\n";
        conf << "SmallImage=" << smallImageName << "\n";
        conf << "SmallImageTooltip=" << smallImageDesc << "\n";
        conf.close();
        Sleep(framesDelay);
    }
    return 69;
}

