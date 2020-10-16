set logging file /tmp/backtrace.log
set logging overwrite on
set pagination 0
set logging on

set print thread-events off

echo \n--- DEBUG: --- START\n\n

echo \n--- DEBUG: BACKTRACE FULL\n\n
bt full

echo \n--- DEBUG: INFO THREAD\n\n
info thread

echo \n--- DEBUG: THREAD APPLY ALL BACKTRACE\n
thread apply all backtrace

echo \n--- DEBUG: --- STOP\n\n

set logging off
quit
