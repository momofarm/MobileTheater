#!/usr/bin/python
#-*-coding:utf-8-*-

import MySQLdb as dbs

username = ''
pwd = ''
db_host = 'localhost'
db_name = 'movie_time'

class DB_Proxy:
	conn_instance = None
	def __init__(self):
		pass

	#function to connect database
	def conn(self):
		connection = dbs.connect(host = db_host,
				user = username,
				passwd = pwd,
				db = db_name,
				use_unicode = True,
				)

		global conn_instance

		conn_instance = connection
		
		return connection
		
	
	#return status of database connection
	def connected(self):
		global conn_instance

		if conn_instance:
			return true
		else:
			return false

	#close connection to database
	def close_conn(self):
		global conn_instance

		if conn_instance:
			conn_instance.close()
	
		
	#pass SQL query (only one)
	def DoQuery(self, query, param = None):
		global conn_instance
		cursor = conn_instance.cursor()
		cursor.execute(query, param)
		return cursor
	
	#pass multiple SQL query(many, many)
	def DoManyQuery(self, query, list):
		global conn_instance
		cursor = conn_instance.cursor()
		cursor.executemany(query, list)
		return cursor

