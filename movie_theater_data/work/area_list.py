#!/usr/bin/python
#-*-coding:utf-8-*-


#from urllib2 import urlopen

import time
import StringIO
from dmsg import dMsg, setDbgOn, setDbgOff


def arealist_data(strURL):
	
	area_url = []

	from lxml.html import tostring, parse, find_class
	import codecs
	from lxml import etree

	parser = etree.HTMLParser()
 
	p = parse(strURL, parser).getroot()

	#Get theater name
	urllist = p.xpath('//span[@class=\'at11\']/a')

	#use your own datasource, please fill host info here
	master_url = ''
 
	for u in urllist:
		urls = u.xpath('@href')
		name = u.xpath('text()')
		if urls:
			url = master_url + urls[0] 
			
			urlz = urls[0]
				
			url_temp = urlz.split('_')[1]
			
			urlkey = unicode(url_temp).encode('utf-8')

			url_tuple = (url, urlkey)
			
			area_url.append(url_tuple)


			dMsg(master_url + urls[0])
		else:
			print 'error no url'
			return
	

	return area_url
	
	
