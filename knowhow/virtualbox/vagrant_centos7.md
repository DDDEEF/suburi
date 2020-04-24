# VagrantでCentOS7環境の構築

### ◾️boxを新規追加
※環境の元になるboxと呼ばれるもの(仮想マシンのイメージファイル)を追加する。<br>
box一覧
https://app.vagrantup.com/centos/boxes/7

```
$ vagrant box add centos/7
```

### ◾️追加済みの確認
```
$ vagrant box list
```

### ◾️初期設定
```
$ mkdir centos7
$ cd centos7
$ vagrant init centos/7
```

### ◾️起動とログイン
```
$ vagrant up
$ vagrant ssh
```

### ◾️仮想マシンの停止
```
$ vagrant halt
```

### ◾️vagrantファイルに設定を追加
```
$ vim Vagrantfile
config.vm.network "private_network", ip: "192.168.10.2"
```

### ◾️現状確認
```
$ vagrant status
```

### ◾️再起動
```
$ vagrant reload
```
