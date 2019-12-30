#include <syslog.h>

int main(){
  /* openlog()せずに使ってみる */
  syslog(LOG_USER|LOG_DEBUG, "openlog()せずにsyslogのテスト:DEBUG");

  /* syslogの使用開始 */
  openlog("syslogTest", LOG_PID, LOG_USER|LOG_DEBUG);

  /* syslogに出力 */
  syslog(LOG_USER|LOG_EMERG, "syslogのテスト:EMERG");
  syslog(LOG_USER|LOG_ALERT, "syslogのテスト:ALERT");
  syslog(LOG_USER|LOG_CRIT, "syslogのテスト:CRIT");
  syslog(LOG_USER|LOG_ERR, "syslogのテスト:ERR");
  syslog(LOG_USER|LOG_WARNING, "syslogのテスト:WARNING");
  syslog(LOG_USER|LOG_NOTICE, "syslogのテスト:NOTICE");
  syslog(LOG_USER|LOG_INFO, "syslogのテスト:INFO");
  syslog(LOG_USER|LOG_DEBUG, "syslogのテスト:DEBUG");

  /* マスクをしてみる */
  setlogmask(LOG_MASK(LOG_EMERG)|LOG_MASK(LOG_NOTICE));

  syslog(LOG_USER|LOG_EMERG, "syslogのマスクのテスト:EMERG");
  syslog(LOG_USER|LOG_ALERT, "syslogのマスクのテスト:ALERT");
  syslog(LOG_USER|LOG_CRIT, "syslogのマスクのテスト:CRIT");
  syslog(LOG_USER|LOG_ERR, "syslogのマスクのテスト:ERR");
  syslog(LOG_USER|LOG_WARNING, "syslogのマスクのテスト:WARNING");
  syslog(LOG_USER|LOG_NOTICE, "syslogのマスクのテスト:NOTICE");
  syslog(LOG_USER|LOG_INFO, "syslogのマスクのテスト:INFO");
  syslog(LOG_USER|LOG_DEBUG, "syslogのマスクのテスト:DEBUG");

  /* クローズ */
  closelog();

  return(0);
}
