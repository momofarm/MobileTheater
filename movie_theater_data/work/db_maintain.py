#!/usr/bin/python
#-*-coding:utf-8-*-

from sql_conn import DB_Proxy
from dmsg import dMsg, setDbgOn, setDbgOff
import time

    
import sys

print sys.getdefaultencoding() 

class DB_Maintain:
	db = None
	#should connect to database first?
	# or something else
	def __init__(self):
		global db

		db = DB_Proxy()
		db.conn()
		db.DoQuery("""SET NAMES \'UTF8\'""")


	#check if this theater already in database
	def CheckTheaterExist(self, sourceID, name):
		c = db.DoQuery("""select SOURCE_ID, NAME from THEATER where SOURCE_ID = %s AND NAME = %s""", (sourceID, name))	
		
		count = c.rowcount

		print count
		
		if count > 1:
			#multiple match, ambigous situation, ouch!!
			return -1
		elif count == 1:
			return 1
		else:
			return 0
			#no match	


	#update theater information
	def UpdateTheaterInfo(self, sourceID, name, addr, phone, gps, part_area, area, time_stamp):

		db.DoQuery("""UPDATE THEATER
				SET ADDRESS = %s, GPS = %s, PART_AREA = %s, AREA = %s, PHONE = %s, TIME_STAMP = %s
				WHERE SOURCE_ID = %s AND NAME = %s""", (addr, gps, part_area, area, phone, time_stamp, sourceID, name))


		

	#add theater information
	def AddTheater(self, sourceID, name, address, phone, gps, partarea, area, time_stamp):
		if self.CheckTheaterExist(sourceID, name):
			self.UpdateTheaterInfo(sourceID, name, address, phone, gps, partarea, area, time_stamp)
			return

		newID = self.GenTheaterID()
	
		#sourceID = unicode(sourceID).encode('utf-8')

		db.DoQuery("""INSERT INTO THEATER VALUES(%s, %s, %s, %s, %s, %s, %s, %s, %s)""", (newID, sourceID, 
			name, address, phone, gps, partarea, area, time_stamp))


	#return the same result like GetMovieTime, but using theaterID as parameter
	def GetMovieTime(self, theaterID):
		cursor = db.DoQuery("""SELECT HALL_NAME, MOVIE_NAME, TIME FROM THEATER_TIME where THEATER_ID = %s""", (theaterID))
	
		count = cursor.rowcount

		result = cursor.fetchmany(count)
		
		return result

	def GetTheaterID(self, sourceID):
		cursor = db.DoQuery("""SELECT THEATER_ID FROM THEATER where SOURCE_ID = %s""", (sourceID))

		theaterID = cursor.fetchone()
	
		if cursor.rowcount > 0:
			return theaterID[0]
		else:
			return None

	def CheckHallExist(self, sourceID, hallname):
		theaterID = self.GetTheaterID(sourceID)		
	
		cursor = db.DoQuery("""SELECT MOVIE_NAME, TIME FROM THEATER_TIME where THEATER_ID = %s AND HALL_NAME = %s""", (theaterID, hallname))
				
		if cursor.rowcount > 0:
			return True
		else:
			return False

	def UpdateGPS(self, id):
		c = db.DoQuery("""SELECT THEATER_ID, ADDRESS FROM THEATER where THEATER_ID = %s""", id)

		addr_list = c.fetchmany(c.rowcount)

		from geoloc import get_loc

		blacklist = ['T00003']

		for d in addr_list:
			#print d[1]
			
			print d
			addr = d[1]
			
			if d[0] == 'T00003':
				continue
			
			#print type(addr)			
			addrs = addr.encode('raw_unicode_escape').decode('utf-8')
			
			print addrs

			
			lat, lng = get_loc(addrs)

			gps_loc = "%s,%s"% (lng, lat)

			
			db.DoQuery("""UPDATE THEATER SET GPS = %s where THEATER_ID = %s""", (gps_loc, d[0]))

			time.sleep(20)	
	
			
		pass

	def CheckTheaterExist(self, sourceID, theaterName):
		theaterID = self.GetTheaterID(sourceID)
		
		if theaterID:
			return True
		else:
			return False	
	
	def AddTheaterTime(self, sourceID, hallname, movie_name, time):
		if self.CheckHallExist(sourceID, hallname):
			self.UpdateMovieTime(sourceID, hallname, movie_name, time)
			return
		
		
		theaterID = self.GetTheaterID(sourceID)
		
		print theaterID
	
		db.DoQuery("""INSERT INTO THEATER_TIME VALUES(%s, %s, %s, %s);""", (theaterID, hallname, movie_name, time))
		
		

	def UpdateMovieTime(self, sourceID, hallname, movie_name, time):
		theaterID = self.GetTheaterID(sourceID)
		
		if not self.CheckHallExist(sourceID, hallname):
			dMsg('hall name not exist')
			self.AddTheaterTime(sourceID, hallname, movie_name, time)
			return
		
		db.DoQuery("""UPDATE THEATER_TIME
				SET MOVIE_NAME = %s, TIME = %s
				WHERE THEATER_ID = %s AND HALL_NAME = %s""", (movie_name, time, theaterID, hallname))
		
	
	def GenTheaterID(self):
		cursor = db.DoQuery("""SELECT THEATER_ID FROM THEATER""")		

		result_count = cursor.rowcount
		
		result = cursor.fetchmany(result_count)
		
		result_list = list(result)
	
		if len(result_list) == 0:
			return 'T00001'
		else:
			match = None

			for i in range(1, 10000):
				testID = "T%05d"%i
				
				if self.CheckDuplicateKey(testID, result):
					continue

				match = i
				break
			
		#check if exist?
			#newIDNum = match + 1
		
			newID = "T%05d"%match
			
			if newID in result:
				dmsg('error, gen number error')
				return -1

			else:
				return newID
					
	
	def CheckDuplicateKey(self, key, tuplelist):
		for tuple in tuplelist:
			if tuple[0] == key:
				return True
					
		
		return False
	

	def Close_conn(self):
		db.close_conn()	

	#####################################################################################
	## retrive data section
	####################################################################################
	def GetNameID(self, area):
		
		cursor = db.DoQuery("""select THEATER_ID, NAME from THEATER where PART_AREA = %s""", area)	
	
		out = cursor.fetchmany(cursor.rowcount)
		
		for a in out:
			for z in a:
				print type(z)
				print z
				
		return out	

		
	def GetTheaterInfo(self, ID):
		cursor = db.DoQuery("""select NAME, ADDRESS, PHONE from THEATER where THEATER_ID = %s""", ID)

		if cursor.rowcount > 1:
			dMsg('error, more than one IDs')
			return None 		#error, should not exceed than one
		
		info = cursor.fetchmany(cursor.rowcount)
		
		return info 

	def GetTheaterMovies(self, ID):
		cursor = db.DoQuery("""select HALL_NAME, MOVIE_NAME, TIME from THEATER_TIME where THEATER_ID = %s;""", ID)
		
		info = cursor.fetchmany(cursor.rowcount)

		return info

	
		


