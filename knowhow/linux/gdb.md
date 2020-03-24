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
