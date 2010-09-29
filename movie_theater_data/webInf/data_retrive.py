#!/usr/bin/python

import sys
reload(sys)
sys.setdefaultencoding('utf-8')

sys.path.append('../work')
from db_maintain import DB_Maintain

import json

d = DB_Maintain()

def GetIDs(areaAry):
	#result = d.GetNameID(area)

	aryResult = []

	for data in areaAry:
		print data.THEATER_ID
		print data.NAME		
		id = data.THEATER_ID
		name = data.NAME
		aryResult.append((id, name))		

		
	jsonText = json.dumps(aryResult, ensure_ascii = False)

	print jsonText

	return jsonText

def GetTheaterInfo(info, time):
	dict = {}
	aryTime = []
	result = []

	for d in info:
		dict['name'] = d.NAME 
		dict['address'] = d.ADDRESS
		dict['phone'] = d.PHONE
		
	for t in time:
		hallname = t.HALL_NAME
		movie_name = t.MOVIE_NAME 
		movie_time = t.TIME
		aryTime.append((hallname, movie_name, movie_time))

	result.append(dict)
	result.append(aryTime)	
	
	jsonText = json.dumps(result, ensure_ascii = False)

	return jsonText

	
def GetAreas(areas):
	aryAreas = []

	for d in areas:
		aryAreas.append(d.AREA_NAME)


	jsonText = json.dumps(aryAreas, ensure_ascii = False)

	return jsonText


def GetNearFiveLocation(lng, lat, datas):
	from distance import Calc_Distance

	print "lng is %s, lat is %s" % (lng, lat)

	for d in datas:
		THEATER_ID = d[0]
		gps_data = d[1]
		"""d[3] is for data """
		
		gps_str = gps_data.encode('raw_unicode_escape').decode('utf-8')
	
		gps_strings = gps_data.split(",")
	
		if len(gps_strings) < 2:
			continue
		
		print gps_strings

		lng2 = gps_strings[0]
			
		lat2 = gps_strings[1]
		
		print "lng2 is %s, lat2 is %s" % (lng2, lat2)

		d[2] = Calc_Distance(float(lat), float(lng), float(lat2), float(lng2))
		
		print "distance is %s" % d[2]
	
		
	datas.sort(key = lambda x : x[2])

	print '---------------------------------\n'

	result = []
	
	print datas

	for a in range(0,5):
		print datas[a]
		result.append([datas[a][0], datas[a][1], datas[a][2], datas[a][3]])

	jsonText = json.dumps(result, ensure_ascii = False)

	return jsonText

