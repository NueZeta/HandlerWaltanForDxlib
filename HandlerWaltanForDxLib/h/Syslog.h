#pragma once
#include "Utilities.h"


/**
* @author   Suzuki N
* @date     24/08/25
* @note     ���O���o�͂���N���X�̒�`
*/


/**
 * @enum	LogLevel	
 * @brief	Syslog���x��
 */
enum class LogLevel
{
    //! �f�o�b�O(0)
    debug,
    //! ���(1)
    info,
    //! �G���[(2)
    err,
};


/**
 * @struct	
 * @brief	
 */
typedef struct
{
    //! �N
    int Year;
    //! ��
    int Mon;
    //! ��
    int Day;
    //! ����
    int Hour;
    //! ��
    int Min;
    //! �b
    int Sec;
    //! �~���b
    long long millisec;
}TimeData;

/**
 * @struct	LogInfo
 * @brief	Syslog�̏o�͂ɕK�v�ȏ��
 */
typedef struct
{
    //! Syslog���x��
    LogLevel loglevel;
    //! ���O���b�Z�[�W
    std::string logMessage;
    //! �o�͎���
    TimeData timeData;

}LogInfo;


/**
 * @class   	Syslog
 * @brief   	�w��̃��O���o�͂���N���X
 * @detail      �ÓI�N���X�Ő݌v����
 */
class Syslog
{
private:

    /*     �����o�ϐ�     */

    /**
     * @brief		���O���b�Z�[�W�̃R���e�i
     * @History		24/08/25 �쐬(Suzuki N)
     */
    static std::vector<LogInfo> logInfoVec;


public:

    /*     ���\�b�h     */

    static void Message(const LogLevel _loglevel, const std::string& _logMessage);

private:

    /**
     * @brief       �R���X�g���N�^�͍폜
     * @author      Suzuki N
     * @date        24/08/25
     */
    Syslog() = delete;


    /**
     * @brief       ���O����ǉ�����
     * @author      Suzuki N
     * @date        24/08/25
     */
    static void AddLogInfoAsymc(const LogLevel _loglevel, const std::string& _logMessage);
};