typedef enum{
  EV_STOP,
  EV_PLAY_PAUSE
} EventCode;

typedef enum{
  ST_IDLE,
  ST_PLAY,
  ST_PAUSE
} State;

void initialize(){
  state = ST_IDLE;
}

int state = 0;

void onEvent(EventCode ec){
  switch(state){
    case ST_IDLE:
      if(ec == EV_PLAY_PAUSE){
        startPlayer();
      }
      break;
    case ST_PLAY:
      switch(ec){
        case EV_STOP:
          stopPlayer();
          break;
        case EV_PLAY_PAUSE:
          pausePlayer();
          break;
        default:
          break;
      }
    case ST_PAUSE:
      switch(ec){
        case EV_STOP:
          stopPlayer();
          break;
        case EV_PLAY_PAUSE:
          resumePlayer();
          break;
        default:
          break;
      }
    default:
      break;
  }
}

void stopPlayer(){
  state = ST_IDLE;
}

void pausePlayer(){
  state = ST_PAUSE;
}

void resumePlayer(){
  state = ST_PLAY;
}

void startPlayer(){
  state = ST_PLAY;
}
