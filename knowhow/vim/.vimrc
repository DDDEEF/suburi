"基本設定
"文字コードをUFT-8に設定
set fenc=utf-8
"バックアップファイルを作らない
set nobackup
"スワップファイルを作らない
set noswapfile
"編集中のファイルが変更されたら自動で読み直す
set autoread
"バッファが編集中でもその他のファイルを開けるように
set hidden
"入力中のコマンドをステータスに表示する
set showcmd
"行番号を表示
set number
"現在の行を強調表示
set cursorline
"現在の行を強調表示（縦）
set cursorcolumn
"行末の1文字先までカーソルを移動できるように
set virtualedit=onemore
"インデントはスマートインデント
set smartindent
"括弧入力時の対応する括弧を表示
set showmatch
"ステータスラインを常に表示
set laststatus=2
"コマンドラインの補完
set wildmode=list:longest
"シンタックスハイライトの有効化
syntax on
"カラースキーマ設定
colorscheme elflord
"Tab文字を半角スペースにする
set expandtab
"行頭以外のTab文字の表示幅（スペースいくつ分）
set tabstop=2
"行頭でのTab文字の表示幅
set shiftwidth=2
"挿入モードでback spaceが効かない対策
set backspace=indent,eol,start
"ヤンクした内容を別のウィンドウにペーストできるようにする
set clipboard=unnamed,autoselect
"閲覧中のファイルのパスを表示
set statusline+=%F

"入力補完
"大括弧の入力補完
imap [ []<Left>
"中括弧の入力補完
imap { {<return><return>}<UP><TAB>
"小括弧の入力補完
imap ( ()
"クォーテーションの入力補完
inoremap " ""<LEFT>
inoremap ' ''<LEFT>

"tab設定
nnoremap t :<C-u>tabnew<space>
nnoremap < gt
nnoremap > gT

"検索の設定
"検索結果のハイライト
set hlsearch
"ハイライト解除
nnoremap r :<C-u>noh<CR>

"ctagsの設定
"vim tagを再帰的に検索する
set tags+=tags;

"gtagsの設定
map <C-g> :Gtags
map <C-h> :Gtags -f %<CR>
map <C-j> :GtagsCursor<CR>
map <C-n> :cn<CR>
map <C-p> :cp<CR>
