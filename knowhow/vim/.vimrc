"基本設定
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
colorscheme morning
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
"閲覧中のファイルの絶対パスを表示
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

"タブ設定
nnoremap . gt
nnoremap , gT
nnoremap st :tabnew<space>
"タブラインの設定
" Anywhere SID.
function! s:SID_PREFIX()
  return matchstr(expand('<sfile>'), '<SNR>\d\+_\zeSID_PREFIX$')
endfunction

" Set tabline.
function! s:my_tabline()  "{{{
  let s = ''
  for i in range(1, tabpagenr('$'))
    let bufnrs = tabpagebuflist(i)
    let bufnr = bufnrs[tabpagewinnr(i) - 1]  " first window, first appears
    let no = i  " display 0-origin tabpagenr.
    let mod = getbufvar(bufnr, '&modified') ? '!' : ' '
    let title = fnamemodify(bufname(bufnr), ':t')
    let title = '[' . title . ']'
    let s .= '%'.i.'T'
    let s .= '%#' . (i == tabpagenr() ? 'TabLineSel' : 'TabLine') . '#'
    let s .= no . ':' . title
    let s .= mod
    let s .= '%#TabLineFill# '
  endfor
  let s .= '%#TabLineFill#%T%=%#TabLine#'
  return s
endfunction "}}}
let &tabline = '%!'. s:SID_PREFIX() . 'my_tabline()'
set showtabline=2 " 常にタブラインを表示

"検索の設定
"検索結果のハイライト
set hlsearch
"文字列のハイライト
"検索後に該当箇所を画面中央にする
nmap n nzz
nmap N Nzz
nmap * *Nzz
nmap # #Nzz

"ブックマーク機能の設定
nnoremap bm :<C-u>marks<CR>
if !exists('g:markrement_char')
    let g:markrement_char = [
    \     'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    \     'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
    \ ]
endif
nnoremap <silent>m :<C-u>call <SID>AutoMarkrement()<CR>
function! s:AutoMarkrement()
    if !exists('b:markrement_pos')
        let b:markrement_pos = 0
    else
        let b:markrement_pos = (b:markrement_pos + 1) % len(g:markrement_char)
    endif
    execute 'mark' g:markrement_char[b:markrement_pos]
    echo 'marked' g:markrement_char[b:markrement_pos]
endfunction
"次/前のマーク
"nnoremap > ]`
"nnoremap < [`

"gtagsの設定
"grep検索
nnoremap <C-g> :tab sp<CR> :Gtags -g<space>
"カーソル位置の文字列をgrep
nnoremap <C-]> :tab sp<CR> :<C-u>exe('Gtags -g '.expand('<cword>'))<CR>
"カーソル位置の関数へジャンプ
nnoremap <C-j> :tab sp<CR> :GtagsCursor<CR>
"関数の定義元(define)へタグジャンプ
nnoremap <C-d> :tab sp<CR> :<C-u>exe('Gtags '.expand('<cword>'))<CR>
"関数の参照元(reference)へジャンプ
nnoremap <C-r> :tab sp<CR> :<C-u>exe('Gtags -r '.expand('<cword>'))<CR>
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
