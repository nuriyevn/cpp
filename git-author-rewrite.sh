#!/bin/sh

# git clone --bare https://github.com/user/repo.git
# cd repo.git
# ...run this script...
# ...review the history if everything is ok..
# git push --force --tags origin 'refs/heads/*'


git filter-branch --env-filter '

OLD_EMAIL="nuriyevn@github.com"
CORRECT_NAME="nuriyevn"
CORRECT_EMAIL="nuriyevn@gmail.com"
if [ "$GIT_COMMITTER_EMAIL" = "$OLD_EMAIL" ]
then
	export GIT_COMMITTER_NAME="$CORRECT_NAME"
	export GIT_COMMITTER_EMAIL="$CORRECT_EMAIL"
fi
if [ "$GIT_AUTHOR_EMAIL" = "$OLD_EMAIL" ]
then
	export GIT_AUTHOR_NAME="$CORRECT_NAME"
	export GIT_AUTHOR_EMAIL="$CORRECT_EMAIL"
fi
' --tag-name-filter cat -- --branches --tags

