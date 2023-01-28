#include "Practice4.h"
#include <stdio.h>  
#include <windows.h>
#include <condition_variable>
#include <mutex>
#include <iostream>
#pragma comment(lib, "winmm.lib")  

HWAVEIN hWaveIn;  //�����豸
WAVEFORMATEX waveform; //�ɼ���Ƶ�ĸ�ʽ���ṹ��
BYTE* pBuffer1;//�ɼ���Ƶʱ�����ݻ���
WAVEHDR wHdr1; //�ɼ���Ƶʱ�������ݻ���Ľṹ��
FILE* pf;
std::mutex mut;

char buf[1024 * 1024 * 4];

void play_thread();

void record_thread()
{
    HANDLE          wait;
    waveform.wFormatTag = WAVE_FORMAT_PCM;//������ʽΪPCM
    waveform.nSamplesPerSec = 8000;//�����ʣ�16000��/��
    waveform.wBitsPerSample = 16;//�������أ�16bits/��
    waveform.nChannels = 1;//������������2����
    waveform.nAvgBytesPerSec = 16000;//ÿ��������ʣ�����ÿ���ܲɼ������ֽڵ�����
    waveform.nBlockAlign = 2;//һ����Ĵ�С������bit���ֽ�������������
    waveform.cbSize = 0;//һ��Ϊ0

    wait = CreateEvent(NULL, 0, 0, NULL);
    //ʹ��waveInOpen����������Ƶ�ɼ�
    waveInOpen(&hWaveIn, WAVE_MAPPER, &waveform, (DWORD_PTR)wait, 0L, CALLBACK_EVENT);
    
    //�����������飨������Խ���������飩����������Ƶ����
    DWORD bufsize = 1024 * 100;//ÿ�ο���10k�Ļ���洢¼������
    int i = 20;

    while (i--)//¼��20�����������������Ƶ��������紫������޸�Ϊʵʱ¼�����ŵĻ�����ʵ�ֶԽ�����
    {
        fopen_s(&pf, "test.pcm", "wb");
        pBuffer1 = new BYTE[bufsize];
        wHdr1.lpData = (LPSTR)pBuffer1;
        wHdr1.dwBufferLength = bufsize;
        wHdr1.dwBytesRecorded = 0;
        wHdr1.dwUser = 0;
        wHdr1.dwFlags = 0;
        wHdr1.dwLoops = 1;
        waveInPrepareHeader(hWaveIn, &wHdr1, sizeof(WAVEHDR));//׼��һ���������ݿ�ͷ����¼��
        waveInAddBuffer(hWaveIn, &wHdr1, sizeof(WAVEHDR));//ָ���������ݿ�Ϊ¼�����뻺��
        waveInStart(hWaveIn);//��ʼ¼��
        Sleep(1000);//�ȴ�����¼��1s
        waveInReset(hWaveIn);//ֹͣ¼��
        fwrite(pBuffer1, 1, wHdr1.dwBytesRecorded, pf);
        delete pBuffer1;
        printf("%ds  ", i);
        fclose(pf);
        std::thread t(play_thread);
        if (t.joinable())
        {
            t.join();
        }
    }
    waveInClose(hWaveIn);
}

void play_thread()
{
    FILE* thbgm;//�ļ�
    int             cnt;
    HWAVEOUT        hwo;
    WAVEHDR         wh;
    WAVEFORMATEX    wfx;
    HANDLE          wait;

    wfx.wFormatTag = WAVE_FORMAT_PCM;//���ò��������ĸ�ʽ
    wfx.nChannels = 1;//������Ƶ�ļ���ͨ������
    wfx.nSamplesPerSec = 8000;//����ÿ���������źͼ�¼ʱ������Ƶ��
    wfx.nAvgBytesPerSec = 16000;//���������ƽ�����ݴ�����,��λbyte/s�����ֵ���ڴ��������С�Ǻ����õ�
    wfx.nBlockAlign = 2;//���ֽ�Ϊ��λ���ÿ����
    wfx.wBitsPerSample = 16;
    wfx.cbSize = 0;//������Ϣ�Ĵ�С

    fopen_s(&thbgm, "test.pcm", "rb");
    while (true)
    {
        wait = CreateEvent(NULL, 0, 0, NULL);
        waveOutOpen(&hwo, WAVE_MAPPER, &wfx, (DWORD_PTR)wait, 0L, CALLBACK_EVENT);//��һ�������Ĳ�����Ƶ���װ�������лط�
        if (thbgm == nullptr)
        {
            waveOutClose(hwo);
            return;
        }
        cnt = fread(buf, sizeof(char), 1024, thbgm);//��ȡ�ļ�4M�����ݵ��ڴ������в��ţ�ͨ��������ֵ��޸ģ������߳̿ɱ��������Ƶ���ݵ�ʵʱ���䡣��Ȼ���ϣ��������������Ƶ�ļ���Ҳ��Ҫ��������΢��һ��
        if (cnt <= 0)
        {
            waveOutClose(hwo);
            fclose(thbgm);
            break;
        }
        int dolenght = 0;
        int playsize = 1024;
        while (cnt > 0) {//��һ������Ҫ�ر�ע�������ѭ������֮���ܻ�̫����ʱ��ȥ����ȡ����֮��Ĺ�������Ȼ��ÿ��ѭ���ļ�϶���С����ա�������
            //wh.lpData = buf + dolenght;
            //wh.dwBufferLength = playsize;
            //wh.dwFlags = 0L;
            //wh.dwLoops = 1L;
            //waveOutPrepareHeader(hwo, &wh, sizeof(WAVEHDR));//׼��һ���������ݿ����ڲ���
            //waveOutWrite(hwo, &wh, sizeof(WAVEHDR));//����Ƶý���в��ŵڶ�������whָ��������
            //WaitForSingleObject(wait, INFINITE);//�������hHandle�¼����ź�״̬����ĳһ�߳��е��øú���ʱ���߳���ʱ��������ڹ����INFINITE�����ڣ��߳����ȴ��Ķ����Ϊ���ź�״̬����ú�����������
            //std::cout << "play audio" << std::endl;

            dolenght = dolenght + playsize;
            cnt = cnt - playsize;
            std::cout << cnt << std::endl;
        }
        waveOutClose(hwo);
    }
    fclose(thbgm);
}

void CcPracticeRecordAndPlay(const char* msgIn, char* msgOut)
{
    FILE* file;
    fopen_s(&file, "test.pcm", "wb");
    fclose(file);
    std::thread t(record_thread);
    t.join();
    return;
}
