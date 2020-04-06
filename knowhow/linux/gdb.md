# gdb 使い方

gdbをインストール
```
$ sudo yum install gdb
```

debuginfoをインストール
```
$ # cat /etc/yum.repos.d/CentOS-Debuginfo.repo | grep enable
→ enabled=0だったらenabled=1に書き換える
$ sudo yum install yum-utils
$ debuginfo-install glibc
```

debuginfoのインストールがうまく行かない場合、下記の2パターンを試す。
```
$ sudo yum install -y centos-release-scl
$ sudo yum update -y
$ sudo yum install -y devtoolset-7 

or

$ sudo yum install nss-softokn-debuginfo --nogpgcheck
```

デバッグ可能な方式でコンパイルする
```
$ gcc -g3 list2-18.c list2-17.c image.c bmp.c -o test
```
コマンドライン引数つきでプログラムを動かす方法
```
$ gdb program
$ (gdb) run foo bar
```

mainが記述されているファイル以外の関数でブレークポイントを作る方法
```
$ (gdb) break test.c:100
```

変数の中身を見る
```
$ (gdb) p 変数名
```

関数名でブレークポイントを作る
```
$ (gdb) break main
```
