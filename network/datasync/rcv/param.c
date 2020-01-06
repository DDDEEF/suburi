#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>
#include <pthread.h>
#include "sock.h"
#include "token.h"
#include "log.h"
#include "param.h"

/* ログ出力関数 */
void ParamLogOut(){
  int i;
  Syslog(LOG_INFO,"ParamLogOut:VERSION_STRING=%s\n", VERSION_STRING);
  Syslog(LOG_INFO,"ParamLogOut:TargetFolderCnt=%d\n", Param.TargetFolderCnt);
  for(i = 0; i < Param.TargetFolderCnt; i++){
    Syslog(LOG_INFO, "ParamLogOut:TargetFolder%d=%s, %s\n", i, Param.TargetFolder[i].name, Param.TargetFolder[i].path);
  }
  Syslog(LOG_INFO,"ParamLogOut:Port=%s\n", Param.Port);
  Syslog(LOG_INFO,"ParamLogOut:RecvTimeout=%d\n", Param.RecvTimeout);
  Syslog(LOG_INFO,"ParamLogOut:UseDigest=%d\n", Param.UseDigest);
  Syslog(LOG_INFO,"ParamLogOut:LogPath=%s\n", Param.LogPath);
  Syslog(LOG_INFO,"ParamLogOut:LogLevel=%d\n", Param.LogLevel);
  Syslog(LOG_INFO,"ParamLogOut:StderrOut=%d\n", Param.StderrOut);
  Syslog(LOG_INFO,"ParamLogOut:VersionFilePath=%s\n", Param.VersionFilePath);
  Syslog(LOG_INFO,"ParamLogOut:WorkFilePath=%s\n", Param.WorkFilePath);
  Syslog(LOG_INFO,"ParamLogOut:DeleteFlag=%d\n", Param.DeleteFlag);
}

/* パラメータファイル読み込み関数 */
int ReadParam(char *filename){
  FILF *fp;
  char buf[1024];
  char *ptr;
  int no;
  int i;

  if((fp = fopen(filename, "r")) == NULL){
    fprintf(stderr, "cannot read %s\n", filename);
    return(-1);
  }

  Param.TargetFolder = NULL;
  Param.TargetFolderCnt = 0;

  while(1){
    if(fgets(buf, sizeof(buf), fp) == NULL){
      break;
    }
    if(buf[0] == '#'){
      continue;
    }
    if((ptr = strtok(buf, "=")) == NULL){
      continue;
    }
    if(strcmp(buf, "TargetFolderCnt") == 0){
      if((ptr = strtok(NULL, "\r\n")) != NULL){
        Param.TargetFolderCnt = atoi(ptr);
        Param.TargetFolder = (FOLDER *)calloc(Param.TargetFolderCnt, sizeof(FOLDER));
      }
    }else if(strncmp(buf, "TargetFolder", strlen("TargetFolder")) == 0){
      no = atoi(&buf[strlen("TargetFolder")]);
      if(no < 0){
        Syslog(LOG_ERR, "ReadPara:TargetFolder:%d<0\n", no);
        fclose(fp);
        return(-1);
      }else if(no >= Param.TargetFolderCnt){
        Syslog(LOG_ERR, "ReadParam:TargetFolder:%d>=TargetFolderCnt(%d)\n", no, Param.TargetFolderCnt);
        fclose(fp);
        return(-1);
      }else{
        if((ptr = strtok(NULL, ",")) != NULL){
          Param.TargetFolder[no].name = strdup(ptr);
          if((ptr = strtok(NULL, "\r\n")) != NULL){
            Param.TargetFolder[no].path = strdup(ptr);
          }else{
            Syslog(LOG_ERR, "ReadParam:TargetFolder:%d:%s:no path\n", no, Param.TargetFolder[no].name);
            free(Param.TargetFolder[no].name);
            Param.TargetFolder[no].name = NULL;
            fclose(fp);
            return(-1);
          }
        }else{
          Syslog(LOG_ERR, "ReadParam:TargetFolder%d:no ','\n", no);
          fclose(fp);
          return(-1);
        }
      }
    }else if(strcmp(buf, "Port") == 0){
      if((ptr = strtok(NULL, "\r\n")) != NULL){
        Param.Port = strdup(ptr);
      }
    }else if(strcmp(buf, "RecvTimeout") == 0){
      if((ptr = strtok(NULL, "\r\n")) != NULL){
        Param.RecvTimeout = atoi(ptr);
      }
    }else if(strcmp(buf, "UseDigest") == 0){
      if((ptr = strtok(NULL, "\r\n")) != NULL){
        Param.UseDigest = atoi(ptr);
      }
    }else if(strcmp(buf, "LogPath") == 0){
      if((ptr = strtok(NULL, "\r\n")) != NULL){
        Param.LogPath = strdup(ptr);
      }
    }else if(strcmp(buf, "LogLevel") == 0){
      if((ptr = strtok(NULL, "\r\n")) != NULL){
        Param.LogLevle = GetLogLevelValue(ptr);
      }
    }else if(strcmp(buf, "SlaveRecvTimeout") == 0){
      if((ptr = strtok(NULL, "\r\n")) != NULL){
        Param.LogLevel = atoi(ptr);
        if(Param.LogLevel == -1){
          Param.LogLevel = LOG_INFO;
        }
      }
    }else if(strcmp(buf, "StderrOut") == 0){
      if((ptr = strtok(NULL, "\r\n")) != NULL){
        Param.StderrOut = atoi(ptr);
      }
    }else if(strcmp(buf, "VersionFilePath") == 0){
      if((ptr = strtok(NULL, "\r\n")) != NULL){
        Param.VersionFilePath = strdup(ptr);
      }
    }else if(strcmp(buf, "WorkFilePath") == 0){
      if((ptr = strtok(NULL, "\r\n")) != NULL){
        Param.WorkFilePath = strdup(ptr);
      }
    }else if(strcmp(buf, "DeleteFlag") == 0){
      if((ptr = strtok(NULL, "\r\n")) != NULL){
        Param.DeleteFlag = atoi(ptr);
      }
    }
  }

  fclose(fp);

  for(i = 0; i < Param.TargetFolderCnt; i++){
    if(Param.TargetFolder[i].name == NULL || Param.TargetFolder[i].path == NULL){
      Syslog(LOG_ERR, "ReadParam:TargetFolder%d:no data\n", no);
      return(-1);
    }
  }

  return(0);
}
