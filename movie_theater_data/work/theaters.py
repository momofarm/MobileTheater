#!/usr/bin/python
#-*-coding:utf-8-*-


#from urllib2 import urlopen

import time
import StringIO
from dmsg import dMsg, setDbgOn, setDbgOff

from db_maintain import DB_Maintain


def theater_data(strURL, sourceID, area_name):
	
	db = DB_Maintain()

	data = []
		
	#init section
	sourceIDText = unicode(sourceID).encode('utf-8')
	theaterNameText = None
	theaterAddressText = None
	theaterPhoneText = None

	from lxml.html import tostring, parse, find_class
	import codecs
	from lxml import etree

	parser = etree.HTMLParser()
 
	p = parse(strURL, parser).getroot()

	#Get theater name
	theaterName = p.xpath('/html/body/div/div[2]/div[2]/div[4]/div[2]/p/span/text()')

	if theaterName:
		data.append(unicode(theaterName[0].strip()).encode('utf-8'))
		theaterNameText = unicode(theaterName[0].strip()).encode('utf-8') 
	else:
		dMsg('unexpected, no theater name')
		dMsg('url is %s\n' % strURL)
		return 

	#print unicode(theaterName[0].strip()).encode('utf-8')

	#Get theater address
	theaterAddress = p.xpath('/html/body/div/div[2]/div[2]/div[4]/div[2]/p/span[2]/text()')
	#print unicode(theaterAddress[0].strip()).encode('utf-8')

	data.append(unicode(theaterAddress[0].strip()).encode('utf-8'))
	theaterAddressText = unicode(theaterAddress[0].strip()).encode('utf-8') 

	#get phone number
	theaterPhone = p.xpath('.//br/following-sibling::text()')

	#print unicode(theaterPhone[0].strip()).encode('utf-8')
	data.append(unicode(theaterPhone[0].strip()).encode('utf-8'))
	theaterPhoneText = unicode(theaterPhone[0].strip()).encode('utf-8') 	
	
	#update time stamp observation 
	time_stamp = p.xpath('.//div[@class=\'update\']/text()')

	time_stamp_text = unicode(time_stamp[0].strip()).encode('utf-8')
	if time_stamp:	
		dMsg(unicode(time_stamp[0].strip()).encode('utf-8'))
		data.append(unicode(time_stamp[0].strip()).encode('utf-8'))
 	else:
		dMsg('error, mo time stamp\n')
		return

	#db.AddTheater(sourceID, theaterName, theaterAddress, theaterPhone, ' ', ' ', ' ')
	db.AddTheater(sourceIDText, theaterNameText, theaterAddressText, theaterPhoneText, ' ', area_name, ' ', time_stamp_text)	


	#Get movie show/time/hall
	r = p.xpath('//div[@class=\'showtime01\']/descendant-or-self::*')
	
	Hallname_Text = None
	Moviename_text = None
	Time_txt = None


	for d in r:
		#Hallname_Text = None
		#Moviename_text = None
		#Time_txt = None

		titles = d.xpath('.//div[@class=\'row-1\']/a')

		if titles:
			for title in titles:
				#print unicode((title.text).strip()).encode('utf-8')
				data.append(unicode((title.text).strip()).encode('utf-8'))
				Moviename_text = unicode((title.text).strip()).encode('utf-8')
	
		Hall = d.xpath('.//div[@class=\'time\']//span//font/text()')

		if Hall and titles:
			#this is the Hallname
			#print unicode(Hall[0].strip()).encode('utf-8')
			Hallname = unicode(Hall[0].strip()).encode('utf-8')
 	
			if len(Hall) > 1:
				#this should be a description of hall(like "digital one"/"3D one" / "IMax one"
				#print unicode(Hall[1].strip()).encode('utf-8')
				Hallname = Hallname + ' ' + unicode(Hall[1].strip()).encode('utf-8')
 				
			data.append(Hallname)
			Hallname_Text = Hallname				

		times = d.xpath('.//div[@class=\'time\']//span//br/following-sibling::text() | .//div[@class=\'time\']//span/text()')

		if times and titles:
			#print 'time is \n'
			time_text = ' '

			for time in times:
				if time:
					time.lstrip()
					time.rstrip()
					time = time.replace('\n', '')
					time = time.replace('\r', '')
					time = time.replace('\t', '')
					time = time.strip()
					#print unicode(time).encode('utf-8')
					time_text += ' ' + unicode(time).encode('utf-8')
			Time_txt = time_text

			data.append(time_text)
	
		aryCheck = [sourceIDText, Hallname_Text, Moviename_text, Time_txt]
	
		if CheckContent(aryCheck):
			db.AddTheaterTime(sourceIDText, Hallname_Text, Moviename_text, Time_txt)

	return data

def CheckContent(contents):
	true_count = 0

	for text in contents:
		if text == None:
			continue
		if len(text) > 0:
			true_count = true_count + 1

	
	if true_count == len(contents):
		return True
	else:
		return False
