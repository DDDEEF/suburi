# vimで使える便利機能

### ◾️概要
vimで使える便利機能をまとめる

### ◾️tabで全部のファイルを開く
```
$ vim -p test.php test2.php
```

### ◾️作業前の状態をまるごと復元する
vimを開いている状態で
```
$ :mks
```
もしくは
```
$ :mks!
```

カレントフォルダに「Session.vim」が作られるので、以下で復元する
```
$ vim -S Session.vim
```
<参考URL><br>
https://qiita.com/Rasukarusan/items/969e6ad5956e82b9c343

### ◾️クリッポボードのテキストをvimエディタ上に貼り付ける方法
```
:set paste
```
このあと、貼り付けたいところに貼り付けると上手くいく
