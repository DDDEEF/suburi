typedef struct State{
  const struct State *(* const stop)(const struct State *pThis);
  const struct State *(* const playOrPause)(const struct State *This);
} State;

void initialize()
void onStop();
void onPlayOrPause();

static const State *pCurrentState;

static const State *ignore(const State *pThis);
static const State *startPlay(const State *pThis);
static const State *stopPlay(const State *pThis);
static const State *pausePlay(const State *pThis);
static const State *resumePlay(const State *pThis);

const State IDLE = {
  ignore,       // [Play/Pause]ボタン押下時の動作
  startPlay     // [Stop]ボタン押下時の動作
};

const State PLAY = {
  stopPlay,     // [Play/Pause]ボタン押下時の動作
  pausePlay     // [Stop]ボタン押下時の動作
};

const State PAUSE = {
  stopPlay,     // [Play/Pause]ボタン押下時の動作
  resumePlay    // [Stop]ボタン押下時の動作
};

void initialize(){
  pCurrentState = &IDLE;
}

void onStop(){
  pCurrentState = pCurrentState->stop(pCurrentState);
}

void onPlayOrPause(){
  pCurrentState = pCurrentState->playOrPause(pCurrentState);
}

static const State *ignore(const State *pThis){
  return pCurrentState;
}

static const State *stopPlay(const State *pThis){
  return &IDLE;
}

static const State *pausePlay(const State *pThis){
  return &PAUSE;
}

static const State *resumePlay(const State *pThis){
  return &PLAY;
}

static const State *startPlay(const State *pThis){
  return &PLAY;
}

initialize();
onPlayOrPause();        //再生開始
onPlayOrPause();        //一時停止
onPlayOrPause();        //再生再開
onStop();               //停止
