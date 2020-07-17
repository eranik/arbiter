# arbiter_script

There is a file that defines the entry point for the console application, which is named
`APP_ENTRY_FILE="./cmpt225exercises.cpp"`
in `./arbiter_script.sh`, 
put it next to `arbiter_script.sh`

Also put zip file contianing submission zip files next to `arbiter_script.sh` as well, and pass it as argument to `./arbiter_script.sh`:

`./arbiter_script submissions.zip`


For each submission, **compile.log** and **run.log** is created after compile and run, respectively.

Also **time.log** logs run duration of compiled binary; if timeout happens it will also log it.