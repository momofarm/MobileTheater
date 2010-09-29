#!/bin/sh

clear:
	mysql movie_time -u user -p < ../DB/clear.sql

cb:
	mysql movie_time -u user -p < ../DB/clear.sql
	mysql movie_time -u user -p < ../DB/movie.sql

status:
	mysql movie_time -u user -p < ../DB/status.sql

create:
	mysql  -u user -p < ../DB/movie.sql
