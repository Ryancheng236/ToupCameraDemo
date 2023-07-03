#ifndef CTOUPCAMERA_H
#define CTOUPCAMERA_H

#include <toupcam.h>
#include <QString>
#include "ccamera.h"
#include "qdebug.h"


class CToupCamera : public CCamera
{

public:
//    static CToupCamera& getInstance();
    CToupCamera();
    ~CToupCamera();
    bool isOpened() const override;
    int open() override;
    int open(int index) override;
    void close() override;
    bool read(cv::Mat& frame) override;
    void getCameraList(std::vector<std::string> &camera_list) override;
    void saveImage() override;
    void setAutoExpo(int state) override;
    void setExpoTime(int value) override;
    void setExpoTarget(int value) override;
    void setExpoGain(int value) override;
    void getContext(Context& ctx) override;
    void getResolution(std::vector<std::string>& res) override;
private:
//    CToupCamera();
//    CToupCamera(const CToupCamera&) = delete;
//    CToupCamera& operator=(const CToupCamera&) = delete;
//    ~CToupCamera() = default;

    int m_index;
    HToupcam        m_hcam =nullptr;
    uchar*          m_pData = nullptr;
    int             m_res;
    unsigned        m_imgWidth;
    unsigned        m_imgHeight;
    ToupcamFrameInfoV2* pInfo;
    ToupcamDeviceV2 m_arr[TOUPCAM_MAX]; //所有相机
    ToupcamDeviceV2  m_curDev;
    unsigned toupCamCount;
private:
    void evtCallback(unsigned nEvent);
    static void __stdcall eventCallBack(unsigned nEvent, void *pCallbackCtx);
};

#endif // CTOUPCAMERA_H
