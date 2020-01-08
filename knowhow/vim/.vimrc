"Dein.vim タグジャンプが使えるようにする
"dein Scripts-----------------------------
if &compatible
  set nocompatible               " Be iMproved
endif

" Required:
set runtimepath+=/Users/suzuki05/.vim/dein/repos/github.com/Shougo/dein.vim

" Required:
if dein#load_state('/Users/suzuki05/.vim/dein')
  call dein#begin('/Users/suzuki05/.vim/dein')

  " Let dein manage dein
  " Required:
  call dein#add('/Users/suzuki05/.vim/dein/repos/github.com/Shougo/dein.vim')

  " Add or remove your plugins here like this:
  "call dein#add('Shougo/neosnippet.vim')
  "call dein#add('Shougo/neosnippet-snippets')

  " Required:
  call dein#end()
  call dein#save_state()
endif

" Required:
filetype plugin indent on
syntax enable

" If you want to install not installed plugins on startup.
"if dein#check_install()
"  call dein#install()
"endif

"End dein Scripts-------------------------
call dein#add('vim-scripts/taglist.vim')

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

"ウィンドウの設定
"定義値一覧ウィンドウ
nnoremap <silent> q :TlistOpen<CR>
"左
nnoremap a <C-w>h
"上
nnoremap w <C-w>k
"右
nnoremap d <C-w>l
"下
nnoremap s <C-w>j
"ウィンドウとタブを閉じる"
nnoremap g :<C-u>q<CR>
"縦分割
nnoremap 1 :<C-u>vs<Space>
"横分割
nnoremap 2 :<C-u>sp<Space>

"タブの設定
"新たにタブを開く
nnoremap e :<C-u>tabnew<Space>
"進む
nnoremap . gt
"戻る
nnoremap , gT

"Grepの設定(quickfix-window)
"Grep後に自動的にquickfix-windowを開く
autocmd QuickFixCmdPost *grep* cwindow

"検索の設定
"検索結果のハイライト
set hlsearch
"ハイライト解除
nnoremap r :<C-u>noh<CR>

"ctagsの設定
"vim tagを再帰的に検索する
set tags+=tags;

"termの設定
