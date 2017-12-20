# this is a homework for csapp echo server & echo app

in CSAPP, chapter 11.6 we first meet Tiny http server
in the following homework, we develop more function for it.

### use echoserver & echoclient

    open two terminals
    one:
    $sudo ./echoserver 8899
    another:
    $./echoclient 127.0.0.1 8899

### use tinyhttp
    
    open two terminals
    one:
    $./tinyhttpserver 8899
    another:
    // static
    $./tinyhttpclient 127.0.0.1 8899
    // dynamic
    //TODO
