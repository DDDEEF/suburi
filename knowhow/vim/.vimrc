"基本設定
"viとの互換性をとらないようにする
set nocompatible
"vimの内部文字コードをutf-8にエンコードする
set encoding=utf-8
"書き込み時の文字コードを指定する
set fileencoding=utf-8
"読み込み時の文字コードを指定する、左から順番に成功した文字コードになる
set fileencodings=utf-8,sjis,euc-jp,cp932,iso-2022-jp
"開いたソースファイルの改行コードの自動認識する
set fileformats=unix,dos,mac
"ソースファイルの改行コードを指定する
setl ff=unix
"特定の文字が崩れるのを防ぐ
set ambiwidth=double
"バックアップファイルを作らないようにする
set nobackup
"スワップファイルを作らないようにする
set noswapfile
"編集中のファイルが変更されたら自動で読み直す
set autoread
"バッファが編集中でもその他のファイルを開けるようにする
set hidden
".viminfoファイルを作成しない
set viminfo=
"タイトルを表示する
set title
"入力中のコマンドをステータスに表示する
"set showcmd
"行番号を表示する
set number
"現在の行を強調表示する
set cursorline
"現在の行を強調表示する（縦）
set cursorcolumn
"行末の1文字先までカーソルを移動できるようにする
set virtualedit=onemore
"括弧入力時の対応する括弧を表示する
set showmatch
"ファイル名表示
set statusline=%F
"変更チェック表示
set statusline+=%m
"読み込み専用かどうか表示
set statusline+=%r
"ヘルプページなら[HELP]と表示
set statusline+=%h
"プレビューウインドウなら[Prevew]と表示
set statusline+=%w
"これ以降は右寄せ表示
set statusline+=%=
"file encoding
set statusline+=[ENC=%{&fileencoding}]
"現在行数/全行数
set statusline+=[LOW=%l/%L]
"ステータスラインを常に表示(0:表示しない、1:2つ以上ウィンドウがある時だけ表示)
set laststatus=2
"メッセージ表示欄を2行確保
set cmdheight=2
"コマンドラインの補完をする
set wildmode=list:longest
"起動時に前回の検索文字をハイライトしない
"set viminfo+=h
"インデントはスマートインデントにする
set smartindent
"Tab文字を半角スペースにする
set expandtab
"行頭以外のTab文字の表示幅（スペース2つ分）
set tabstop=2
"行頭でのTab文字の表示幅
set shiftwidth=2
"改行時に前の行のインデントを継続する
set autoindent
"挿入モードでback spaceが効かない対策
set backspace=indent,eol,start
"ヤンクした内容を別のウィンドウにペーストできるようにする
set clipboard=unnamed,autoselect
"検索がループしないようにする
set nowrapscan
"小文字で検索した時、大文字小文字を無視
set ignorecase
"大文字で検索した時、大文字小文字を無視しない
set smartcase
"インクリメントサーチを有効にする
"set incsearch
"行は折り返さないようにする
"set nowrap
"カーソルを行頭、行末で止まらないようにする
set whichwrap=h,l
"文字ないところにカーソル移動ができるようにする
set virtualedit=block
"カーソルの上または下に表示する最小限の行数を設定する
set scrolloff=5
"左下に表示される挿入などの文字を表示しない
set noshowmode
"コメント改行時に自動でコメントヘッダを挿入しない（ファイルタイプ：全て）
autocmd FileType * set formatoptions-=ro
".viminfoの位置を固定 削除はrmコマンド
"set viminfo+=n~/.vim/.viminfo
"ビープ音と画面フラッシュを止める
set noerrorbells
set visualbell t_vb=
"標準プラグインのnetrw.vimでディレクトリをツリー表示する
let g:netrw_liststyle=3
"エクスプローラを開く
nnoremap tt :Texplore <CR>

"入力補完
"ノーマルモードへ
inoremap <C-c> <Esc>
"インサートモードで右へ
inoremap <C-l> <Right>
"インサートモードで左へ
inoremap <C-h> <Left>
"インサートモードへo
inoremap <C-o> <Esc>o
"インサートモードでa
inoremap <C-a> <Esc>A
"インサートモードで;
inoremap <C-;> <Esc>A;

