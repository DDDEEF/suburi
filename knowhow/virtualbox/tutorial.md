# VirtualBoxでLinux環境を作る方法

##  VirtualBoxをインストール

*下記のリンクから必要なOSを引っ張ってくる*

https://www.virtualbox.org/wiki/Download_Old_Builds_6_0

## Vagrantをインストール
*VirtualBoxを簡単に使うことができるようにするツールのVagrantを下記から引っ張ってくる*

https://www.vagrantup.com/downloads.html

## 仮想マシンを立ち上げるまで
### 作業ディレクトリを作成する
```
$ mkdir vagrant
```
### 仮想マシンを作るフォルダを作成する
```
$ cd vagrant
$ mkdir CentOS
```

### 仮想マシン設定用のVagrantfileを作る
```
$ cd CentOS
$ vagrant init bento/centos-6.8
```

### 仮想マシンのIPアドレスを設定する
```
$ sed -i '' -e 's/# config.vm.network "private_network", ip: "192.168.33.10"/config.vm.network "private_network", ip: "192.168.33.10"/' Vagrantfile
```

### 仮想マシンを起動する（少し時間かかります）
```
$ vagrant up
```
### 仮想マシンの状態を確認する
```
$ vagrant status
```

### 仮想マシンにssh接続する
```
$ vagrant ssh
```

## 開発環境の構築をする。
### gccコンパイラをインストール
```
$ sudo yum install gcc
```

### autoconfをインストール
```
$ sudo yum install autoconf
```

### wgetをインストール
```
$ sudo yum install wget
```

### gitをインストール
```
$ sudo yum install git
```

### vimをインストール
```
$ sudo yum install vim
```

### gdbをインストール
```
$ sudo yum install gdb
```
### ncurses-develをインストール
```
$ sudo yum install ncurses-devel.x86_64 
```

### vimのためのctagsをインストール
```
$ sudo yum install ctags
$ ctags -R
```

### vimのためのgtagsをインストール
```
$ wget http://tamacom.com/global/global-6.5.4.tar.gz
$ tar xzf global-6.5.4.tar.gz
$ cd global-6.5.4 ;pwd
$ ./configure 
$ make
$ sudo make install
$ mkdir -p ~/.vim/plugin
$ cp -ip /usr/local/share/gtags/gtags.vim ~/.vim/plugin
$ gtags
```
