| gitでよく使うコマンド一覧 |
|:--------------------------|
| ローカルにリモートリポジトリ(master)をクローンする <br> $ git clone git@github.com:suzuki05/suburi.git |
| ローカルにリモートリポジトリ(newbranch)をクローンする <br> $ git clone -b newbranch git@github.com:suzuki05/suburi.git |
| リモートリポジトリをoriginに登録、以降originと打つだけで良い(originとはリモートリポジトリ(master)である)<br> $ git remote add origin git@github.com:suzuki05/suburi.git |
| リモートリポジトリのURLを確認 <br> $ git remote -v |
| ローカル環境のファイルをgitで管理するときの初期設定 <br> $ git init |
| ブランチごとの履歴を見る <br> $ git log 201912151130 --oneline |
| リモートリポジトリ(master)からローカルのmasterに変更をpullし、margeする <br> $ git checkout master <br> $ git pull origin master <br> $ git checkout newbranch |
| pullの内訳(fetchではリモート追跡ブランチ(origin/master)のことをわかっている必要がある。) <br> $ git fetch origin master (リモートリポジトリoriginのmasterブランチをリモート追跡ブランチ(origin/master)に落とす) <br> $ git merge origin/master (ローカルリポジトリ内のリモート追跡ブランチmasterよりローカルのmasterブランチにマージする。) <br> 【参考】 <br> https://qiita.com/uasi/items/69368c17c79e99aaddbf <br> https://qiita.com/bitarx/items/4558f86e43a2c3493fa9 |
| ローカルのnewbranchにリモートのnewbranchの変更を反映させる <br> 該当するnewbranchに切り替えてから<br>$ git pull <br> (non-fast-forward こんなエラーが出たときは試す)|
| commit履歴を見る <br> $ git log newbranch --oneline |
| ローカルで管理しているブランチの表示 <br> $ git branch |
| ブランチ作成 <br> $ git branch newbranch |
| ブランチ移動 <br> $ git checkout newbranch |
| ローカルにあるブランチを削除 <br> $ git branch -D oldbranch |
| 変更のあったファイルを確認 <br> $ git status |
| 変更をadd <br> $ git add . |
| addしたファイルをcommit <br> $ git commit -m "message" |
| ブランチの変更をリモートリポジトリ(master)に反映させる PR <br> $ git push origin newbranch |
| git管理下のフォルダ・ファイルを削除 <br> $ git rm [削除したいファイル] <br> $ git rm -r [削除したいディレクトリ] <br> その後は、commitしてpush|
| commitログをファイルに出力する <br> $ git log -p git_cmd.md > log.txt |