"大括弧の入力補完
inoremap [ []<ESC>i
"中括弧の入力補完
inoremap { {<return><return>}<UP><TAB>
"小括弧の入力補完
inoremap ( ()<ESC>i
"クォーテーションの入力補完
inoremap " ""<LEFT>
inoremap ' ''<LEFT>
"qで閉じる
nnoremap q :q <CR>
"aで行末から入力
nnoremap a A
";で行末に;を入力
nnoremap ; A;<ESC>
"{で行末に{を入力
nnoremap { A{<return><return>}<UP><TAB>
"=で行末に=を入力
nnoremap = A<Space>=<Space>

"検索の設定
"検索結果のハイライト
set hlsearch
"文字列のハイライト
"検索後に該当箇所を画面中央にする
nnoremap n nzt
nnoremap N Nzt
nnoremap * *Nzt
nnoremap # #Nzt

"タブページの設定
"タブページを常に表示
set showtabline=2
"タブページの移動
nnoremap . gt
nnoremap , gT

"quickhlvim設定
"カーソル上の文字ハイライト
nmap <Space>m <Plug>(quickhl-manual-this)
xmap <Space>m <Plug>(quickhl-manual-this)
"カーソル上の単語ハイライト
nmap <Space>w <Plug>(quickhl-manual-this-whole-word)
xmap <Space>w <Plug>(quickhl-manual-this-whole-word)
"トグルモード
nmap <Space>j <Plug>(quickhl-cword-toggle)

"gtagsの設定
"grep検索
nnoremap <C-g> :tab sp<CR> :Gtags -g<space>-l<space>
"カーソル位置の文字列をgrep検索
nnoremap <C-]> :tab sp<CR> :<C-u>exe('Gtags -g -l '.expand('<cword>'))<CR>zt
"カーソル位置の関数の定義元へタグジャンプ
nnoremap <C-j> :tab sp<CR> :GtagsCursor<CR>zt
"開いているファイルに定義されている関数一覧を表示
nnoremap <C-h> :Gtags -f %<CR>zt
"次の検索結果へジャンプする
nnoremap <C-n> :cn<CR>zt
"前の検索結果にジャンプする
nnoremap <C-p> :cp<CR>zt

"Quickfixの設定
"Quickfixも一緒に閉じるようにする
augroup QfAutoCommands
  autocmd!
  " Auto-close quickfix window
  autocmd WinEnter * if (winnr('$') == 1) && (getbufvar(winbufnr(0), '&buftype')) == 'quickfix' | quit | endif
augroup END

"コンパイルスイッチ用の設定
"マクロが定義されていて、かつ値が0orFALSEのもの
autocmd BufEnter * match Error /\<FIZZ\|BUZZ\>/
"マクロが定義されていて、TRUEになるもの
autocmd BufEnter * 2match Todo /\<HOGE\|FUGA\>/

"シンタックスハイライトの有効化する
syntax enable
"カラーの設定
set background=light
hi clear
set t_Co=256

"ステータスラインの色
hi StatusLine term=NONE cterm=NONE ctermfg=black ctermbg=white

"通常文字
hi Normal term=NONE cterm=NONE ctermfg=NONE ctermbg=NONE

"特殊文字
hi Special term=bold cterm=bold ctermfg=127

"コメント
hi Comment term=NONE cterm=NONE ctermfg=27

hi Constant term=bold cterm=bold ctermfg=red
hi String term=NONE cterm=NONE ctermfg=red
hi Character term=NONE cterm=NONE ctermfg=red
hi Number term=NONE cterm=NONE ctermfg=red
hi Boolean term=NONE cterm=bold ctermfg=red
hi Float term=NONE cterm=NONE ctermfg=red

hi Identifier term=bold cterm=bold ctermfg=17
hi Function term=bold cterm=bold ctermfg=17

hi Statement term=bold cterm=bold ctermfg=89
hi Conditional term=bold cterm=bold ctermfg=89
hi Repeat term=bold cterm=bold ctermfg=89
hi Label term=bold cterm=bold ctermfg=89
hi Operator term=bold cterm=bold ctermfg=89
hi Keyword term=bold cterm=bold ctermfg=89
hi Exception term=bold cterm=bold ctermfg=89

hi PreProc term=NONE cterm=NONE ctermfg=127
hi Include term=NONE cterm=NONE ctermfg=127
hi Define term=NONE cterm=NONE ctermfg=127
hi Macro term=NONE cterm=NONE ctermfg=127
hi PreCondit term=NONE cterm=NONE ctermfg=127

hi Type term=NONE cterm=NONE ctermfg=127
hi StorageClass term=NONE cterm=NONE ctermfg=127
hi Structure term=NONE cterm=NONE ctermfg=127
hi Typedef term=NONE cterm=NONE ctermfg=127

"行
hi LineNr term=NONE cterm=NONE ctermfg=27
hi CursorLineNr term=NONE cterm=NONE ctermfg=27

"タブバー
hi TabLineFill ctermfg=black
hi TabLine ctermfg=white ctermbg=black
hi TabLineSel term=NONE cterm=NONE ctermfg=black ctermbg=white

hi clear SignColumn
