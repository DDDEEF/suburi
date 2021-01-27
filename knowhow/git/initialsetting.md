# 開発環境が変わった時のgitのInitialSetting

## ssh公開鍵を作成
*Enter passphraseではエンター3連打*
```
$ ssh-keygen
```
```
Enter file in which to save the key (/home/vagrant/.ssh/id_rsa):
Enter passphrase (empty for no passphrase):
Enter same passphrase again:
```

## 公開鍵を確認
*ssh-rsaから始まるデタラメな文字列が公開鍵そのものである。
こちらを丸ごとコピーする。*
```
$ cat ~/.ssh/id_rsa.pub
```

## GitHubに公開鍵を登録
*GitHubにアクセス！！*
setting->SSH and GPS keys

## git configにユーザーを登録

```
$ git config --global user.name GitHubに登録したユーザー名
$ git config --global user.email GitHubに登録したメールアドレス
```

*登録できているか確認する*
```
$ git config --global --list
```

### ローカルで公開するプロジェクトのルートディレクトリでコマンド打つ
```
$ git remote add origin git@github.com:foo/bar.git
```

### git管理対象外ファイルの指定
```
$ vim .gitignore
```

### GitHubのremote先を設定する
```
$ git remote add origin git@github.com:foo/bar.git
```
