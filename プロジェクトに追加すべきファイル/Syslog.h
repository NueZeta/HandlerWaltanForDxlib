#pragma once
#include "Utilities.h"


/**
* @author   Suzuki N
* @date     24/08/25
* @note     ログを出力するクラスの定義
*/


/**
 * @enum	LogLevel	
 * @brief	Syslogレベル
 */
enum class LogLevel
{
    //! デバッグ(0)
    debug,
    //! 情報(1)
    info,
    //! エラー(2)
    err,
};


/**
 * @struct	
 * @brief	
 */
typedef struct
{
    //! 年
    int Year;
    //! 月
    int Mon;
    //! 日
    int Day;
    //! 時間
    int Hour;
    //! 分
    int Min;
    //! 秒
    int Sec;
    //! ミリ秒
    long long millisec;
}TimeData;

/**
 * @struct	LogInfo
 * @brief	Syslogの出力に必要な情報
 */
typedef struct
{
    //! Syslogレベル
    LogLevel loglevel;
    //! ログメッセージ
    std::string logMessage;
    //! 出力時刻
    TimeData timeData;

}LogInfo;


/**
 * @class  	Syslog
 * @brief  	指定のログを出力するクラス
 * @detail  静的クラスで設計する
 */
class Syslog final
{
private:

    /*     メンバ変数     */

    /**
     * @brief		ログメッセージのコンテナ
     * @History		24/08/25 作成(Suzuki N)
     */
    static std::vector<LogInfo> logInfoVec;

    /**
     * @brief		スレッドセーフでテキストファイルに書き込むため
     * @History		24/09/11 作成(Suzuki N)
     */
    static std::mutex mtx;

    /**
     * @brief		スレッドセーフでテキストファイルに書き込むため
     * @History		24/09/11 作成(Suzuki N)
     */
    std::thread syslogThread;

public:

    /*     メソッド     */

    static void Message(const LogLevel _loglevel, const std::string& _logMessage);

private:

    /**
     * @brief       コンストラクタは削除
     * @author      Suzuki N
     * @date        24/08/25
     */
    Syslog() = delete;


    /**
     * @brief       ログ情報を追加する
     * @author      Suzuki N
     * @date        24/08/25
     */
    static void AddLogInfoAsymc(const LogLevel _loglevel, const std::string& _logMessage);
};