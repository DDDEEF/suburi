"viとの互換性をとらないようにする
set nocompatible
"vimの内部文字コードをutf-8にエンコードする
scriptencoding utf-8
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
set showcmd
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
"file encoding
set statusline=%{&fileencoding}
"変更チェック表示
set statusline+=%m
"読み込み専用かどうか表示
set statusline+=%r
"現在列数
set statusline+=[%c]
"現在行数/全行数
set statusline+=[%l/%L]
"これ以降は右寄せ表示
set statusline+=%=
"ファイル名表示
set statusline+=%F
"ステータスラインを常に表示(0:表示しない、1:2つ以上ウィンドウがある時だけ表示)
set laststatus=2
"メッセージ表示欄を2行確保
"set cmdheight=2
"コマンドラインの補完をする
set wildmode=longest,full
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
set backspace=2
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

"現在の関数を表示
fun! ShowFuncName()
  let lnum = line(".")
  let col = col(".")
  echohl ModeMsg
  echo getline(search("^[^ \t#/]\\{2}.*[^:]\s*$", 'bW'))
  echohl None
  call search("\\%" . lnum . "l" . "\\%" . col . "c")
endfun
map f :call ShowFuncName() <CR>

"シンタックスハイライトの有効化する
syntax enable
"カラーの設定
hi clear
set t_Co=256
"cterm(CUIのbold/underlineなどの設定)
"ctermfg(CUIの文字色設定)
"ctermbg(CUIの文字背景食設定)
"文字・背景色
hi Normal                          ctermfg=250 ctermbg=235
"ステータスライン
hi StatusLine           cterm=NONE ctermfg=250 ctermbg=235
"カーソルのある行
hi CursorLine           cterm=NONE ctermfg=NONE ctermbg=236
"行番号
hi LineNr               cterm=NONE ctermfg=240 ctermbg=235
"カーソルのある行番号
hi CursorLineNr         cterm=NONE ctermfg=250 ctermbg=236
"カーソルのある列
hi cursorcolumn         cterm=NONE ctermfg=NONE  ctermbg=236
"アクティブなタブ
hi TabLineSel           cterm=NONE ctermfg=250 ctermbg=235
"非アクティブなタブ
hi TabLine              cterm=NONE ctermfg=247 ctermbg=236
"タブがないところ
hi TabLineFill          cterm=NONE ctermfg=000 ctermbg=NONE
"ビジュアルモード選択
hi Visual               cterm=NONE ctermfg=NONE ctermbg=012
"ビジュアルモード非選択
hi VisualNOS            cterm=NONE ctermfg=250  ctermbg=235
"カーソル下の括弧に対応する括弧
hi MatchParen           cterm=NONE ctermfg=NONE ctermbg=012
"ディテクトリ名
hi Directory            cterm=NONE ctermfg=250 ctermbg=NONE
"wildmodeの補完での現在の候補
hi WildMenu             cterm=NONE ctermfg=250 ctermbg=235
"コマンドライン上のエラーメッセージ
hi ErrorMsg             cterm=NONE ctermfg=160 ctermbg=235
"yes/no
hi Question             cterm=NONE ctermfg=160 ctermbg=235
" –INSERT–メッセージ
hi ModeMsg              cterm=NONE ctermfg=160 ctermbg=235
" –More–メッセージ
hi MoreMsg              cterm=NONE ctermfg=160 ctermbg=235
"警告
hi WarningMsg           cterm=NONE ctermfg=160 ctermbg=235
"最後に検索した単語のハイライト
hi Search               cterm=NONE ctermfg=250 ctermbg=012
"インクリメントサーチ
hi IncSearch            cterm=NONE ctermfg=250 ctermbg=012
"コメントアウト
hi Comment              cterm=NONE ctermfg=240 ctermbg=NONE
"定数
hi Constant             cterm=NONE ctermfg=027 ctermbg=NONE
" ""で囲まれる文字列定数
hi String               cterm=NONE ctermfg=027 ctermbg=NONE
" ''で囲まれる1文字の定数
hi Character            cterm=NONE ctermfg=026 ctermbg=NONE
"数字定数
hi Number               cterm=NONE ctermfg=026 ctermbg=NONE
"ブール定数
hi Boolean              cterm=NONE ctermfg=026 ctermbg=NONE
"浮動小数点定数
hi Float                cterm=NONE ctermfg=006 ctermbg=NONE
"変数名
hi Identifier           cterm=NONE ctermfg=250 ctermbg=NONE
"関数名・クラス名
hi Function             cterm=NONE ctermfg=250 ctermbg=NONE
"命令文
hi Statement            cterm=NONE ctermfg=127 ctermbg=NONE
"条件分岐 if then else endif switch
hi Conditional          cterm=NONE ctermfg=127 ctermbg=NONE
"繰り返し　for do while
hi Repeat               cterm=NONE ctermfg=127 ctermbg=NONE
"ラベル case default
hi Label                cterm=NONE ctermfg=127 ctermbg=NONE
"演算子 sizeof + *
hi Operator             cterm=NONE ctermfg=127 ctermbg=NONE
"その他キーワード
hi Keyword              cterm=NONE ctermfg=127 ctermbg=NONE
"例外処理 try catch throw
hi Exception            cterm=NONE ctermfg=127 ctermbg=NONE
"一般的なプリプロセッサ
hi PreProc              cterm=NONE ctermfg=127 ctermbg=NONE
"#includeプリプロセッサー
hi Include              cterm=NONE ctermfg=127 ctermbg=NONE
"#defineプリプロセッサー
hi Define               cterm=NONE ctermfg=127 ctermbg=NONE
"#defineと同じ
hi Macro                cterm=NONE ctermfg=127 ctermbg=NONE
"プリプロセッサー #if #else #endif
hi PreCondit            cterm=NONE ctermfg=127 ctermbg=NONE
"int long char その他
hi Type                 cterm=NONE ctermfg=026 ctermbg=NONE
"static register volatile その他
hi StorageClass         cterm=NONE ctermfg=031 ctermbg=NONE
"struct union enum その他
hi Structure            cterm=NONE ctermfg=002 ctermbg=NONE
"typedef宣言
hi Typedef              cterm=NONE ctermfg=002 ctermbg=NONE
"特殊文字
hi Special              cterm=NONE ctermfg=250 ctermbg=NONE
"特殊な文字定数
hi SpecialChar          cterm=NONE ctermfg=250 ctermbg=NONE
"Tag
hi Tag                  cterm=underline ctermfg=NONE ctermbg=NONE
"注意が必要な文字
hi Delimiter            cterm=NONE ctermfg=127 ctermbg=NONE
"コメント内の特筆事項
hi SpecialComment       cterm=NONE ctermfg=039 ctermbg=NONE
"デバッグ命令
hi Debug                cterm=NONE ctermfg=250 ctermbg=NONE
"Underlined
hi Underlined           cterm=NONE ctermfg=250 ctermbg=NONE
"Ignore
hi Ignore               cterm=NONE ctermfg=250 ctermbg=NONE
"Error
hi Error                cterm=NONE ctermfg=250 ctermbg=NONE
"Todo
hi Todo                 cterm=NONE ctermfg=250 ctermbg=NONE
