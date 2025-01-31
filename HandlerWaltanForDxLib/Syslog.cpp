#include "h/Syslog.h"


/**
* @author   NZ
* @date     24/07/29
* @note		HWComponentの実装ファイル
*/


// 静的メンバ変数の初期化
std::vector<LogInfo> Syslog::logInfoVec;
std::mutex Syslog::mtx;


#pragma region privateメソッド



void Syslog::AddLogInfoAsymc(const LogLevel _loglevel, const std::string& _logMessage)
{
    // スレッドセーフで動かす
    std::lock_guard <std::mutex> lock(mtx);

    //! ログに必要な情報
    LogInfo logInfo;

    // ログ情報を設定
    logInfo.loglevel = _loglevel;
    logInfo.logMessage = _logMessage;

    // 現在時刻を取得
    auto now = std::chrono::system_clock::now();
    // 時刻を秒に変換
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    // std::tm構造体を準備
    std::tm now_tm = {};
    // 現在時刻をstd::tmに変換（安全な方法）
    localtime_s(&now_tm, &now_time_t);
    // ミリ秒を取得
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto value = now_ms.time_since_epoch();

    logInfo.timeData.Year = now_tm.tm_year + 1900;
    logInfo.timeData.Mon = now_tm.tm_mon + 1;
    logInfo.timeData.Day = now_tm.tm_mday;
    logInfo.timeData.Hour = now_tm.tm_hour;
    logInfo.timeData.Min = now_tm.tm_min;
    logInfo.timeData.Sec = now_tm.tm_sec;
    logInfo.timeData.millisec = value.count() % 1000;

    // 書き込むデータを追加する
    logInfoVec.push_back(logInfo);
}


#pragma endregion

#pragma region publicメソッド


void Syslog::Message(const LogLevel _loglevel, const std::string& _logMessage)
{


}


#pragma endregion
