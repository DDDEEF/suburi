# gtagsをvimで使えるようにする方法

### global-x.x.x.tar.gzをダウンロード
```
https://www.gnu.org/software/global/ 
```

### tmpファイルにダウンロードしたファイルを移動して、順次下記コマンドを入力
```
$ cd tmp
$ sudo apt-get updata
$ sudo apt install build-essential 
$ ./configure --disable-gtagscscope
$ make
$ mkdir -p ~/bin 
$ cp global/global ~/bin 
$ cp gtags/gtags ~/bin 
$ mkdir -p ~/.vim/plugin 
$ cp gtags.vim ~/.vim/plugin 
```

### 環境変数の設定
```
$ ~/bin/gtags //gtagsでタグ生成ができるか試す
$ vim .bash_profile
export PATH="$PATH:/home/username/bin"  //環境変数に追加
$ source ~/.bash_profile 
$ printenv //環境変数を表示して確認 
```
### Gtags小技
#### grep対象を絞りたい時
```
$ cd project
$ cd project/module
$ vim .
$ :Gtags -g -l write // moduleディレクトリに潜って、vimを起動し、writeを検索
```
参考
https://www.tamacom.com/handbook/column.html
