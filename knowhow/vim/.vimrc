"基本設定
"viとの互換性をとらないようにする
set nocompatible
"vimの内部文字コードをutf-8にエンコードする
set encoding=utf-8
"書き込み時の文字コードを指定する
set fileencoding=utf-8
"読み込み時の文字コードを指定する、左から順番に成功した文字コードになる
set fileencodings=utf-8,sjis,euc-jp,cp932,iso-2022-jp
"開いたソースファイルの改行コードの自動認識
set fileformats=unix,dos,mac
"ソースファイルの改行コードを指定する
setl ff=unix
"バックアップファイルを作らない
set nobackup
"スワップファイルを作らない
set noswapfile
"編集中のファイルが変更されたら自動で読み直す
set autoread
"バッファが編集中でもその他のファイルを開けるようにする
set hidden
"入力中のコマンドをステータスに表示する
set showcmd
"行番号を表示
set number
"現在の行を強調表示する
set cursorline
"現在の行を強調表示する（縦）
set cursorcolumn
"行末の1文字先までカーソルを移動できるようにする
set virtualedit=onemore
"インデントはスマートインデント
set smartindent
"括弧入力時の対応する括弧を表示する
set showmatch
"ステータスラインを常に表示する
set laststatus=2
"ステータスラインに閲覧中のファイルの絶対パスを表示する
set statusline+=%F
"ステータスラインに文字コードと改行文字を表示する
set statusline=%<%f\ %m%r%h%w%{'['.(&fenc!=''?&fenc:&enc).']['.&ff.']'}%=%l,%c%V%8P
"コマンドラインの補完をする
set wildmode=list:longest
"シンタックスハイライトの有効化する
syntax on
"起動時に前回の検索文字をハイライトしない
set viminfo+=h
"カラースキーマ設定
"colorscheme morning
"Tab文字を半角スペースにする
set expandtab
"行頭以外のTab文字の表示幅（スペース2つ分）
set tabstop=2
"行頭でのTab文字の表示幅
set shiftwidth=2
"挿入モードでback spaceが効かない対策
set backspace=indent,eol,start
"ヤンクした内容を別のウィンドウにペーストできるようにする
set clipboard=unnamed,autoselect
"検索がループしないようにする
set nowrapscan
"行は折り返さない
set nowrap
"カーソルを行頭、行末で止まらないようにする
set whichwrap=h,l
"文字ないところにカーソル移動ができるようにする
set virtualedit=block
"カーソルの上または下に表示する最小限の行数
set scrolloff=2
"左下に表示される挿入などの文字を表示しない
set noshowmode
"ステータスラインの色
highlight StatusLine term=bold cterm=bold ctermfg=black ctermbg=white
"ブラウザと同じ操作 スペースでダウンアップ
nnoremap <Space>  <C-E>
nnoremap <S-Space> <C-Y>
"コメント改行時に自動でコメントヘッダを挿入しない（ファイルタイプ：全て）
autocmd FileType * set formatoptions-=ro
"標準プラグインのnetrw.vimでディレクトリをツリー表示する
"tで新しいタブで開く
let g:netrw_liststyle=3
".viminfoの位置を固定 削除はrmコマンド
set viminfo+=n~/.vim/.viminfo
"ビープ音と画面フラッシュを止める
set noerrorbells visualbell t_vb=

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

"タブページの設定
"タブページを常に表示
set showtabline=2
"タブページの移動
nnoremap . gt
nnoremap , gT

"検索の設定
"検索結果のハイライト
set hlsearch
"文字列のハイライト
"検索後に該当箇所を画面中央にする
nnoremap n nzz
nnoremap N Nzz
nnoremap * *Nzz
nnoremap # #Nzz

"現在の関数名を表示
fun! ShowFuncName()
  let lnum = line(".")
  let col = col(".")
  echohl ModeMsg
  echo getline(search("^[^ \t#/]\\{2}.*[^:]\s*$", 'bW'))
  echohl None
  call search("\\%" . lnum . "l" . "\\%" . col . "c")
endfun
map f :call ShowFuncName() <CR>

"gtagsの設定
"grep検索
nnoremap <C-g> :tab sp<CR> :Gtags -g<space>
"カーソル位置の文字列をgrep
nnoremap <C-]> :tab sp<CR> :<C-u>exe('Gtags -g '.expand('<cword>'))<CR>
"カーソル位置の関数へジャンプ
nnoremap <C-j> :tab sp<CR> :GtagsCursor<CR>
"開いているファイルに定義されている関数一覧を表示
nnoremap <C-h> :Gtags -f %<CR>
"次の検索結果へジャンプする
nnoremap <C-n> :cn<CR>
"前の検索結果にジャンプする
nnoremap <C-p> :cp<CR>

"Quickfixの設定
"Quickfixも一緒に閉じるようにする
augroup QfAutoCommands
  autocmd!

  " Auto-close quickfix window
  autocmd WinEnter * if (winnr('$') == 1) && (getbufvar(winbufnr(0), '&buftype')) == 'quickfix' | quit | endif
augroup END

"コンパイルスイッチ用の設定
"マクロが定義されていて、かつ値が0orFALSEのもの
autocmd BufEnter * match Todo /\<FIZZ\|BUZZ\>/
"マクロが定義されていて、TRUEになるもの
autocmd BufEnter * 2match Underlined /\<HOGE\|FUGA\>/
