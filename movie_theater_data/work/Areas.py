#!/usr/bin/python
#-*-coding:utf-8-*-


#from urllib2 import urlopen
from dmsg import dMsg, setDbgOn, setDbgOff

def getAddRess():
	import time
	import StringIO

	strURL = ''
	
	from lxml.html import tostring, parse, find_class
	import codecs
	
	from lxml import etree

	parser = etree.HTMLParser()
 
	p = parse(strURL, parser).getroot()

	#print p

	areas = p.xpath('/html/body/div/div[2]/div[2]/div[2]/map/area')

	Address = []

	for area in areas:
		areaNames = area.xpath('@alt')
		areaUrl = area.xpath('@href')
		
		count = 0

		for areaName in areaNames:
			dMsg(unicode(areaName.strip()).encode('utf-8'))
			dMsg(areaUrl)
			name = unicode(areaName.strip()).encode('utf-8')
			temp = [name, areaUrl[count]]
			Address.append(temp)
			count = count + 1

	return Address

#Test purpose only

#for name in Address:
#	print name[0]
#	print name[1]
		

