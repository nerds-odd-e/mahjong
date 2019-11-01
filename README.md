mahjong
===========

The C plus plus version of the mahjong game. Mahjong is a Chinese game.

#How to build

First, get the unit testing frame work https://github.com/cpputest/cpputest installed.

Then, make sure you have make and cmake. Run

<pre>
    mkdir build
    cd build
    cmake ..
make
</pre>

# How to run
<pre>
src/game
</pre>
and then it will start a http service on port 8889. Visit http://localhost:8889 to play the game.

# Acceptance Test

Acceptance Test is using Behave with Python.
