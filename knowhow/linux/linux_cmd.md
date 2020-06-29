# Linuxでよく使うコマンド一覧
## ファイルの文字コード変換
$ nkf --version     //version確認 <br>
$ brew install nkf  //インストール <br>
$ nkf -g **  //ファイルの文字コードを確認 <br>
$ nkf -w --overwrite \*\*/\*\*  //ファイルをUTF-8に変換(ディレクトリを上手く避けながら使う) <br>

参考情報<br>
https://qiita.com/BEMU/items/9b16414c9fe354017838


## バイナリファイルを表示する方法
```
$ hexdump -C picture.png
```
## リンク以下にあるファイルを再帰的に取得する方法
```
$ wget --http-user=aaa --http-passwd=bbb -H -r -np -R zip http://aiueo.co.jp/share/aaa
```

## ディレクトリ以下のファイルを再帰的に削除する方法
```
$ find ./ -type f -name "*.html" -delete
```

## ディレクトリ以下のファイルをコピーする方法
```
$ cp -r コピー元ディレクトリ コピー先ディレクトリ
```

## ファイルの名前を変更する方法
```
$ mv 元ファイル名 新しいファイル名
```
