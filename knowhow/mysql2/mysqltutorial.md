# MySQL2使い方

### ◾️MySQLのスタート
```
$ mysql service start
$ mysql -u root -p
```

### ◾️DBの作成
```
$ mysql> create database sampledb;
Query OK, 1 row affected (0.03 sec)
```

### ◾️DBを確認
```
$ mysql> show databases;
```

### ◾️DBに接続
```
$ mysql> use sampledb;
```

### ◾️DBを削除
```
$ mysql> drop database sampledb;
```

### ◾️作業用ユーザを作成
TBD


### ◾️テーブルを作成
```
$ mysql>
create table user (
id int auto_increment primary key,
username varchar(255),
email varchar(255),
password char(30)
);

create table テーブル名 (
フィールド名 データ型,
フィールド名 データ型,
フィールド名 データ型
);
```
### ◾️テーブルのカラムを確認
```
$ mysql> show tables;
```
### ◾️レコードを追加
```
$ mysql> insert into user(username,email,password) values('sato','sato@techacademy.jp','cccccc');
```

### ◾️テーブルの中身を確認
```
$ mysql> desc user;
```

### ◾️テーブルを削除
```
$ mysql> drop table  user;
```

### ◾️データの確認
```
$ mysql> select * from user;
```

### ◾️データを全削除
```
$ mysql> truncate table user;
```

### ◾️ホスト名の確認
```
$ mysql> show variables like 'hostname';
```

### ◾️初期設定後ログインできない問題
・エラー内容<br>
ERROR 1045 (28000): Access denied for user 'root'@'localhost' (using password: NO)

・対応内容<br>
下記コマンドで初期パスワードを探して入力
```
下記コマンドで表示される初期設定のパスワードを入力
$ cat /var/log/mysqld.log | grep 'password is generated'
```

・その後、パスワードが初期設定のままだと怒られる<br>
ERROR 1820 (HY000): You must reset your password using ALTER USER statement before executing this statement.<br>
```
$ mysql> ALTER USER 'root'@'localhost' IDENTIFIED BY 'Abcdef01.';
```
・パスワードのポリシーに引っかかる時は上記の例を参考<br>
ERROR 1819 (HY000): Your password does not satisfy the current policy requirements
