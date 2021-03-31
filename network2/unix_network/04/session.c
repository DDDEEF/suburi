#include <sys/types.h>
#include <curses.h>
#include <signal.h>

#define BUF_LEN 20
#define MIN_X 1
#define MIN_Y 1
#define MAX_X 60
#define MAX_Y 20

/* 移動キーの割当 */
#define NORTH 'k'
#define SOUTH 'j'
#define EAST  'l'
#define WEST  'h'
#define QUIT  'q'

/* プライベート変数 */
static int session_soc;
static fd_set mask;
static int width;
static char my_char, peer_char;

typedef struct {
  int x, y;
  char look;
} PLAYER;

static PLAYER me, peer;

static char buf[BUF_LEN];

static WINDOW *win;

/* session モジュールにプライベートな関数 */
static void hide(PLAYER *who);
static void show(PLAYER *who);
static int update(PLAYER *who, int c);
static int interpret(PLAYER *who);
static void die();

/* sessionモジュールの初期化 */
/* soc ソケットのディスクリプタ */
/* 自分の表示用の文字 */
/* 自分の初期x座標 */
/* 自分の初期y座標 */
/* 相手の表示用の文字 */
/* 相手の初期x座標 */
/* 相手の初期y座標 */
void session_init(int soc, char mc, int mx, int my, char pc, int px, int py)
{
  session_soc = soc;
  width = soc + 1;
  FD_ZERO(&mask);
  FD_SET(0, &mask);
  FD_SET(session_soc, &mask);
  me.look = mc;
  peer.look = pc;

  me.x = mx; me.y = my;
  peer.x = px; peer.y = py;

  /* cursesの初期化 */
  initscr();
  signal(SIGINT, die);

  /* ウィンドウ枠 */
  win = newwin(MAX_Y + 2, MAX_Y + 2, 0, 0);
  box(win, ':', '-');

  /* 端末設定 */
  cbreak();
  noecho();
}

/* sessionメインループ */
void session_loop()
{
  int c;
  int flag;
  fd_set readOk;

  /* 自分の姿の表示 */
  show(&me);

  /* ループ継続フラッグの初期化 */
  flag = 1;
  
  /* ループ */
  while(1){
    /* selectの前に前回readOkを初期化する */
    readOk = mask;
    select(width, (fd_set*)&readOk, NULL, NULL, NULL);

    /* キーボードからの入力ありか？ */
    if(FD_ISSET(0, &readOk)){
      c = getchar();
      hide(&me);
      flag = update(&me, c);
      show(&me);
      write(session_soc, buf, BUF_LEN);
      if(flag == 0) break;
    }

    /* ソケットにデータあり？ */
    if(FD_ISSET(session_soc, &readOk)){
      read(session_soc, buf, BUF_LEN);
      hide(&peer);
      flag = interpret(&peer);
      show(&peer);
      if(flag == 0) break;
    }
  }
  /* 端末属性を復旧しｓて終わる */
  die();
}

static void show(PLAYER *who)
{
  /* who 誰を表示するか */
  wmove(win, who->y, who->x);
  waddch(win, who->look);
  wmove(win, who->y, who->x);
  wrefresh(win);
}

static void hide(PLAYER *who)
{
  /* who 誰の姿を消すか */
  wmove(win, who->y, who->x);
  waddch(win, ' ');
}

static int update(PLAYER *who, int c)
{
  /* who 誰を */
  /* c どちらへ動かすか */

  switch(c){
  case WEST:
    if(who->x > MIN_X) who->x--;
    break;
  case SOUTH:
    if(who->y < MAX_Y) who->y++;
    break;
  case NORTH:
    if(who->y > MIN_X) who->y--;
    break;
  case EAST:
    if(who->x < MAX_X) who->x++;
    break;
  case QUIT:
    buf[0] = QUIT;
    return 0;
  defalut:
    break;
  }

  /* 更新された位置データを送信用文字列に変換する */
  sprintf(buf, "%d %d\n", who->x, who->y);
  return 1;
}

static int interpret(PLAYER *who)
{
  /* who解釈後のデータの格納先を指す */

  /* もし相手が終了を希望したら */
  if(buf[0] == 'q'){
    return 0;
  }

  /* 受信文字列から位置データに変換する */
  sscanf(buf, "%d %d", &who->x, &who->y);
  return 1;
}

static void die()
{
  endwin();
  exit(0);
}
