#!/usr/bin/python
#-*-coding:utf-8-*-

import Areas
import theaters
import area_list
import time
from dmsg import dMsg, setDbgOn, setDbgOff

areas = Areas.getAddRess()

for area in areas:
	area_name = area[0]
	area_url = area[1]

	setDbgOn()

	dMsg('now processing area ' + area_name)
	
	urldata = area_list.arealist_data(area_url)
	
	dMsg('current url count is %d' % len(urldata))

	for data in urldata:
		url = data[0]
		urlkey = data[1]
	 
		dMsg(url)
		dMsg(urlkey)
			
		data = theaters.theater_data(url, urlkey, area_name)
		
		if data:	
			dMsg('size of d is %d' % len(data))

			for d in data:
				dMsg(d)
		else:
			dMsg('error no data, and data is %s' % data)

		time.sleep(40)
