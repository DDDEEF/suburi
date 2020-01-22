# コードリーディングルールと手法・C言語

## ルール
* ヘッダーファイルは必要になった時に初めて読む
* 変数と構造体の宣言は必要になった時に初めて読む

## 手法
* vim + gtags の二つを使って読む
* コンパイルスイッチのプリプロセッサ処理の未到達部分についてはコンパイルで切り捨てる

## 手法詳細

### gtags
*1. gtagsをvimで使えるようにする*
```
$ brew upgrade python@2
$ sudo pip install Pygments
$ brew install global
$ mkdir -p ~/.vim/plugin/
$ cp /usr/local/share/gtags/gtags.vim ~/.vim/plugin/gtags.vim
```

*2. .vimrcに設定を追加する*
```
map <C-g> :Gtags
map <C-h> :Gtags -f %<CR>
map <C-j> :GtagsCursor<CR>
map <C-n> :cn<CR>
map <C-p> :cp<CR>
```

*3. リーディング対象のプロジェクト上でコマンドを打つ*
```
$ gtags -v
```

*4. キーバインドの使い方*
```
$ vim .  /* vimを開く */
```
```
/main    読みたいソースファイル上に飛ぶ
Ctrl＋h   ソース上の情報がGNU GLOBALの領域に表示される
Ctrl＋n   GNU GLOBALの領域で下に移動
Ctrl＋p   GNU GLOBALの領域で上に移動
Ctrl＋j   vim領域の気になった関数の定義先に飛ぶ(別ファイルでも)
Ctrl＋o   ジャンプ直前の場所に戻る
Ctrl＋i   直前の表示に進む
Ctrl＋g   grep -g 検索ワード
```

参考元
http://blog.matsumoto-r.jp/?p=2369

### vim tab
```
t ファイル名  tabで新規に開く
<           前のtabへ
>           次のtabへ
:tab sp     tabの複製
```
