#include "h/Syslog.h"


/**
* @author   Suzuki N
* @date     24/07/29
* @note		HWComponent�̎����t�@�C��
*/


// �ÓI�����o�ϐ��̏�����
std::vector<LogInfo> Syslog::logInfoVec;
std::mutex Syslog::mtx;


#pragma region private���\�b�h



void Syslog::AddLogInfoAsymc(const LogLevel _loglevel, const std::string& _logMessage)
{
    // �X���b�h�Z�[�t�œ�����
    std::lock_guard <std::mutex> lock(mtx);

    //! ���O�ɕK�v�ȏ��
    LogInfo logInfo;

    // ���O����ݒ�
    logInfo.loglevel = _loglevel;
    logInfo.logMessage = _logMessage;

    // ���ݎ������擾
    auto now = std::chrono::system_clock::now();
    // ������b�ɕϊ�
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    // std::tm�\���̂�����
    std::tm now_tm = {};
    // ���ݎ�����std::tm�ɕϊ��i���S�ȕ��@�j
    localtime_s(&now_tm, &now_time_t);
    // �~���b���擾
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto value = now_ms.time_since_epoch();

    logInfo.timeData.Year = now_tm.tm_year + 1900;
    logInfo.timeData.Mon = now_tm.tm_mon + 1;
    logInfo.timeData.Day = now_tm.tm_mday;
    logInfo.timeData.Hour = now_tm.tm_hour;
    logInfo.timeData.Min = now_tm.tm_min;
    logInfo.timeData.Sec = now_tm.tm_sec;
    logInfo.timeData.millisec = value.count() % 1000;

    // �������ރf�[�^��ǉ�����
    logInfoVec.push_back(logInfo);
}


#pragma endregion

#pragma region public���\�b�h


void Syslog::Message(const LogLevel _loglevel, const std::string& _logMessage)
{


}


#pragma endregion
