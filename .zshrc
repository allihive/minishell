autoload -U colors && colors
PS1="%B%{$fg[red]%}[%{$fg[yellow]%}%n%{$fg[green]%}@%{$fg[blue]%}%M %{$fg[magenta]%}%~%{$fg[red]%}]%{$reset_color%}$%b "

export CLICOLOR=1
export LSCOLORS=ExGxBxDxCxEgEdxbxgxcxd
alias ll='ls -alG'
alias cc42='cc -Wall -Wextra -Werror'

export MAIL='alli@student.hive.fi'

alias francinette=/Users/alli/francinette/tester.sh

alias paco=/Users/alli/francinette/tester.sh
export PATH=$HOME/.brew/bin:$PATH
alias code='/Applications/Visual\ Studio\ Code.app/Contents/Resources/app/bin/code'
