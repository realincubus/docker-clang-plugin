execute pathogen#infect()
syntax on
filetype plugin indent on

let g:clang_c_options = '-std=gnu11'
let g:clang_cpp_options = '-std=c++11 -stdlib=libc++'
let g:ycm_confirm_extra_conf = 0 

set shiftwidth=2
set softtabstop=2

set number

function! g:EmitAcc()
    let g:emit_type="-emit-openacc"
    YcmCompleter ClearCompilationFlagCache 
    YcmRestartServer 
    "YcmForceCompileAndDiagnostics
    echo "starting to emit acc code"
endfunction

function! g:EmitTbb()
    let g:emit_type="-emit-tbb"
    YcmCompleter ClearCompilationFlagCache 
    YcmRestartServer 
    "YcmForceCompileAndDiagnostics
    echo "starting to emit tbb code"
endfunction

function! g:EmitOmp()
    let g:emit_type="-emit-openmp"
    YcmCompleter ClearCompilationFlagCache 
    YcmRestartServer 
    "YcmForceCompileAndDiagnostics
    echo "starting to emit omp code"
endfunction

function! g:EmitCilk()
    let g:emit_type="-emit-cilk"
    YcmCompleter ClearCompilationFlagCache 
    YcmRestartServer 
    "YcmForceCompileAndDiagnostics
    echo "starting to emit cilk code"
endfunction

function! g:EmitHpx()
    let g:emit_type="-emit-hpx"
    YcmCompleter ClearCompilationFlagCache 
    YcmRestartServer 
    "YcmForceCompileAndDiagnostics
    echo "starting to emit hpx code"
endfunction

map <F1> :call g:EmitAcc() <CR>
map <F2> :call g:EmitOmp() <CR>
map <F3> :call g:EmitTbb() <CR>
map <F4> :call g:EmitCilk() <CR>
map <F5> :call g:EmitHpx() <CR>
map <F6> :YcmForceCompileAndDiagnostics <CR>
map <F7> :YcmCompleter FixIt <CR>

set hlsearch 

" make YCM compatible with UltiSnips (using supertab)
let g:ycm_key_list_select_completion = ['<C-n>', '<Down>']
let g:ycm_key_list_previous_completion = ['<C-p>', '<Up>']
let g:ycm_echo_current_diagnostic = 1
let g:emit_type=""
let g:ycm_extra_conf_vim_data = ['g:emit_type']

" better key bindings for UltiSnipsExpandTrigger
let g:UltiSnipsExpandTrigger = "<tab>"
let g:UltiSnipsJumpForwardTrigger = "<tab>"
let g:UltiSnipsJumpBackwardTrigger = "<s-tab>"
