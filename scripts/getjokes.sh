#!/bin/sh

curl https://raw.githubusercontent.com/yesinteractive/dadjokes/master/controllers/jokes.txt | sed 's:<>: <i>:' | sed 's:$:</i>:' > jokes.txt
