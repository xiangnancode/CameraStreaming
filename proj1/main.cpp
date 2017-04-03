#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <algorithm>

#include "hi_type.h"
#include "hi_net_dev_sdk.h"
#include "hi_net_dev_errors.h"
#include "INIReader.h"


#define UNAME	"admin"
#define PWORD	"admin"
#define HOST	"192.168.0.38"
#define PORT	80

#define RECORD_FILE "test.hx"

using namespace std;

HI_S32 OnEventCallback(HI_U32 u32Handle, /* 句柄 */
                                HI_U32 u32Event,      /* 事件 */
                                HI_VOID* pUserData  /* 用户数据*/
                                )
{
	return HI_SUCCESS;
}

void SaveRecordFile(HI_CHAR *pPath, HI_U8* pu8Buffer, HI_U32 u32Length)
{
	FILE* fp;

	fp = fopen(pPath, "ab+");
	fwrite(pu8Buffer, 1, u32Length, fp);
	fclose(fp);
}

HI_S32 OnStreamCallback(HI_U32 u32Handle, /* 句柄 */
                                HI_U32 u32DataType,     /* 数据类型，视频或音频数据或音视频复合数据 */
                                HI_U8*  pu8Buffer,      /* 数据包含帧头 */
                                HI_U32 u32Length,      /* 数据长度 */
                                HI_VOID* pUserData    /* 用户数据*/
                                )
{

	HI_S_AVFrame* pstruAV = HI_NULL;
	HI_S_SysHeader* pstruSys = HI_NULL;
	
	string str = "Video.hx";
	char *output = new char[str.size() + 1];
	copy(str.begin(), str.end(), output);
	output[str.size()] = '\0';

	if (u32DataType == HI_NET_DEV_AV_DATA)
	{
		pstruAV = (HI_S_AVFrame*)pu8Buffer;

		if (pstruAV->u32AVFrameFlag == HI_NET_DEV_VIDEO_FRAME_FLAG)
		{
			printf("Video %u PTS: %u \n", pstruAV->u32VFrameType, pstruAV->u32AVFramePTS);
			SaveRecordFile(output, pu8Buffer, u32Length);			
		}
		else
		if (pstruAV->u32AVFrameFlag == HI_NET_DEV_AUDIO_FRAME_FLAG)
		{
			printf("Audio %u PTS: %u \n", pstruAV->u32AVFrameLen, pstruAV->u32AVFramePTS);
			SaveRecordFile(output, pu8Buffer, u32Length);			
		}
	}
	else
	if (u32DataType == HI_NET_DEV_SYS_DATA)
	{
		pstruSys = (HI_S_SysHeader*)pu8Buffer;
		printf("Video W:%u H:%u Audio: %u \n", pstruSys->struVHeader.u32Width, pstruSys->struVHeader.u32Height, pstruSys->struAHeader.u32Format);
	} 

	return HI_SUCCESS;
}

HI_S32 OnDataCallback(HI_U32 u32Handle, /* 句柄 */
                                HI_U32 u32DataType,       /* 数据类型*/
                                HI_U8*  pu8Buffer,      /* 数据 */
                                HI_U32 u32Length,      /* 数据长度 */
                                HI_VOID* pUserData    /* 用户数据*/
                                )
{
	return HI_SUCCESS;
}

string get_Config(string filename, string section, string name) {
	INIReader reader("./Data/"+filename);

    if (reader.ParseError() < 0) {
        std::cout << "Can't load 'config_net.ini'\n";
        return NULL;
    }
	string str = reader.Get(section, name, "UNKNOWN");
	//cout << str << endl;
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    //cout << str << endl;
    str.erase(remove(str.begin(), str.end(), '"'), str.end());
    //cout << str << endl;
    return str;
}


int main (int argc, char * const argv[]) 
{
	cout << "hello world" << endl;
	HI_S32 s32Ret = !HI_SUCCESS;
    HI_U32 u32Handle = 0;
    HI_S_STREAM_INFO struStreamInfo;
    HI_U32 a;
	HI_NET_DEV_Init();
    
	//get_Config configinfo;
	//read IP address and Port
	
    string ipaddr = get_Config("config_net.ini", "netinfo", "ipaddr");
    string port = get_Config("config_net.ini", "netsvr", "httpport");
    //print out 
	cout << ipaddr << endl;
	cout << port << endl;

	const HI_CHAR *cHOST = ipaddr.c_str();
	HI_U16 cPORT = atoi(port.c_str());

	//read username and password under userID #
	int userID = 0;
	while (s32Ret != HI_SUCCESS) {
		string username = get_Config("config_user.ini", "user"+to_string(userID), "username");
		string password = get_Config("config_user.ini", "user"+to_string(userID), "password");
		cout << userID << endl;
		cout << username << endl;
		cout << password << endl;
		if (username == "UNKNOWN") {break;}
		const HI_CHAR *cUNAME = username.c_str();
		const HI_CHAR *cPWORD = password.c_str();
		s32Ret = HI_NET_DEV_Login(&u32Handle, cUNAME, cPWORD, cHOST, cPORT);
		++userID;
	}
    //camera
    if (s32Ret != HI_SUCCESS)
    {
        HI_NET_DEV_DeInit();
	return -1;
    }
    HI_NET_DEV_SetEventCallBack(u32Handle, OnEventCallback, &a);
	HI_NET_DEV_SetStreamCallBack(u32Handle, OnStreamCallback, &a);
	HI_NET_DEV_SetDataCallBack(u32Handle, OnDataCallback, &a);

	struStreamInfo.u32Channel = HI_NET_DEV_CHANNEL_1;
	struStreamInfo.blFlag = HI_TRUE;//HI_FALSE;
	struStreamInfo.u32Mode = HI_NET_DEV_STREAM_MODE_TCP;
	struStreamInfo.u8Type = HI_NET_DEV_STREAM_ALL;
	//cout << "before" << struStreamInfo.u32Channel << endl;
	s32Ret = HI_NET_DEV_StartStream(u32Handle, &struStreamInfo);
	//cout << "after" << struStreamInfo.u32Channel << endl;
	if (s32Ret != HI_SUCCESS)
	{
		HI_NET_DEV_Logout(u32Handle);
		u32Handle = 0;
		return -1;
	}    
    sleep(5);
   
    HI_NET_DEV_StopStream(u32Handle);
    HI_NET_DEV_Logout(u32Handle);
    
    HI_NET_DEV_DeInit();

    printf("stop\n");
    return 0;
}