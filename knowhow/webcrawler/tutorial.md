# CentOS7+RubyでWebクローリング

### ◾️概要
Webクローリングの環境構築<br>

### ◾️環境構築
- CentOS7
- Ruby
- MySQL2
- Selenium
- Chromeヘッドレスブラウザ

### ◾️MySQL2導入
#### ・必要な物をインストール
"mysql80-community-release-el7-3.noarch.rpm"は下記のリリース情報を参考にして下さい。
https://dev.mysql.com/downloads/repo/yum/

```
$ sudo yum install -y mysql-devel
$ sudo yum -y install ruby-devel
$ sudo yum localinstallhttp://dev.mysql.com/get/mysql80-community-release-el7-3.noarch.rpm
```
#### ・設定を確認
```
$ cd /etc/yum.repos.d/
$ ls
```
下のリポジトリができていれば成功<br>
mysql-community-source.repo  mysql-community.repo<br>

リポジトリの情報を確認できる
```
$ yum info mysql-community-server
```

#### ・MySQLをインストール
```
$ sudo yum install -y mysql-community-server
```

#### ・MySQLが入っているか確認
```
$ mysqld --version
```

#### ・その他
起動
```
$ systemctl start mysqld
```
停止
```
$ systemctl stop mysqld
```
Rubyインストール後にGemをインストール
```
$ gem install mysql2
```
<br><br>

### ◾️Ruby導入
#### ・rbenv導入
```
$ git clone https://github.com/sstephenson/rbenv.git ~/.rbenv
```
rbenv設定
「\~/.rbenv/bin」を環境変数に追加するための記述を「~/.bash_profile」に追記

```
$ echo 'export PATH="$HOME/.rbenv/bin:$PATH"' >> ~/.bash_profile
```
rbenvを初期化する記述を「~/.bash_profile」に追記
```
$ echo 'eval "$(rbenv init -)"' >> ~/.bash_profile
```
~/.bash_profileを再読み込み
```
$ exec $SHELL -l
```

rbenv実行のためのプラグイン
```
$ git clone https://github.com/sstephenson/ruby-build.git ~/.rbenv/plugins/ruby-build
$ sudo .rbenv/plugins/ruby-build/install.sh
```

#### ・Ruby導入
Rubyのインストールに必要なもの
```
$ sudo yum install -y openssl-devel readline-devel zlib-devel
```

Rubyのインストール
```
$ rbenv install -v 2.6.2
```

Linux全体で有効にするRubyを設定
```
$ rbenv global 2.6.2
```
カレントディレクトリで有効にするRubyを設定
```
$ rbenv local 2.6.2
```
有効なRubyのバージョンを確認
```
$ ruby -v
```

#### ・Gemを管理するためのBundler
```
$ gem install bundler
```

プロジェクトのルートフォルダでGemをセットアップ → Gemfileが生成される → Gemfileを編集
```
$ bundle init
```

Gemfile
```
# frozen_string_literal: true

source "https://rubygems.org"

git_source(:github) {|repo_name| "https://github.com/#{repo_name}" }

# gem "rails"

gem 'mysql2'
gem 'selenium-webdriver'
gem 'nokogiri'

```

Gemのインストール
```
$ bundle install
```

### ・RubyでMySQL2に繋いで処理を進めようとするとエラーが出る時
#### エラー内容
Authentication plugin 'caching_sha2_password' cannot be loaded: /usr/lib64/mysql/plugin/caching_sha2_password.so: cannot open shared object file: No such file or directory (Mysql2::Error)
#### 対策
MySQL8.0.4以降 のログイン認証方式はcaching_sha2_password がデフォルト<br>
しかしRubyの接続ライブラリがcaching_sha2_passwordに未対応のため、接続不可
認証方式を mysql_native_password に戻す必要がある

#### 手順
・既存ユーザの認証方法を確認
```
$ mysql > SELECT user, host, plugin FROM mysql.user;
```
・rootユーザの認証方法を変更
```
$ mysql > ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'P@ssw0rd';
```
・新規ユーザ作成時の認証方法を変更<br>
/etc/my.cnf に下記を追記
```
[mysqld]
default_authentication_plugin=mysql_native_password
```

### ◾️Chrome導入
#### 事前にインストール
```
$ sudo yum install -y libX11 GConf2 fontconfig
```

#### 事前設定
```
$ cd etc/yum.repo.d
$ vim google-chrome.repo
```
vimで新たに"google-chrome.repo"を作成したら下記を書き込む
```
[google-chrome]
name=google-chrome
baseurl=http://dl.google.com/linux/chrome/rpm/stable/$basearch
enabled=1
gpgcheck=1
gpgkey=https://dl-ssl.google.com/linux/linux_signing_key.pub
```

#### インストール
```
$ yum install google-chrome-stable
```

#### chromeのバージョンの確認
インストールしたバージョンとドライバを合わせる必要があるので、必ず確認すること
```
$ google-chrome-stable -version
```

#### 起動確認
```
$ google-chrome --disable-setuid-sandbox --no-sandbox --headless --disable-gpu --dump-dom https://www.chromestatus.com/
```

### ◾️chromedriver導入
#### chromeのバージョンに合わせてドライバを導入
リリースバージョンについては下記を見ること
https://sites.google.com/a/chromium.org/chromedriver/downloads<br>
今回は"81.0.4044.69"を導入する

```
$ sudo wget https://chromedriver.storage.googleapis.com/81.0.4044.69/chromedriver_linux64.zip
```

#### インストールと設定
```
$ sudo unzip chromedriver_linux64.zip
$ sudo mv chromedriver /usr/local/bin/
$ sudo chown root:root /usr/local/bin/chromedriver
```

#### バージョンの確認
```
$ chromedriver -v
```
ドライバのバージョンが完全に一致するものがないときはできるだけリリースナンバーの近いものを持ってくる。

### ◾️seleniumのテスト
```
require 'selenium-webdriver'

options = Selenium::WebDriver::Chrome::Options.new
options.add_argument('--headless')
begin
  driver = Selenium::WebDriver.for :chrome, options: options
  driver.get "https://qiita.com/"
  sleep 5
  driver.save_screenshot "#{Time.now.to_i}.png"
ensure
  driver.close unless driver.nil?
  driver.quit unless driver.nil?
end
```
これで動けばとりあえずOK
